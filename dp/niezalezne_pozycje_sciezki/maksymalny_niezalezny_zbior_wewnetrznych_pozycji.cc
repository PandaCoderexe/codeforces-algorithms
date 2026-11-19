// Dwustanowe DP zbioru niezależnego na ścieżce
//
// Oryginał w zbiorze codeforces/2178/dp/goodbye2025B.cc
// https://codeforces.com/contest/2178
//
// Co oblicza kod
//
// Zminimalizować liczbę zastąpionych znaków u, zostawiając tylko u wewnątrz napisu i bez dwóch sąsiednich pozostawionych u.
//
// Pomysł
//
// Maksymalizować liczbę pozostawionych u. Stan 0 oznacza niewybraną poprzednią pozycję, stan 1 wybraną. wybranie obecnej wymaga poprzedniego stanu 0.
//
// Stan i niezmiennik
//
// ndp0=max(dp0,dp1), ndp1=dp0+1 tylko dla wewnętrznego u. dp0/dp1 przechowują optimum po przetworzonym prefiksie. odpowiedź totalU-max(dp0,dp1).
//
// Złożoność
//
// Czas O(n), O(1) stanów DP, O(n) pamięci napisu.
//
// Przypadki brzegowe
//
// Napisy długości 1/2 nie pozwalają zachować żadnego u. Inne znaki są niewybieralne i rozdzielają konflikty. NEG oznacza stan niemożliwy.
//
// Kiedy rozpoznać ten wariant
//
// Wybieramy dozwolone pozycje z zakazem sąsiedztwa. zamiast minimalizować usunięcia maksymalizujemy pozostawione elementy.
//
// KONIEC OPISU
#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        string r;
        cin >> r;
        int n = (int)r.size();

        int totalU = 0;
        for (char c : r) if (c == 'u') totalU++;

        const int NEG = -1e9;
        int dp0 = 0, dp1 = NEG;

        for (int i = 0; i < n; i++) {
            int ndp0 = max(dp0, dp1);
            int ndp1 = NEG;

            // można zostawić 'u' tylko w środku (nie na końcach) i tylko jeśli to faktycznie 'u'
            if (i > 0 && i < n - 1 && r[i] == 'u') {
                ndp1 = dp0 + 1;
            }

            dp0 = ndp0;
            dp1 = ndp1;
        }

        int keep = max(dp0, dp1);
        int ans = totalU - keep;
        cout << ans << "\n";
    }
    return 0;
}
