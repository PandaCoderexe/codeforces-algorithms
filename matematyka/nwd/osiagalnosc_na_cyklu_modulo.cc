// NWD i osiągalność na cyklu
//
// Oryginał w zbiorze codeforces/2180/implementation/2180A.cc
// https://codeforces.com/contest/2180
//
// Co oblicza kod
//
// Znajduje największą wartość osiągalną od a przez wielokrotne dodanie b modulo l.
//
// Pomysł
//
// Osiągalne reszty są dokładnie zgodne z a modulo gcd(l,b). Znajdź największą taką liczbę nie większą niż l-1.
//
// Stan i niezmiennik
//
// Każdy ruch zachowuje resztę modulo g. Działanie na cyklu osiąga wszystkie l/g wartości z tej klasy.
//
// Złożoność
//
// O(log(min(l,b))) czasu na NWD i O(1) pamięci.
//
// Przypadki brzegowe
//
// - Gdy g=1, osiągalne jest l-1.
// - Gdy krok jest wielokrotnością l, osiągalne pozostaje a.
//
// Kiedy rozpoznać ten wariant
//
// Gdy ruchy dodają stały krok na okręgu albo operacje zachowują klasę reszty.
//
// KONIEC OPISU
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int l, a, b;
        cin >> l >> a >> b;
        int g = std::gcd(l, b);

        int diff = (l - 1 - a);          // >= 0
        int r = diff % g;
        int ans = (l - 1) - r;

        cout << ans << "\n";
    }
    return 0;
}
