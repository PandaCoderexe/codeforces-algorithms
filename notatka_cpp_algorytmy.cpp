/*NOTATKA C++17 - BITY, TUPLE, SORTOWANIE, POTEGOWANIE, MACIERZE, DP NA DRZEWIE
================================================================================

0. PODSTAWY
------------
Przyklady zakladaja:
    #include <bits/stdc++.h>
    using namespace std;

Typy:
    int              zwykle 32 bity
    long long        zwykle 64 bity (ze znakiem)
    unsigned long long 64 bity (bez znaku)


1. BITY I MASKI BITOWE
---------------------
Maska to liczba, w ktorej bit i koduje informacje 0/1 (np. czy element i nalezy do zbioru).
Bity sa numerowane od 0. Dla n elementow maski maja wartosci od 0 do (1<<n)-1.

Operatory:
    a & b   AND: 1 tylko gdy oba bity sa 1
    a | b   OR:  1 gdy przynajmniej jeden bit jest 1
    a ^ b   XOR: 1 gdy bity sa rozne
    ~a      NOT: odwraca WSZYSTKIE bity typu
    a << k  przesuniecie w lewo (dla bezpiecznych wartosci: razy 2^k)
    a >> k  przesuniecie w prawo (dla nieujemnych: przez 2^k)

Przyklad: a=10 (1010), b=12 (1100)
    a&b = 8  (1000)
    a|b = 14 (1110)
    a^b = 6  (0110)

Najwazniejsze operacje (i = numer bitu):
    bool jest = (mask & (1LL << i)) != 0;  // sprawdzenie
    mask |= (1LL << i);                    // ustaw bit na 1
    mask &= ~(1LL << i);                   // wyzeruj bit
    mask ^= (1LL << i);                    // przelacz bit
    long long bit = 1LL << i;              // maska z jednym bitem

Zwykle dla masek 64-bitowych lepiej stosowac 1ULL << i i unsigned long long.
Nie rob 1 << i dla i >= 31 na 32-bitowym int; i musi byc mniejsze od szerokosci typu.

Przydatne wzory:
    int ile = __builtin_popcount((unsigned)mask);      // jedynki w 32 bitach
    int ile64 = __builtin_popcountll((unsigned long long)mask);
    int pierwszy = __builtin_ctzll(mask);               // indeks najmniej znaczacej 1, mask != 0!
    mask & (mask - 1)                                   // usuwa najnizszy ustawiony bit
    mask & -mask                                        // izoluje najnizszy ustawiony bit (dla niezerowej maski)

Wszystkie n-bitowe maski (dla umiarkowanego n, tutaj n < 31):
    for (int mask = 0; mask < (1 << n); ++mask) {
        // przetworz wybrany podzbior
    }

Iteracja po ustawionych bitach (maska typu unsigned long long):
    for (unsigned long long x = mask; x; x &= x - 1) {
        int i = __builtin_ctzll(x);
        // element i nalezy do zbioru
    }

Wszystkie NIEZEROWE podmaski mask (od najwiekszej do najmniejszej):
    for (int s = mask; s; s = (s - 1) & mask) {
        // s jest podmaska mask
    }
    // Pusta podmaska 0 nie jest tu uwzgledniona.
    // Aby uwzglednic 0: przetworz ja osobno.

Uzupelnienie w zakresie n bitow:
    int all = (1 << n) - 1;
    int brakujace = all ^ mask;  // rownowaznie: (~mask) & all

Zlozonosci:
    wszystkie maski: O(2^n)
    wszystkie podmaski kazdej maski lacznie: O(3^n)
    iteracja po ustawionych bitach: O(liczba jedynek)

Typowe zastosowania: reprezentacja podzbiorow, subset DP, stany z ograniczona liczba
flag 0/1, testowanie przynaleznosci i dzialania na zbiorach.


2. PAIR I TUPLE
---------------
    pair<int,int> p = {4, 9};
    cout << p.first << " " << p.second;

    tuple<int,int,string> t = {2, 7, "abc"};
    cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t);
    get<1>(t) = 10;                        // zmiana elementu

    auto t2 = make_tuple(3, 5, 'x');
    auto p2 = make_pair(8, 1);

    auto [a, b, napis] = t;               // structured bindings (C++17): kopia
    auto& [x, y, z] = t;                  // referencje: modyfikuja t

    int a1, b1;
    string c1;
    tie(a1, b1, c1) = t;                 // rozpakowanie istniejacych zmiennych
    tie(a1, ignore, c1) = t;             // pomin srodkowy element

Porownywanie pair/tuple jest LEKSYKOGRAFICZNE:
    najpierw pierwszy element; przy remisie drugi; przy remisie trzeci itd.
    (1, 9) < (2, 0)            -> true
    (1, 4, 8) < (1, 5, 0)      -> true

Przydatne w sortowaniu i jako klucze set/map:
    vector<tuple<int,int,int>> v = {{2,1,9}, {1,5,3}, {1,2,7}};
    sort(v.begin(), v.end());            // rosnaco leksykograficznie
    sort(v.begin(), v.end(), greater<>()); // malejaco leksykograficznie

    set<tuple<int,int,int>> s;
    map<pair<int,int>, long long> mp;
    mp[{2,5}] = 10;


3. SORTOWANIE: sort, set, map, greater, KOMPARATORY
-----------------------------------------------------
A) sort sortuje elementy kontenera o iteratorach random access (np. vector, array).
   Nie sortuje bezposrednio set ani map.

    vector<pair<int,int>> v = {{2,3},{1,9},{2,1}};
    sort(v.begin(), v.end());              // (1,9), (2,1), (2,3)
    sort(v.begin(), v.end(), greater<>()); // (2,3), (2,1), (1,9)

B) Wlasna kolejnosc: lambda. Zwraca true, gdy a powinno byc PRZED b.
   Przyklad: malejaco po second, przy remisie rosnaco po first.

    sort(v.begin(), v.end(), [](const auto& a, const auto& b) {
        if (a.second != b.second) return a.second > b.second;
        return a.first < b.first;
    });

   To samo dla tuple: po drugim rosnaco, potem pierwszym malejaco,
   potem trzecim rosnaco:

    vector<tuple<int,int,int>> vt;
    sort(vt.begin(), vt.end(), [](const auto& a, const auto& b) {
        if (get<1>(a) != get<1>(b)) return get<1>(a) < get<1>(b);
        if (get<0>(a) != get<0>(b)) return get<0>(a) > get<0>(b);
        return get<2>(a) < get<2>(b);
    });

C) Wlasny komparator jako funkcja (dla sort):

    bool cmp(const pair<int,int>& a, const pair<int,int>& b) {
        if (a.second != b.second) return a.second > b.second;
        return a.first < b.first;
    }
    // w main: sort(v.begin(), v.end(), cmp);

D) Wlasny komparator dla set (funktor, czyli typ z operator()):

    struct Cmp {
        bool operator()(const pair<int,int>& a,
                        const pair<int,int>& b) const {
            if (a.second != b.second) return a.second > b.second;
            return a.first < b.first;
        }
    };
    set<pair<int,int>, Cmp> st;
    st.insert({1,4});
    st.insert({2,4});

    set<int, greater<int>> malejaco;       // 9, 7, 3, ...
    set<pair<int,int>, greater<>> paryMalejaco;

E) map sortuje KLUCZE (nie wartosci):

    map<int, string, greater<int>> m1;     // klucze malejaco
    map<pair<int,int>, int, Cmp> m2;       // klucze wg Cmp

   Jesli chcesz posortowac map po WARTOSCIACH, skopiuj elementy do vector:

    map<int,int> m = {{2,7}, {1,3}, {4,7}};
    vector<pair<int,int>> a(m.begin(), m.end());
    sort(a.begin(), a.end(), [](const auto& x, const auto& y) {
        if (x.second != y.second) return x.second > y.second;
        return x.first < y.first;
    });

UWAGA: Komparator musi okreslac SPOJNY SCISLY PORZADEK (strict weak ordering).
    cmp(a,a) musi byc false;
    dla rownych w sensie porzadku obie strony sa false;
    nie uzywaj <= ani >= jako ostatniego porownania.

W set/map dwa klucze sa traktowane jako rownowazne, gdy
    !cmp(a,b) && !cmp(b,a).
Jesli porownujesz pary TYLKO po second, rozne pary z tym samym second
moga byc uznane za ten sam klucz! Dodaj rozstrzyganie remisu.

Zlozonosci:
    sort: O(n log n)
    set/map (drzewiaste): find/insert/erase O(log n)
    unordered_map/unordered_set: srednio O(1), bez porzadku sortowania


4. SZYBKIE POTEGOWANIE (BINARY EXPONENTIATION)
-----------------------------------------------
Chcemy a^b. Zamiast b mnozen korzystamy z bitow wykladnika:
    gdy bit b jest 1, dokladamy aktualna potege a do wyniku;
    w kazdym kroku a = a*a, b = b/2.

    long long modpow(long long a, long long b, long long MOD) {
        long long res = 1 % MOD;
        a %= MOD;
        while (b > 0) {
            if (b & 1LL) res = res * a % MOD;
            a = a * a % MOD;
            b >>= 1;
        }
        return res;
    }

Przyklad: 3^13 = 3^(8+4+1) -> wybieramy potegi 3^8, 3^4, 3^1.
Zlozonosc: O(log b) mnozen, pamiec O(1).
Zalozenia: b >= 0, MOD > 0; zwykle MOD <= 1e9+7, aby mnozenie long long
nie przepelnilo sie. Dla bardzo duzego MOD potrzebne bezpieczne mnozenie.
Bez modulo mozna liczyc tak samo, ale bardzo latwo przekroczyc zakres typu.


5. MNOZENIE MACIERZY I POTEGOWANIE MACIERZY
--------------------------------------------
Macierz A rozmiaru n x n: C = A*B, gdzie
    C[i][j] = suma(A[i][k] * B[k][j]) po wszystkich k.

Macierz jednostkowa I ma jedynki na przekatnej, zera poza nia:
    I*A = A*I = A.

Kod dla kwadratowych macierzy n x n, modulo MOD:

    using Mat = vector<vector<long long>>;
    const long long MOD = 1000000007LL;

    Mat identity(int n) {
        Mat I(n, vector<long long>(n, 0));
        for (int i = 0; i < n; ++i) I[i][i] = 1;
        return I;
    }

    Mat multiply(const Mat& A, const Mat& B) {
        int n = (int)A.size();
        Mat C(n, vector<long long>(n, 0));
        for (int i = 0; i < n; ++i)
            for (int k = 0; k < n; ++k)
                for (int j = 0; j < n; ++j)
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
        return C;
    }

    Mat matrixPower(Mat A, long long e) {
        int n = (int)A.size();
        Mat R = identity(n);
        while (e > 0) {
            if (e & 1LL) R = multiply(R, A);
            A = multiply(A, A);
            e >>= 1;
        }
        return R;
    }

    // A^0 = I, A^1 = A, A^k = A*A*...*A.

Zlozonosci:
    zwykle mnozenie macierzy n x n: O(n^3), pamiec O(n^2)
    szybkie potegowanie macierzy: O(n^3 log e), pamiec O(n^2)

Skad zastosowania? Dla liniowych przejsc:
    stan(t+1) = A * stan(t), wiec stan(t) = A^t * stan(0).
To pozwala szybko przeskakiwac ogromna liczbe krokow, jesli wymiar stanu
jest maly i staly.

Przyklad Fibonacci:
    [F(k+1)]   [1 1] [F(k)  ]
    [F(k)  ] = [1 0] [F(k-1)]

Dla F(0)=0, F(1)=1:
    A = {{1,1},{1,0}};
    F(n) = (A^n)[0][1]  (dla n >= 0).

Uwaga: dla macierzy kolejnosc mnozenia ma znaczenie (A*B zwykle != B*A).
W potegowaniu jednej macierzy R i A sa potegami tej samej A, ale ogolnie
nie wolno zamieniac kolejnosci mnozenia roznych macierzy.


6. DP NA DRZEWIE - JAK WYMYSLAC STANY I PRZEJSCIA
---------------------------------------------------
Podstawowy pomysl: ukorzen drzewo (np. w 0). Dzieki temu kazdy wierzcholek
ma rodzica i dzieci, a poddrzewa dzieci sa rozlaczne.

SCHEMAT MYSLENIA:
1) Co liczymy? Zdefiniuj precyzyjnie wynik (liczba sposobow, maksimum, minimum).
2) Co jest podproblemem? Najczesciej "odpowiedz dla poddrzewa u".
3) Jaka informacja z zewnatrz poddrzewa moze wplynac na wynik?
   Zwykle tylko sytuacja na krawedzi (rodzic, u) lub wybor w samym u.
4) Dodaj do stanu TYLKO informacje potrzebne do polaczenia z rodzicem.
5) Zastanow sie, jakie decyzje dzieci sa dozwolone dla kazdego stanu u.
6) Polacz wyniki dzieci (sumowanie dla maksimum, mnozenie dla liczby
   niezaleznych wyborow, czasem knapsack po dzieciach).
7) Ustal przypadek liscia, wynik w korzeniu i kolejnosc obliczania: dzieci przed u.
8) Udowodnij, ze podzial obejmuje wszystkie mozliwosci bez podwojnego liczenia.

PRZYKLAD: liczba zbiorow niezaleznych w drzewie (modulo MOD).
Zbior niezalezny = wybrane wierzcholki, ale zadne dwa sasiednie nie sa wybrane.

Stan:
    dp[u][0] = liczba poprawnych wyborow w poddrzewie u, gdy u NIE jest wybrane.
    dp[u][1] = liczba poprawnych wyborow w poddrzewie u, gdy u JEST wybrane.

Przejscia dla kazdego dziecka v wierzcholka u:
    jesli u nie wybrane: dziecko v moze byc wybrane lub nie,
       dp[u][0] *= (dp[v][0] + dp[v][1]);
    jesli u wybrane: dziecko v musi byc niewybrane,
       dp[u][1] *= dp[v][0].

Poczatkowo dp[u][0] = dp[u][1] = 1, bo pusty iloczyn = 1 (lisc).
Wynik: (dp[root][0] + dp[root][1]) % MOD.

    const long long MOD = 1000000007LL;
    vector<vector<int>> g;
    vector<array<long long, 2>> dp;

    void dfs(int u, int parent) {
        dp[u][0] = dp[u][1] = 1;
        for (int v : g[u]) {
            if (v == parent) continue;
            dfs(v, u);
            dp[u][0] = dp[u][0] * ((dp[v][0] + dp[v][1]) % MOD) % MOD;
            dp[u][1] = dp[u][1] * dp[v][0] % MOD;
        }
    }
    // po zbudowaniu g i dp.resize(n): dfs(0, -1);
    // odpowiedz = (dp[0][0] + dp[0][1]) % MOD;

DLACZEGO TO DZIALA?
    Krawedz u-v zabrania tylko kombinacji (u=1, v=1).
    Po ustaleniu stanu u wybor w roznych poddrzewach dzieci jest niezalezny.
    Stad mnozymy liczby sposobow dla dzieci, ale dla kazdego dziecka
    dopuszczamy tylko kompatybilne stany.

WARIANT: maksymalna LICZEBNOSC zbioru niezaleznego, zamiast liczby sposobow:
    dp[u][0] = suma po dzieciach v: max(dp[v][0], dp[v][1]);
    dp[u][1] = 1 + suma po dzieciach v: dp[v][0];
    wynik = max(dp[root][0], dp[root][1]).
Zwracaj uwage, co znaczy stan: liczbe konfiguracji laczy sie mnozeniem,
a wartosci maksimum zwykle dodawaniem po niezaleznych poddrzewach.

KIEDY POTRZEBA WIECEJ STANOW?
    - Gdy decyzja rodzica wymaga wiedzy np. o odleglosci, liczbie wybranych
      wierzcholkow lub stanie krawedzi do rodzica.
    - Jesli dp[u][k] opisuje dokladnie k wybranych w poddrzewie,
      przy laczeniu dzieci moze pojawic sie miniknapsack.
    - Jesli odpowiedz ma dotyczyc KAZDEGO mozliwego korzenia,
      warto rozwazyc rerooting (DP w dol i przekazywanie wplywu z gory).

KONTROLA POPRAWNOSCI DP:
    - Czy stan zawiera wszystkie informacje potrzebne rodzicowi?
    - Czy decyzje dla roznych dzieci sa niezalezne po ustaleniu stanu u?
    - Czy przejscie nie liczy tej samej konfiguracji dwa razy?
    - Czy znasz wynik dla liscia oraz jak odczytac wynik z korzenia?
    - Czy kazda krawedz i kazdy wierzcholek sa przetwarzane oczekiwana
      liczbe razy?

Zlozonosc przy 2 stanach i stalym koszcie na dziecko: O(n) czasu i O(n)
pamieci (plus stos rekurencji do O(n)). Na bardzo glebokim drzewie DFS
rekurencyjny moze przepelnic stos - wtedy uzyj iteracyjnego DFS i
przetwarzania w odwrotnej kolejnosci odwiedzin (postorder).


7. MINI-SCIAGA: NAJCZESTSZE POMYLKI
----------------------------------
- "1 << i" dla duzego i: uzyj 1LL/1ULL i sprawdz szerokosc typu.
- "~mask" odwraca tez bity POZA zakresem n: ogranicz przez & ((1<<n)-1).
- __builtin_ctz(0) / __builtin_ctzll(0): wynik niezdefiniowany.
- pair/tuple porownuja sie leksykograficznie, nie np. po sumie elementow.
- sort nie dziala bezposrednio na set/map: kolejnosc ustala komparator typu.
- set/map: komparator okresla tez rownowaznosc kluczy; pamietaj o remisach.
- cmp(a,a) == true lub uzycie <= w komparatorze psuje porzadek.
- Szybkie potegowanie modulo: kontroluj przepelnienie przy mnozeniu.
- Potegowanie macierzy startuje od I, nie od macierzy zerowej.
- W DP na drzewie stan musi mowic, CO DOKLADNIE liczy; przejscie
  wynika z tego, ktore stany dzieci sa kompatybilne ze stanem rodzica.
*/