// Równe sygnatury i wykluczenie nakładania
//
// Oryginał w zbiorze codeforces/2275/dataStructures/2275C.cc
// https://codeforces.com/problemset/problem/2275/C
//
// Co oblicza kod
//
// Policzyć pary rozłącznych trójdźwięków na pozycjach (i,i+2,i+4), mających równą sygnaturę a[i]+a[i+2]−a[i+4].
//
// Pomysł
//
// Zsumować c(c−1)/2 dla częstości sygnatur. odjąć równe sygnatury o odległości startów 2 lub 4.
//
// Stan i niezmiennik
//
// Jedyne wspólne indeksy trójek i,i+2,i+4 występują przy odległości startów 2 lub 4, a każda taka para jest odjęta raz.
//
// Złożoność
//
// O(n) oczekiwanego czasu, O(n²) pesymistycznie dla unordered_map i O(n) pamięci.
//
// Przypadki brzegowe
//
// Domena n≥6 i a_i z −10000..10000. wszystkie sygnatury równe. nakładanie dla odległości startów 2 lub 4. sąsiednie starty bez wspólnych indeksów.
//
// Kiedy rozpoznać ten wariant
//
// Rozpoznaj wzorzec. równe sygnatury i wykluczenie nakładania. Zsumować c(c−1)/2 dla częstości sygnatur. odjąć równe sygnatury o odległości startów 2 lub 4.
//
// Warunki i uwagi
//
// - Potwierdzone ograniczenia oficjalne: n≥6 i −10000≤a_i≤10000. Rozmiar n−4 jest dodatni, a sygnatura mieści się w −30000..30000, więc int jest poprawny.
// - Oczekiwana liniowość wynika z unordered_map; w ogólnej analizie haszowania pesymistyczny czas może być kwadratowy.
//
// KONIEC OPISU
#include <bits/stdc++.h>
#define ll long long

using namespace std;

void solve()
{
    int n; cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    int m = n-4;
    vector<int> sum(m);
    unordered_map<ll,ll> cnt;
    for(int i = 0; i < m; i++)
    {
        sum[i] = a[i] +a[i+2] -a[i+4];
        cnt[sum[i]]++;
    }

    ll ans = 0;
    for(auto [x,c] : cnt) ans += c*(c-1)/2;
    for(int i = 0; i < m; i++)
    {
        if(i+2 < m && sum[i] == sum[i+2]) ans--;
        if(i+4 < m && sum[i] == sum[i+4]) ans--;
    }

    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();
}