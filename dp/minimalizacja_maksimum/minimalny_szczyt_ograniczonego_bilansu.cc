// DP z kosztem będącym maksimum po ścieżce
//
// Oryginał w zbiorze codeforces/2238/dp/2238E.cc
// https://codeforces.com/contest/2238
//
// Co oblicza kod
//
// Wybrać F/T na pozycjach N, aby zmaksymalizować liczbę F minus najwyższy osiągnięty bilans, gdzie F zwiększa bilans, a T zmniejsza do minimum 0.
//
// Pomysł
//
// Stan (f,s) pamięta liczbę F i obecny bilans. Wartość stanu to najmniejszy historyczny szczyt. dla tych samych f,s mniejszy szczyt dominuje.
//
// Stan i niezmiennik
//
// dp[f][s]=minimalny max bilansu po prefiksie. T przechodzi do (f,max(0,s-1)) bez zmiany kosztu, F do (f+1,s+1) z max(dp,s+1). Wynik max(f-dp[f][s]).
//
// Złożoność
//
// Czas O(n^3), pamięć O(n^2), dwie warstwy.
//
// Przypadki brzegowe
//
// Bilans odbija się od 0, a nie staje ujemny. Alfabet F,T,N. inny znak blokuje wszystkie ścieżki.
//
// Kiedy rozpoznać ten wariant
//
// Cel zależy od historycznego maksimum, lecz dla ustalonego bieżącego stanu wystarczy przechowywać najmniejszy możliwy szczyt.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;

const int inf = 1e9;

void solve()
{
    int n;
    cin >> n;

    string str;
    cin >> str;

    vector<vector<int>> dp(n + 1, vector<int>(n + 1, inf));
    vector<vector<int>> new_dp(n + 1, vector<int>(n + 1, inf));

    dp[0][0] = 0;

    for (int i = 0; i < n; i++)
    {
        for (int f = 0; f <= n; f++)
        {
            for (int s_ = 0; s_ <= n; s_++)
            {
                new_dp[f][s_] = inf;
            }
        }

        for (int f = 0; f <= i; f++)
        {
            for (int s_ = 0; s_ <= i; s_++)
            {
                if (dp[f][s_] == inf) continue;

                if (str[i] == 'T' || str[i] == 'N')
                {
                    int s_new = max(0, s_ - 1);
                    int s_max = dp[f][s_];

                    new_dp[f][s_new] = min(new_dp[f][s_new], s_max);
                }

                if (str[i] == 'F' || str[i] == 'N')
                {
                    int s_new = s_ + 1;
                    int s_max = max(dp[f][s_], s_new);

                    new_dp[f + 1][s_new] = min(new_dp[f + 1][s_new], s_max);
                }
            }
        }

        swap(dp, new_dp);
    }

    int ans = 0;

    for (int f = 0; f <= n; f++)
    {
        for (int s_ = 0; s_ <= n; s_++)
        {
            if (dp[f][s_] == inf) continue;

            ans = max(ans, f - dp[f][s_]);
        }
    }

    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--) solve();

    return 0;
}