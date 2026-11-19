// Enumeracja globalnego parametru przed DP
//
// Oryginał w zbiorze codeforces/2245/dp/2245A.cc
// https://codeforces.com/contest/2245
//
// Co oblicza kod
//
// Minimalizować odległość Hamminga do napisu L/R z końcową liczbą L równą parametrowi L i warunkami. przy R pozostaje >=k przyszłych L, przy L wystąpiło już >=k R.
//
// Pomysł
//
// Enumerować końcowe L od 0 do n. Wtedy przyszła liczba L jest L-l, a dotychczasowa liczba R to i-l, więc pozornie globalne warunki stają się lokalne dla stanu (i,l).
//
// Stan i niezmiennik
//
// dp[i][l] jest minimalnym kosztem prefiksu długości i z l literami L. R wymaga L-l>=k, L wymaga l+1<=L i i-l>=k. przejście płaci 0/1 za zgodność z s[i].
//
// Złożoność
//
// Czas O(n^3), pamięć O(n^2).
//
// Przypadki brzegowe
//
// k=0. L=0 lub n. niemożliwy wynik daje -1. Stały zewnętrzny parametr L trzeba odróżnić od liczby wybranych l.
//
// Kiedy rozpoznać ten wariant
//
// Przejścia zależą od liczby przyszłych zdarzeń. ustalenie końcowej liczby zamienia ją w różnicę znanej stałej i bieżącego stanu.
//
// Warunki i uwagi
//
// - Czas O(n^3), pamięć O(n^2). Dokładne warunki: R wymaga L-l>=k; L wymaga l+1<=L i i-l>=k. Semantyka warunków wymaga treści zadania.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;

const int inf = 1e9+7; 

void solve()
{
    int n, k;
    cin >> n >> k;
    string s; cin >> s;
    int minimum = inf; 
    for (int L = 0; L <= n; L++)
    {
        vector<vector<int>> dp(n+1, vector<int>(n+1, inf));
        dp[0][0]= 0;
        for (int i = 0; i < n; i++)
        {
            for (int l = 0; l <= i; l++)
            {
                if (dp[i][l] == inf) continue;
                int r = i - l;

                {// if we do R
                    if (L - l >= k)
                    {
                        int cost = (s[i] == 'R' ? 0 : 1);
                        dp[i + 1][l] = min(dp[i + 1][l], dp[i][l] + cost);
                    }
                }
                
                {// if we do L
                    if (l + 1 <= L && r>=k)
                    {
                        int cost = (s[i] == 'L' ? 0 : 1);
                        dp[i + 1][l+1] = min(dp[i + 1][l+1], dp[i][l] + cost);
                    }

                }

            }
        }

        minimum = min(minimum, dp[n][L]);
        
    }

    if (minimum != inf) cout << minimum << "\n";
    else cout << -1 << "\n";

}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) solve();
}