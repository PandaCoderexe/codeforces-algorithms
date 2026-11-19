#!/usr/bin/env python3
"""Odtwórz przykłady z katalogu i lokalnego zbioru źródeł."""
import argparse
import hashlib
import json
import os
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SECTIONS = (
    ('goal', 'Co oblicza kod'),
    ('idea', 'Pomysł'),
    ('invariant', 'Stan i niezmiennik'),
    ('complexity', 'Złożoność'),
    ('edge_cases', 'Przypadki brzegowe'),
    ('recognition', 'Kiedy rozpoznać ten wariant'),
)


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def load_catalog():
    catalog = json.loads((ROOT / 'katalog.json').read_text(encoding='utf-8'))
    destinations = set()
    sources = set()
    for record in catalog['records']:
        source = Path(record['source'])
        if source.is_absolute() or '..' in source.parts or 'new_contest' in source.parts:
            raise ValueError(f'Niedozwolona ścieżka źródła {source}')
        if record['source'] in sources:
            raise ValueError(f'Powtórzone źródło {source}')
        sources.add(record['source'])
        for example in record['examples']:
            destination = Path(example['destination'])
            if (destination.is_absolute() or '..' in destination.parts
                    or 'new_contest' in destination.parts
                    or destination.suffix not in {'.cc', '.py'}):
                raise ValueError(f'Niedozwolona ścieżka wyniku {destination}')
            if example['destination'] in destinations:
                raise ValueError(f'Powtórzona nazwa {destination}')
            destinations.add(example['destination'])
            for key, _ in SECTIONS:
                if not example.get(key):
                    raise ValueError(f'Brak pola {key} w {destination}')
    return catalog


def render_header(record, example):
    prefix = '# ' if example['destination'].endswith('.py') else '// '
    lines = [example['title'], '', f'Oryginał w zbiorze codeforces/{record["source"]}']
    if record.get('official_url'):
        lines.append(record['official_url'])
    if example.get('source_ranges'):
        lines.append('Samodzielny fragment szablonu. Brak funkcji main jest zamierzony.')
    lines.append('')
    for key, heading in SECTIONS:
        lines.extend([heading, ''])
        value = example[key]
        if isinstance(value, list):
            lines.extend('- ' + str(item) for item in value)
        else:
            lines.extend(str(value).splitlines())
        lines.append('')
    warnings = list(dict.fromkeys(record.get('warnings', []) + example.get('warnings', [])))
    if warnings:
        lines.extend(['Warunki i uwagi', ''])
        lines.extend('- ' + warning for warning in warnings)
        lines.append('')
    if example.get('patches'):
        lines.extend(['Zmiany kopii względem oryginału', ''])
        lines.extend('- ' + patch['reason'] for patch in example['patches'])
        lines.append('')
    return ('\n'.join(prefix + line if line else prefix.rstrip() for line in lines)
            + '\n' + prefix + 'KONIEC OPISU\n').encode('utf-8')


def body_from_source(source_bytes, example):
    ranges = example.get('source_ranges')
    if ranges:
        lines = source_bytes.splitlines(keepends=True)
        body = b''
        for start, end in ranges:
            if not 1 <= start <= end <= len(lines):
                raise ValueError('Nieprawidłowy zakres fragmentu')
            body += b''.join(lines[start - 1:end])
    else:
        body = source_bytes
    for patch in example.get('patches', []):
        old = patch['old'].encode('utf-8')
        new = patch['new'].encode('utf-8')
        if body.count(old) != patch.get('count', 1):
            raise ValueError(f'Niejednoznaczna poprawka w {example["destination"]}')
        body = body.replace(old, new)
    return body


def read_example_body(path):
    marker = b'# KONIEC OPISU\n' if path.suffix == '.py' else b'// KONIEC OPISU\n'
    data = path.read_bytes()
    if marker not in data:
        raise ValueError(f'Brak końca opisu w {path.relative_to(ROOT)}')
    return data.split(marker, 1)[1]


def generate(source_root, check):
    catalog = load_catalog()
    actual_sources = set()
    for folder, directories, names in os.walk(source_root):
        directories[:] = [name for name in directories
                          if name != 'new_contest' and not name.startswith('.')]
        for name in names:
            path = Path(folder) / name
            if path.suffix in {'.cc', '.py'}:
                actual_sources.add(path.relative_to(source_root).as_posix())
    expected_sources = {record['source'] for record in catalog['records']}
    if actual_sources != expected_sources:
        missing = expected_sources - actual_sources
        unlisted = actual_sources - expected_sources
        raise ValueError(f'Niezgodny spis źródeł. Brak {missing}, nowe {unlisted}')
    count = 0
    for record in catalog['records']:
        source = source_root / record['source']
        if source.is_symlink() or not source.resolve().is_relative_to(source_root.resolve()):
            raise ValueError(f'Źródło wychodzi poza wskazany katalog {source}')
        source_bytes = source.read_bytes()
        if sha256(source_bytes) != record['source_sha256']:
            raise ValueError(f'Źródło zmieniło się od przeglądu {record["source"]}')
        for example in record['examples']:
            body = body_from_source(source_bytes, example)
            if sha256(body) != example['body_sha256']:
                raise ValueError(f'Niezgodny kod przykładu {example["destination"]}')
            expected = render_header(record, example) + body
            target = ROOT / example['destination']
            if not target.resolve().is_relative_to(ROOT.resolve()):
                raise ValueError(f'Wynik wychodzi poza repo {example["destination"]}')
            for component in (target, *target.parents):
                if component == ROOT:
                    break
                if component.is_symlink():
                    raise ValueError(f'Dowiązanie w ścieżce wyniku {example["destination"]}')
            if check:
                if not target.is_file() or target.read_bytes() != expected:
                    raise ValueError(f'Przykład wymaga odtworzenia {example["destination"]}')
            else:
                target.parent.mkdir(parents=True, exist_ok=True)
                if target.exists() and target.read_bytes() != expected:
                    if read_example_body(target) != body:
                        raise ValueError(f'Kopia ma własne zmiany kodu {example["destination"]}')
                target.write_bytes(expected)
            count += 1
    print(f'Zweryfikowano {count} przykładów i {len(catalog["records"])} źródeł.')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--source-root', required=True, type=Path,
                        help='Katalog codeforces z oryginalnymi rozwiązaniami')
    parser.add_argument('--check', action='store_true', help='Porównaj pliki bez zapisu')
    args = parser.parse_args()
    generate(args.source_root, args.check)


if __name__ == '__main__':
    main()
