"""Sprawdzenia dwóch regresji znalezionych przy przeglądzie generatora."""
import contextlib
import io
import json
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

import generuj


class GeneratorBoundaries(unittest.TestCase):
    def setUp(self):
        build = generuj.ROOT / '.build'
        build.mkdir(exist_ok=True)
        self.temp = tempfile.TemporaryDirectory(dir=build)
        self.addCleanup(self.temp.cleanup)
        base = Path(self.temp.name)
        self.source = base / 'source'
        self.output = base / 'output'
        self.source.mkdir()
        self.output.mkdir()
        self.body = b'int main() {return 0;}\n'
        (self.source / 'program.cc').write_bytes(self.body)
        self.example = {key: 'Opis' for key, _ in generuj.SECTIONS}
        self.example.update(destination='algorytmy/przyklad.cc', title='Przykład',
                            body_sha256=generuj.sha256(self.body))
        self.record = dict(source='program.cc', source_sha256=generuj.sha256(self.body),
                           examples=[self.example], warnings=[])
        self.catalog = {'records': [self.record]}
        (self.output / 'katalog.json').write_text(json.dumps(self.catalog))
        self.root_patch = patch.object(generuj, 'ROOT', self.output)
        self.root_patch.start()
        self.addCleanup(self.root_patch.stop)

    def generate(self):
        with contextlib.redirect_stdout(io.StringIO()):
            generuj.generate(self.source, check=False)

    def test_rejects_unlisted_source(self):
        (self.source / 'nowe.cc').write_text('int other;')
        with self.assertRaises(ValueError):
            self.generate()

    def test_excludes_new_contest_from_inventory(self):
        folder = self.source / 'new_contest'
        folder.mkdir()
        (folder / 'nowe.cc').write_text('int other;')
        self.generate()
        self.assertTrue((self.output / self.example['destination']).is_file())

    def test_rejects_symlinked_output_directory(self):
        outside = self.output.parent / 'outside'
        outside.mkdir()
        (self.output / 'algorytmy').symlink_to(outside, target_is_directory=True)
        with self.assertRaises(ValueError):
            self.generate()
        self.assertFalse((outside / 'przyklad.cc').exists())

    def test_second_run_produces_identical_file(self):
        self.generate()
        expected = (self.output / self.example['destination']).read_bytes()
        self.generate()
        self.assertEqual((self.output / self.example['destination']).read_bytes(), expected)


if __name__ == '__main__':
    unittest.main()
