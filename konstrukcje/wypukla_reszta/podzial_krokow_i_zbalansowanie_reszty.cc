// Podział kolejnych kroków i wypukła reszta
//
// Oryginał w zbiorze codeforces/2253/math/2253D.cc
// https://codeforces.com/contest/2253
//
// Co oblicza kod
//
// Rozdziela kolejne kroki 1..m między dwa zasoby x i y. Maksymalizuje liczbę pełnych kroków m, a potem minimalizuje sumę kwadratów pozostałych zasobów. Wypisuje przydział X/Y w kolejności kroków od m do jednego.
//
// Pomysł
//
// Binary search odwraca sumę trójkątną m*(m+1)/2<=x+y. Resztę d rozdziel jak najbliżej połowy, z ograniczeniami 0<=dx<=x i 0<=dy<=y. Dla docelowej sumy p=x-dx zachłannie bierz kolejne malejące kroki do X, jeśli mieszczą się w p.
//
// Stan i niezmiennik
//
// Funkcja dx^2+(d-dx)^2 jest wypukła i minimalna przy d/2. Każdą sumę 0..m*(m+1)/2 da się złożyć z 1..m, a malejący wybór zachowuje możliwość odtworzenia pozostałej sumy.
//
// Złożoność
//
// O(log(x+y)+m) czasu i O(m) pamięci na napis wyniku.
//
// Przypadki brzegowe
//
// - Wymagane x,y>=0 i m mieszczące się w zakresie wyszukiwania 0..2*10^9.
// - Kandydatów floor(d/2) i ceil(d/2) trzeba przyciąć do dozwolonego przedziału.
// - Kwadraty reszt i x+y muszą mieścić się w long long.
//
// Kiedy rozpoznać ten wariant
//
// Gdy najpierw maksymalizujesz liczbę kolejnych kroków, potem równoważysz wypukły koszt reszty i rekonstruujesz podzbiór liczb 1..m.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve()
{
    ll x, y;
    cin >> x >> y;

    ll sum = x + y, l = 0, r = 2000000000LL;
    while (l < r)
    {
        ll m = l + (r - l + 1) / 2;
        ll s = m * (m + 1) / 2;

        if (s <= sum) l = m;
        else r = m - 1;
    }

    ll m = l;
    ll s = m * (m + 1) / 2;
    ll d = sum - s;
    ll L = max(0LL, d - y);
    ll R = min(d, x);
    ll dx1 = d / 2, dx2 = (d + 1) / 2;

    dx1 = max(L, min(R, dx1));
    dx2 = max(L, min(R, dx2));
    ll dy1 = d - dx1, dy2 = d - dx2;

    ll ans1 = dx1 * dx1 + dy1 * dy1, ans2 = dx2 * dx2 + dy2 * dy2;
    ll dx;
    if (ans1 <= ans2) dx = dx1;
    else dx = dx2;
    ll p = x - dx;

    string ans;
    for (ll val = m; val >= 1; val--)
    {
        if (p >= val)
        {
            ans += 'X';
            p -= val;
        }
        else ans += 'Y';
    }
    cout << ans << '\n';
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}