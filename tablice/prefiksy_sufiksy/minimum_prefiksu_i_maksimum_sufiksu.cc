// Rozdzielające cięcie tablicy
//
// Oryginał w zbiorze codeforces/2171/ds/2171D.cc
// https://codeforces.com/contest/2171
//
// Co oblicza kod
//
// Wypisuje No, gdy istnieje cięcie z każdym lewym elementem większym od każdego prawego. inaczej Yes.
//
// Pomysł
//
// Zbudować prefMin i suffMax, a następnie sprawdzić każde cięcie przez prefMin[k]>suffMax[k+1].
//
// Stan i niezmiennik
//
// prefMin[k] jest minimum całej lewej części, suffMax[k+1] maksimum całej prawej. nierówność dowodzi, że każdy lewy element przewyższa każdy prawy.
//
// Złożoność
//
// O(n) czasu i O(n) pamięci.
//
// Przypadki brzegowe
//
// n≥1. tablica rosnąca. malejąca. jeden element. równości, jeśli dopuszczone.
//
// Kiedy rozpoznać ten wariant
//
// Warunek między wszystkimi parami po obu stronach cięcia można sprowadzić do dwóch ekstremów.
//
// Warunki i uwagi
//
// - Nie używa DSU.
//
// KONIEC OPISU
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> p(n);
        for (int i = 0; i < n; ++i) cin >> p[i];

        vector<int> prefMin(n), suffMax(n);

        prefMin[0] = p[0];
        for (int i = 1; i < n; ++i)
            prefMin[i] = min(prefMin[i-1], p[i]);

        suffMax[n-1] = p[n-1];
        for (int i = n-2; i >= 0; --i)
            suffMax[i] = max(suffMax[i+1], p[i]);

        bool bad = false;
        for (int k = 0; k < n-1; ++k) {
            if (prefMin[k] > suffMax[k+1]) {
                bad = true;
                break;
            }
        }

        cout << (bad ? "No\n" : "Yes\n");
    }
    return 0;
}
