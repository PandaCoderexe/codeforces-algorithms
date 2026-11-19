// Podtablice bez powtórzeń i kolejne wartości
//
// Oryginał w zbiorze codeforces/2236/dp/2236E.cc
// https://codeforces.com/contest/2236
//
// Co oblicza kod
//
// Znaleźć największe L, dla którego zakresy wartości [x,x+L-1] i [x+L,x+2L-1] są oba reprezentowane przez pewne podtablice wejścia będące ich permutacjami.
//
// Pomysł
//
// Dla każdego lewego końca rozszerzać prawy, pamiętając minimum, maksimum i powtórzenia. Bez powtórzeń warunek max-min=r-l równoważy brak luk wartości. Zapisać good[min][max], potem skanować długości malejąco.
//
// Stan i niezmiennik
//
// good[u][v] oznacza istnienie spójnej podtablicy będącej permutacją wszystkich liczb u..v. Sprawdzenie dwóch sąsiadujących zakresów dotyczy zakresów wartości, a nie sąsiedztwa położeń podtablic.
//
// Złożoność
//
// Czas O(n^2), pamięć O(n^2).
//
// Przypadki brzegowe
//
// Wymagane 1<=a[i]<=n. Po pierwszym powtórzeniu unique pozostaje false dla danej lewej granicy. Podtablice reprezentujące zakresy nie muszą leżeć obok siebie.
//
// Kiedy rozpoznać ten wariant
//
// Przedział indeksów ma tworzyć dokładnie przedział wartości. unikalność i równość rozpiętości z długością zastępują sortowanie każdej podtablicy.
//
// Warunki i uwagi
//
// - a[i] musi należeć do 1..n, bo indeksuje seen i good. O(n^2) czasu i pamięci.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int n;
    cin >> n;

    vector<int> a(n+1, 0);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<vector<bool>> good(n+1, vector<bool>(n+1, 0));
    for (int l = 1;l <= n; l++)
    {
        vector<bool> seen(n+1, 0);

        int mn = n+1;
        int mx = 0;
        bool unique = 1;

        for (int r = l; r <= n; r++)
        {
            if (seen[a[r]]) unique = 0;

            seen[a[r]] = 1;
            mn = min(mn, a[r]);
            mx = max(mx, a[r]);

            if (unique && mx - mn == r - l)
            {
                good[mn][mx] = 1;
            }
        }

    }

    for (int len = n/2; len > 0;len--)
    {
        for (int x = 1; x + 2 * len-1 <= n; x++)
        {
            if (good[x][x+len-1] && good[x+len][x + 2 * len -1])
            {
                cout << len << "\n";
                return;
            }
        }
    }

    cout << 0 << "\n";
    return;
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--)
    {
        solve();
    }

    return 0;
}