// DP bitowe od najmłodszych bitów
//
// Oryginał w zbiorze codeforces/2173/dp/2173D.cc
// https://codeforces.com/contest/2173
//
// Co oblicza kod
//
// Dla k<32 znaleźć najmniejszy popcount(n+m), gdzie m ma najwyżej k jedynek, i wypisać popcount(n)-minimum+k.
//
// Pomysł
//
// Przetwarzać bity od LSB, pamiętać liczbę jedynek m i przeniesienie. Wybrany bit m daje bit wyniku oraz nowe przeniesienie.
//
// Stan i niezmiennik
//
// dp[i][j][carry] minimalizuje liczbę jedynek w i niższych bitach sumy. total=bit(n)+bit(m)+carry. Na końcu dopisać carry do kosztu i wziąć minimum po j<=k.
//
// Złożoność
//
// Dla B=64. czas O(B*k), pamięć O(B*k). kod rezerwuje stałe 65*33*2.
//
// Przypadki brzegowe
//
// Gałąź k>=32 stosować tylko przy potwierdzonych ograniczeniach n. n=0 wymaga uwagi. Przetwarzany zakres dodawanego m obejmuje 64 bity. wynik może mieć 65.
//
// Kiedy rozpoznać ten wariant
//
// Ograniczenie popcount składnika przy optymalizacji popcount sumy. przeniesienia wymuszają kierunek LSB do MSB.
//
// Warunki i uwagi
//
// - Skrót dla k>=32 wymaga ograniczenia n, np. 0<n<2^32. Dla ogólnego long long nie jest dowiedziony ani poprawny: n=0,k=32 daje 31 zamiast 32 według części DP.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve()
{
    ll n, k; cin >> n >> k;

    int initial_popcount = __builtin_popcountll(n);

    if (k >= 32)
    {
        cout << k + initial_popcount - 1 << '\n';
        return;
    }

    int K = (int)k;

    const int INF = 1e9;

    int dp[65][33][2];
    for (int i = 0; i < 65; i++)
    {
        for (int j = 0; j < 33; j++)
        {
            for (int x = 0; x < 2; x++)
            {
                dp[i][j][x] = INF;
            }
        }
    }

    dp[0][0][0] = 0;

    for (int i = 0; i < 64; i++)
    {
        int cur = (n >> i) & 1LL;

        for (int j = 0; j < 33; j++)
        {
            for (int x = 0; x < 2; x++)
            {
                if (dp[i][j][x] == INF) continue;

                for (int y = 0; y < 2; y++)
                {
                    if (j + y > K) continue;


                    int total = x + y + cur;

                    int result_bit = total %2;
                    int next_bit = total/2;

                    dp[i+1][j+y][next_bit] = min(
                        dp[i+1][j+y][next_bit],
                        dp[i][j][x] + result_bit
                    );
                }
            }
        }
    }

    int new_popcount = INF;
    for (int i = 0; i <= K; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            new_popcount = min(new_popcount, dp[64][i][j]+j);
        }
    }

    ll answer = initial_popcount - new_popcount + k;

    cout << answer << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) solve();
}