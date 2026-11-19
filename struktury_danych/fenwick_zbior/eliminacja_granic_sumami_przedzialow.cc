// Fenwick i amortyzowana eliminacja zbioru
//
// Oryginał w zbiorze codeforces/2262/bit/2262B.cc
// https://codeforces.com/contest/2262
//
// Co oblicza kod
//
// Dodaje indeksy w odwróconym p, utrzymuje zbiór granic i usuwa kolejne granice, gdy aktywna suma między granicami osiąga wagę kandydata. zapisuje rozmiar zbioru minus 1.
//
// Pomysł
//
// BIT sumuje aktywne wagi, set wyznacza poprzednią granicę. dodawać lub usuwać granice zgodnie z porównaniem sumy do wagi kandydata.
//
// Stan i niezmiennik
//
// Każdy indeks aktywowany raz jest dodawany do set najwyżej raz i usuwany najwyżej raz, co amortyzuje pętlę kasowania.
//
// Złożoność
//
// O(n log n) czasu amortyzowanego i O(n) pamięci.
//
// Przypadki brzegowe
//
// Pierwsza aktywacja. wiele usunięć. skrajne indeksy. zerowe wagi wymagają sprawdzenia założeń.
//
// Kiedy rozpoznać ten wariant
//
// Rozpoznaj wzorzec. Fenwick i amortyzowana eliminacja zbioru. BIT sumuje aktywne wagi, set wyznacza poprzednią granicę. dodawać lub usuwać granice zgodnie z porównaniem sumy do wagi kandydata.
//
// Warunki i uwagi
//
// - Interpretacja granic wymaga treści zadania i założeń o dodatnich wagach. Wymaga p będącego permutacją 1..n.
//
// KONIEC OPISU
#include <bits/stdc++.h>
#define ll long long

using namespace std;

struct Fenwick
{
    int n;
    vector<ll> bit;

    Fenwick(int n) : n(n), bit(n + 1, 0) {}

    void add(int i, ll x)
    {
        for(; i <= n; i += i & -i) bit[i] += x;
    }

    ll sum(int i)
    {
        ll res = 0;
        for(; i > 0; i -= i & -i) res += bit[i];
        return res;
    }

    ll query(int l, int r)
    {
        return sum(r) - sum(l - 1);
    }
};

void solve()
{
    int n; cin >> n;
    vector<ll> a(n + 1);
    vector<int> p(n + 1), ans(n);

    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) cin >> p[i];

    Fenwick fw(n);
    set<int> s;

    for (int i = n; i >= 1; i--)
    {
        int idx = p[i];
        fw.add(idx, a[idx]);
        auto it = s.lower_bound(idx);

        int j = 0;
        if (it != s.begin())
        {
            --it;
            j = *it;
        }

        if (fw.query(j, idx-1) < a[idx])
        {
            s.insert(idx);
            j = idx;
        }

        auto nxt = s.upper_bound(idx);
        while(nxt != s.end())
        {
            int num = *nxt;
            if (fw.query(j, num-1) < a[num]) break;
            nxt = s.erase(nxt);
        }

        ans[i-1] = (int)s.size()-1;
    }

    for (int x:ans) cout << x << " ";
    cout << "\n";
}


int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();
}