// DP podziału cyklu na bloki długości 2 i 3
//
// Oryginał w zbiorze codeforces/2153/dp/2153D.cc
// https://codeforces.com/contest/2153
//
// Co oblicza kod
//
// Zminimalizować sumę rozstępów bloków długości 2/3 dzielących cykliczny ciąg.
//
// Pomysł
//
// Uruchomić liniowe DP dla startów 0,1,2. Granica dowolnego takiego podziału występuje wśród pierwszych trzech pozycji. rozcięcie na tej granicy usuwa cykl.
//
// Stan i niezmiennik
//
// dp[i]=min(dp[i-2]+abs(a[i-2]-a[i-1]),dp[i-3]+max(trójka)-min(trójka)). indeksy przesunięte modulo n. dp[0]=0, dp[1]=INF.
//
// Złożoność
//
// Czas O(n), pamięć O(n).
//
// Przypadki brzegowe
//
// n>=2. dla n=1 brak dopuszczalnego podziału i kod wypisuje wartownik. Ujemne wartości działają przy bezpiecznych różnicach.
//
// Kiedy rozpoznać ten wariant
//
// Lokalne bloki o ograniczonej długości na cyklu. kilka rozcięć wystarcza, jeśli każdy podział ma bliską granicę.
//
// KONIEC OPISU
#include <bits/stdc++.h>
#define int long long

using namespace std;

void solve()
{
    int n; cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    const int INF = LLONG_MAX/4;
    int ans = INF;

    for (int start = 0; start < 3; start++)
    {
        vector<int> dp(n+1, INF);
        dp[0]=0;

        for (int i = 2; i <= n; i++)
        {
            int left = a[(start+i-2)%n];
            int right = a[(start+i-1)%n];

            int cost_2 = abs(left-right);
            dp[i] = min(dp[i], dp[i-2]+cost_2);
            if (i >= 3)
            {
                int first = a[(start+i-3)%n];
                int second = a[(start+i-2)%n];
                int third = a[(start+i-1)%n];

                int maximum = max({first, second, third});
                int minimum = min({first, second, third});

                int cost_3 = maximum - minimum;

                dp[i] = min(dp[i], dp[i-3] + cost_3);
            }
        }

        ans = min(ans, dp[n]);
    }

    cout << ans << "\n";


}

signed main()
{
    ios_base::sync_with_stdio(0);cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}