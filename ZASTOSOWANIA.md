# Co chcę osiągnąć?

Przewodnik obejmuje wszystkie 158 przykładów w repozytorium. Zacznij od celu, potem sprawdź warunki metody i nagłówek konkretnego pliku. Przykłady realizują konkretne modele zadań. Warunki wejścia są częścią ich zastosowania.

- [Chcę sprawdzić osiągalność lub znaleźć drogę](#drogi)
- [Chcę policzyć wynik na drzewie](#drzewa)
- [Chcę szybko obsługiwać przedziały i zmiany wartości](#przedzialy)
- [Chcę policzyć sposoby, podzbiory lub podprzedziały](#zliczanie)
- [Chcę szukać liczb spełniających warunki na cyfrach](#liczby)
- [Chcę porównywać napisy, dopasować wzorzec lub zmieniać znaki](#napisy)
- [Chcę sterować XOR-em, bitami lub parzystością](#bity)
- [Chcę znaleźć minimum lub maksimum przez podział na stany](#minimum)
- [Chcę znaleźć największy możliwy lub najmniejszy wystarczający próg](#prog)
- [Chcę uporządkować dane lub wykorzystać ich kolejność](#kolejnosc)
- [Chcę odtworzyć rozwiązanie lub zbudować poprawny obiekt](#konstrukcja)
- [Chcę wybierać zasoby, terminy lub pary](#zachlanne)
- [Chcę uprościć obliczenia przez NWD, dzielniki lub wzór](#arytmetyka)
- [Chcę policzyć wystąpienia, pary lub brakującą wartość](#czestosci)
- [Chcę przyspieszyć rozwiązanie lub zmniejszyć pamięć](#optymalizacja)

<a id="drogi"></a>

## Chcę sprawdzić osiągalność lub znaleźć drogę

BFS wybierz przy jednakowym koszcie każdego ruchu. DFS wystarczy do sprawdzenia osiągalności. Jeśli przyszłe ruchy zależą od kierunku, czasu lub parzystości, dodaj te informacje do stanu. Porządek topologiczny pozwala przetwarzać zależności w DAG.

- [DP na rosnącym grafie liczb](dp/graf_acykliczny/sciezka_po_liczbach_wzglednie_pierwszych.cc). Znajduje najkrótszy rosnący ciąg od a do b, którego sąsiednie liczby są względnie pierwsze, i wypisuje długości kolejnych kroków.
- [Kompresja składowych implicitnej siatki](dp/kompresja_skladowych/skladowe_siatki_z_odwrocona_przekatna.cc). Obliczyć maksimum rozmiaru składowej zer macierzy n*n, której kolumna i zawiera s[i] poza odwróconą przekątną.
- [Symulacja automatu ze znacznikiem zapytania](grafy/automat/symulacja_pozycji_kierunku_i_czasu.cc). Skacze między kolejnymi światłami i wykrywa powtórzenie stanu (indeks,kierunek,czas modulo k). odpowiada, czy ruch opuści zakres świateł.
- [BFS minimalnej liczby skoków](grafy/bfs/najmniejsza_liczba_skokow.cc). Liczy najmniejszą liczbę skoków o 1..j pozycji w prawo po znakach 1.
- [Bfs po parzystości długości](grafy/bfs_parzystosc/najkrotsze_marszruty_dwoch_parzystosci.cc). Oblicza najkrótsze marszruty obu parzystości i porównuje je z sumą długości oraz sumą po odrzuceniu najmniejszej nieparzystej.
- [Binary search limitu i dp na dag](grafy/dag_dp/minimalny_limit_zasobu.cc). Minimalizuje limit zasobu x, przy którym można przejść od 1 do n, respektując progi krawędzi i przyrosty zasobu w wierzchołkach.
- [DFS z jawnym stosem](grafy/dfs/iteracyjny_dfs_na_dwuwierszowej_planszy.cc). Sprawdza osiągalność dowolnej komórki ostatniej kolumny ze startu (0,0), dopuszczając pion oraz ruch do następnej kolumny.
- [Dwukolorowanie wszystkich składowych](grafy/dwudzielnosc/klasy_dwudzielnosci_skladowych.cc). Sumuje większą klasę dwudzielności dwudzielnych składowych, izolowane wierzchołki liczy jako 1, a niedwudzielne składowe jako 0.
- [Eliminacja dwóch typów krawędzi](grafy/eliminacja/zanik_jednego_typu_krawedzi.cc). Usuwa wierzchołki, przy których zanika jeden z dwóch typów krawędzi, przypisując znak oraz malejący moduł. pozostawiony rdzeń powoduje NO.
- [Graf funkcyjny skompresowanych odbić](grafy/graf_funkcyjny/osiagalnosc_wyjscia_po_odbiciach.cc). Grupuje światła według d−p i d+p modulo k, buduje 2n stanów zmiany kierunku i propaguje osiągalność wyjścia po odwróconych krawędziach.
- [Mosty tarjana lowlink i składowe bez mostów](grafy/mosty_lowlink/mosty_i_dwudzielnosc_skladowych.cc). Policzyć modulo 998244353 przypisania nieustalonych wartości z zakresu 0..V−1 w balanced XOR graph. wewnątrz każdej składowej po usunięciu mostów ustalone wartości muszą być zgodne, składowa niedwudzielna wymusza 0, a nieustalona dwudzielna wnosi V możliwości.
- [Rekonstrukcja z macierzy osiągalności](grafy/osiagalnosc/rekonstrukcja_drzewa_z_domkniecia.cc). Usuwa relacje z pośrednikiem, sprawdza n−1 krawędzi i spójność podkładu, a następnie odtwarza osiągalność i porównuje całą macierz.
- [Kahn i najdłuższe ścieżki wag 0/1](grafy/toposort/ograniczenia_roznicowe_w_dag.cc). Z przekątnej wyznacza znaki, z par tworzy dolne ograniczenia modułów i wylicza je topologicznie. sprzeczności lub cykl dają NO.

<a id="drzewa"></a>

## Chcę policzyć wynik na drzewie

Wynik zależny od dzieci sugeruje DP od liści. Wynik dla różnych korzeni sugeruje rerooting. Plecak warstw służy do wyboru grup określonego rozmiaru. Własności stopni i kształtu drzewa mogą uprościć problem do rozpoznania struktury.

- [DP drzewa z najlepszą gałęzią poza dzieckiem](dp/drzewo_dwie_najwieksze_wysokosci/dp_drzewa_z_dwiema_najwiekszymi_wysokosciami.cc). Dla korzenia rozważanego poddrzewa maksymalizuje sumę a[u]*dist(korzen,u) po co najwyżej jednym odcięciu i podłączeniu gałęzi do wierzchołka nadal połączonego z korzeniem.
- [DP drzewa i splot osiągalnych reszt](dp/drzewo_splot_reszt/przekroj_drzewa_o_licznosci_podzielnej_przez_trzy.cc). Sprawdzić istnienie przekroju korzeniowego drzewa o liczności podzielnej przez 3. wybieramy v albo przekroje wszystkich dzieci v.
- [BFS z granicą przejścia](drzewa/bfs/bfs_z_zablokowanym_wierzcholkiem.cc). BFS od n zapisuje odległość do 1 jako ans, ale nie kolejkuje 1. następnie maksymalizuje ans przez dist[v]+1 dla wskazanych osiągalnych v.
- [Przedziały liści i cykliczny porządek dzieci](drzewa/dp_przedzialow/przedzialy_lisci_i_cykliczny_porzadek.cc). Sprawdza max−min+1=liczba liści w każdym poddrzewie oraz najwyżej jeden cykliczny spadek minimów dzieci.
- [Dp od liści i prefiksy ścieżek](drzewa/dwa_przebiegi/wagi_poddrzew_i_sumy_sciezek.cc). Dla liści wyznacza wagę 1, dla węzła wewnętrznego sumę wag obu synów plus 3. wypisuje sumę wag na ścieżce od korzenia do każdego wierzchołka modulo 1e9+7.
- [Drzewo-gąsienica i silnie liści](drzewa/gasienice/rozpoznawanie_gasienicy_i_silnie_lisci.cc). Liczy uporządkowania wierzchołków na dwóch brzegach bez przecinania krawędzi. Rozpoznaje spójne drzewo-gąsienicę i mnoży liczby ustawień liści przy jego kręgosłupie.
- [Drzewo kartezjańskie i wysokość](drzewa/kartezjanskie/drzewo_kartezjanskie_i_wysokosc.cc). Buduje maksymalne drzewo kartezjańskie tablicy i wypisuje n minus wysokość liczona w wierzchołkach.
- [Mediana trójki i sumy symetryczne](drzewa/kombinatoryka/mediana_trojki_i_sumy_symetryczne.cc). Liczy trójki różnych wierzchołków, których mediana w drzewie ma kwadratową wartość a. sumuje iloczyny rozmiarów trzech różnych gałęzi wraz z singletonem mediany.
- [Orientacja przez wierzchołek stopnia dwa](drzewa/orientacja/jedna_sciezka_dlugosci_dwa.cc). Wybiera wierzchołek stopnia 2 jako jedyne miejsce przejścia wejście-wyjście, a pozostałe wierzchołki orientuje jako źródła lub ujścia.
- [Bitset plecaka i pakowanie binarne](drzewa/plecak_warstw/bitset_i_pakowanie_binarnie.cc). Maksymalizuje długość najdłuższego wspólnego podciągu wszystkich binarnych napisów na ścieżkach od korzenia do liścia, przy dokładnie k etykietach zero. Niech h oznacza najmniejszą głębokość liścia przy głębokości korzenia jeden. Kod wypisuje h, gdy suma s osiągalna plecakiem rozmiarów warstw spełnia 0<=k-s<=n-sum(cnt). W przeciwnym razie wypisuje h-1.
- [Plecak 0/1 rozmiarów warstw](drzewa/plecak_warstw/plecak_zero_jedynkowy_rozmiarow_warstw.cc). Maksymalizuje długość najdłuższego wspólnego podciągu wszystkich binarnych napisów na ścieżkach od korzenia do liścia, przy dokładnie k etykietach zero. Niech h oznacza najmniejszą głębokość liścia przy głębokości korzenia jeden. Kod wypisuje h, gdy suma s osiągalna plecakiem rozmiarów warstw spełnia 0<=k-s<=n-sum(cnt). W przeciwnym razie wypisuje h-1.
- [Rerooting liczby dużych poddrzew](drzewa/rerooting/liczba_duzych_poddrzew.cc). Sumuje po wszystkich korzeniach liczbę wierzchołków, których poddrzewo ma co najmniej k elementów.
- [Usuwanie liści według parzystości](drzewa/usuwanie_lisci/usuwanie_lisci_wedlug_parzystosci.cc). Korzeni w n, utrzymuje liście w dwóch stosach według parzystości głębokości i generuje operacje 1 oraz 2 v, usuwając liście przeciwnego koloru do cat_color.

<a id="przedzialy"></a>

## Chcę szybko obsługiwać przedziały i zmiany wartości

Dla stałych danych rozważ sumy prefiksowe. Dodawanie do wielu zakresów przed jednym odczytem pasuje do tablicy różnicowej. Zmiany przeplatane z pytaniami sugerują Fenwicka lub segment tree. Wybierz wariant zgodny z rodzajem aktualizacji i pytania.

- [Długości bloków, próg i kongruencja](bloki/progi_dlugosci_i_sumy_sufiksowe/progi_dlugosci_i_sumy_sufiksowe.cc). Policzyć różne długości bloku x, dla których k>=mn i (k-mn) mod ile=0, gdzie ile to liczba bloków długości co najmniej x, a mn=sum tych długości-ile*(x-1).
- [Skan luk w ciągu cyklicznym](ciagi/luki_na_cyklu/najdluzsza_luka_miedzy_jedynkami_na_cyklu.cc). Dla napisu binarnego zawierającego co najmniej jedną jedynkę obliczyć długość najdłuższego cyklicznego odcinka zer.
- [Fenwick z liniową budową](struktury_danych/fenwick/fenwick_z_budowa_liniowa.cc). Udostępnić wyłącznie poprawną strukturę Fenwick2. liniową budowę z a[1..n], dodawanie punktowe oraz sumę prefiksową.
- [Dwa fenwicki, inwersje i wyszukiwanie rangi](struktury_danych/fenwick/rekonstrukcja_rangi_dwoma_licznikami.cc). Od prawej rekonstruuje nieznane wartości na podstawie różnic s, liczb większych aktywnych elementów i inwersji bloków znanych wartości.
- [Fenwick i amortyzowana eliminacja zbioru](struktury_danych/fenwick_zbior/eliminacja_granic_sumami_przedzialow.cc). Dodaje indeksy w odwróconym p, utrzymuje zbiór granic i usuwa kolejne granice, gdy aktywna suma między granicami osiąga wagę kandydata. zapisuje rozmiar zbioru minus 1.
- [Lazy. dodawanie przedziałowe i minimum](struktury_danych/lazy_minimum/balansy_progowe_prefiksow.cc). Dla każdego prefiksu utrzymuje balansy progów i zwiększa mex, gdy próbne odjęcie przedziału zachowuje nieujemne minimum na [0,mex].
- [Multiset i najmniejszy element utrzymujący dodatni prefiks](struktury_danych/multiset_i_dodatni_prefiks/multiset_i_dodatni_prefiks.cc). Ułożyć elementy tak, aby każda suma prefiksowa była dodatnia, i wypisać te sumy. przy niepozytywnej sumie całkowitej wypisać -1.
- [Persistent segment tree](struktury_danych/persistent_segment_tree/roznice_wersji_i_kty_element.cc). Kopiuje ścieżkę aktualizacji, pyta o sumę różnicy dwóch wersji i wybiera k-ty element różnicy.
- [Dodawanie na przedziale i odczyt punktu](struktury_danych/segment_tree/dodawanie_na_przedziale_i_odczyt_punktu.cc). Dodaje wartość do przedziału i odczytuje aktualną wartość wskazanego elementu.
- [Dodawanie na przedziale i suma przedziału](struktury_danych/segment_tree/dodawanie_na_przedziale_i_suma.cc). Dodaje wartość do wszystkich elementów zakresu i odpowiada na sumy dowolnych przedziałów.
- [Dodawanie punktowe i suma przedziału](struktury_danych/segment_tree/dodawanie_punktowe_i_suma.cc). Dodaje wartość do jednego elementu i odpowiada na sumy przedziałów.
- [Suma i maksimum prefiksowe przy obrotach](struktury_danych/segment_tree/maksimum_prefiksowe_przy_obrotach.cc). Liczy obroty permutacji, których każdy prefiks jako zbiór wartości ma najwyżej dwie spójne składowe na ścieżce 1..n.
- [Histogram i harmoniczne grupowanie ilorazów](sumy_prefiksowe/grupowanie_po_ilorazach/grupowanie_po_ilorazach.cc). Dla kolejnych k>=1, j=2^k, obliczyć maksimum po y=1..m sumy min(floor(a/y),j-1)+[a=j*y]. po j>m wynikiem jest suma a.
- [Bazowy niezależny wybór i najtańsza naprawa okna](sumy_prefiksowe/koszt_okna/koszt_narzucenia_jednorodnej_decyzji_w_oknie.cc). Zminimalizować sumę wyników modulo p, wybierając przed nim opcjonalne modulo q na każdej pozycji, z warunkiem istnienia okna długości k o jednakowej decyzji.
- [Zapytania o liczbę bloków niezgodności](sumy_prefiksowe/liczenie_blokow_niezgodnosci/liczenie_blokow_niezgodnosci.cc). Dla fragmentu [l,r] stwierdzić, czy minimum liczby bloków niezgodności z globalnymi wzorcami 0101... i 1010... jest najwyżej k.
- [Sprawdzanie nieujemnych prefiksów bilansu](sumy_prefiksowe/nieujemny_bilans_prefiksu/nieujemny_bilans_prefiksu.cc). Sprawdzić, czy dla każdego prefiksu suma b jest co najmniej sumą a.
- [Minimalny koszt cięcia napisu](sumy_prefiksowe/optymalny_punkt_podzialu/optymalny_punkt_podzialu.cc). Znaleźć granicę minimalizującą liczbę znaków ( po lewej i ) po prawej, a potem oznaczyć do min(k,koszt) takich pozycji maską 1.
- [Minimalny koszt propagacji nadmiernej luki po usunięciu](sumy_prefiksowe/prefiksy_prefiksow_i_lower_bound/prefiksy_prefiksow_i_lower_bound.cc). Dla każdego indeksu niezależnie usunąć a[i] i obliczyć minimalną liczbę operacji zmniejszenia elementu o 1, po których tablica ponownie jest niemalejąca i każda sąsiednia różnica nie przekracza k.
- [Przedziały stałej wartości ceil(a/x)](sumy_prefiksowe/przedzialy_ilorazu/grupowanie_cen_przez_sufity_ilorazu.cc). Maksymalizować po całkowitym x w [2,A] wartość sum_j j*c_j-y*max(0,c_j-freq[j]), gdzie c_j zlicza ceny z ceil(a/x)=j.
- [Równe reszty prefiksów z opóźnionym dopuszczaniem](sumy_prefiksowe/reszty_prefiksow_z_opoznieniem/reszty_prefiksow_z_opoznieniem.cc). Policzyć spójne podtablice długości co najmniej k+1, których suma jest podzielna przez k.
- [Tablica różnicowa dla pokrycia przedziałami](sumy_prefiksowe/roznicowe_zakazane_przedzialy/dopelnienie_sumy_zakazanych_przedzialow_tablica_roznicowa.cc). Wypisać wszystkie x z 0..n-1, które nie należą do żadnego przedziału [a[k]*k,min(n-1,(a[k]+1)*k-1)].
- [Sumy sąsiedztwa na cyklu przez potrojenie tablicy](sumy_prefiksowe/sasiedztwo_na_okregu/sasiedztwo_na_okregu.cc). Obliczyć sumę max(0,2*d*a[i]-suma d poprzednich-suma d następnych wartości) dla wszystkich pozycji cyklu.
- [Sumy pól pod funkcją schodkową na dzielnikach](sumy_prefiksowe/schodkowa_funkcja_na_dzielnikach/schodkowa_funkcja_na_dzielnikach.cc). Dla s>0 zdefiniować H(u)=s/d, gdzie d jest najmniejszym dzielnikiem s nie mniejszym niż u, i dla zapytania x,y policzyć sumę min(y,H(u)) po 1<=u<=min(x,s), przy y uciętym do s.
- [Zamiana istnienia drugiego cięcia na maksimum sufiksowe](sumy_prefiksowe/sufiksowe_maksimum_prefiksow/sufiksowe_maksimum_prefiksow.cc). Sprawdzić istnienie 1<=x<y<=n-1 z p1[x]>=0 i p2[y]>=p2[x], dla wag p1. 1 daje +1, reszta -1. p2. 3 daje -1, reszta +1.
- [Sumowanie odcinków wyznaczonych punktami cięcia](sumy_prefiksowe/sumy_odcinkow_po_cieciach/sumy_odcinkow_po_cieciach.cc). Policzyć sumę modułów sum kolejnych fragmentów zakończonych w posortowanych punktach b oraz zwykłą sumę końcowego sufiksu.
- [Zakazane przedziały przez tablicę różnicową](sumy_prefiksowe/tablica_roznicowa_i_weryfikacja/tablica_roznicowa_i_weryfikacja.cc). Zbudować binarny napis, w którym dla każdego znanego b[i]=len najbliższa jedynka jest dokładnie w odległości len, albo zwrócić -1.
- [Maksimum po wykluczeniu elementu](tablice/ekstrema/maksimum_po_wykluczeniu_elementu.py). Oblicza największy element i maksimum po usunięciu jego pierwszego wystąpienia. dla każdego elementu wypisuje różnicę do maksimum pozostałych.
- [Rozdzielające cięcie tablicy](tablice/prefiksy_sufiksy/minimum_prefiksu_i_maksimum_sufiksu.cc). Wypisuje No, gdy istnieje cięcie z każdym lewym elementem większym od każdego prawego. inaczej Yes.
- [Sweep line z klasami reszt](tablice/sweep_line/aktywne_przedzialy_i_reszty_poteg_dwojki.cc). Dla każdej pozycji i sumuje po przedziałach [l,r] zawierających i wartość (i-l+1)*lowbit(i-l+1). lowbit(x) jest największą potęgą dwójki dzielącą x.
- [Lokalna zmiana kosztu po usunięciu](tablice/wklad_lokalny/usuniecie_elementu_a_suma_roznic.cc). Minimalizuje sumę bezwzględnych różnic kolejnych elementów po usunięciu co najwyżej jednego elementu.

<a id="zliczanie"></a>

## Chcę policzyć sposoby, podzbiory lub podprzedziały

Najpierw określ, co wyróżnia dwa różne rozwiązania. DP zliczające sumuje liczby przejść, a kombinatoryka zastępuje je wzorem. Gdy potrzebujesz też sumy długości albo wartości, przechowuj obok liczności dodatkowy agregat.

- [DP ścieżek z poprzednią wartością](dp/graf_wartosci_slownik/zliczanie_sciezek_addytywnych_po_wartosciach.cc). Zliczyć skierowane ścieżki z >=2 wierzchołkami, na których każda wartość od trzeciej jest sumą dwóch poprzednich.
- [DP ostatniej pozycji z przesuwaną granicą](dp/okno_ostatniego_elementu/zliczanie_podzbiorow_z_blokami_zakazanymi_i_obowiazkowymi.cc). Policzyć podzbiory S zbioru 0..n-1, dla których mex zbioru {floor(x/k):x w S} jest równy a[k] dla każdego k.
- [Plecak 0/1 z mnożnikiem liczby wyborów](dp/plecak_wazone_zliczanie/wazony_plecak_czestosci.cc). Obliczyć sumę wag podzbiorów klas wartości, których łączna częstość jest >=M, gdzie M to największa częstość. waga podzbioru jest iloczynem częstości wybranych klas.
- [Liniowe zliczanie aktywnych podprzedziałów](dp/zliczanie_aktywnych_podprzedzialow/zliczanie_podprzedzialow_automatem_z_likwidacja_stanow.cc). Zliczyć podprzedziały, których stan nie zostaje zlikwidowany. start w 0, przy a=b przejście a-1->a, przy a!=b zakaz stanów a-1 i b-1.
- [Gwiazdki i kreski dla bloków](kombinatoryka/dwumiany/podzial_liczebnosci_na_niepuste_bloki.cc). Liczy napisy binarne z takimi samymi licznościami znaków oraz taką samą naprzemienną sekwencją bloków jak wejście.
- [Suma potęg modularnych na unikalnym sufiksie](kombinatoryka/sufiks_i_potegowanie/suma_poteg_po_sufiksie_bez_powtorzen.cc). Obliczyć 1+sum (a[i]-1)^(n-i) modulo 1e9+7 dla indeksów i od n-1 w dół do pierwszego indeksu z a[i]==a[i-1], z wyłączeniem tego indeksu.
- [Kombinatoryka zagnieżdżonych zakresów](kombinatoryka/zagniezdzone_przedzialy/zagniezdzone_przedzialy_pozycji_i_iloczyn_wyborow.cc). Obliczyć wynik 2 pomnożony przez czynniki swobody zagnieżdżonych zakresów pozycji wartości >=i, odrzucając niespójność albo dwustronne rozszerzenie.

<a id="liczby"></a>

## Chcę szukać liczb spełniających warunki na cyfrach

Digit DP buduje liczbę po cyfrze. tight ogranicza prefiks górną granicą, started rozróżnia zera wiodące, a maska zapamiętuje użyte cyfry. Stan i agregat dobierz do celu zliczania, sumowania lub szukania najbliższej liczby.

- [Rekurencyjne generowanie liczb z alfabetu cyfr](brute_force/generowanie_liczb_z_cyfr/generowanie_liczb_z_cyfr.cc). Zminimalizować odległość |a-v| wśród nieujemnych liczb zapisanych wyłącznie dozwolonymi cyframi, bez zer wiodących poza liczbą 0.
- [Digit DP. liczba niezerowych cyfr](dp/digit_dp/zliczanie_liczb_z_limitem_niezerowych_cyfr.cc). Policzyć liczby z [l,r] z najwyżej trzema niezerowymi cyframi.
- [Digit DP sum cyfr i wyszukiwanie pozycji w konkatenacji](dp/digit_dp_i_wyszukiwanie/suma_prefiksu_ciagu_cyfr_przez_bisekcje_i_digit_dp.cc). Obliczyć sumę pierwszych k cyfr nieskończonej konkatenacji dodatnich liczb dziesiętnych.
- [Digit DP. maska cyfr, started i para count/sum](dp/digit_dp_maska_agregaty/suma_liczb_z_maska_uzytych_cyfr.cc). Zsumować modulo 998244353 liczby z [l,r] używające najwyżej k różnych cyfr.
- [Digit DP najbliższej liczby z relacją mniejsza/równa/większa](dp/digit_dp_najblizsza_liczba/najblizsza_liczba_z_dozwolonych_cyfr.cc). Dla nieujemnego a<=10^17 i niepustego zbioru dozwolonych cyfr znaleźć najmniejszą odległość |a-b| po nieujemnych b zapisanych wyłącznie dozwolonymi cyframi, bez zer wiodących poza liczbą zero.

<a id="napisy"></a>

## Chcę porównywać napisy, dopasować wzorzec lub zmieniać znaki

Równość multizbiorów znaków sprawdzisz przez częstości albo sortowanie. Podciąg zachowuje kolejność i może pomijać znaki, a podnapis jest spójnym fragmentem. Automat zapamiętuje postęp dopasowania lub ograniczenia zmian.

- [Automat czterech stanów z kosztem zmian](dp/automat_xor/minimalne_poprawki_dwoch_napisow_dla_xor_prefiksowego.cc). Zminimalizować łączną odległość Hamminga x do X i y do Y przy Y[i]=X[0] xor ... xor X[i].
- [LCS po przekształceniu na sumy prefiksowe](dp/lcs_prefiksow_modulo/lcs_sum_prefiksowych_modulo_dziesiec.cc). Dla równych łącznych sum cyfr modulo 10 znaleźć LCS ciągów sum prefiksowych z zerem początkowym i wypisać jego długość minus 1. przy różnych sumach zwrócić -1.
- [Zliczanie i suma długości podciągów nawiasowych z automatem](dp/nawiasy_i_automat/zliczanie_i_suma_dlugosci_podciagow_nawiasowych.cc). Obliczyć modulo 998244353 sumę (długość podciągu-2) po wszystkich podciągach wejściowego napisu nawiasowego, które mają nieujemny bilans każdego prefiksu, bilans końcowy 0 i osiągają stan automatu opt=3. po pierwszym wybranym zamknięciu występują co najmniej dwa późniejsze wybrane otwarcia. Podciągi rozróżnia się przez wybrane indeksy.
- [Boolowskie DP stałego automatu dla trzech limitów](dp/osiagalnosc_automatu/osiagalnosc_po_znakach_z_ograniczona_zmiana_wartosci.cc). Znaleźć najmniejsze i w 1..3, dla którego istnieją stany z zakresu -3..3 o znakach zgodnych z napisem, startując z 0, zmieniając stan na każdym kroku i zachowując |x-y|<=i.
- [Multizbiory znaków przez sortowanie](napisy/anagramy/porownanie_multizbiorow_przez_sortowanie.py). Czy litery trzeciego napisu są dokładnie połączeniem liter dwóch pierwszych napisów?
- [Greedy podciągu naprzemiennego z bilansem usunięć](napisy/najdluzszy_podciag_naprzemienny_z_bilansem/najdluzszy_podciag_naprzemienny_z_bilansem.cc). Wyznaczyć najdłuższy naprzemienny podciąg binarny, po którego usunięciu różnica liczby usuniętych zer i jedynek ma moduł najwyżej 1. wypisać liczbę usuniętych znaków lub -1.
- [Następne wystąpienia i liniowe wkłady przedziałów](napisy/nastepne_wystapienia/podciagi_i_liniowe_wklady_przedzialow.cc). Dla każdej pozycji liczy pokrywające ją podnapisy, w których występowanie 2025 jako podciągu implikuje występowanie 2026 jako podciągu.
- [Parzystość bloków po odcięciu monotonicznych brzegów](napisy/parzystosc_dlugosci_blokow/parzystosc_dlugosci_blokow.cc). Wypisać Alice wtedy i tylko wtedy, gdy po pominięciu początkowych zer i końcowych jedynek pozostaje blok o nieparzystej długości. inaczej Bob.
- [Parowanie przez stos indeksów](struktury_danych/stos/parowanie_otwarc_i_zamkniec.cc). Paruje 1 z późniejszym 2, wypisując dopasowane zamknięcia i niedopasowane otwarcia. pomija sparowane otwarcia, samotne zamknięcia i pozostałe znaki.
- [Zachłanne dołączanie słów](zachlanne/leksykograficzne/dolaczanie_napisu_na_poczatek_lub_koniec.cc). Buduje leksykograficznie najmniejszy napis przez dołączanie kolejnych słów na początku lub końcu.

<a id="bity"></a>

## Chcę sterować XOR-em, bitami lub parzystością

Rozdziel operacje na wartościach od operacji na indeksach. Maska opisuje zbiór bitów, trie porównuje liczby od najwyższego bitu, a DP z przeniesieniem obsługuje zależności między sąsiednimi pozycjami bitowymi.

- [Kod Graya i pojedyncze przełączenia bitu](bity/kod_graya_i_roznice_xor/kod_graya_i_roznice_xor.cc). Dla b=minimalnego z 2^b>n wygenerować różnice XOR kolejnych kodów Graya, ostatni kod oraz ponownie te same różnice.
- [Korygowanie bitów XOR przez podwajanie potęg dwójki](bity/korygowanie_xor_od_najwyzszego_bitu/korygowanie_xor_od_najwyzszego_bitu.cc). Wybrać oznaczenia podwojenia liczb 1..n według procedury, która zaczyna od podwojenia n, a następnie od najwyższego bitu koryguje zera aktualnego XOR podwojeniem wybranych potęg dwójki.
- [Aktualizacja punktowa licznika parzystych popcount](bity/licznik_parzystosci_popcount_po_zmianach/licznik_parzystosci_popcount_po_zmianach.cc). Utrzymywać liczbę elementów, których 32-bitowy popcount jest parzysty, i wypisać ją przed aktualizacjami oraz po każdej z nich.
- [Zachłanny poprzednik w zbiorze podmasek](bity/poprzednik_podmaska/najwieksza_podmaska_nieprzekraczajaca_ograniczenia.cc). Dla s=x+y znaleźć największą podmaskę a liczby s nieprzekraczającą x i wypisać s oraz x-a.
- [Minima sufiksowe kosztów pod ograniczeniem końcowych zer](bity/preprocessing_kosztow_i_sufiksowych_minimow/preprocessing_kosztow_i_sufiksowych_minimow.cc). Dla k=0..17 minimalizować sumę kosztów przekształcenia a[i] do x>=a[i] z co najmniej k końcowymi zerami, wymuszając dokładnie k zer dla przynajmniej jednego elementu, następnie odjąć k(n-1). Koszt to x-a+floor(log2 x)+popcount(x).
- [Kupowanie najtańszych ustawionych bitów](bity/zachlanne_kupowanie_bitow/zachlanne_kupowanie_bitow.cc). Zmaksymalizować sumę popcount length nieujemnych liczb, gdy suma ich wartości nie przekracza limitSum.
- [Porównanie elementu z XOR pozostałych](bity/zmniejszenie_elementu_przez_xor/zmniejszenie_elementu_przez_xor.cc). Odtworzyć dokładny wynik kodu. dla n=1 zwrócić 0. dla n>1 i X=0 zwrócić 1. inaczej policzyć a[i] większe od XOR pozostałych.
- [Bitowe DP relacji porządku i odległości L1](dp/bity_porownania_i_norma_l1/najblizsza_para_z_rozlacznymi_bitami.cc). Znaleźć nieujemne p,q<2^31 z p&q=0 minimalizujące |x-p|+|y-q|.
- [DP bitowe od najmłodszych bitów](dp/bity_przeniesienie/bitowe_dp_dodawania_z_przeniesieniem.cc). Dla k<32 znaleźć najmniejszy popcount(n+m), gdzie m ma najwyżej k jedynek, i wypisać popcount(n)-minimum+k.
- [Gra binarna. ostatnia skuteczna decyzja](gry/ostatni_ruch_xor/gra_xor_i_parzystosc_ostatniej_roznicy.cc). Dla binarnych tablic i modelu naprzemiennych zamian a[i],b[i] wyznaczyć wynik gry przez XOR-y i ostatnią różniącą pozycję.
- [Segment tree z minimum, maksimum i progiem XOR](struktury_danych/segment_tree/minimum_maksimum_i_prog_sortowania_xor.cc). Po każdej zmianie punktowej wyznacza minimalny próg k, dla którego można posortować tablicę zamianami indeksów i,j spełniających i XOR j<=k.
- [Binarne trie xor z indeksem](struktury_danych/trie_xor/najblizsza_para_z_progiem.cc). Znajduje najkrótszy przedział zawierający parę o XOR co najmniej k. dla k=0 wypisuje 1, przy braku pary −1.
- [Zachłanne bity ze stanem tight/loose](zachlanne/konstrukcja_bitowa/maksymalna_suma_liczb_z_zadanym_xor.cc). Zbudować k nieujemnych liczb <=n o XOR-ze n i możliwie największej sumie.

<a id="minimum"></a>

## Chcę znaleźć minimum lub maksimum przez podział na stany

Zapisz znaczenie dp i wszystkie decyzje prowadzące do stanu. Wybierz minimum dla kosztu i maksimum dla zysku. Dla podziału na bloki stanem bywa długość prefiksu, a dla budżetu dodatkowa wykorzystana suma. Oddziel koszt przejścia od kolejności przetwarzania.

- [Kwadratowy przegląd z bieżącym maksimum przedziału](brute_force/maksima_przedzialow/maksimum_polaczenia_dwoch_profili_przez_maksimum_przedzialu.cc). Obliczyć max(0,max_{i<=j}(cnt[i]+cnt[j]-cnt[argmax a[i..j]])), gdzie cnt[i]=sum_t(h-max a[min(i,t)..max(i,t)]).
- [Podtablice bez powtórzeń i kolejne wartości](brute_force/zbiory_kolejnych_wartosci/wykrywanie_podtablic_bedacych_przedzialami_wartosci.cc). Znaleźć największe L, dla którego zakresy wartości [x,x+L-1] i [x+L,x+2L-1] są oba reprezentowane przez pewne podtablice wejścia będące ich permutacjami.
- [Amortyzowane DP grup stanów w mapie](dp/amortyzowane_grupowanie_mapa/agregacja_stanow_koncowych_przez_scalanie_mapy.cc). Zsumować po wszystkich końcach r wartości aktywnych stanów początków, aktualizowanych regułą progową zależną od a[r] i a[r-1].
- [Liniowe minimum po dwóch poprzednich prefiksach](dp/dp_prefiksowe/minimalny_koszt_prefiksu_z_dwoma_poprzednikami.cc). Minimalizuje liczbę bezpośrednich ataków zadających po jednym obrażeniu, potrzebnych do zniszczenia stosu potworów o zdrowiach h[i]. Uwzględnia dodatkowe obrażenia powstające przy spadaniu stosu.
- [Top-down DP po dzielnikach i sito SPF](dp/dzielniki_pierwsze_memoizacja/memoizacja_kosztu_po_dzielnikach_pierwszych.cc). Obliczyć sumę f(a[i]), gdzie f(x)=0 dla x<=k, a f(x)=min_{p pierwsze,p|x}(1+p*f(x/p)).
- [Enumeracja globalnego parametru przed DP](dp/enumeracja_parametru_globalnego/minimalne_zmiany_po_ustaleniu_koncowej_liczby_liter.cc). Minimalizować odległość Hamminga do napisu L/R z końcową liczbą L równą parametrowi L i warunkami. przy R pozostaje >=k przyszłych L, przy L wystąpiło już >=k R.
- [DP, aktywacja offline i maksimum prefiksowe](dp/fenwick_aktywacja_offline/maksymalna_suma_z_odstepami_przez_zdarzenia_i_fenwicka.cc). Znaleźć maksymalną sumę a po wybranych rosnących indeksach, gdzie sąsiednie wybrane j<i spełniają i-j>max(a[i],a[j]). pusty wybór dopuszcza wynik 0.
- [Kadane od prawej i zliczanie dobrych początków](dp/kadane_od_prawej/kadane_od_prawej.cc). Policzyć indeksy i, dla których istnieje j>=i z dodatnią sumą a[i..j].
- [DP kafelkowania 2xn z pamięcią stałą](dp/kafelki_dwa_wiersze/pokrycie_dwoch_wierszy_dominami_z_minimalnym_kosztem.cc). Pokryć planszę 2xm dominami, minimalizując liczbę domin obejmujących dwie różne litery.
- [DP z kosztem będącym maksimum po ścieżce](dp/minimalizacja_maksimum/minimalny_szczyt_ograniczonego_bilansu.cc). Wybrać F/T na pozycjach N, aby zmaksymalizować liczbę F minus najwyższy osiągnięty bilans, gdzie F zwiększa bilans, a T zmniejsza do minimum 0.
- [Dwustanowe DP zbioru niezależnego na ścieżce](dp/niezalezne_pozycje_sciezki/maksymalny_niezalezny_zbior_wewnetrznych_pozycji.cc). Zminimalizować liczbę zastąpionych znaków u, zostawiając tylko u wewnątrz napisu i bez dwóch sąsiednich pozostawionych u.
- [DP z budżetem i rekordowym poziomem](dp/optymalizacja_maksimum_prefiksowe/dp_etapow_z_maksimum_prefiksowym.cc). Maksymalizować sumę length*level po etapach maksymalnej wartości prefiksu, płacąc nowy poziom przy jego ścisłym podniesieniu i nie przekraczając budżetu k.
- [Plecak dwuwymiarowy z rekonstrukcją bloków](dp/plecak_rekonstrukcja/plecak_dlugosci_blokow_z_odtwarzaniem_permutacji.cc). Zbudować permutację n elementów o dokładnie k inwersjach w rodzinie rosnących bloków ustawionych malejąco według wartości.
- [DP podziału cyklu na bloki długości 2 i 3](dp/podzial_cyklu/podzial_cyklu_na_pary_i_trojki.cc). Zminimalizować sumę rozstępów bloków długości 2/3 dzielących cykliczny ciąg.
- [DP segmentacji z prefiksowym testem mediany](dp/podzial_na_dobre_przedzialy/podzial_na_nieparzyste_bloki_o_wspolnej_medianie.cc). Maksymalizować liczbę nieparzystych bloków dzielących całą tablicę, z medianą każdego równą górnej medianie całej tablicy.
- [DP z przedziałami i dominacją](dp/przedzialy/otwarte_przedzialy_stanow_i_dominacja.cc). Dla kolejnych odległości d między punktami wybiera dodatnie wartości r_i, spełniające r_(i-1)+r_i<=d, i maksymalizuje liczbę wybranych równości.

<a id="prog"></a>

## Chcę znaleźć największy możliwy lub najmniejszy wystarczający próg

Binary search po odpowiedzi wymaga monotonicznego testu wykonalności. Uzasadnij, w którą stronę zmienia się odpowiedź testu. Całkowity koszt to liczba prób pomnożona przez koszt checkera. lower_bound służy także do znalezienia sąsiada w uporządkowanych danych.

- [MEX i zachłanny warunek wykonalności](binary_search/dopasowanie/maksymalny_mex_i_zachlanne_dopasowanie.cc). Znajduje największy MEX osiągalny przez pokrycie brakujących wartości za pomocą dostępnych duplikatów i większych liczb o progach floor((x-1)/2).
- [Binary search z izolacją punktów i zachłannym parowaniem](binary_search/izolowane_punkty_i_zachlanne_parowanie/izolowane_punkty_i_zachlanne_parowanie.cc). Dla posortowanych punktów a znaleźć najmniejsze k w 1..10^9, dla którego po usunięciu punktów mających sąsiada w odległości <=k pozostałe punkty da się podzielić na najwyżej x jedno- lub dwuosobowych grup. para wymaga odległości <=2k.
- [Maksymalizacja wspólnego progu z sumowanym kosztem](binary_search/maksymalny_wspolny_prog_kosztu/maksymalny_wspolny_prog_kosztu.cc). Zmaksymalizować x w zakresie [minimum sum trójek, minimum+k], gdy suma kosztów trójek jest najwyżej k. koszt dla sumy<x określają jawne gałęzie check.
- [Binary search MEX z zapotrzebowaniem od wysokich poziomów](binary_search/mex_skompresowanych_licznosci_i_podwajanie_potrzeb/mex_skompresowanych_licznosci_i_podwajanie_potrzeb.cc). Wyznaczyć największą liczbę, która może kiedykolwiek wystąpić w multizbiorze po dowolnej liczbie operacji zastąpienia niepustej wybranej kolekcji jednym elementem równym jej MEX-owi. wejście podaje pary wartość i liczność.
- [Najbliższy element do różnicy pary](binary_search/najblizszy_element_do_roznicy/najblizszy_element_do_roznicy.py). Obliczyć minimum dostępnego elementu po jednej lub dwóch operacjach dopisania bezwzględnej różnicy dwóch liczb. dla k>=3 kod zwraca zero.
- [Przydział wolnego następcy i bisekcja parametru](binary_search/odpowiedz_i_zachlanny_przydzial/bisekcja_minimalnego_przesuniecia_z_przydzialem_nastepnika.cc). Po wyznaczeniu różnych b[i]>=a[i] znaleźć minimalne t, dla którego liczby min(a[i]+t,b[i]) mają krotności <=k.
- [Pierwszy dzień przekroczenia sumy cyklicznej](binary_search/pierwszy_dzien_osiagniecia_progu/pierwszy_dzien_osiagniecia_progu.py). Znaleźć najmniejszy dzień d z sumą cyklicznych przyrostów a,b,c co najmniej n.
- [Sortowanie ułamków bez błędów zmiennoprzecinkowych](binary_search/porownywanie_ulamkow_iloczynem/porownywanie_ulamkow_iloczynem.cc). Obliczyć modulo 998244353 sumę po i<j liczby uporządkowanych par p!=q z b[q]/b[p]<a[i]/a[j], podzieloną przez n(n-1).
- [Prefiksy sąsiednich par i binary search w zapytaniu](binary_search/prefiksy_par_i_monotoniczne_rownanie/prefiksy_par_i_monotoniczne_rownanie.cc). Dla każdego fragmentu domkniętego w cykl znaleźć najmniejsze m>=c01 spełniające m-c01>=max(0,c00-m)+max(0,c11-m) i wypisać 4*m-długość.
- [Binary search sumy ilorazów i konstrukcja bloków](binary_search/suma_wielokrotnosci_i_konstrukcja_blokow/suma_wielokrotnosci_i_konstrukcja_blokow.cc). Znaleźć minimalne k z sumą po i=1..k wartości i*floor(k/i)>=n, a potem utworzyć n etykiet w blokach długości i z co najwyżej floor(k/i) blokami danego rozmiaru.

<a id="kolejnosc"></a>

## Chcę uporządkować dane lub wykorzystać ich kolejność

Sortowanie może ujawnić sąsiednie wartości, grupy i pary skrajnych elementów. Stos monotoniczny pomaga utrzymywać kandydatów na ekstrema. Przed sortowaniem sprawdź, czy wolno zmienić kolejność danych i czy trzeba zachować oryginalne indeksy.

- [Sortowanie i zużywanie par skrajnych](dwa_wskazniki/parowanie_skrajnych_po_sortowaniu/parowanie_skrajnych_po_sortowaniu.cc). Obliczyć sum(a)-n*c powiększoną o dodatnie niedobory c-a[i] dla co najwyżej floor(n/2) najmniejszych wartości poniżej c.
- [Stabilny merge sort](sortowanie/merge_sort/stabilne_sortowanie_przez_scalanie.cc). Sortuje tablicę przez rekurencyjny podział na połowy i stabilne scalanie.
- [Sortowanie bloków różnic](sortowanie/roznice/sortowanie_blokow_roznic_tego_samego_typu.cc). Odtwarza tablicę po posortowaniu sąsiednich różnic osobno w każdym maksymalnym bloku tej samej parzystości.
- [Utrzymywanie m największych elementów przez scalanie](sortowanie/scalanie_top_m_sufiksu_wierszy/scalanie_top_m_sufiksu_wierszy.cc). Dla każdego sufiksu wierszy znaleźć najmniejszą dodatnią liczbę największych wartości potrzebną do osiągnięcia progu v[r] i zwrócić minimum po wierszach, z domyślnym wynikiem m.
- [Stos monotoniczny i sumy maksimów dla wszystkich obrotów](stos_monotoniczny/sumy_maksimow_dla_obrotow/sumy_maksimow_dla_obrotow.cc). Dla każdego obrotu cyklicznej tablicy h obliczyć sumę min(max(h[0..k]),max(h[k+1..n-1])) po n-1 cięciach.
- [Normalizacja przez odjęcie indeksu](tablice/normalizacja/ciag_kolejnych_wartosci_po_odjeciu_indeksu.cc). Znajduje długość najdłuższego łańcucha kolejnych różnych wartości w multizbiorze a[i]-i.

<a id="konstrukcja"></a>

## Chcę odtworzyć rozwiązanie lub zbudować poprawny obiekt

Samo istnienie rozwiązania nie wystarcza do jego wypisania. Zapamiętaj poprzednika w DP albo utrzymuj niezmiennik, który pozwala dobierać kolejne elementy. W konstrukcjach sprawdź też liczbę wypisanych elementów, powtórzenia i legalność każdej operacji.

- [Enumeracja początku deterministycznego ciągu](konstrukcje/enumeracja_poczatku_rekurencji/enumeracja_dwoch_pierwszych_bitow_rekurencji.cc). Policzyć uzupełnienia znaków ? spełniające a[i]=a[i-2] xor 1.
- [Rekonstrukcja z różnic grup](konstrukcje/grupowanie/rekonstrukcja_wartosci_z_roznic_grup.cc). Odtwarza rosnące wartości przypisane równym kluczom b, tak aby różnica kolejnych kluczy była iloczynem wartości i rozmiaru poprzedniej grupy.
- [Odtwarzanie etykiet po wskazaniu poprzednika](konstrukcje/odtwarzanie_poprzednika/rekonstrukcja_etykiet_z_roznic_prefiksowych.cc). Odtworzyć ciąg etykiet według prev=i-(b[i]-b[i-1]). nowa etykieta dla prev=0, inaczej etykieta pozycji prev.
- [Okresowa konstrukcja o stałej sumie okna](konstrukcje/okresowa_sekwencja_o_stalej_sumie/okresowa_sekwencja_o_stalej_sumie.cc). Dla k<=m utworzyć dodatni ciąg długości n, w którym każde pełne okno długości k ma sumę m. dla k>m wypisać NO.
- [Wstawianie indeksów przy ograniczeniach liczby większych](konstrukcje/wstawianie_do_kolejnosci/rekonstrukcja_kolejnosci_przez_wstawianie.cc). Zbudować permutację q tak, by dla każdego i dokładnie d[i] indeksów j>i z p[j]>p[i] znajdowało się na prawo od i w kolejności wyznaczonej q.
- [Podział kolejnych kroków i wypukła reszta](konstrukcje/wypukla_reszta/podzial_krokow_i_zbalansowanie_reszty.cc). Rozdziela kolejne kroki 1..m między dwa zasoby x i y. Maksymalizuje liczbę pełnych kroków m, a potem minimalizuje sumę kwadratów pozostałych zasobów. Wypisuje przydział X/Y w kolejności kroków od m do jednego.
- [Rekurencja ruchów na trzech palikach](rekurencja/hanoi_z_parametrem/rekurencyjne_przenoszenie_stosow_z_pominietym_prefiksem.cc). Wygenerować listę trójek (numer,s,t) przez podaną rekurencję dla parametrów 0<=a[i]<=i.

<a id="zachlanne"></a>

## Chcę wybierać zasoby, terminy lub pary

Zachłanność wymaga uzasadnienia lokalnego wyboru. Szukaj argumentu wymiany, zachowania największej rezerwy dla przyszłych decyzji albo szczególnej własności danych. W przykładach warunki dotyczą m.in. nominałów, progów i kolejności zasobów.

- [Kopiec k najmniejszych prefiksu](struktury_danych/kopiec/najmniejsze_elementy_prefiksu.cc). Maksymalizuje m*a[i] minus sumę m−1 najmniejszych poprzedników a[i]. dla m=1 zwraca maksimum.
- [Zachłanny wybór globalnych maksimów i dwa końce](zachlanne/dwa_konce_i_parzystosc/przydzial_maksimow_do_dwoch_koncow_z_parzystoscia.cc). Sprawdzić, czy sekwencję elementów pobieranych malejąco z klas parzystości oryginalnego indeksu można przydzielać do dwóch końców, naprzemiennie wymagających klasy 0/1.
- [Przenoszenie elementów do większości przy wypukłym koszcie](zachlanne/koncentracja_licznosci/maksymalizacja_wypuklej_funkcji_dwoch_licznosci.cc). Po zmianie najwyżej k bitów zmaksymalizować 1+z(z+1)/2+o(o+1)/2, gdzie z,o są końcowymi licznościami znaków.
- [Mediana minimalizuje sumę odległości](zachlanne/mediana/minimalizacja_sumy_odleglosci.py). Znajduje minimalną sumę odległości trzech punktów na osi do wspólnego miejsca spotkania.
- [Kanoniczny zestaw nominałów](zachlanne/nominaly_kanoniczne/zachlanne_rozmienianie_nominalow_kanonicznych.cc). Wyznaczyć minimalną liczbę nominałów 100,20,10,5,1 sumujących się do nieujemnego x.
- [Pakiety dodatniego zysku i kolejka progów](zachlanne/pakiety_i_kolejka/zyskowne_pakiety_transakcji_z_progami_kapitalu.cc). Dla wielu łańcuchów transakcji i kapitału x znaleźć największy osiągalny prefiks jednego łańcucha po możliwości korzystania z pozostałych. wypisać długość i pierwszy indeks osiągający maksimum.
- [Podział według parzystości i prefiksy największych wartości](zachlanne/parzystosc_i_prefiksy/wyniki_dla_wszystkich_licznosci_z_podzialem_na_parzystosc.cc). Wyznaczyć dokładną tablicę ans[k] implementacji z największą nieparzystą i malejącymi prefiksami parzystych. Dla O=0 wszystkie wyniki są 0.
- [Zachłanne pakowanie jednakowych bloków w serie zer](zachlanne/serie_zer/upakowanie_blokow_z_jednodniowa_przerwa.cc). Zsumować maksymalną liczbę bloków długości k w seriach zer przy co najmniej jednym dniu przerwy między blokami.
- [Osiągalność przez sąsiednie wysokości](zachlanne/sortowanie/osiagalnosc_po_rosnacych_wysokosciach.cc). Sprawdza, czy od wysokości wybranej wieży można dotrzeć do największej wysokości bez przekroczenia dopuszczalnej różnicy.
- [Malejąca kolejność i terminy darmowych usunięć](zachlanne/sortowanie_i_symulacja/darmowe_usuniecia_przy_podwajaniu_wag.cc). Dla dodatnich wag i progu c zminimalizować liczbę płatnych usunięć, gdy pozostałe wagi podwajają się po każdym usunięciu, a wagę >c usuwa się płatnie.
- [Zachłanny wzrost zasobu ze wspólnym budżetem](zachlanne/sortowanie_zasob/wzrost_zasobu_z_ograniczonym_budzetem_inwestycji.cc). Po posortowaniu nieujemnych a zwiększać zasób c przez dostępne elementy a[i]<=c, inwestując w element najwyżej min(k,c-a[i]) jednostek wspólnego budżetu k. wypisać końcowe c.
- [Uporządkowane dopasowanie pozycji jedynek](zachlanne/uporzadkowane_dopasowanie/dopasowanie_jedynek_w_klasach_parzystosci.cc). Sprawdzić zgodność liczby jedynek w każdej klasie parzystości i obliczyć minimalną sumę przemieszczeń o dwa pola.
- [Wielozbiór progów i wymiana przez lower_bound](zachlanne/wielozbior_progow/wymiana_progow_przedzialowych_w_wielozbiorze.cc). Po każdej parze [l,r] podać rozmiar wielozbioru progów minus jeden zgodnie z regułą implementacji.
- [Zachłanny skan dla ustalonej długości podciągu](zachlanne/wybor_podciagu_dla_dlugosci/wybor_podciagu_po_ustaleniu_docelowej_dlugosci.cc). Znaleźć największe m zaakceptowane przez skan. wybierany element i na pozycji cnt+1 od lewej i m-cnt od prawej musi leżeć poza zakazami [l[i],r[i]] i [u[i],v[i]].

<a id="arytmetyka"></a>

## Chcę uprościć obliczenia przez NWD, dzielniki lub wzór

NWD opisuje klasy osiągalnych reszt. Dzielniki rozpatruj parami do pierwiastka. Przy iloczynach będących kwadratami wystarczy parzystość wykładników pierwszych. Szukaj też teleskopowania i odcinków, na których wynik dzielenia jest stały.

- [Dopasowanie dwóch liniowych wzorców](matematyka/dwa_wspolczynniki/dwa_wspolczynniki.cc). Sprawdzić istnienie nieujemnych całkowitych x,y takich, że a[i]=x(i+1)+y(n-i).
- [Agregacja po dzielnikach](matematyka/dzielniki/agregacja_wielokrotnosci_dzielnikow.cc). Liczy największą sumę elementów tablicy podzielnych przez wybrany dzielnik x większy niż jeden.
- [Enumeracja par dzielników](matematyka/dzielniki/maksimum_po_parach_dzielnikow.cc). Znajduje największą parzystą wartość a*d+b/d po dodatnich dzielnikach d liczby b.
- [Niezmiennik klas reszt](matematyka/nwd/niezmiennik_klas_reszt_permutacji.cc). Sprawdza, czy każdy element permutacji należy do tej samej klasy modulo gcd(x,y), co jego docelowa pozycja.
- [NWD i osiągalność na cyklu](matematyka/nwd/osiagalnosc_na_cyklu_modulo.cc). Znajduje największą wartość osiągalną od a przez wielokrotne dodanie b modulo l.
- [Potęgowanie binarne modulo](matematyka/potegowanie/potegowanie_binarne_modulo.cc). Oblicza 2^(rows*columns-(rows-scanRows+1)*(columns-scanColumns+1)) modulo 998244353.
- [Rdzeń bezkwadratowy i prefiksy](matematyka/rozklad_na_czynniki/rdzen_bezkwadratowy_i_parzystosc_prefiksow.cc). Dla każdego niepustego prefiksu liczy elementy całej tablicy, których iloczyn z iloczynem prefiksu jest kwadratem. Sumuje te liczby.
- [Suma reszt ze stałym ogonem](matematyka/sumowanie/staly_ogon_sumy_reszt.cc). Oblicza sumę (y-x) modulo (x+i) dla i od 0 do k-1.
- [Teleskopowanie sumy różnic](matematyka/teleskopowanie/minimalizacja_sumy_roznic.cc). Uzupełnia nieznane wartości tak, aby zminimalizować wartość bezwzględną sumy sąsiednich różnic.
- [Przedziały zawierające punkt i zerowy XOR kolejnych liczb](matematyka/zliczanie_klas_modulo_cztery/zliczanie_klas_modulo_cztery.cc). Policzyć modulo 998244353 pary 0<=l<x<=r<=n takie, że XOR kolejnych liczb l+1..r jest zerowy.

<a id="czestosci"></a>

## Chcę policzyć wystąpienia, pary lub brakującą wartość

Mała dziedzina wartości pasuje do tablicy częstości, a duża do mapy. Zbiór przechowuje obecność, zaś multiset także liczbę kopii. Przy liczeniu par sprawdź, czy elementy mogą się pokrywać i czy kolejność par ma znaczenie.

- [Globalne częstości słów](struktury_danych/czestosci/punktowanie_globalnych_czestosci_slow.py). Dla trzech list słów liczy globalne wystąpienia i przyznaje każdej pozycji 3 punkty za częstość 1, 1 za częstość 2, w pozostałych przypadkach 0.
- [Równe sygnatury i wykluczenie nakładania](struktury_danych/zliczanie_par/rowne_sygnatury_bez_nakladania.cc). Policzyć pary rozłącznych trójdźwięków na pozycjach (i,i+2,i+4), mających równą sygnaturę a[i]+a[i+2]−a[i+4].
- [Premia za pierwsze wystąpienie](zbiory/pierwsze_wystapienie/liczenie_premii_za_nowy_element.py). Sumuje 2 za pierwsze wystąpienie znaku i 1 za każde kolejne, czyli długość napisu plus liczbę różnych znaków.
- [MEX ograniczonej domeny](zliczanie/mex/mex_przez_tablice_obecnosci.cc). Wypisuje pierwszą nieobecną liczbę spośród 0..100 lub 101, ignorując wartości poza 0..100.

<a id="optymalizacja"></a>

## Chcę przyspieszyć rozwiązanie lub zmniejszyć pamięć

### Wielokrotnie sumuję ten sam fragment tablicy

Dla niezmiennych danych przygotuj prefiksy w O(n). Sumę odcinka otrzymasz przez dwa odczyty i odejmowanie w O(1).

Przykład [Sumowanie odcinków wyznaczonych punktami cięcia](sumy_prefiksowe/sumy_odcinkow_po_cieciach/sumy_odcinkow_po_cieciach.cc).

### Aktualizuję wartości i ponownie przeliczam sumy

Przy punktowym dodawaniu i sumach prefiksowych Fenwick daje O(log n) na operację. Przy dodawaniu do całego zakresu i sumach zakresów wybierz segment tree z lazy propagation.

Przykład [Dodawanie na przedziale i suma przedziału](struktury_danych/segment_tree/dodawanie_na_przedziale_i_suma.cc).

### Każdy stan DP przegląda wszystkich poprzedników

Jeśli zbiór legalnych poprzedników jest prefiksem i można zaplanować moment ich aktywacji, Fenwick z maksimum zastąpi skan zapytaniem O(log n). Najpierw wyprowadź warunki legalności przejścia.

Przykład [DP, aktywacja offline i maksimum prefiksowe](dp/fenwick_aktywacja_offline/maksymalna_suma_z_odstepami_przez_zdarzenia_i_fenwicka.cc).

### DP zużywa pamięć na wszystkie wcześniejsze pozycje

Jeśli przejścia korzystają wyłącznie z dwóch poprzednich stanów i nie odtwarzasz ścieżki, możesz przechowywać tylko te stany. Przykład kafelkowania używa O(1) pamięci DP.

Przykład [DP kafelkowania 2xn z pamięcią stałą](dp/kafelki_dwa_wiersze/pokrycie_dwoch_wierszy_dominami_z_minimalnym_kosztem.cc).

### Boolowski plecak jest zbyt wolny

Gdy chodzi o osiągalność sum, bitset wykonuje wiele przesunięć i operacji OR maszynowo. Wariant z powtarzalnymi wagami dodatkowo pakuje ich liczności binarnie. Sprawdź limit liczby bitów.

Przykład [Bitset plecaka i pakowanie binarne](drzewa/plecak_warstw/bitset_i_pakowanie_binarnie.cc).

### Trzymam wiele stanów, które niczego nie poprawiają

Stan o niegorszym wyniku i zawierającym zbiorze dalszych możliwości dominuje drugi. Można usunąć stan zdominowany. Samo usuwanie dominacji nie daje jeszcze gwarancji małej liczby stanów.

Przykład [DP z przedziałami i dominacją](dp/przedzialy/otwarte_przedzialy_stanow_i_dominacja.cc).

### Osobno liczę wkład każdego początku i końca

Poszukaj odcinków ze stałym lub liniowym wkładem. Tablice różnicowe współczynnika i wyrazu wolnego pozwalają dodać funkcję liniową do przedziału i odczytać końcowe wyniki jednym skanem.

Przykład [Następne wystąpienia i liniowe wkłady przedziałów](napisy/nastepne_wystapienia/podciagi_i_liniowe_wklady_przedzialow.cc).

### Powtarzam dzielenie dla ogromnej liczby kandydatów

Połącz zakresy argumentów o tym samym ilorazie i sumuj je zbiorczo. Zysk zależy od liczby różnych ilorazów i granic konkretnego zadania.

Przykład [Histogram i harmoniczne grupowanie ilorazów](sumy_prefiksowe/grupowanie_po_ilorazach/grupowanie_po_ilorazach.cc).

### Po jednej zmianie przeliczam cały koszt

Wyodrębnij składniki dotknięte zmianą. Przy usunięciu elementu z sumy odległości znikają dwie sąsiednie różnice i pojawia się jedna nowa. Koszt kandydata policzysz w O(1) po przygotowaniu sumy.

Przykład [Lokalna zmiana kosztu po usunięciu](tablice/wklad_lokalny/usuniecie_elementu_a_suma_roznic.cc).

### Uruchamiam obliczenia osobno dla każdego korzenia drzewa

Rerooting przenosi wynik między sąsiednimi korzeniami. W tym przykładzie wszystkie odpowiedzi można zagregować w O(n), wykorzystując rozmiary poddrzew i wkład obu stron krawędzi.

Przykład [Rerooting liczby dużych poddrzew](drzewa/rerooting/liczba_duzych_poddrzew.cc).

Katalog według nazw technik znajduje się w [README](README.md#katalog-przykładów). Aby sprawdzić aktualność tego przewodnika, uruchom `python3 narzedzia/grupuj_zastosowania.py --check`.
