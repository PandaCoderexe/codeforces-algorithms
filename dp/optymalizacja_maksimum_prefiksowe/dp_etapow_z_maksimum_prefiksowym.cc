// DP z budżetem i rekordowym poziomem
//
// Oryginał w zbiorze codeforces/2174/dp/2174B.cc
// https://codeforces.com/contest/2174
//
// Co oblicza kod
//
// Maksymalizować sumę length*level po etapach maksymalnej wartości prefiksu, płacąc nowy poziom przy jego ścisłym podniesieniu i nie przekraczając budżetu k.
//
// Pomysł
//
// Skompresować stałe maksima prefiksu do (capacity,length). Nowy poziom jest stary albo ściśle wyższy, <=capacity. najlepszy stan z mniejszym poziomem pobrać z prefiksowego maksimum.
//
// Stan i niezmiennik
//
// dp[sum][level] to najlepszy wynik po etapach. best[s][m]=max_{j<m}dp[s][j]. new_dp[s][m]=length*m+max(dp[s][m],best[s-m][m]) przy warunkach m>0,m<=capacity,m<=s.
//
// Złożoność
//
// Dla S etapów. czas O(n+S*k^2), pamięć O(n+k^2).
//
// Przypadki brzegowe
//
// n>=1. k=0. niemożliwe stany mają NEG i nie wolno do nich dodawać. Maksimum prefiksowe musi być ścisłe. poziom j<m.
//
// Kiedy rozpoznać ten wariant
//
// Przejście DP zawiera maksimum po całym przedziale wcześniejszego parametru. można je wyliczyć zbiorczo raz na warstwę.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve()
{
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> pref_maximum(n);
    pref_maximum[0] = a[0];
    for (int i = 1; i < n; i++) pref_maximum[i] = max(a[i], pref_maximum[i-1]);

    vector<pair<int, int>> stages;

    int left = 0;
    while(left < n)
    {
        int right = left;

        while (right < n && pref_maximum[left] == pref_maximum[right]) right++;

        stages.push_back({pref_maximum[left], right-left});
        left = right;
    }

    const ll NEG = -(1LL << 60);
    vector<vector<ll>> dp(k+1, vector<ll>(k+1, NEG));
    dp[0][0] = 0;

    for (auto [capacity, length] : stages)
    {
        vector<vector<ll>> best(k+1, vector<ll>(k+1, NEG));
        for (int sum = 0; sum <= k; sum++)
        {
            ll prefix_best = NEG;
            for (int maximum = 0; maximum <= k; maximum++)
            {
                best[sum][maximum] = prefix_best;
                prefix_best = max(prefix_best, dp[sum][maximum]);
            }
        }

        
        vector<vector<ll>> new_dp(k+1, vector<ll>(k+1, NEG));

        for (int sum = 0; sum <= k; sum++)
        {
            for (int maximum = 0; maximum <= k; maximum++)
            {
                if (dp[sum][maximum] != NEG)
                {
                    new_dp[sum][maximum] = max(new_dp[sum][maximum], dp[sum][maximum] + 1LL * length * maximum);
                }

                if (maximum > 0 && maximum <= capacity && maximum <= sum && best[sum-maximum][maximum] != NEG)
                {
                    new_dp[sum][maximum] = max(new_dp[sum][maximum], best[sum-maximum][maximum] + 1LL * length * maximum);
                }
            }
        }

        dp.swap(new_dp);
    }


    ll ans = 0;

    for (int sum = 0; sum <= k; sum++)
    {
        for (int maximum = 0; maximum <= k; maximum++)
        {
            ans = max(ans, dp[sum][maximum]);
        }
    }

    cout << ans << '\n';

}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) solve();
}