// Rekonstrukcja z różnic grup
//
// Oryginał w zbiorze codeforces/2254/math/2254D.cc
// https://codeforces.com/contest/2254
//
// Co oblicza kod
//
// Odtwarza rosnące wartości przypisane równym kluczom b, tak aby różnica kolejnych kluczy była iloczynem wartości i rozmiaru poprzedniej grupy.
//
// Pomysł
//
// Pogrupuj klucze mapą. Dla sąsiednich grup podziel różnicę kluczy przez liczność wcześniejszej. Sprawdź podzielność i ścisły wzrost otrzymanych wartości.
//
// Stan i niezmiennik
//
// Dla grupy i musi zachodzić b_(i+1)-b_i=count_i*value_i. Ostatnia grupa może dostać wartość o jeden większą od poprzedniej.
//
// Złożoność
//
// O(n log n) czasu i O(n) pamięci.
//
// Przypadki brzegowe
//
// - Najmniejszy klucz musi wynosić zero.
// - Jedna grupa dostaje wartość jeden.
// - Niepodzielna różnica lub brak ścisłego wzrostu daje -1.
//
// Kiedy rozpoznać ten wariant
//
// Gdy skumulowane statystyki są stałe w grupach, a różnice są iloczynem nieznanej wartości i znanej liczności.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve()
{
    int n; cin >> n;

    vector<ll> b(n);
    map<ll, int> cnt;
    for (int i = 0; i < n; i++)
    {
        cin >> b[i];
        cnt[b[i]]++;
    }
    if (cnt.begin()->first != 0)
    {
        cout << -1 << '\n';
        return;
    }

    vector<pair<ll, int>> g(cnt.begin(), cnt.end());
    map<ll, ll> value;

    ll prev = 0;
    for (int i = 0; i + 1 < (int)g.size(); i++)
    {
        ll diff = g[i + 1].first-g[i].first; 
        ll c = g[i].second;

        if (diff % c != 0)
        {
            cout << -1 <<'\n';
            return;
        }

        ll cur = diff / c;

        if (cur <= prev)
        {
            cout << -1<<'\n'; 
            return;
        }

        value[g[i].first] = cur;
        prev = cur;
    }

    if ((int)g.size() == 1) value[0] =1;
    else value[g.back().first] = prev+1;
    for (ll x : b) cout<<value[x]<< ' ';

    cout << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}