// Uporządkowane dopasowanie pozycji jedynek
//
// Oryginał w zbiorze codeforces/2254/greedy/2254C2.cc
// https://codeforces.com/contest/2254
//
// Co oblicza kod
//
// Sprawdzić zgodność liczby jedynek w każdej klasie parzystości i obliczyć minimalną sumę przemieszczeń o dwa pola.
//
// Pomysł
//
// Rozdzielić pozycje modulo 2. W każdej klasie dopasować j-tą jedynkę źródła do j-tej jedynki celu. skrzyżowane dopasowania nie zmniejszają sumy odległości.
//
// Stan i niezmiennik
//
// Liczności w każdej klasie są niezmiennikiem osiągalności. Po dopasowaniu pierwszych j pozycji ich koszt jest sumą |a_pos-b_pos|/2 i nie ma potrzeby zmieniać kolejności.
//
// Złożoność
//
// Czas O(n), pamięć O(n). pozycje są już posortowane przez skan.
//
// Przypadki brzegowe
//
// Brak jedynek. nierówne liczności dają -1. pozycje tej samej parzystości zapewniają całkowite dzielenie przez 2.
//
// Kiedy rozpoznać ten wariant
//
// Obiekty na prostej są nierozróżnialne, ruch zachowuje klasę modulo, a koszt jest odległością. wystarcza monotoniczne dopasowanie.
//
// Warunki i uwagi
//
// - Interpretacja jako liczby legalnych ruchów wymaga, by dozwolone operacje były odpowiednimi zamianami pozycji odległych o 2; kod sam oblicza koszt transportu.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve()
{
    int n;
    cin >> n;

    string a, b;
    cin >> a >> b;

    vector<int> a_[2], b_[2];
    for (int i = 0; i < n; i++)
    {
        if (a[i] == '1') a_[i % 2].push_back(i);
        if (b[i] == '1') b_[i % 2].push_back(i);
    }

    if (a_[0].size() != b_[0].size() || a_[1].size() != b_[1].size())
    {
        cout << -1 << '\n';
        return;
    }

    ll ans = 0;
    for (int i = 0; i<2; i++)
    {
        for (int j = 0; j < (int)a_[i].size(); j++) ans += abs(a_[i][j] -b_[i][j])/2;
    }
    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}