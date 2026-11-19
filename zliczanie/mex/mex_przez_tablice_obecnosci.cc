// MEX ograniczonej domeny
//
// Oryginał w zbiorze codeforces/2160/ds/2160A.cc
// https://codeforces.com/contest/2160
//
// Co oblicza kod
//
// Wypisuje pierwszą nieobecną liczbę spośród 0..100 lub 101, ignorując wartości poza 0..100.
//
// Pomysł
//
// Zaznaczyć wystąpienia wartości 0..100, następnie przesuwać mex od 0, dopóki pozycja jest obecna.
//
// Stan i niezmiennik
//
// Wszystkie liczby mniejsze od bieżącego mex wystąpiły. pierwsza nieobecna kończy wyszukiwanie.
//
// Złożoność
//
// O(n+102) czasu i O(102) pamięci, czyli stałej dla tej domeny.
//
// Przypadki brzegowe
//
// Domena wartości 0..100. brak zera. wszystkie wartości 0..100. wielokrotne wystąpienia.
//
// Kiedy rozpoznać ten wariant
//
// Najmniejsza nieujemna brakująca wartość w małej ograniczonej dziedzinie.
//
// Warunki i uwagi
//
// - Kontrakt: wartości należą do 0..100; 101 jest dodatkowym zawsze wolnym miejscem kończącym wyszukiwanie. Kod celowo ignoruje wartości poza domeną.
//
// KONIEC OPISU
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; 
    if (!(cin >> t)) return 0;
    while (t--) {
        int n; cin >> n;
        vector<int> cnt(102, 0);
        for (int i = 0; i < n; ++i) {
            int x; cin >> x;
            if (0 <= x && x <= 100) cnt[x]++;
        }
        int mex = 0;
        while (mex <= 101 && cnt[mex] > 0) ++mex;
        cout << mex << '\n';
    }
    return 0;
}

