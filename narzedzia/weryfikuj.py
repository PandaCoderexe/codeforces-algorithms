#!/usr/bin/env python3
"""Sprawdź strukturę, kompilację i niezależne próby zachowania przykładów."""
import argparse
from concurrent.futures import ThreadPoolExecutor
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile

from generuj import ROOT, generate, load_catalog, read_example_body, render_header, sha256


def check_metadata(catalog):
    expected = set()
    for record in catalog['records']:
        for example in record['examples']:
            relative = example['destination']
            expected.add(relative)
            path = ROOT / relative
            if path.is_symlink() or not path.resolve().is_relative_to(ROOT):
                raise ValueError(f'Przykład wychodzi poza repo {relative}')
            data = path.read_bytes()
            if not data.startswith(render_header(record, example)):
                raise ValueError(f'Niezgodny opis {relative}')
            if sha256(read_example_body(path)) != example['body_sha256']:
                raise ValueError(f'Niezgodna treść {relative}')
            if any(part.startswith('.') for part in Path(relative).parts):
                raise ValueError(f'Ukryta ścieżka wyniku {relative}')
    actual = set()
    for folder, dirs, files in os.walk(ROOT):
        dirs[:] = [d for d in dirs if not d.startswith('.') and d not in {'narzedzia', 'docs'}]
        for name in files:
            path = Path(folder) / name
            if path.suffix in {'.cc', '.py'}:
                actual.add(path.relative_to(ROOT).as_posix())
    if expected != actual:
        raise ValueError(f'Niezgodny zbiór przykładów. Brak {expected-actual}, nadmiar {actual-expected}')
    return expected


def compile_examples(catalog, compiler, build_dir, jobs):
    examples = [e for r in catalog['records'] for e in r['examples']]

    def compile_one(example):
        relative = example['destination']
        path = ROOT / relative
        binary = build_dir / sha256(relative.encode('utf-8'))[:16]
        if path.suffix == '.py':
            try:
                compile(path.read_bytes(), relative, 'exec')
                return {'file': relative, 'status': 'passed', 'kind': 'python'}, None
            except SyntaxError as error:
                return {'file': relative, 'status': 'failed', 'details': str(error)}, None
        command = [compiler, '-std=c++20', '-O1', '-fsanitize=undefined',
                   '-fno-sanitize-recover=all', '-I', str(ROOT / 'narzedzia/include'), str(path)]
        template = bool(example.get('source_ranges'))
        if template:
            command.append('-c')
        command += ['-o', str(binary)]
        try:
            result = subprocess.run(command, capture_output=True, text=True, timeout=90)
        except (OSError, subprocess.TimeoutExpired) as error:
            return {'file': relative, 'status': 'failed', 'details': str(error)}, None
        item = {'file': relative, 'kind': 'template' if template else 'cpp',
                'status': 'passed' if result.returncode == 0 else 'failed'}
        if result.returncode:
            item['details'] = result.stderr[-4000:]
        return item, None if template or result.returncode else binary

    checks = []
    binaries = {}
    with ThreadPoolExecutor(max_workers=jobs) as pool:
        for example, (result, binary) in zip(examples, pool.map(compile_one, examples)):
            checks.append(result)
            if binary is not None:
                binaries[example['destination']] = binary
    return checks, binaries


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--source-root', type=Path, help='Opcjonalne sprawdzenie niezmienionych oryginałów')
    parser.add_argument('--compiler', default=os.environ.get('CXX') or shutil.which('g++') or shutil.which('c++'))
    parser.add_argument('--jobs', type=int, default=4)
    parser.add_argument('--report', type=Path, default=ROOT / 'weryfikacja.json')
    parser.add_argument('--compile-only', action='store_true', help='Pomiń próby działania')
    args = parser.parse_args()
    if args.jobs < 1 or not args.compiler:
        parser.error('Wymagany kompilator C++ i dodatnia liczba jobs')
    catalog = load_catalog()
    expected = check_metadata(catalog)
    if args.source_root:
        generate(args.source_root, check=True)
    print(f'Metadane i hashe {len(expected)} przykładów zgodne.', flush=True)
    build_root = ROOT / '.build'
    build_root.mkdir(exist_ok=True)
    report = {'sources_reviewed': len(catalog['records']), 'examples': len(expected),
              'originals_checked': bool(args.source_root), 'compiler': Path(args.compiler).name,
              'standard': 'c++20', 'sanitizer': 'undefined, non-recovering',
              'compilation': [], 'behavior': [],
              'limitations': 'Kompilacja i wybrane próby zachowania nie są dowodem poprawności wszystkich rozwiązań. Status Accepted nie był sprawdzany.'}
    with tempfile.TemporaryDirectory(prefix='verify-', dir=build_root) as folder:
        checks, binaries = compile_examples(catalog, args.compiler, Path(folder), args.jobs)
        report['compilation'] = checks
        failures = [check for check in checks if check['status'] != 'passed']
        print(f'Kompilacja/składnia {len(checks)-len(failures)}/{len(checks)}.', flush=True)
        for check in failures:
            print(check['file'] + '\n' + check['details'], flush=True)
        if not args.compile_only and not failures:
            from sprawdz_zachowanie import run_behavior_checks
            from sprawdz_szablony import run_template_checks
            report['behavior'] = run_behavior_checks(catalog, binaries, ROOT)
            report['behavior'].extend(run_template_checks(catalog, ROOT, args.compiler, Path(folder)))
            for check in report['behavior']:
                print(f'{check["status"]} {check["name"]} ({check["cases"]})', flush=True)
                if check['status'] != 'passed':
                    print(check.get('details', ''), flush=True)
    successful = (all(c['status'] == 'passed' for c in report['compilation'])
                  and all(c['status'] == 'passed' for c in report['behavior']))
    report['status'] = 'passed' if successful else 'failed'
    report['behavior_executed'] = not args.compile_only and bool(report['behavior'])
    args.report.parent.mkdir(parents=True, exist_ok=True)
    args.report.write_text(json.dumps(report, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
    print(f'Raport {args.report.name}, wynik {report["status"]}.', flush=True)
    return 0 if successful else 1


if __name__ == '__main__':
    sys.exit(main())
