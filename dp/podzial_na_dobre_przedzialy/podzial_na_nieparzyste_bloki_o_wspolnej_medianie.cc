// DP segmentacji z prefiksowym testem mediany
//
// Oryginał w zbiorze codeforces/2222/dp/2222C.cc
// https://codeforces.com/contest/2222
//
// Co oblicza kod
//
// Maksymalizować liczbę nieparzystych bloków dzielących całą tablicę, z medianą każdego równą górnej medianie całej tablicy.
//
// Pomysł
//
// Posortować kopię do wyznaczenia mediany. Trzy liczniki prefiksowe pozwalają sprawdzić medianę każdego [l,r] w O(1), po czym DP wybiera ostatni dobry blok.
//
// Stan i niezmiennik
//
// good[l][r] zachodzi przy nieparzystej długości i liczbach mniejszych/większych <=len/2. dp[i]=max(dp[j]+1) po dobrych [j,i-1], dp[0]=0, nieosiągalne=-1.
//
// Złożoność
//
// Czas O(n^2), pamięć O(n^2), w tym macierz good.
//
// Przypadki brzegowe
//
// n>=1. parzyste n używa a_sorted[n/2] jako mediany docelowej. powtórzenia. wynik -1 przy braku podziału.
//
// Kiedy rozpoznać ten wariant
//
// Najlepszy podział prefiksu na fragmenty z własnością sprawdzaną niezależnie. prefiksy statystyk redukują koszt testu segmentu.
//
// Warunki i uwagi
//
// - Czas O(n^2), pamięć O(n^2), mimo prefiksów. Wynik -1 oznacza brak pełnego podziału.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve()
{
    int n;
    cin >> n;

    vector<ll> a(n);

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    vector<ll> a_sorted = a;
    sort(a_sorted.begin(), a_sorted.end());

    ll median = a_sorted[n / 2];

    vector<ll> less(n + 1, 0), more(n + 1, 0), equal(n + 1, 0);

    for (int i = 0; i < n; i++)
    {
        less[i + 1] = less[i];
        more[i + 1] = more[i];
        equal[i + 1] = equal[i];

        if (a[i] < median)
        {
            less[i + 1]++;
        }
        else if (a[i] > median)
        {
            more[i + 1]++;
        }
        else
        {
            equal[i + 1]++;
        }
    }

    vector<vector<bool>> good(n, vector<bool>(n, 0));
    for (int l = 0; l < n; l++)
    {
        for (int r = l; r < n; r++)
        {
            int len = r-l+1;
            if (len % 2 == 1)
            {
                ll cnt_less = less[r + 1] - less[l];
                ll cnt_more = more[r + 1] - more[l];
                ll cnt_equal = equal[r + 1] - equal[l];

                if (cnt_less <= len/2 && cnt_more <= len/2 && cnt_equal > 0)
                {
                    good[l][r] = 1;
                }
            }
        }
    }

    vector<ll> dp(n + 1, -1);
    dp[0] = 0;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            int l = j;
            int r = i - 1;

            int len = r - l + 1;

            if (dp[j] == -1) continue;

            if (len % 2 == 1 && good[l][r])
            {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }

    cout << dp[n] << "\n";

    return;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);

    int t; cin >> t;
    while(t--)
    {
        solve();
    }

    return 0;
}