// Lokalna zmiana kosztu po usunięciu
//
// Oryginał w zbiorze codeforces/2179/implementation/2179B.cc
// https://codeforces.com/contest/2179
//
// Co oblicza kod
//
// Minimalizuje sumę bezwzględnych różnic kolejnych elementów po usunięciu co najwyżej jednego elementu.
//
// Pomysł
//
// Policz pełny koszt. Usunięcie wewnętrznego elementu usuwa dwie krawędzie i dodaje jedną łączącą sąsiadów. Końce rozpatrz osobno.
//
// Stan i niezmiennik
//
// Dla pozycji k nowy koszt to S-|a[k-1]-a[k]|-|a[k]-a[k+1]|+|a[k-1]-a[k+1]|.
//
// Złożoność
//
// O(n) czasu i O(n) pamięci na tablicę.
//
// Przypadki brzegowe
//
// - Jednoelementowa tablica daje zero.
// - Usuwanie początku i końca ma tylko jeden składnik kosztu.
// - Długie różnice wymagają long long.
//
// Kiedy rozpoznać ten wariant
//
// Gdy jedna operacja zmienia tylko kilka składników globalnej funkcji kosztu.
//
// KONIEC OPISU
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;
using ll = long long;

static inline ll absl(ll x) { return x < 0 ? -x : x; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<ll> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        if (n <= 1) {
            cout << 0 << "\n";
            continue;
        }

        ll S = 0;
        for (int i = 0; i < n - 1; i++) {
            S += absl(a[i] - a[i + 1]);
        }

        ll ans = S; 


        ans = min(ans, S - absl(a[0] - a[1]));

        ans = min(ans, S - absl(a[n - 2] - a[n - 1]));

        for (int k = 1; k <= n - 2; k++) {
            ll removed = absl(a[k - 1] - a[k]) + absl(a[k] - a[k + 1]);
            ll added = absl(a[k - 1] - a[k + 1]);
            ll S2 = S - removed + added;
            ans = min(ans, S2);
        }

        cout << ans << "\n";
    }
    return 0;
}
