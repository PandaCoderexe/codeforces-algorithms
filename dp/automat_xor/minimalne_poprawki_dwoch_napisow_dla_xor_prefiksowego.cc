// Automat czterech stanów z kosztem zmian
//
// Oryginał w zbiorze codeforces/2181/dp/2181M.cc
// https://codeforces.com/contest/2181
//
// Co oblicza kod
//
// Zminimalizować łączną odległość Hamminga x do X i y do Y przy Y[i]=X[0] xor ... xor X[i].
//
// Pomysł
//
// Stan przechowuje wybrane X[i],Y[i]. Dopuszczalne przejście spełnia Y[i]=Y[i-1] xor X[i], koszt liczy różnice wobec wejścia.
//
// Stan i niezmiennik
//
// dp[i][state] jest minimalnym kosztem prefiksu kończącego się daną parą bitów. Na pozycji 0 dozwolone są wyłącznie 00 i 11.
//
// Złożoność
//
// Czas O(n*4*4)=O(n), pamięć O(n).
//
// Przypadki brzegowe
//
// Oba napisy muszą być niepuste, binarne i równej długości. n=1. wynik bierze minimum po wszystkich stanach końcowych.
//
// Kiedy rozpoznać ten wariant
//
// Globalna własność prefiksowa ma stały automat i lokalny koszt modyfikacji znaków.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll inf = 4e18;

void solve()
{
    string x, y;
    cin >> x >> y;
    int n = (int)x.size();

    vector<vector<ll>> dp(n, vector<ll>(4,inf));
    vector<string> positions = {"00", "01", "10", "11"};

    for (int state = 0; state < 4; state++)
    {
        int cur_x = positions[state][0] - '0';
        int cur_y = positions[state][1] - '0';

        if (cur_y != cur_x) continue;

        int cost = 0;
        if (cur_x != x[0] - '0') cost++;
        if (cur_y != y[0] - '0') cost++;

        dp[0][state] = cost;
    }


    for (int i = 1; i < n; i++)
    {
        for (int prev = 0; prev < 4; prev++)
        {
            if (dp[i-1][prev] == inf) continue;

            int prev_y = positions[prev][1]-'0';

            for (int cur = 0; cur < 4; cur++)
            {
                int cur_x = positions[cur][0] - '0';
                int cur_y = positions[cur][1] - '0';

                if (cur_y != (prev_y ^ cur_x)) continue;

                int cost = (cur_x == x[i] - '0' ? 0 : 1) + (cur_y == y[i] - '0' ? 0 : 1);

                dp[i][cur] = min(dp[i][cur], dp[i-1][prev] + cost);
            }
        }
    }

    ll ans = inf;
    for (ll x : dp[n-1]) ans = min (ans, x);
    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) solve();
}