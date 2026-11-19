// Binary search limitu i dp na dag
//
// Oryginał w zbiorze codeforces/2110/graph/2110D.cc
// https://codeforces.com/contest/2110
//
// Co oblicza kod
//
// Minimalizuje limit zasobu x, przy którym można przejść od 1 do n, respektując progi krawędzi i przyrosty zasobu w wierzchołkach.
//
// Pomysł
//
// Dla limitu x przechowywać największy zasób dp[v], relaksować do min(x,dp[v]+b[t]) po spełnieniu progu w. binary search pierwszego wykonalnego limitu.
//
// Stan i niezmiennik
//
// Większy zasób w tym samym wierzchołku dominuje mniejszy. wykonalność rośnie z x.
//
// Złożoność
//
// O((n+m) log(max(2,W))) czasu i O(n+m) pamięci, W=max w.
//
// Przypadki brzegowe
//
// Brak drogi. zasób startowy. n=1. optimum 0.
//
// Kiedy rozpoznać ten wariant
//
// Rozpoznaj wzorzec. binary search limitu i DP na DAG. Dla limitu x przechowywać największy zasób dp[v], relaksować do min(x,dp[v]+b[t]) po spełnieniu progu w. binary search pierwszego wykonalnego limitu.
//
// Warunki i uwagi
//
// - Wymaga indeksów będących porządkiem topologicznym. Wyszukiwanie od 1 nie obsługuje poprawnego optimum 0 bez dodatkowych ograniczeń.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
struct Passage
{
    int t;
    int w;
};

void solve()
{
    int n,m; cin >> n >>m;
    vector<ll> b(n+1);
    for (int i = 1; i <= n; i++) cin >> b[i];

    vector<vector<Passage>> passages(n+1);
    int max_w = 0;
    for (int i = 1; i <= m; i++)
    {
        int s,t,w;
        cin >> s >> t >> w;
        passages[s].push_back({t,w});
        max_w = max(max_w, w);
    }

    auto check = [&](ll x) -> bool {
        vector<ll> dp(n+1, -1);
        dp[1] = min(x, b[1]);
        for (int i = 1; i < n; i++)
        {
            if (dp[i] == -1) continue;
            for (auto& [t,w] : passages[i])
            {
                if (dp[i] < w) continue;

                dp[t] = max(dp[t], min(x, dp[i] + b[t]));
            }
        }
        if (dp[n] == -1) return false;
        return true;
    };

    if (!check(max_w))
    {
        cout << -1 << "\n";
        return;
    }

    int l = 1, r = max_w;
    while(l < r)
    {
        int m = l + (r-l) /2;
        if (!check(m))
        {
            l = m+1;
        }
        else
        {
            r = m;
        }
    }
    cout << l << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) solve();
}