// Boolowskie DP stałego automatu dla trzech limitów
//
// Oryginał w zbiorze codeforces/2260/dp/2260D.cc
// https://codeforces.com/contest/2260
//
// Co oblicza kod
//
// Znaleźć najmniejsze i w 1..3, dla którego istnieją stany z zakresu -3..3 o znakach zgodnych z napisem, startując z 0, zmieniając stan na każdym kroku i zachowując |x-y|<=i.
//
// Pomysł
//
// Dla każdego limitu uruchomić DP osiągalności na siedmiu stanach. Przejście filtruje znak bieżącego symbolu oraz nierówność i odległość stanów.
//
// Stan i niezmiennik
//
// dp[x+3] oznacza osiągalność x po prefiksie. ndp[y+3] jest OR-em osiągalnych x spełniających x!=y,|x-y|<=i i znak y zgodny z c.
//
// Złożoność
//
// Czas O(3*n*7^2)=O(n), pamięć O(1) dla DP plus O(n) napis.
//
// Przypadki brzegowe
//
// Dwa kolejne symbole 0 są niemożliwe, bo wymagają pozostania w 0. Pierwszy stan też musi różnić się od startowego 0.
//
// Kiedy rozpoznać ten wariant
//
// Szukana sekwencja liczb ma tylko kilka istotnych klas stanów. koszt graniczny sprawdza się kilkoma automatami.
//
// Warunki i uwagi
//
// - Należy oddzielić twierdzenie, że wystarczy zakres -3..3, od samego działania checkera; treść zadania nie jest dostępna. O(n) czasu i O(1) dodatkowej pamięci poza napisem.
// - Redukcja pierwotnego zadania do zakresu -3..3 oraz limitów 1..3 wymaga treści i dowodu; kandydat opisuje dokładnie skończony problem rozwiązywany przez kod.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;

#include <bits/stdc++.h>

using namespace std;

bool dp(string s, int i)
{
    bool dp[7] = {};
    dp[3] = 1;

    for (char c : s)
    {
        bool ndp[7] = {};

        for (int x = -3; x <= 3; x++)
        {
            if (!dp[x + 3]) continue;

            for (int y = -3; y <= 3; y++)
            {
                if (x == y || abs(x - y) > i) continue;
                if ((c == '+' && y > 0) || (c == '-' && y < 0) || (c == '0' && y == 0))
                {
                    ndp[y + 3] = 1;
                }
            }
        }

        copy(ndp, ndp+7, dp);
    }

    for (int i = 0; i < 7; i++) if (dp[i]) return true;
    return false;
}

void solve()
{
    int n;
    cin >> n;

    string s;
    cin >> s;

    for (int i = 1; i <= 3; i++)
    {
        if (dp(s, i))
        {
            cout << i << "\n";
            return;
        }
    }

    cout << -1 << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();
}