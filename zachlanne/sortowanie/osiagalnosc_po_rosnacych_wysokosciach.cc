// Osiągalność przez sąsiednie wysokości
//
// Oryginał w zbiorze codeforces/2126/sorting/2126C.cc
// https://codeforces.com/contest/2126
//
// Co oblicza kod
//
// Sprawdza, czy od wysokości wybranej wieży można dotrzeć do największej wysokości bez przekroczenia dopuszczalnej różnicy.
//
// Pomysł
//
// Posortuj wysokości. Pomiń mniejsze od początkowej i sprawdź każdy kolejny skok, bo pomijanie pośrednich wież powiększa wymagany skok.
//
// Stan i niezmiennik
//
// cur jest ostatnią rozpatrzoną wysokością. dist pozostaje początkową wysokością. Każda różnica kolejnych wysokości musi być nie większa niż dist.
//
// Złożoność
//
// O(n log n) czasu i O(n) pamięci.
//
// Przypadki brzegowe
//
// - Powtórzone wysokości dają skok zero.
// - Start na maksimum od razu spełnia warunek.
//
// Kiedy rozpoznać ten wariant
//
// Gdy przechodzenie przez wszystkie pośrednie wartości minimalizuje największy skok.
//
// KONIEC OPISU
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
void solve()
{
    int num, my;
    cin >> num >> my;
    bool ans = true;

    vector<int> v(num + 1); 

    for (int i = 1; i <= num; ++i) {
        cin >> v[i];
    }

    int cur = v[my];
    int dist = v[my];

    sort(v.begin() + 1, v.end());

    for (int i = 1; i <= num; ++i) {
        if(v[i] < cur) continue;

        if (v[i] - cur > dist) {
            ans = false;
        }

        cur = v[i];     // teleportujesz się do tej wieży
    }

    if (ans) cout << "YES\n";
    else cout << "NO\n";
}

int main() 
{
    int t;
    cin >> t;
    while(t--) solve();
    return 0;
}