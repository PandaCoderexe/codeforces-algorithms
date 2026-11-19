#!/usr/bin/env python3
"""Buduje przewodnik zastosowań na podstawie istniejącego katalogu przykładów."""
import argparse
from collections import defaultdict
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
GROUPS = {
    'drogi': ('Chcę sprawdzić osiągalność lub znaleźć drogę', 'BFS wybierz przy jednakowym koszcie każdego ruchu. DFS wystarczy do sprawdzenia osiągalności. Jeśli przyszłe ruchy zależą od kierunku, czasu lub parzystości, dodaj te informacje do stanu. Porządek topologiczny pozwala przetwarzać zależności w DAG.'),
    'drzewa': ('Chcę policzyć wynik na drzewie', 'Wynik zależny od dzieci sugeruje DP od liści. Wynik dla różnych korzeni sugeruje rerooting. Plecak warstw służy do wyboru grup określonego rozmiaru. Własności stopni i kształtu drzewa mogą uprościć problem do rozpoznania struktury.'),
    'przedzialy': ('Chcę szybko obsługiwać przedziały i zmiany wartości', 'Dla stałych danych rozważ sumy prefiksowe. Dodawanie do wielu zakresów przed jednym odczytem pasuje do tablicy różnicowej. Zmiany przeplatane z pytaniami sugerują Fenwicka lub segment tree. Wybierz wariant zgodny z rodzajem aktualizacji i pytania.'),
    'zliczanie': ('Chcę policzyć sposoby, podzbiory lub podprzedziały', 'Najpierw określ, co wyróżnia dwa różne rozwiązania. DP zliczające sumuje liczby przejść, a kombinatoryka zastępuje je wzorem. Gdy potrzebujesz też sumy długości albo wartości, przechowuj obok liczności dodatkowy agregat.'),
    'liczby': ('Chcę szukać liczb spełniających warunki na cyfrach', 'Digit DP buduje liczbę po cyfrze. tight ogranicza prefiks górną granicą, started rozróżnia zera wiodące, a maska zapamiętuje użyte cyfry. Stan i agregat dobierz do celu zliczania, sumowania lub szukania najbliższej liczby.'),
    'napisy': ('Chcę porównywać napisy, dopasować wzorzec lub zmieniać znaki', 'Równość multizbiorów znaków sprawdzisz przez częstości albo sortowanie. Podciąg zachowuje kolejność i może pomijać znaki, a podnapis jest spójnym fragmentem. Automat zapamiętuje postęp dopasowania lub ograniczenia zmian.'),
    'bity': ('Chcę sterować XOR-em, bitami lub parzystością', 'Rozdziel operacje na wartościach od operacji na indeksach. Maska opisuje zbiór bitów, trie porównuje liczby od najwyższego bitu, a DP z przeniesieniem obsługuje zależności między sąsiednimi pozycjami bitowymi.'),
    'minimum': ('Chcę znaleźć minimum lub maksimum przez podział na stany', 'Zapisz znaczenie dp i wszystkie decyzje prowadzące do stanu. Wybierz minimum dla kosztu i maksimum dla zysku. Dla podziału na bloki stanem bywa długość prefiksu, a dla budżetu dodatkowa wykorzystana suma. Oddziel koszt przejścia od kolejności przetwarzania.'),
    'prog': ('Chcę znaleźć największy możliwy lub najmniejszy wystarczający próg', 'Binary search po odpowiedzi wymaga monotonicznego testu wykonalności. Uzasadnij, w którą stronę zmienia się odpowiedź testu. Całkowity koszt to liczba prób pomnożona przez koszt checkera. lower_bound służy także do znalezienia sąsiada w uporządkowanych danych.'),
    'kolejnosc': ('Chcę uporządkować dane lub wykorzystać ich kolejność', 'Sortowanie może ujawnić sąsiednie wartości, grupy i pary skrajnych elementów. Stos monotoniczny pomaga utrzymywać kandydatów na ekstrema. Przed sortowaniem sprawdź, czy wolno zmienić kolejność danych i czy trzeba zachować oryginalne indeksy.'),
    'konstrukcja': ('Chcę odtworzyć rozwiązanie lub zbudować poprawny obiekt', 'Samo istnienie rozwiązania nie wystarcza do jego wypisania. Zapamiętaj poprzednika w DP albo utrzymuj niezmiennik, który pozwala dobierać kolejne elementy. W konstrukcjach sprawdź też liczbę wypisanych elementów, powtórzenia i legalność każdej operacji.'),
    'zachlanne': ('Chcę wybierać zasoby, terminy lub pary', 'Zachłanność wymaga uzasadnienia lokalnego wyboru. Szukaj argumentu wymiany, zachowania największej rezerwy dla przyszłych decyzji albo szczególnej własności danych. W przykładach warunki dotyczą m.in. nominałów, progów i kolejności zasobów.'),
    'arytmetyka': ('Chcę uprościć obliczenia przez NWD, dzielniki lub wzór', 'NWD opisuje klasy osiągalnych reszt. Dzielniki rozpatruj parami do pierwiastka. Przy iloczynach będących kwadratami wystarczy parzystość wykładników pierwszych. Szukaj też teleskopowania i odcinków, na których wynik dzielenia jest stały.'),
    'czestosci': ('Chcę policzyć wystąpienia, pary lub brakującą wartość', 'Mała dziedzina wartości pasuje do tablicy częstości, a duża do mapy. Zbiór przechowuje obecność, zaś multiset także liczbę kopii. Przy liczeniu par sprawdź, czy elementy mogą się pokrywać i czy kolejność par ma znaczenie.'),
}
DEFAULT = {
    'grafy':'drogi', 'drzewa':'drzewa', 'dp':'minimum', 'sumy_prefiksowe':'przedzialy',
    'struktury_danych':'przedzialy', 'binary_search':'prog', 'bity':'bity', 'napisy':'napisy',
    'zachlanne':'zachlanne', 'matematyka':'arytmetyka', 'kombinatoryka':'zliczanie',
    'konstrukcje':'konstrukcja', 'rekurencja':'konstrukcja', 'sortowanie':'kolejnosc',
    'stos_monotoniczny':'kolejnosc', 'dwa_wskazniki':'kolejnosc', 'tablice':'przedzialy',
    'zbiory':'czestosci', 'zliczanie':'czestosci', 'bloki':'przedzialy',
    'ciagi':'przedzialy', 'gry':'bity', 'brute_force':'minimum',
}
# Doprecyzowania według rzeczywistego celu implementacji.
OVERRIDES = {
    'dp/digit_dp':'liczby',
    'dp/drzewo_':'drzewa',
    'dp/graf_acykliczny':'drogi',
    'dp/graf_wartosci':'zliczanie',
    'dp/kompresja_skladowych':'drogi',
    'dp/plecak_wazone':'zliczanie',
    'dp/zliczanie_':'zliczanie',
    'dp/okno_ostatniego':'zliczanie',
    'dp/nawiasy_':'napisy',
    'dp/lcs_':'napisy',
    'dp/automat_xor':'napisy',
    'dp/bity_':'bity',
    'dp/osiagalnosc_':'napisy',
    'struktury_danych/trie_':'bity',
    'struktury_danych/czestosci':'czestosci',
    'struktury_danych/zliczanie_par':'czestosci',
    'struktury_danych/stos':'napisy',
    'struktury_danych/kopiec':'zachlanne',
    'struktury_danych/segment_tree/minimum_maksimum':'bity',
    'brute_force/generowanie_liczb':'liczby',
    'tablice/normalizacja':'kolejnosc',
    'zachlanne/konstrukcja_bitowa':'bity',
    'zachlanne/leksykograficzne':'napisy',
}


def render():
    catalog = json.loads((ROOT/'katalog.json').read_text(encoding='utf-8'))
    grouped = defaultdict(list)
    sources = {}
    for record in catalog['records']:
        for example in record['examples']:
            path = example['destination']
            group = DEFAULT[path.split('/')[0]]
            for prefix, target in OVERRIDES.items():
                if path.startswith(prefix):
                    group = target
            if not (ROOT/path).is_file():
                raise ValueError(f'Brak przykładu {path}')
            grouped[group].append(example)
            sources.setdefault(record['source'], example)
    count = sum(map(len, grouped.values()))
    text = f'# Co chcę osiągnąć?\n\nPrzewodnik obejmuje wszystkie {count} przykładów w repozytorium. Zacznij od celu, potem sprawdź warunki metody i nagłówek konkretnego pliku. Przykłady realizują konkretne modele zadań. Warunki wejścia są częścią ich zastosowania.\n\n'
    for key, (title, _) in GROUPS.items():
        text += f'- [{title}](#{key})\n'
    text += '- [Chcę przyspieszyć rozwiązanie lub zmniejszyć pamięć](#optymalizacja)\n\n'
    for key, (title, hint) in GROUPS.items():
        text += f'<a id="{key}"></a>\n\n## {title}\n\n{hint}\n\n'
        for example in sorted(grouped[key], key=lambda e:e['destination']):
            text += f'- [{example["title"]}]({example["destination"]}). {example["goal"]}\n'
        text += '\n'

    def example(source):
        e = sources[source]
        return f'[{e["title"]}]({e["destination"]})'

    text += '<a id="optymalizacja"></a>\n\n## Chcę przyspieszyć rozwiązanie lub zmniejszyć pamięć\n\n'
    improvements = [
        ('Wielokrotnie sumuję ten sam fragment tablicy', 'Dla niezmiennych danych przygotuj prefiksy w O(n). Sumę odcinka otrzymasz przez dwa odczyty i odejmowanie w O(1).', '2244/suffixPrefix_sum/2244D.cc'),
        ('Aktualizuję wartości i ponownie przeliczam sumy', 'Przy punktowym dodawaniu i sumach prefiksowych Fenwick daje O(log n) na operację. Przy dodawaniu do całego zakresu i sumach zakresów wybierz segment tree z lazy propagation.', 'tree/segTree.cc'),
        ('Każdy stan DP przegląda wszystkich poprzedników', 'Jeśli zbiór legalnych poprzedników jest prefiksem i można zaplanować moment ich aktywacji, Fenwick z maksimum zastąpi skan zapytaniem O(log n). Najpierw wyprowadź warunki legalności przejścia.', '2244/dp/2244G.cc'),
        ('DP zużywa pamięć na wszystkie wcześniejsze pozycje', 'Jeśli przejścia korzystają wyłącznie z dwóch poprzednich stanów i nie odtwarzasz ścieżki, możesz przechowywać tylko te stany. Przykład kafelkowania używa O(1) pamięci DP.', '2225/dp/2225C.cc'),
        ('Boolowski plecak jest zbyt wolny', 'Gdy chodzi o osiągalność sum, bitset wykonuje wiele przesunięć i operacji OR maszynowo. Wariant z powtarzalnymi wagami dodatkowo pakuje ich liczności binarnie. Sprawdź limit liczby bitów.', '2138/tree/2138C2.cc'),
        ('Trzymam wiele stanów, które niczego nie poprawiają', 'Stan o niegorszym wyniku i zawierającym zbiorze dalszych możliwości dominuje drugi. Można usunąć stan zdominowany. Samo usuwanie dominacji nie daje jeszcze gwarancji małej liczby stanów.', '2180/math/2180D.cc'),
        ('Osobno liczę wkład każdego początku i końca', 'Poszukaj odcinków ze stałym lub liniowym wkładem. Tablice różnicowe współczynnika i wyrazu wolnego pozwalają dodać funkcję liniową do przedziału i odczytać końcowe wyniki jednym skanem.', '2276/math/2276E.cc'),
        ('Powtarzam dzielenie dla ogromnej liczby kandydatów', 'Połącz zakresy argumentów o tym samym ilorazie i sumuj je zbiorczo. Zysk zależy od liczby różnych ilorazów i granic konkretnego zadania.', '2258/suffixPrefix_sum/2258B2.cc'),
        ('Po jednej zmianie przeliczam cały koszt', 'Wyodrębnij składniki dotknięte zmianą. Przy usunięciu elementu z sumy odległości znikają dwie sąsiednie różnice i pojawia się jedna nowa. Koszt kandydata policzysz w O(1) po przygotowaniu sumy.', '2179/implementation/2179B.cc'),
        ('Uruchamiam obliczenia osobno dla każdego korzenia drzewa', 'Rerooting przenosi wynik między sąsiednimi korzeniami. W tym przykładzie wszystkie odpowiedzi można zagregować w O(n), wykorzystując rozmiary poddrzew i wkład obu stron krawędzi.', '2167/tree/2167F.cc'),
    ]
    for title, hint, source in improvements:
        text += f'### {title}\n\n{hint}\n\nPrzykład {example(source)}.\n\n'
    text += 'Katalog według nazw technik znajduje się w [README](README.md#katalog-przykładów). Aby sprawdzić aktualność tego przewodnika, uruchom `python3 narzedzia/grupuj_zastosowania.py --check`.\n'
    return text


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    expected = render()
    target = ROOT/'ZASTOSOWANIA.md'
    if args.check:
        if not target.is_file() or target.read_text(encoding='utf-8') != expected:
            raise SystemExit('Przewodnik wymaga odtworzenia.')
        print('Przewodnik zastosowań zgodny z katalogiem.')
    else:
        target.write_text(expected, encoding='utf-8')
        print('Zapisano ZASTOSOWANIA.md.')


if __name__ == '__main__':
    main()
