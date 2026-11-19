// Sumy sąsiedztwa na cyklu przez potrojenie tablicy
//
// Oryginał w zbiorze codeforces/2239/suffixPrefix_sum/2239B.cc
// https://codeforces.com/contest/2239
//
// Co oblicza kod
//
// Obliczyć sumę max(0,2*d*a[i]-suma d poprzednich-suma d następnych wartości) dla wszystkich pozycji cyklu.
//
// Pomysł
//
// Powiel tablicę trzykrotnie, umieść badaną pozycję w środkowej kopii i policz obie sumy sąsiedztwa różnicami prefiksów.
//
// Stan i niezmiennik
//
// pref[r]-pref[l] jest sumą półotwartego przedziału [l,r). dla pos=i+n oba sąsiedztwa mają dokładnie d elementów i pomijają środek.
//
// Złożoność
//
// O(n) czasu i O(n) pamięci.
//
// Przypadki brzegowe
//
// Potrojenie zapewnia bezpieczne indeksy dla 0<=d<=n. większe d może wyjść poza tablicę. d=0 daje 0. Przy d=n oba sąsiedztwa zawierają po jednej pełnej kopii cyklu.
//
// Kiedy rozpoznać ten wariant
//
// Masz wiele stałej długości okien wokół każdej pozycji na cyklu i chcesz uniknąć oddzielnej obsługi zawijania.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve()
{
    int n, d;
    cin >> n >> d;

    vector<ll> a(n);
    for (ll &x : a) cin >> x;

    vector<ll> b(3 * n);
    for (int i = 0; i < 3 * n; i++)
        b[i] = a[i % n];

    vector<ll> pref(3 * n + 1, 0);

    for (int i = 0; i < 3 * n; i++)
        pref[i + 1] = pref[i] + b[i];

    ll ans = 0;

    for (int i = 0; i < n; i++)
    {
        int pos = i + n;

        ll left_sum = pref[pos] - pref[pos - d];
        ll right_sum = pref[pos + d + 1] - pref[pos + 1];

        ll value = 2LL * d * a[i] - left_sum - right_sum;

        ans += max(0LL, value);
    }

    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();
}