// Niezmiennik klas reszt
//
// Oryginał w zbiorze codeforces/2244/implementation/2244C.cc
// https://codeforces.com/contest/2244
//
// Co oblicza kod
//
// Sprawdza, czy każdy element permutacji należy do tej samej klasy modulo gcd(x,y), co jego docelowa pozycja.
//
// Pomysł
//
// Oblicz g algorytmem Euklidesa. Dla każdej pozycji porównaj i%g z p[i]%g.
//
// Stan i niezmiennik
//
// Przesunięcia o x i y zachowują klasę modulo g. Kod sprawdza zgodność wszystkich pozycji z tym podziałem.
//
// Złożoność
//
// O(n+log(min(x,y))) czasu i O(n) pamięci.
//
// Przypadki brzegowe
//
// - Dla g=1 każdy element należy do jednej klasy.
// - Pozycje i wartości są numerowane od jednego.
//
// Kiedy rozpoznać ten wariant
//
// Gdy dozwolone przesunięcia mają stałe długości i trzeba wykryć rozłączne klasy osiągalności.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int gcd(int a, int b)
{
    while(b != 0)
    {
        int c = a % b;
        a = b;
        b = c;
    }
    return a;
}

void solve()
{
    int n, x, y;
    cin >> n >> x >> y;
    vector<int> p(n+1);
    for (int i = 1; i <= n; i++) cin >> p[i];

    int g = gcd(x, y);
    bool flag = 1;

    for (int i = 1; i <= n; i++) if (i % g != p[i] % g) flag = false;

    if (flag) cout << "YES\n";
    else cout << "NO\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--)
    {
        solve();
    }

    return 0;
}