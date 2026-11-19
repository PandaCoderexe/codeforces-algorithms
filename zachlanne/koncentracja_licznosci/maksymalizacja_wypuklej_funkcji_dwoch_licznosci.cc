// Przenoszenie elementów do większości przy wypukłym koszcie
//
// Oryginał w zbiorze codeforces/2285/greedy/B.cc
// https://codeforces.com/contest/2285
//
// Co oblicza kod
//
// Po zmianie najwyżej k bitów zmaksymalizować 1+z(z+1)/2+o(o+1)/2, gdzie z,o są końcowymi licznościami znaków.
//
// Pomysł
//
// Przy stałym z+o suma kwadratowa rośnie z nierównowagą. Zmieniać znaki mniejszości w większość, aż wyczerpie się k albo mniejszość.
//
// Stan i niezmiennik
//
// Każdy kolejny transfer do obecnej większości nie zmniejsza jej przewagi, a przyrost funkcji jest nieujemny i rośnie. Końcowe liczności to maksimum nierównowagi osiągalne w k zmianach.
//
// Złożoność
//
// Czas O(n), pamięć O(n) dla napisu, O(1) liczników.
//
// Przypadki brzegowe
//
// Remis liczności może być rozstrzygnięty w dowolną stronę. k większe od mniejszości pozostawia niewykorzystane zmiany. wszystkie jednakowe znaki.
//
// Kiedy rozpoznać ten wariant
//
// Cel jest wypukły w licznościach przy stałej sumie, więc optimum leży przy największej osiągalnej koncentracji.
//
// Warunki i uwagi
//
// - Cel kombinatoryczny wzoru wymaga treści zadania; nie jest to ogólnie liczba jednolitych podnapisów zależna od kolejności.
// - To funkcja samych liczności; nie utożsamiać z liczbą jednolitych podnapisów zależną od ich kolejności.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int n, k; cin >> n >> k;
    string s; cin >> s;

    int zeros = 0, ones = 0;

    for (int i = 0; i < n; i++)
    {
        if (s[i] == '0') zeros++;
        else ones++;
    }

    if (zeros > ones)
    {
        int able = min(k, ones);
        zeros += able;
        ones -= able;
    }
    else
    {
        int able = min(k, zeros);
        ones += able;
        zeros -= able;
    }

    long long ans = 1LL * zeros*(zeros + 1)/ 2 + 1LL*ones*(ones +1)/2 +1;

    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();
}