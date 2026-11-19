// Suma reszt ze stałym ogonem
//
// Oryginał w zbiorze codeforces/2260/math/2260B.cc
// https://codeforces.com/contest/2260
//
// Co oblicza kod
//
// Oblicza sumę (y-x) modulo (x+i) dla i od 0 do k-1.
//
// Pomysł
//
// Iteruj tylko po mianownikach nie większych od d=y-x. Dla każdego większego mianownika reszta wynosi d, więc cały ogon dodaj jednym mnożeniem.
//
// Stan i niezmiennik
//
// Po zakończeniu pętli każdy nieprzetworzony mianownik jest większy od d, a jego wkład jest stały.
//
// Złożoność
//
// O(min(k,max(0,y-2*x+1))) iteracji arytmetycznych i O(1) pamięci.
//
// Przypadki brzegowe
//
// - Wymagane x>0 i y>=x.
// - Dla x>d cała suma jest stałym ogonem.
// - Iloczyn (k-i)*d musi mieścić się w long long.
//
// Kiedy rozpoznać ten wariant
//
// Gdy po przekroczeniu progu wszystkie dalsze składniki sumy upraszczają się do tej samej wartości.
//
// KONIEC OPISU
#include <bits/stdc++.h>
#define ll long long

using namespace std;

void solve()
{
    ll x, y, k; cin >> x >> y >> k;
    ll d = y - x, ans = 0, i = 0;
    while (i < k && x + i <= d)
    {
        ans += d % (x + i);
        i++;
    }

    ans += (k - i) * d;
    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}