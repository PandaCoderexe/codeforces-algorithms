# Codeforces algorithms

Biblioteka 158 przykładów algorytmów i ich wariantów, wybranych po przeczytaniu 284 lokalnych plików C++ i Python. Opisy są po polsku. Pliki `new_contest` są wyłączone z przeglądu.

Nazwy plików opisują zastosowaną metodę. Każdy przykład zaczyna się od celu obliczenia, pomysłu, stanu lub niezmiennika, złożoności i przypadków brzegowych. W komentarzu znajduje się też ścieżka oryginału i odnośnik do konkursu albo zadania.

## Znajdź algorytm według celu

Otwórz [Co chcę osiągnąć?](ZASTOSOWANIA.md). Przewodnik grupuje wszystkie 158 przykładów według zastosowań i wyjaśnia warunki wyboru metody.

- [Chcę znaleźć drogę lub sprawdzić osiągalność](ZASTOSOWANIA.md#drogi).
- [Chcę znaleźć minimum albo maksimum](ZASTOSOWANIA.md#minimum).
- [Chcę szybko obsługiwać przedziały i aktualizacje](ZASTOSOWANIA.md#przedzialy).
- [Chcę policzyć sposoby lub podzbiory](ZASTOSOWANIA.md#zliczanie).
- [Chcę rozwiązać problem na drzewie](ZASTOSOWANIA.md#drzewa).
- [Chcę znaleźć liczbę spełniającą warunki na cyfrach](ZASTOSOWANIA.md#liczby).
- [Chcę przyspieszyć kod albo zmniejszyć pamięć](ZASTOSOWANIA.md#optymalizacja).

## Od czego zacząć

Pozycje oznaczone **Start** pokazują podstawowe lub szczególnie reprezentatywne warianty. Najpierw przeczytaj nagłówek, potem prześledź stan na małym wejściu, a następnie sprawdź granice indeksów i warunki zadania.

- [Mediana minimalizuje sumę odległości](zachlanne/mediana/minimalizacja_sumy_odleglosci.py) pokazuje prostą zachłanność.
- [Liniowe minimum po dwóch poprzednich prefiksach](dp/dp_prefiksowe/minimalny_koszt_prefiksu_z_dwoma_poprzednikami.cc) przechowuje pełną tablicę jednowymiarowego DP.
- [DP kafelkowania 2xn z pamięcią stałą](dp/kafelki_dwa_wiersze/pokrycie_dwoch_wierszy_dominami_z_minimalnym_kosztem.cc) ogranicza pamięć DP do poprzednich stanów.
- [BFS minimalnej liczby skoków](grafy/bfs/najmniejsza_liczba_skokow.cc) pokazuje podstawowe BFS.
- [Bfs po parzystości długości](grafy/bfs_parzystosc/najkrotsze_marszruty_dwoch_parzystosci.cc) rozbudowuje wierzchołek o parzystość.
- [Mosty tarjana lowlink i składowe bez mostów](grafy/mosty_lowlink/mosty_i_dwudzielnosc_skladowych.cc) zawiera lowlink Tarjana do mostów.
- [Rerooting liczby dużych poddrzew](drzewa/rerooting/liczba_duzych_poddrzew.cc) przenosi wynik między korzeniami drzewa.

## Różne warianty digit DP

- [Digit DP. liczba niezerowych cyfr](dp/digit_dp/zliczanie_liczb_z_limitem_niezerowych_cyfr.cc) ma stan logiczny `(pos, non_zero, tight)`. Kod alokuje tablicę trójwymiarową, a zapamiętane wyniki przy `tight=false` zależą od dwóch parametrów. Trzeci indeks tablicy jest wtedy zawsze zerem.
- [Digit DP. maska cyfr, started i para count/sum](dp/digit_dp_maska_agregaty/suma_liczb_z_maska_uzytych_cyfr.cc) memoizuje `(pos, mask, started)` przy `tight=false`. Maska opisuje użyte cyfry, `started` odróżnia zera wiodące, a komórka przechowuje zarówno liczność, jak i sumę.
- [Digit DP najbliższej liczby z relacją mniejsza/równa/większa](dp/digit_dp_najblizsza_liczba/najblizsza_liczba_z_dozwolonych_cyfr.cc) używa dwuwymiarowego `dp[pos][relation]`. Trzy wartości `relation` opisują relację prefiksu do szukanej liczby. Wariant optymalizuje odległość zamiast zliczać rozwiązania.
- [Digit DP sum cyfr i wyszukiwanie pozycji w konkatenacji](dp/digit_dp_i_wyszukiwanie/suma_prefiksu_ciagu_cyfr_przez_bisekcje_i_digit_dp.cc) łączy sumowanie cyfr z wyszukiwaniem pozycji w ciągu zapisanych liczb.

## Uruchomienie i sprawdzenie

Wymagane są Python 3.9 lub nowszy oraz kompilator C++20 obsługujący UBSan, np. GCC albo Clang. Repo zawiera standardowe nagłówki zastępujące GNU `bits/stdc++.h` podczas weryfikacji z Clang.

```sh
python3 narzedzia/weryfikuj.py --compiler g++
python3 -m unittest discover -s narzedzia -p test_generowania.py
```

Weryfikator sprawdza opisy, nazwy i hashe kodu. Kompiluje każdy przykład C++, sprawdza składnię Pythona i uruchamia niezależne porównania z brute force dla wybranych metod. Szablony struktur danych są porównywane z naiwną tablicą. UBSan przerywa wykonanie przy wykrytym niezdefiniowanym zachowaniu.

Aktualny wynik zawiera [raport weryfikacji](weryfikacja.json). Raport rozróżnia wszystkie skompilowane pliki i przykłady z testami wyników. Testy dotyczą opisanych przypadków i dziedzin. Status Accepted na Codeforces nie był sprawdzany.

Aby potwierdzić zgodność z własnym katalogiem oryginałów, podaj jego ścieżkę.

```sh
python3 narzedzia/generuj.py --source-root /sciezka/do/codeforces --check
python3 narzedzia/weryfikuj.py --source-root /sciezka/do/codeforces --compiler g++
```

Generator porównuje pełny spis źródeł z rejestrem, pomija `new_contest` i odrzuca zmienione oryginały. Ponowne generowanie zachowuje treść kodu. Opisane poprawki kopii oraz zakresy wydzielonych fragmentów są zapisane w rejestrze.

## Rejestr pochodzenia i wyboru

[katalog.json](katalog.json) zawiera osobny wpis dla każdego przejrzanego pliku, jego sumę kontrolną, klasyfikację, ocenę i ścieżki przykładów. Wpisy obejmują także szkice, powtórzenia i rozwiązania interaktywne, które pozostały poza kolekcją. Oryginalne pliki są zachowane. Numery zadań można odszukać w komentarzach i rejestrze.

Część plików udostępnia samą strukturę lub funkcję do dołączenia do programu. Wymagania wejścia i granice stosowania każdego wariantu są opisane w jego nagłówku. Przy ogólnych strukturach ważna jest m.in. różnica między dodaniem wartości a przypisaniem.

## Katalog przykładów

### Programowanie dynamiczne

- [Amortyzowane DP grup stanów w mapie](dp/amortyzowane_grupowanie_mapa/agregacja_stanow_koncowych_przez_scalanie_mapy.cc)
- [Automat czterech stanów z kosztem zmian](dp/automat_xor/minimalne_poprawki_dwoch_napisow_dla_xor_prefiksowego.cc)
- [Bitowe DP relacji porządku i odległości L1](dp/bity_porownania_i_norma_l1/najblizsza_para_z_rozlacznymi_bitami.cc)
- [DP bitowe od najmłodszych bitów](dp/bity_przeniesienie/bitowe_dp_dodawania_z_przeniesieniem.cc)
- **Start** [Digit DP. liczba niezerowych cyfr](dp/digit_dp/zliczanie_liczb_z_limitem_niezerowych_cyfr.cc)
- [Digit DP sum cyfr i wyszukiwanie pozycji w konkatenacji](dp/digit_dp_i_wyszukiwanie/suma_prefiksu_ciagu_cyfr_przez_bisekcje_i_digit_dp.cc)
- **Start** [Digit DP. maska cyfr, started i para count/sum](dp/digit_dp_maska_agregaty/suma_liczb_z_maska_uzytych_cyfr.cc)
- [Digit DP najbliższej liczby z relacją mniejsza/równa/większa](dp/digit_dp_najblizsza_liczba/najblizsza_liczba_z_dozwolonych_cyfr.cc)
- **Start** [Liniowe minimum po dwóch poprzednich prefiksach](dp/dp_prefiksowe/minimalny_koszt_prefiksu_z_dwoma_poprzednikami.cc)
- [DP drzewa z najlepszą gałęzią poza dzieckiem](dp/drzewo_dwie_najwieksze_wysokosci/dp_drzewa_z_dwiema_najwiekszymi_wysokosciami.cc)
- [DP drzewa i splot osiągalnych reszt](dp/drzewo_splot_reszt/przekroj_drzewa_o_licznosci_podzielnej_przez_trzy.cc)
- [Top-down DP po dzielnikach i sito SPF](dp/dzielniki_pierwsze_memoizacja/memoizacja_kosztu_po_dzielnikach_pierwszych.cc)
- [Enumeracja globalnego parametru przed DP](dp/enumeracja_parametru_globalnego/minimalne_zmiany_po_ustaleniu_koncowej_liczby_liter.cc)
- [DP, aktywacja offline i maksimum prefiksowe](dp/fenwick_aktywacja_offline/maksymalna_suma_z_odstepami_przez_zdarzenia_i_fenwicka.cc)
- [DP na rosnącym grafie liczb](dp/graf_acykliczny/sciezka_po_liczbach_wzglednie_pierwszych.cc)
- [DP ścieżek z poprzednią wartością](dp/graf_wartosci_slownik/zliczanie_sciezek_addytywnych_po_wartosciach.cc)
- [Kadane od prawej i zliczanie dobrych początków](dp/kadane_od_prawej/kadane_od_prawej.cc)
- **Start** [DP kafelkowania 2xn z pamięcią stałą](dp/kafelki_dwa_wiersze/pokrycie_dwoch_wierszy_dominami_z_minimalnym_kosztem.cc)
- [Kompresja składowych implicitnej siatki](dp/kompresja_skladowych/skladowe_siatki_z_odwrocona_przekatna.cc)
- [LCS po przekształceniu na sumy prefiksowe](dp/lcs_prefiksow_modulo/lcs_sum_prefiksowych_modulo_dziesiec.cc)
- [DP z kosztem będącym maksimum po ścieżce](dp/minimalizacja_maksimum/minimalny_szczyt_ograniczonego_bilansu.cc)
- [Zliczanie i suma długości podciągów nawiasowych z automatem](dp/nawiasy_i_automat/zliczanie_i_suma_dlugosci_podciagow_nawiasowych.cc)
- [Dwustanowe DP zbioru niezależnego na ścieżce](dp/niezalezne_pozycje_sciezki/maksymalny_niezalezny_zbior_wewnetrznych_pozycji.cc)
- [DP ostatniej pozycji z przesuwaną granicą](dp/okno_ostatniego_elementu/zliczanie_podzbiorow_z_blokami_zakazanymi_i_obowiazkowymi.cc)
- [DP z budżetem i rekordowym poziomem](dp/optymalizacja_maksimum_prefiksowe/dp_etapow_z_maksimum_prefiksowym.cc)
- [Boolowskie DP stałego automatu dla trzech limitów](dp/osiagalnosc_automatu/osiagalnosc_po_znakach_z_ograniczona_zmiana_wartosci.cc)
- [Plecak dwuwymiarowy z rekonstrukcją bloków](dp/plecak_rekonstrukcja/plecak_dlugosci_blokow_z_odtwarzaniem_permutacji.cc)
- [Plecak 0/1 z mnożnikiem liczby wyborów](dp/plecak_wazone_zliczanie/wazony_plecak_czestosci.cc)
- [DP podziału cyklu na bloki długości 2 i 3](dp/podzial_cyklu/podzial_cyklu_na_pary_i_trojki.cc)
- [DP segmentacji z prefiksowym testem mediany](dp/podzial_na_dobre_przedzialy/podzial_na_nieparzyste_bloki_o_wspolnej_medianie.cc)
- [DP z przedziałami i dominacją](dp/przedzialy/otwarte_przedzialy_stanow_i_dominacja.cc)
- [Liniowe zliczanie aktywnych podprzedziałów](dp/zliczanie_aktywnych_podprzedzialow/zliczanie_podprzedzialow_automatem_z_likwidacja_stanow.cc)

### Grafy

- [Symulacja automatu ze znacznikiem zapytania](grafy/automat/symulacja_pozycji_kierunku_i_czasu.cc)
- **Start** [BFS minimalnej liczby skoków](grafy/bfs/najmniejsza_liczba_skokow.cc)
- **Start** [Bfs po parzystości długości](grafy/bfs_parzystosc/najkrotsze_marszruty_dwoch_parzystosci.cc)
- [Binary search limitu i dp na dag](grafy/dag_dp/minimalny_limit_zasobu.cc)
- [DFS z jawnym stosem](grafy/dfs/iteracyjny_dfs_na_dwuwierszowej_planszy.cc)
- [Dwukolorowanie wszystkich składowych](grafy/dwudzielnosc/klasy_dwudzielnosci_skladowych.cc)
- [Eliminacja dwóch typów krawędzi](grafy/eliminacja/zanik_jednego_typu_krawedzi.cc)
- **Start** [Graf funkcyjny skompresowanych odbić](grafy/graf_funkcyjny/osiagalnosc_wyjscia_po_odbiciach.cc)
- **Start** [Mosty tarjana lowlink i składowe bez mostów](grafy/mosty_lowlink/mosty_i_dwudzielnosc_skladowych.cc)
- [Rekonstrukcja z macierzy osiągalności](grafy/osiagalnosc/rekonstrukcja_drzewa_z_domkniecia.cc)
- [Kahn i najdłuższe ścieżki wag 0/1](grafy/toposort/ograniczenia_roznicowe_w_dag.cc)

### Drzewa

- [BFS z granicą przejścia](drzewa/bfs/bfs_z_zablokowanym_wierzcholkiem.cc)
- [Przedziały liści i cykliczny porządek dzieci](drzewa/dp_przedzialow/przedzialy_lisci_i_cykliczny_porzadek.cc)
- [Dp od liści i prefiksy ścieżek](drzewa/dwa_przebiegi/wagi_poddrzew_i_sumy_sciezek.cc)
- [Drzewo-gąsienica i silnie liści](drzewa/gasienice/rozpoznawanie_gasienicy_i_silnie_lisci.cc)
- [Drzewo kartezjańskie i wysokość](drzewa/kartezjanskie/drzewo_kartezjanskie_i_wysokosc.cc)
- [Mediana trójki i sumy symetryczne](drzewa/kombinatoryka/mediana_trojki_i_sumy_symetryczne.cc)
- [Orientacja przez wierzchołek stopnia dwa](drzewa/orientacja/jedna_sciezka_dlugosci_dwa.cc)
- **Start** [Bitset plecaka i pakowanie binarne](drzewa/plecak_warstw/bitset_i_pakowanie_binarnie.cc)
- **Start** [Plecak 0/1 rozmiarów warstw](drzewa/plecak_warstw/plecak_zero_jedynkowy_rozmiarow_warstw.cc)
- **Start** [Rerooting liczby dużych poddrzew](drzewa/rerooting/liczba_duzych_poddrzew.cc)
- [Usuwanie liści według parzystości](drzewa/usuwanie_lisci/usuwanie_lisci_wedlug_parzystosci.cc)

### Struktury danych

- [Globalne częstości słów](struktury_danych/czestosci/punktowanie_globalnych_czestosci_slow.py)
- **Start** [Fenwick z liniową budową](struktury_danych/fenwick/fenwick_z_budowa_liniowa.cc)
- [Dwa fenwicki, inwersje i wyszukiwanie rangi](struktury_danych/fenwick/rekonstrukcja_rangi_dwoma_licznikami.cc)
- [Fenwick i amortyzowana eliminacja zbioru](struktury_danych/fenwick_zbior/eliminacja_granic_sumami_przedzialow.cc)
- [Kopiec k najmniejszych prefiksu](struktury_danych/kopiec/najmniejsze_elementy_prefiksu.cc)
- [Lazy. dodawanie przedziałowe i minimum](struktury_danych/lazy_minimum/balansy_progowe_prefiksow.cc)
- [Multiset i najmniejszy element utrzymujący dodatni prefiks](struktury_danych/multiset_i_dodatni_prefiks/multiset_i_dodatni_prefiks.cc)
- **Start** [Persistent segment tree](struktury_danych/persistent_segment_tree/roznice_wersji_i_kty_element.cc)
- **Start** [Dodawanie na przedziale i odczyt punktu](struktury_danych/segment_tree/dodawanie_na_przedziale_i_odczyt_punktu.cc)
- **Start** [Dodawanie na przedziale i suma przedziału](struktury_danych/segment_tree/dodawanie_na_przedziale_i_suma.cc)
- **Start** [Dodawanie punktowe i suma przedziału](struktury_danych/segment_tree/dodawanie_punktowe_i_suma.cc)
- [Suma i maksimum prefiksowe przy obrotach](struktury_danych/segment_tree/maksimum_prefiksowe_przy_obrotach.cc)
- [Segment tree z minimum, maksimum i progiem XOR](struktury_danych/segment_tree/minimum_maksimum_i_prog_sortowania_xor.cc)
- [Parowanie przez stos indeksów](struktury_danych/stos/parowanie_otwarc_i_zamkniec.cc)
- [Binarne trie xor z indeksem](struktury_danych/trie_xor/najblizsza_para_z_progiem.cc)
- [Równe sygnatury i wykluczenie nakładania](struktury_danych/zliczanie_par/rowne_sygnatury_bez_nakladania.cc)

### Wyszukiwanie binarne

- [MEX i zachłanny warunek wykonalności](binary_search/dopasowanie/maksymalny_mex_i_zachlanne_dopasowanie.cc)
- [Binary search z izolacją punktów i zachłannym parowaniem](binary_search/izolowane_punkty_i_zachlanne_parowanie/izolowane_punkty_i_zachlanne_parowanie.cc)
- [Maksymalizacja wspólnego progu z sumowanym kosztem](binary_search/maksymalny_wspolny_prog_kosztu/maksymalny_wspolny_prog_kosztu.cc)
- [Binary search MEX z zapotrzebowaniem od wysokich poziomów](binary_search/mex_skompresowanych_licznosci_i_podwajanie_potrzeb/mex_skompresowanych_licznosci_i_podwajanie_potrzeb.cc)
- [Najbliższy element do różnicy pary](binary_search/najblizszy_element_do_roznicy/najblizszy_element_do_roznicy.py)
- [Przydział wolnego następcy i bisekcja parametru](binary_search/odpowiedz_i_zachlanny_przydzial/bisekcja_minimalnego_przesuniecia_z_przydzialem_nastepnika.cc)
- **Start** [Pierwszy dzień przekroczenia sumy cyklicznej](binary_search/pierwszy_dzien_osiagniecia_progu/pierwszy_dzien_osiagniecia_progu.py)
- [Sortowanie ułamków bez błędów zmiennoprzecinkowych](binary_search/porownywanie_ulamkow_iloczynem/porownywanie_ulamkow_iloczynem.cc)
- [Prefiksy sąsiednich par i binary search w zapytaniu](binary_search/prefiksy_par_i_monotoniczne_rownanie/prefiksy_par_i_monotoniczne_rownanie.cc)
- [Binary search sumy ilorazów i konstrukcja bloków](binary_search/suma_wielokrotnosci_i_konstrukcja_blokow/suma_wielokrotnosci_i_konstrukcja_blokow.cc)

### Algorytmy zachłanne

- [Zachłanny wybór globalnych maksimów i dwa końce](zachlanne/dwa_konce_i_parzystosc/przydzial_maksimow_do_dwoch_koncow_z_parzystoscia.cc)
- [Przenoszenie elementów do większości przy wypukłym koszcie](zachlanne/koncentracja_licznosci/maksymalizacja_wypuklej_funkcji_dwoch_licznosci.cc)
- [Zachłanne bity ze stanem tight/loose](zachlanne/konstrukcja_bitowa/maksymalna_suma_liczb_z_zadanym_xor.cc)
- [Zachłanne dołączanie słów](zachlanne/leksykograficzne/dolaczanie_napisu_na_poczatek_lub_koniec.cc)
- **Start** [Mediana minimalizuje sumę odległości](zachlanne/mediana/minimalizacja_sumy_odleglosci.py)
- [Kanoniczny zestaw nominałów](zachlanne/nominaly_kanoniczne/zachlanne_rozmienianie_nominalow_kanonicznych.cc)
- [Pakiety dodatniego zysku i kolejka progów](zachlanne/pakiety_i_kolejka/zyskowne_pakiety_transakcji_z_progami_kapitalu.cc)
- [Podział według parzystości i prefiksy największych wartości](zachlanne/parzystosc_i_prefiksy/wyniki_dla_wszystkich_licznosci_z_podzialem_na_parzystosc.cc)
- [Zachłanne pakowanie jednakowych bloków w serie zer](zachlanne/serie_zer/upakowanie_blokow_z_jednodniowa_przerwa.cc)
- [Osiągalność przez sąsiednie wysokości](zachlanne/sortowanie/osiagalnosc_po_rosnacych_wysokosciach.cc)
- [Malejąca kolejność i terminy darmowych usunięć](zachlanne/sortowanie_i_symulacja/darmowe_usuniecia_przy_podwajaniu_wag.cc)
- [Zachłanny wzrost zasobu ze wspólnym budżetem](zachlanne/sortowanie_zasob/wzrost_zasobu_z_ograniczonym_budzetem_inwestycji.cc)
- [Uporządkowane dopasowanie pozycji jedynek](zachlanne/uporzadkowane_dopasowanie/dopasowanie_jedynek_w_klasach_parzystosci.cc)
- [Wielozbiór progów i wymiana przez lower_bound](zachlanne/wielozbior_progow/wymiana_progow_przedzialowych_w_wielozbiorze.cc)
- [Zachłanny skan dla ustalonej długości podciągu](zachlanne/wybor_podciagu_dla_dlugosci/wybor_podciagu_po_ustaleniu_docelowej_dlugosci.cc)

### Sumy prefiksowe i różnicowe

- [Histogram i harmoniczne grupowanie ilorazów](sumy_prefiksowe/grupowanie_po_ilorazach/grupowanie_po_ilorazach.cc)
- [Bazowy niezależny wybór i najtańsza naprawa okna](sumy_prefiksowe/koszt_okna/koszt_narzucenia_jednorodnej_decyzji_w_oknie.cc)
- [Zapytania o liczbę bloków niezgodności](sumy_prefiksowe/liczenie_blokow_niezgodnosci/liczenie_blokow_niezgodnosci.cc)
- [Sprawdzanie nieujemnych prefiksów bilansu](sumy_prefiksowe/nieujemny_bilans_prefiksu/nieujemny_bilans_prefiksu.cc)
- [Minimalny koszt cięcia napisu](sumy_prefiksowe/optymalny_punkt_podzialu/optymalny_punkt_podzialu.cc)
- [Minimalny koszt propagacji nadmiernej luki po usunięciu](sumy_prefiksowe/prefiksy_prefiksow_i_lower_bound/prefiksy_prefiksow_i_lower_bound.cc)
- [Przedziały stałej wartości ceil(a/x)](sumy_prefiksowe/przedzialy_ilorazu/grupowanie_cen_przez_sufity_ilorazu.cc)
- [Równe reszty prefiksów z opóźnionym dopuszczaniem](sumy_prefiksowe/reszty_prefiksow_z_opoznieniem/reszty_prefiksow_z_opoznieniem.cc)
- [Tablica różnicowa dla pokrycia przedziałami](sumy_prefiksowe/roznicowe_zakazane_przedzialy/dopelnienie_sumy_zakazanych_przedzialow_tablica_roznicowa.cc)
- [Sumy sąsiedztwa na cyklu przez potrojenie tablicy](sumy_prefiksowe/sasiedztwo_na_okregu/sasiedztwo_na_okregu.cc)
- [Sumy pól pod funkcją schodkową na dzielnikach](sumy_prefiksowe/schodkowa_funkcja_na_dzielnikach/schodkowa_funkcja_na_dzielnikach.cc)
- [Zamiana istnienia drugiego cięcia na maksimum sufiksowe](sumy_prefiksowe/sufiksowe_maksimum_prefiksow/sufiksowe_maksimum_prefiksow.cc)
- [Sumowanie odcinków wyznaczonych punktami cięcia](sumy_prefiksowe/sumy_odcinkow_po_cieciach/sumy_odcinkow_po_cieciach.cc)
- [Zakazane przedziały przez tablicę różnicową](sumy_prefiksowe/tablica_roznicowa_i_weryfikacja/tablica_roznicowa_i_weryfikacja.cc)

### Napisy

- [Multizbiory znaków przez sortowanie](napisy/anagramy/porownanie_multizbiorow_przez_sortowanie.py)
- [Greedy podciągu naprzemiennego z bilansem usunięć](napisy/najdluzszy_podciag_naprzemienny_z_bilansem/najdluzszy_podciag_naprzemienny_z_bilansem.cc)
- [Następne wystąpienia i liniowe wkłady przedziałów](napisy/nastepne_wystapienia/podciagi_i_liniowe_wklady_przedzialow.cc)
- [Parzystość bloków po odcięciu monotonicznych brzegów](napisy/parzystosc_dlugosci_blokow/parzystosc_dlugosci_blokow.cc)

### Sortowanie

- [Stabilny merge sort](sortowanie/merge_sort/stabilne_sortowanie_przez_scalanie.cc)
- [Sortowanie bloków różnic](sortowanie/roznice/sortowanie_blokow_roznic_tego_samego_typu.cc)
- [Utrzymywanie m największych elementów przez scalanie](sortowanie/scalanie_top_m_sufiksu_wierszy/scalanie_top_m_sufiksu_wierszy.cc)

### Tablice

- [Maksimum po wykluczeniu elementu](tablice/ekstrema/maksimum_po_wykluczeniu_elementu.py)
- [Normalizacja przez odjęcie indeksu](tablice/normalizacja/ciag_kolejnych_wartosci_po_odjeciu_indeksu.cc)
- [Rozdzielające cięcie tablicy](tablice/prefiksy_sufiksy/minimum_prefiksu_i_maksimum_sufiksu.cc)
- [Sweep line z klasami reszt](tablice/sweep_line/aktywne_przedzialy_i_reszty_poteg_dwojki.cc)
- **Start** [Lokalna zmiana kosztu po usunięciu](tablice/wklad_lokalny/usuniecie_elementu_a_suma_roznic.cc)

### Matematyka

- [Dopasowanie dwóch liniowych wzorców](matematyka/dwa_wspolczynniki/dwa_wspolczynniki.cc)
- [Agregacja po dzielnikach](matematyka/dzielniki/agregacja_wielokrotnosci_dzielnikow.cc)
- [Enumeracja par dzielników](matematyka/dzielniki/maksimum_po_parach_dzielnikow.cc)
- [Niezmiennik klas reszt](matematyka/nwd/niezmiennik_klas_reszt_permutacji.cc)
- **Start** [NWD i osiągalność na cyklu](matematyka/nwd/osiagalnosc_na_cyklu_modulo.cc)
- [Potęgowanie binarne modulo](matematyka/potegowanie/potegowanie_binarne_modulo.cc)
- [Rdzeń bezkwadratowy i prefiksy](matematyka/rozklad_na_czynniki/rdzen_bezkwadratowy_i_parzystosc_prefiksow.cc)
- [Suma reszt ze stałym ogonem](matematyka/sumowanie/staly_ogon_sumy_reszt.cc)
- [Teleskopowanie sumy różnic](matematyka/teleskopowanie/minimalizacja_sumy_roznic.cc)
- [Przedziały zawierające punkt i zerowy XOR kolejnych liczb](matematyka/zliczanie_klas_modulo_cztery/zliczanie_klas_modulo_cztery.cc)

### Kombinatoryka

- **Start** [Gwiazdki i kreski dla bloków](kombinatoryka/dwumiany/podzial_liczebnosci_na_niepuste_bloki.cc)
- [Suma potęg modularnych na unikalnym sufiksie](kombinatoryka/sufiks_i_potegowanie/suma_poteg_po_sufiksie_bez_powtorzen.cc)
- [Kombinatoryka zagnieżdżonych zakresów](kombinatoryka/zagniezdzone_przedzialy/zagniezdzone_przedzialy_pozycji_i_iloczyn_wyborow.cc)

### Operacje bitowe

- [Kod Graya i pojedyncze przełączenia bitu](bity/kod_graya_i_roznice_xor/kod_graya_i_roznice_xor.cc)
- [Korygowanie bitów XOR przez podwajanie potęg dwójki](bity/korygowanie_xor_od_najwyzszego_bitu/korygowanie_xor_od_najwyzszego_bitu.cc)
- [Aktualizacja punktowa licznika parzystych popcount](bity/licznik_parzystosci_popcount_po_zmianach/licznik_parzystosci_popcount_po_zmianach.cc)
- [Zachłanny poprzednik w zbiorze podmasek](bity/poprzednik_podmaska/najwieksza_podmaska_nieprzekraczajaca_ograniczenia.cc)
- [Minima sufiksowe kosztów pod ograniczeniem końcowych zer](bity/preprocessing_kosztow_i_sufiksowych_minimow/preprocessing_kosztow_i_sufiksowych_minimow.cc)
- [Kupowanie najtańszych ustawionych bitów](bity/zachlanne_kupowanie_bitow/zachlanne_kupowanie_bitow.cc)
- [Porównanie elementu z XOR pozostałych](bity/zmniejszenie_elementu_przez_xor/zmniejszenie_elementu_przez_xor.cc)

### Dwa wskaźniki

- [Sortowanie i zużywanie par skrajnych](dwa_wskazniki/parowanie_skrajnych_po_sortowaniu/parowanie_skrajnych_po_sortowaniu.cc)

### Stos monotoniczny

- [Stos monotoniczny i sumy maksimów dla wszystkich obrotów](stos_monotoniczny/sumy_maksimow_dla_obrotow/sumy_maksimow_dla_obrotow.cc)

### Konstrukcje

- [Enumeracja początku deterministycznego ciągu](konstrukcje/enumeracja_poczatku_rekurencji/enumeracja_dwoch_pierwszych_bitow_rekurencji.cc)
- [Rekonstrukcja z różnic grup](konstrukcje/grupowanie/rekonstrukcja_wartosci_z_roznic_grup.cc)
- [Odtwarzanie etykiet po wskazaniu poprzednika](konstrukcje/odtwarzanie_poprzednika/rekonstrukcja_etykiet_z_roznic_prefiksowych.cc)
- [Okresowa konstrukcja o stałej sumie okna](konstrukcje/okresowa_sekwencja_o_stalej_sumie/okresowa_sekwencja_o_stalej_sumie.cc)
- [Wstawianie indeksów przy ograniczeniach liczby większych](konstrukcje/wstawianie_do_kolejnosci/rekonstrukcja_kolejnosci_przez_wstawianie.cc)
- [Podział kolejnych kroków i wypukła reszta](konstrukcje/wypukla_reszta/podzial_krokow_i_zbalansowanie_reszty.cc)

### Przegląd możliwości

- [Rekurencyjne generowanie liczb z alfabetu cyfr](brute_force/generowanie_liczb_z_cyfr/generowanie_liczb_z_cyfr.cc)
- [Kwadratowy przegląd z bieżącym maksimum przedziału](brute_force/maksima_przedzialow/maksimum_polaczenia_dwoch_profili_przez_maksimum_przedzialu.cc)
- [Podtablice bez powtórzeń i kolejne wartości](brute_force/zbiory_kolejnych_wartosci/wykrywanie_podtablic_bedacych_przedzialami_wartosci.cc)

### Rekurencja

- [Rekurencja ruchów na trzech palikach](rekurencja/hanoi_z_parametrem/rekurencyjne_przenoszenie_stosow_z_pominietym_prefiksem.cc)

### Gry

- [Gra binarna. ostatnia skuteczna decyzja](gry/ostatni_ruch_xor/gra_xor_i_parzystosc_ostatniej_roznicy.cc)

### Zbiory

- [Premia za pierwsze wystąpienie](zbiory/pierwsze_wystapienie/liczenie_premii_za_nowy_element.py)

### Zliczanie

- [MEX ograniczonej domeny](zliczanie/mex/mex_przez_tablice_obecnosci.cc)

### Ciagi

- [Skan luk w ciągu cyklicznym](ciagi/luki_na_cyklu/najdluzsza_luka_miedzy_jedynkami_na_cyklu.cc)

### Bloki

- [Długości bloków, próg i kongruencja](bloki/progi_dlugosci_i_sumy_sufiksowe/progi_dlugosci_i_sumy_sufiksowe.cc)

