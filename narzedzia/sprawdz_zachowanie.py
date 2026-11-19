"""Niezależne, deterministyczne sprawdzenia zachowania gotowych przykładów."""

from collections import Counter, deque
from itertools import combinations, permutations, product
from math import isqrt
from pathlib import Path
import random
import subprocess
import sys


def _batch(cases):
    return str(len(cases)) + "\n" + "".join(text for text, _ in cases)


def _check_output(command, text, expected):
    result = subprocess.run(
        command, input=text, text=True, capture_output=True, timeout=10,
        check=True,
    )
    actual = result.stdout.split()
    wanted = str(expected).split()
    if actual != wanted:
        for index in range(max(len(actual), len(wanted))):
            got = actual[index] if index < len(actual) else "<brak>"
            want = wanted[index] if index < len(wanted) else "<brak>"
            if got != want:
                raise AssertionError(
                    f"token {index + 1}: oczekiwano {want}, otrzymano {got}; "
                    f"wejście={text[:260]!r}"
                )


def _array_case(values, expected):
    return f"{len(values)}\n" + " ".join(map(str, values)) + "\n", expected


def _digit_count(rng):
    cases = []
    for _ in range(100):
        left = rng.randint(1, 20000)
        right = left + rng.randint(0, 1000)
        expected = sum(sum(c != "0" for c in str(x)) <= 3
                       for x in range(left, right + 1))
        cases.append((f"{left} {right}\n", expected))
    return cases, True


def _digit_sum(rng):
    cases = []
    for _ in range(65):
        left = rng.randint(1, 1000)
        right = left + rng.randint(0, 400)
        k = rng.randint(1, 4)
        expected = sum(x for x in range(left, right + 1)
                       if len(set(str(x))) <= k) % 998244353
        cases.append((f"{left} {right} {k}\n", expected))
    return cases, False


def _deletion(rng):
    cases = []
    arrays = [[1], [3, 3], [1, 9, 1], [9, 1, 9, 1]]
    arrays += [[rng.randint(1, 100) for _ in range(rng.randint(2, 15))]
               for _ in range(110)]
    for a in arrays:
        costs = []
        for removed in range(len(a)):
            b = a[:removed] + a[removed + 1:]
            costs.append(sum(abs(x - y) for x, y in zip(b, b[1:])))
        cases.append(_array_case(a, min(costs)))
    return cases, True


def _modular_reach(rng):
    cases = []
    for length in range(1, 28):
        for _ in range(7):
            start = rng.randrange(length)
            step = rng.randint(1, 45)
            reached = set()
            value = start
            while value not in reached:
                reached.add(value)
                value = (value + step) % length
            cases.append((f"{length} {start} {step}\n", max(reached)))
    return cases, True


def _blocks(_rng):
    cases = []
    for n in range(1, 10):
        strings = ["".join(bits) for bits in product("01", repeat=n)]

        def signature(s):
            blocks = tuple(c for i, c in enumerate(s)
                           if i == 0 or c != s[i - 1])
            return s.count("0"), blocks

        counts = Counter(signature(s) for s in strings)
        for s in strings:
            cases.append((f"{n}\n{s}\n", counts[signature(s)]))
    return cases, True


def _square_prefixes(rng):
    cases = []
    arrays = [[1], [1] * 8, [2, 8, 18, 3, 12], [999983, 999983]]
    arrays += [[rng.randint(1, 45) for _ in range(rng.randint(1, 10))]
               for _ in range(100)]
    for a in arrays:
        prefix = 1
        expected = 0
        for value in a:
            prefix *= value
            for other in a:
                number = prefix * other
                expected += isqrt(number) ** 2 == number
        cases.append(_array_case(a, expected))
    return cases, True


def _active_intervals(rng):
    cases = []
    for _ in range(100):
        n = rng.randint(1, 28)
        intervals = []
        for _ in range(rng.randint(1, 25)):
            left = rng.randint(1, n)
            intervals.append((left, rng.randint(left, n)))
        expected = []
        for i in range(1, n + 1):
            total = 0
            for left, right in intervals:
                if left <= i <= right:
                    x = i - left + 1
                    total += x * (x & -x)
            expected.append(total)
        text = f"{n} {len(intervals)}\n"
        text += "".join(f"{left} {right}\n" for left, right in intervals)
        cases.append((text, " ".join(map(str, expected))))
    return cases, True


def _connected_graph(rng, n):
    edges = {(rng.randrange(v), v) for v in range(1, n)}
    for u, v in combinations(range(n), 2):
        if rng.random() < 0.25:
            edges.add((u, v))
    return sorted(edges)


def _parity_walks(rng):
    cases = []
    for _ in range(95):
        n = rng.randint(2, 7)
        edges = _connected_graph(rng, n)
        lengths = [rng.randint(1, 6) for _ in range(rng.randint(1, 5))]
        subset_sums = {0}
        for value in lengths:
            subset_sums |= {old + value for old in subset_sums}
        adjacency = [set() for _ in range(n)]
        for u, v in edges:
            adjacency[u].add(v)
            adjacency[v].add(u)
        reached = set()
        at_length = {0}
        for distance in range(max(subset_sums) + 1):
            if distance in subset_sums:
                reached |= at_length
            at_length = {v for u in at_length for v in adjacency[u]}
        expected = "".join("1" if v in reached else "0" for v in range(n))
        text = f"{n} {len(edges)} {len(lengths)}\n"
        text += " ".join(map(str, lengths)) + "\n"
        text += "".join(f"{u + 1} {v + 1}\n" for u, v in edges)
        cases.append((text, expected))
    return cases, True


def _simple_path_masks(n, edges):
    adjacency = [[] for _ in range(n)]
    for u, v in edges:
        adjacency[u].append(v)
        adjacency[v].append(u)
    pairs = []
    for start, end in combinations(range(n), 2):
        masks = set()

        def visit(u, mask):
            if u == end:
                masks.add(mask)
                return
            for v in adjacency[u]:
                if not mask & (1 << v):
                    visit(v, mask | (1 << v))

        visit(start, 1 << start)
        pairs.append(masks)
    return pairs


def _balanced_graphs(rng):
    cases = []
    graphs = [
        (3, [(0, 1), (1, 2), (0, 2)]),
        (4, [(0, 1), (1, 2), (2, 3), (0, 3)]),
        (5, [(0, 1), (1, 2), (0, 2), (2, 3), (3, 4)]),
    ]
    graphs += [(n, _connected_graph(rng, n))
               for n in (rng.randint(2, 6) for _ in range(45))]
    for number, (n, edges) in enumerate(graphs):
        limit = rng.randint(1, 3)
        a = [-1 if rng.random() < 0.7 else rng.randrange(limit)
             for _ in range(n)]
        if number < 3:
            limit, a = 3, [-1] * n
        paths = _simple_path_masks(n, edges)
        missing = [i for i, value in enumerate(a) if value == -1]
        expected = 0
        for assignment in product(range(limit), repeat=len(missing)):
            values = a.copy()
            for index, value in zip(missing, assignment):
                values[index] = value
            xor_by_mask = [0] * (1 << n)
            for mask in range(1, 1 << n):
                low = mask & -mask
                xor_by_mask[mask] = (xor_by_mask[mask ^ low]
                                     ^ values[low.bit_length() - 1])
            expected += all(len({xor_by_mask[mask] for mask in pair}) == 1
                            for pair in paths)
        text = f"{n} {len(edges)} {limit}\n"
        text += " ".join(map(str, a)) + "\n"
        text += "".join(f"{u + 1} {v + 1}\n" for u, v in edges)
        cases.append((text, expected))
    return cases, True


def _nearest_digits(rng):
    cases = []
    for _ in range(110):
        a = rng.randint(1, 1000)
        digits = sorted(rng.sample(range(10), rng.randint(1, 6)))
        allowed = set(map(str, digits))
        expected = min(abs(a - number) for number in range(20000)
                       if set(str(number)) <= allowed)
        cases.append((f"{a} {len(digits)}\n"
                      + " ".join(map(str, digits)) + "\n", expected))
    for a, digits, expected in [
        (10**17, [0], 10**17),
        (10**17, [1], 11111111111111111),
        (10**17, [9], 1),
        (10**17, [0, 1], 0),
        (10**17 - 1, [0, 1], 1),
    ]:
        cases.append((f"{a} {len(digits)}\n"
                      + " ".join(map(str, digits)) + "\n", expected))
    return cases, True


def _removed_good_array(rng):
    cases = []
    for _ in range(130):
        n, k = rng.randint(2, 15), rng.randint(1, 8)
        a = [rng.randint(1, 8)]
        for _ in range(n - 1):
            a.append(a[-1] + rng.randint(0, k))
        expected = []
        for removed in range(n):
            original = a[:removed] + a[removed + 1:]
            changed = original.copy()
            for i in range(1, len(changed)):
                changed[i] = min(original[i], changed[i - 1] + k)
            expected.append(sum(x - y for x, y in zip(original, changed)))
        text = f"{n} {k}\n" + " ".join(map(str, a)) + "\n"
        cases.append((text, " ".join(map(str, expected))))
    return cases, True


def _mex_brute(initial):
    first = tuple(sorted(initial))
    queue = deque([first])
    seen = {first}
    maximum = max(first)
    while queue:
        state = queue.popleft()
        for mask in range(1, 1 << len(state)):
            chosen = {value for i, value in enumerate(state) if mask >> i & 1}
            mex = 0
            while mex in chosen:
                mex += 1
            maximum = max(maximum, mex)
            following = tuple(sorted(
                [value for i, value in enumerate(state) if not mask >> i & 1]
                + [mex]
            ))
            if following not in seen:
                seen.add(following)
                queue.append(following)
    return maximum


def _mex_replacement(rng):
    cases = []
    for _ in range(45):
        values = [rng.randint(0, 6) for _ in range(rng.randint(1, 5))]
        counts = sorted(Counter(values).items())
        text = f"{len(counts)}\n"
        text += "".join(f"{value} {count}\n" for value, count in counts)
        cases.append((text, _mex_brute(values)))
    official = [
        ([(2, 2), (0, 3), (4, 1), (1, 2)], 5),
        ([(10, 1)], 10), ([(2, 3)], 3),
        ([(0, 1), (2, 2), (3, 1)], 4),
        ([(0, 4), (1, 2), (2, 1)], 4), ([(0, 100)], 7),
        ([(2, 7), (3, 1)], 4), ([(0, 1), (3, 3)], 3),
        ([(0, 1), (1, 1), (59, 1)], 59),
        ([(0, 5), (1, 1), (2, 3), (3, 1)], 5),
    ]
    for counts, expected in official:
        text = f"{len(counts)}\n"
        text += "".join(f"{value} {count}\n" for value, count in counts)
        cases.append((text, expected))
    return cases, True


def _disjoint_triples(rng):
    cases = []
    arrays = [[1] * n for n in range(5, 16)]
    arrays += [[rng.randint(1, 15) for _ in range(rng.randint(5, 17))]
               for _ in range(120)]
    for a in arrays:
        triples = [(i, i + 2, i + 4) for i in range(len(a) - 4)]
        expected = 0
        for first, second in combinations(triples, 2):
            if set(first).isdisjoint(second):
                expected += (a[first[0]] + a[first[1]] - a[first[2]]
                             == a[second[0]] + a[second[1]] - a[second[2]])
        cases.append(_array_case(a, expected))
    return cases, True


def _anagrams(_rng):
    return [
        ("ABC\nDEF\nFEDCBA\n", "YES"),
        ("AAA\nB\nABAA\n", "YES"),
        ("AAA\nB\nAABB\n", "NO"),
        ("A\nA\nAAA\n", "NO"),
    ], False


def _median_distance(rng):
    cases = []
    for _ in range(40):
        positions = [rng.randint(1, 30) for _ in range(3)]
        expected = min(sum(abs(x - meeting) for x in positions)
                       for meeting in range(1, 31))
        cases.append((" ".join(map(str, positions)) + "\n", expected))
    return cases, False


def _cyclic_days(rng):
    cases = []
    for _ in range(120):
        target = rng.randint(1, 1000)
        steps = [rng.randint(1, 40) for _ in range(3)]
        distance = days = 0
        while distance < target:
            distance += steps[days % 3]
            days += 1
        cases.append((f"{target} {' '.join(map(str, steps))}\n", days))
    return cases, True


def _bracket_subsequences(_rng):
    cases = []
    for n in range(1, 9):
        for symbols in product("()", repeat=n):
            text = "".join(symbols)
            expected = 0
            for mask in range(1 << n):
                subsequence = [symbols[i] for i in range(n) if mask >> i & 1]
                balance = 0
                valid = True
                for symbol in subsequence:
                    balance += 1 if symbol == "(" else -1
                    if balance < 0:
                        valid = False
                        break
                if not valid or balance != 0:
                    continue
                contains_pattern = any(
                    subsequence[i] == ")" and subsequence[j] == "("
                    and subsequence[k] == "("
                    for i, j, k in combinations(range(len(subsequence)), 3)
                )
                if contains_pattern:
                    expected += len(subsequence) - 2
            cases.append((f"{n}\n{text}\n", expected % 998244353))
    return cases, True


def _has_subsequence(text, pattern):
    position = 0
    for symbol in text:
        if symbol == pattern[position]:
            position += 1
            if position == len(pattern):
                return True
    return False


def _good_covering_substrings(rng):
    strings = ["0", "2025", "2026", "20252026", "20262025",
               "2200225566", "202520252026", "555555555555"]
    strings += ["".join(rng.choice("012256")
                        for _ in range(rng.randint(1, 12)))
                for _ in range(130)]
    cases = []
    for text in strings:
        expected = [0] * len(text)
        for left in range(len(text)):
            for right in range(left + 1, len(text) + 1):
                fragment = text[left:right]
                good = (not _has_subsequence(fragment, "2025")
                        or _has_subsequence(fragment, "2026"))
                if good:
                    for position in range(left, right):
                        expected[position] += 1
        cases.append((f"{len(text)}\n{text}\n",
                      " ".join(map(str, expected))))
    return cases, True


def _minimum_xor_swap_limit(values):
    n = len(values)
    target = sorted(values)
    maximum = max(i ^ j for i in range(n) for j in range(n))
    for limit in range(maximum + 1):
        unseen = set(range(n))
        possible = True
        while unseen:
            start = unseen.pop()
            component = {start}
            queue = deque([start])
            while queue:
                u = queue.popleft()
                neighbors = {v for v in unseen if (u ^ v) <= limit}
                unseen -= neighbors
                component |= neighbors
                queue.extend(neighbors)
            if sorted(values[i] for i in component) != sorted(
                    target[i] for i in component):
                possible = False
                break
        if possible:
            return limit
    raise AssertionError("Pełny graf powinien pozwalać posortować tablicę")


def _xor_index_updates(rng):
    arrays = [[1], [2, 1], [1, 1, 1], [4, 3, 2, 1],
              [8, 7, 6, 5, 4, 3, 2, 1]]
    arrays += [[rng.randint(1, 12) for _ in range(rng.randint(1, 8))]
               for _ in range(110)]
    cases = []
    for initial in arrays:
        values = initial.copy()
        updates = [(rng.randrange(len(values)), rng.randint(1, 12))
                   for _ in range(rng.randint(1, 9))]
        expected = [_minimum_xor_swap_limit(values)]
        for position, value in updates:
            values[position] = value
            expected.append(_minimum_xor_swap_limit(values))
        text = f"{len(initial)} {len(updates)}\n"
        text += " ".join(map(str, initial)) + "\n"
        text += "".join(f"{position} {value}\n" for position, value in updates)
        cases.append((text, " ".join(map(str, expected))))
    return cases, True


def _count_bank_arrangements(n, edges):
    expected = 0
    for mask in range(1, (1 << n) - 1):
        if any(((mask >> u) & 1) == ((mask >> v) & 1)
               for u, v in edges):
            continue
        left = [i for i in range(n) if mask >> i & 1]
        right = [i for i in range(n) if not mask >> i & 1]
        oriented = [(u, v) if mask >> u & 1 else (v, u) for u, v in edges]
        for left_order in permutations(left):
            left_position = {v: i for i, v in enumerate(left_order)}
            for right_order in permutations(right):
                right_position = {v: i for i, v in enumerate(right_order)}
                crossing = any(
                    u != x and v != y
                    and ((left_position[u] - left_position[x])
                         * (right_position[v] - right_position[y]) < 0)
                    for (u, v), (x, y) in combinations(oriented, 2)
                )
                expected += not crossing
    return expected


def _two_banks(rng):
    graphs = []
    for n in range(2, 7):
        graphs.append((n, [(0, v) for v in range(1, n)]))
        graphs.append((n, [(v - 1, v) for v in range(1, n)]))
        if n >= 3:
            graphs.append((n, [(v, v + 1) for v in range(n - 1)]
                           + [(0, n - 1)]))
    graphs += [(n, _connected_graph(rng, n))
               for n in (rng.randint(2, 6) for _ in range(80))]
    cases = []
    for n, edges in graphs:
        text = f"{n} {len(edges)}\n"
        text += "".join(f"{u + 1} {v + 1}\n" for u, v in edges)
        cases.append((text, _count_bank_arrangements(n, edges)))
    return cases, True


CHECKS = (
    ("DP cyfr: liczba niezerowych cyfr", "1036/dp/1036C.cc", _digit_count),
    ("DP cyfr: suma przy limicie różnych cyfr", "1073/dp/1073E.cc", _digit_sum),
    ("Usunięcie elementu i lokalne krawędzie", "2179/implementation/2179B.cc", _deletion),
    ("Osiągalne reszty modulo", "2180/implementation/2180A.cc", _modular_reach),
    ("Zliczanie rozkładów długości bloków", "2256/math/2256D.cc", _blocks),
    ("Kwadraty iloczynu prefiksu i elementu", "2275/math/2275F.cc", _square_prefixes),
    ("Aktywne przedziały i x*lowbit(x)", "2179/implementation/2179H.cc", _active_intervals),
    ("Dokładne spacery i sumy podzbiorów", "2109/graph/2109D.cc", _parity_walks),
    ("Wszystkie proste ścieżki i XOR", "2135/graph/2135C.cc", _balanced_graphs),
    ("Najbliższa liczba z dozwolonych cyfr", "2228/dp/2228C2.cc", _nearest_digits),
    ("Usuwanie indeksu z dobrej tablicy", "2259/suffixPrefix_sum/2259G.cc", _removed_good_array),
    ("Zastępowanie kolekcji jej MEX-em", "2266/binary_search/2266F.cc", _mex_replacement),
    ("Rozłączne trójki o równym kluczu", "2275/dataStructures/2275C.cc", _disjoint_triples),
    ("Anagramy z krotnościami", "141/sorting/141A.py", _anagrams),
    ("Odległość do mediany", "723/sorting/723A.py", _median_distance),
    ("Pierwszy dzień cyklicznego marszu", "2051/binary_search/2051B.py", _cyclic_days),
    ("Poprawne podciągi nawiasowe z wzorcem", "2190/dp/2190B2.cc", _bracket_subsequences),
    ("Dobre podnapisy pokrywające pozycję", "2276/math/2276E.cc", _good_covering_substrings),
    ("Sortowanie przez XOR indeksów po aktualizacji", "2247/segmenttree/2247D.cc", _xor_index_updates),
    ("Rozmieszczenia na dwóch brzegach bez przecięć", "2127/graph/2127D.cc", _two_banks),
)


def run_behavior_checks(catalog, binaries, root):
    """Sprawdź 20 wskazanych przykładów; brak pliku lub binarki jest błędem."""
    records = {record["source"]: record for record in catalog["records"]}
    root = Path(root)
    reports = []
    for number, (name, source, make_cases) in enumerate(CHECKS):
        report = dict(name=name, source=source, cases=0, status="failed", details="")
        try:
            if source not in records:
                raise KeyError(f"Brak oczekiwanego źródła w katalogu: {source}")
            examples = records[source]["examples"]
            if not examples:
                raise ValueError(f"Brak wybranego przykładu dla {source}")
            destination = examples[0]["destination"]
            if destination.endswith(".py"):
                path = root / destination
                if not path.is_file():
                    raise FileNotFoundError(f"Brak przykładu {destination}")
                command = [sys.executable, str(path)]
            else:
                if destination not in binaries:
                    raise KeyError(f"Brak skompilowanego przykładu {destination}")
                path = Path(binaries[destination])
                if not path.is_file():
                    raise FileNotFoundError(f"Brak pliku wykonywalnego {destination}")
                command = [str(path)]
            cases, batched = make_cases(random.Random(20261119 + number))
            report["cases"] = len(cases)
            if batched:
                expected = "\n".join(str(answer) for _, answer in cases)
                _check_output(command, _batch(cases), expected)
            else:
                for index, (text, expected) in enumerate(cases, 1):
                    try:
                        _check_output(command, text, expected)
                    except Exception as error:
                        raise AssertionError(f"przypadek {index}: {error}") from error
            report.update(status="passed", details="Wyniki zgodne z niezależnym oracle.")
        except subprocess.TimeoutExpired:
            report["details"] = "Przekroczono limit 10 s wykonania przykładu."
        except subprocess.CalledProcessError as error:
            report["details"] = (f"Kod wyjścia {error.returncode}; "
                                 f"stderr={error.stderr[:300]!r}")
        except Exception as error:
            report["details"] = f"{type(error).__name__}: {error}"
        reports.append(report)
    return reports
