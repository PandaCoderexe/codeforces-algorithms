// Dopasowanie dwóch liniowych wzorców
//
// Oryginał w zbiorze codeforces/2117/binary_search/2117D.cc
// https://codeforces.com/contest/2117
//
// Co oblicza kod
//
// Sprawdzić istnienie nieujemnych całkowitych x,y takich, że a[i]=x(i+1)+y(n-i).
//
// Pomysł
//
// Z pierwszych dwóch równań wyznacz y=(2*a[0]-a[1])/(n+1) oraz x=a[1]-a[0]+y. następnie sprawdź każdy element zamiast ufać dzieleniu całkowitemu.
//
// Stan i niezmiennik
//
// Przy n>=2 pierwsze dwa równania wyznaczają jedyną parę współczynników. Końcowe odejmowanie obu wzorców akceptuje wyłącznie dokładne rozwiązanie całkowite.
//
// Złożoność
//
// O(n) czasu i O(n) pamięci na wejście.
//
// Przypadki brzegowe
//
// n=1 odwołuje się do a[1] poza zakresem. Przy niedzielnym liczniku końcowa weryfikacja zwraca NO. Iloczyny współczynników i indeksów muszą mieścić się w long long.
//
// Kiedy rozpoznać ten wariant
//
// Tablica ma powstać jako kombinacja dwóch znanych progresji. rozwiązuj mały układ równań i weryfikuj całość.
//
// Warunki i uwagi
//
// - To algebra, bez binary search. Wymaga n>=2; końcowa weryfikacja wykrywa także niedzielny licznik we wzorze na y.
//
// KONIEC OPISU
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

void solve() {
    ll n;
    cin >> n;
    vector<ll> v(n);
    for(auto &it : v) cin >> it;

    ll y = (2 * v[0] - v[1]) / (n + 1);
    ll x = v[1] - v[0] + y;

    if(y < 0 || x < 0) {
        cout << "NO" << endl;
        return;
    }

    for(int i = 0; i < n; i++) {
        v[i] -= x * (i + 1);
        v[i] -= y * (n - i);
    }

    for(int i = 0; i < n; i++) {
        if(v[i] != 0) {
            cout << "NO" << endl;
            return;
        }
    }

    cout << "YES" << endl;
}

int main() {
    int t;
    cin >> t;
    while(t--) solve();
}