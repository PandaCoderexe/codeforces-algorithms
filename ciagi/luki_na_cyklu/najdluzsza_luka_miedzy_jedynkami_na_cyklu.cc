// Skan luk w ciągu cyklicznym
//
// Oryginał w zbiorze codeforces/2176/greedy/2176B.cc
// https://codeforces.com/contest/2176
//
// Co oblicza kod
//
// Dla napisu binarnego zawierającego co najmniej jedną jedynkę obliczyć długość najdłuższego cyklicznego odcinka zer.
//
// Pomysł
//
// Zapisać pozycje jedynek. Dla każdej pary kolejnych, także ostatniej i pierwszej, policzyć liczbę zer między nimi i wziąć maksimum.
//
// Stan i niezmiennik
//
// Każdy cykliczny odcinek zer leży dokładnie w jednej luce pomiędzy kolejnymi jedynkami. Luka niewrapująca ma długość next-cur-1, wrapująca (n-cur-1)+next.
//
// Złożoność
//
// Czas O(n), pamięć O(n) na napis i pozycje jedynek.
//
// Przypadki brzegowe
//
// Same jedynki dają 0. jedna jedynka daje n-1. jedynki przy obu końcach napisu. n=1. Dla braku jedynek kod zwraca 0, więc taki przypadek jest poza zakresem kandydata.
//
// Kiedy rozpoznać ten wariant
//
// Liniowy skan zdarzeń na cyklu wymaga osobnej pary ostatni-pierwszy. przechowywanie tylko wyróżnionych pozycji upraszcza liczenie luk.
//
// Warunki i uwagi
//
// - Wymagane istnienie co najmniej jednej jedynki. Bez tego założenia literalne 0 nie jest długością najdłuższego cyklicznego odcinka zer.
//
// KONIEC OPISU
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    vector<int> ones;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '1') ones.push_back(i);
    }

    if ((int)ones.size() == n) {
        cout << 0 << "\n";
        return;
    }

    int k = (int)ones.size();
    int best = 0;

    for (int i = 0; i < k; ++i) {
        int cur = ones[i];
        int nxt = ones[(i + 1) % k]; 

        int gap;
        if (nxt > cur) {
            gap = nxt - cur - 1;
        } else {
            gap = (n - cur - 1) + nxt;
        }
        best = max(best, gap);
    }

    cout << best << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
