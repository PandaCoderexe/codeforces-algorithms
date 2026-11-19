// DP ścieżek z poprzednią wartością
//
// Oryginał w zbiorze codeforces/2176/dp/2176D.cc
// https://codeforces.com/contest/2176
//
// Co oblicza kod
//
// Zliczyć skierowane ścieżki z >=2 wierzchołkami, na których każda wartość od trzeciej jest sumą dwóch poprzednich.
//
// Pomysł
//
// Posortować wierzchołki po wartości. Każda krawędź u->v zaczyna nową ścieżkę i może przedłużać dp[u][a[v]-a[u]]. zapisać wynik pod poprzednią wartością a[u].
//
// Stan i niezmiennik
//
// dp[v][y] zlicza ścieżki kończące się w v z przedostatnią wartością y. Dla krawędzi add=1+dp[u][a[v]-a[u]], drugi składnik tylko przy a[v]>a[u]. ans sumuje add modulo MOD.
//
// Złożoność
//
// O(n log n+m) oczekiwanego czasu i O(n+m) pamięci. wrogie haszowanie unordered_map może pogorszyć czas do kwadratowego.
//
// Przypadki brzegowe
//
// Wartości dodatnie zapewniają rosnący porządek po rozpoczęciu rekurencji. powtarzające wartości i różni poprzednicy agregują się po kluczu. Krawędzie równoległe są liczone osobno.
//
// Kiedy rozpoznać ten wariant
//
// Warunek ścieżki dotyczy dwóch kolejnych wartości, ale można grupować cały stan poprzednika według jednej wartości i porządkować zależności monotonicznie.
//
// Warunki i uwagi
//
// - Porządek po wartości zapewnia zależności tylko dla dodatnich wartości a[v]; zera lub wartości ujemne zmieniają poprawność. unordered_map daje złożoność oczekiwaną.
//
// KONIEC OPISU
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353LL;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) {
        return 0;
    }

    while (T--) {
        int n, m;
        cin >> n >> m;

        vector<long long> a(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }


        vector<vector<int>> in(n + 1);
        in.reserve(n + 1);

        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            in[v].push_back(u);
        }


        vector<int> order(n);
        iota(order.begin(), order.end(), 1);
        sort(order.begin(), order.end(),
             [&](int x, int y) {
                 if (a[x] == a[y]) return x < y;
                 return a[x] < a[y];
             });


        vector<unordered_map<long long, int>> dp(n + 1);


        for (int v = 1; v <= n; ++v) {
            if (!in[v].empty()) {
                dp[v].reserve(in[v].size());
            }
        }

        long long ans = 0;


        for (int v : order) {
            long long z = a[v];          

            auto &mpV = dp[v];

            for (int u : in[v]) {
                long long y = a[u];     
                long long add = 1;      

                if (z > y) {
                    long long x = z - y; 
                    auto &mpU = dp[u];
                    auto it = mpU.find(x);
                    if (it != mpU.end()) {
                        add += it->second;
                        if (add >= MOD) add -= MOD;
                    }
                }

                ans += add;
                if (ans >= MOD) ans -= MOD;

                int &ref = mpV[y];       
                ref += (int)add;
                if (ref >= MOD) ref -= MOD;
            }
        }

        cout << (ans % MOD) << '\n';
    }

    return 0;
}
