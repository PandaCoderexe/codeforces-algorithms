// Sortowanie bloków różnic
//
// Oryginał w zbiorze codeforces/2252/sorting/2252D.cc
// https://codeforces.com/contest/2252
//
// Co oblicza kod
//
// Odtwarza tablicę po posortowaniu sąsiednich różnic osobno w każdym maksymalnym bloku tej samej parzystości.
//
// Pomysł
//
// Zamień tablicę na różnice a[i]-a[i-1]. Podziel je przy każdej zmianie parzystości, posortuj każdą grupę i odtwórz wartości przez sumy prefiksowe.
//
// Stan i niezmiennik
//
// Pierwsza wartość pozostaje ustalona, a suma różnic w każdym bloku zachowuje jego koniec. Zmienia się tylko kolejność różnic wewnątrz bloku.
//
// Złożoność
//
// O(n log n) czasu i O(n) pamięci.
//
// Przypadki brzegowe
//
// - Kod wymaga n>=2.
// - Parzystość ujemnej różnicy jest testowana przez !=0.
// - Granice między typami różnic pozostają ustalone.
//
// Kiedy rozpoznać ten wariant
//
// Gdy dozwolone operacje na tablicy odpowiadają przestawianiu sąsiednich różnic wewnątrz rozłącznych grup.
//
// Warunki i uwagi
//
// - Implementacja wymaga n>=2 z powodu odczytu diff[1].
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve()
{
    int n; cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<ll> diff(n+1);
    for (int i = 1; i < n; i++) diff[i] = a[i] - a[i-1];
    
    vector<vector<ll>> g;
    g.push_back(vector<ll>());
    g[0].push_back(diff[1]);
    int pointer = 0;
    bool parity = (diff[1] % 2 != 0);
    for (int i = 2; i < n; i++)
    {
        if (parity == (diff[i] % 2 != 0))
        {
            g[pointer].push_back(diff[i]);
        }
        else 
        {
            g.push_back(vector<ll>());
            pointer++;
            parity = (diff[i] % 2 != 0);
            g[pointer].push_back(diff[i]);
        }
    }

    for (int i = 0; i < (int)g.size(); i++)
    {
        sort(g[i].begin(), g[i].end());
    }

    ll cur = a[0];
    cout << cur << " ";
    for (vector<ll>& group : g)
    {
        for (int j = 0; j < (int)group.size(); j++)
        {
            cout << cur + group[j] << " ";
            cur += group[j];
        }
    }
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) solve();
}