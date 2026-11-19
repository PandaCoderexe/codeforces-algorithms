// Podział według parzystości i prefiksy największych wartości
//
// Oryginał w zbiorze codeforces/2176/greedy/2176C.cc
// https://codeforces.com/contest/2176
//
// Co oblicza kod
//
// Wyznaczyć dokładną tablicę ans[k] implementacji z największą nieparzystą i malejącymi prefiksami parzystych. Dla O=0 wszystkie wyniki są 0.
//
// Pomysł
//
// Niech O,E oznaczają liczby nieparzystych/parzystych, S[m]=maxOdd+suma m największych parzystych. Dla E>0 ustawić ans[k]=S[min(E-1,k-1)] do k=1+2*floor((O-1)/2)+E, a dla k=1+E+2j dodatkowo dopuścić S[E]. Przy E=0 tylko nieparzyste k<=1+2*floor((O-1)/2) dostają maxOdd.
//
// Stan i niezmiennik
//
// Prefiksy preE[m] są największą sumą m parzystych, bo posortowano je malejąco. Dwie rodziny indeksów k rozróżniają pełne zużycie parzystych oraz pozostawienie co najmniej jednej niewykorzystanej. pary dodatkowych nieparzystych zmieniają k o 2 bez zmiany S.
//
// Złożoność
//
// Czas O(n log n), pamięć O(n).
//
// Przypadki brzegowe
//
// Brak nieparzystych. brak parzystych. jedna nieparzysta. wyniki domyślnie 0 dla indeksów spoza dopuszczonych rodzin. Interpretacja maksymalizacji zakłada zwykle dodatnie liczby.
//
// Kiedy rozpoznać ten wariant
//
// Wyniki dla wszystkich k zależą od liczby elementów w dwóch klasach reszt i prefiksu najlepszych wartości jednej klasy.
//
// Warunki i uwagi
//
// - Bez treści zadania nie potwierdzono modelu operacji stojącego za tą tablicą; opisano dokładne rodziny indeksów i formuły kodu.
//
// KONIEC OPISU
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n;
        cin >> n;
        vector<long long> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        vector<long long> odds, evens;
        for (long long x : a) {
            if (x & 1) odds.push_back(x);
            else evens.push_back(x);
        }

        int O_total = (int)odds.size();
        int E_total = (int)evens.size();

        if (O_total == 0) {
            for (int k = 1; k <= n; ++k) {
                cout << 0 << (k == n ? '\n' : ' ');
            }
            continue;
        }

        long long bestOdd = *max_element(odds.begin(), odds.end());

        sort(evens.begin(), evens.end(), greater<long long>());


        vector<long long> preE(E_total + 1, 0);
        for (int i = 0; i < E_total; ++i)
            preE[i + 1] = preE[i] + evens[i];

        vector<long long> S(E_total + 1);
        for (int m = 0; m <= E_total; ++m)
            S[m] = bestOdd + preE[m];

        vector<long long> ans(n + 1, 0); // 1..n

        if (E_total >= 1) {
            int O_rem = O_total - 1;
            int t = O_rem / 2;
            int base_high = 1 + 2 * t + E_total;
            if (base_high > n) base_high = n;


            for (int k = 1; k <= base_high; ++k) {
                int m_max = min(E_total - 1, k - 1);

                ans[k] = S[m_max];
            }


            int M = O_rem / 2;
            for (int j = 0; j <= M; ++j) {
                int k = 1 + E_total + 2 * j;
                if (k > n) break;
                ans[k] = max(ans[k], S[E_total]);
            }
        } else {

            int O_rem = O_total - 1;
            int M = O_rem / 2;
            for (int j = 0; j <= M; ++j) {
                int k = 1 + 2 * j;
                if (k > n) break;
                ans[k] = bestOdd; // S[0]
            }
        }

        for (int k = 1; k <= n; ++k) {
            cout << ans[k] << (k == n ? '\n' : ' ');
        }
    }

    return 0;
}
