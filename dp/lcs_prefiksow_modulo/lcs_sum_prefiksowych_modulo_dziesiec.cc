// LCS po przekształceniu na sumy prefiksowe
//
// Oryginał w zbiorze codeforces/2242/dp/2242D.cc
// https://codeforces.com/contest/2242
//
// Co oblicza kod
//
// Dla równych łącznych sum cyfr modulo 10 znaleźć LCS ciągów sum prefiksowych z zerem początkowym i wypisać jego długość minus 1. przy różnych sumach zwrócić -1.
//
// Pomysł
//
// Zbudować prefiksy modulo 10, następnie klasyczny DP LCS z pomijaniem elementu z dowolnego ciągu i dopasowaniem równych reszt.
//
// Stan i niezmiennik
//
// dp[i][j] jest długością LCS pierwszych i oraz j reszt. Dopasowanie dodaje 1 tylko przy sum_a[i]==sum_b[j]. dwie alternatywy pomijają bieżący prefiks.
//
// Złożoność
//
// Czas O(|a|*|b|), pamięć O(|a|*|b|).
//
// Przypadki brzegowe
//
// Długości napisów mogą być różne. wszystkie cyfry 0. wspólne zero początkowe powoduje końcowe -1 w formule odpowiedzi.
//
// Kiedy rozpoznać ten wariant
//
// Równość sum bloków modulo może zamienić się na dopasowanie granic o równych resztach prefiksowych.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;

void solve()
{
    string a, b;
    cin >> a >> b;

    int n = (int)a.size();
    int m = (int)b.size();
    vector<int>sum_a(n + 1, 0);
    vector<int>sum_b(m + 1, 0);
    for (int i = 0; i < n; i++) sum_a[i + 1] = (sum_a[i] + (a[i] - '0')) % 10;
    for (int i = 0; i < m; i++) sum_b[i + 1] = (sum_b[i] + (b[i] - '0')) % 10;
    
    n++;m++;
    if (sum_a.back() != sum_b.back())
    {
        cout << -1 << "\n";
        return;
    }

    vector<vector<int>> dp(n+1, vector<int>(m+1));

    auto update = [&](int& x, int y) -> void
    {
        x = max(x, y);
    };

    for (int i = 0; i <= n;i++)
    {
        for (int j = 0; j <= m; j++)
        {
            if ( i < n) update(dp[i+1][j], dp[i][j]);
            if ( j < m) update(dp[i][j+1], dp[i][j]);
            if (i < n && j < m && sum_a[i] == sum_b[j]) update(dp[i+1][j+1], dp[i][j]+1);
        }
    }

    cout << dp[n][m] -1 << "\n";
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}