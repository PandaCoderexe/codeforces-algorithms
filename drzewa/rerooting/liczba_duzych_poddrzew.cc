// Rerooting liczby dużych poddrzew
//
// Oryginał w zbiorze codeforces/2167/tree/2167F.cc
// https://codeforces.com/contest/2167
//
// Co oblicza kod
//
// Sumuje po wszystkich korzeniach liczbę wierzchołków, których poddrzewo ma co najmniej k elementów.
//
// Pomysł
//
// Rozmiary s liczyć od liści, a po zmianie korzenia do dziecka stosować dp[child]=dp[parent]−[s[child]≥k]+[n−s[child]≥k].
//
// Stan i niezmiennik
//
// Przesunięcie korzenia przez krawędź zmienia tylko dwa wkłady. dp[v] jest liczbą dużych poddrzew dla korzenia v.
//
// Złożoność
//
// O(n) czasu i pamięci, przejścia iteracyjne.
//
// Przypadki brzegowe
//
// k=1,n. n=1. ścieżka. gwiazda.
//
// Kiedy rozpoznać ten wariant
//
// Rozpoznaj wzorzec. rerooting liczby dużych poddrzew. Rozmiary s liczyć od liści, a po zmianie korzenia do dziecka stosować dp[child]=dp[parent]−[s[child]≥k]+[n−s[child]≥k].
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve()
{
    int n, k; cin >>n>>k;
    vector<vector<int>> tree(n+1);
    for (int i = 0; i < n-1; i++)
    {
        int x,y;
        cin>>x>>y;
        tree[x].push_back(y);
        tree[y].push_back(x);
    }

    vector<int> order, parent(n+1, -1), s(n+1, 1);
    stack<int> st;
    st.push(1);
    parent[1] = 0;
    while(!st.empty())
    {
        int cur = st.top(); st.pop();
        order.push_back(cur);

        for (int child : tree[cur])
        {
            if (parent[child] == -1)
            {
                parent[child] = cur;
                st.push(child);
            }
        }
    }

    for (int i = (int)order.size()-1; i >= 0; i--)
    {
        int cur = order[i];
        ll cnt = 0;
        for (int child: tree[cur])
        {
            if (parent[child] != cur) continue;

            cnt += s[child];
        }

        s[cur] += cnt;
    }

    vector<ll> dp(n+1, 0);
    for (int i = 1; i <= n; i++)
    {
        if (s[i]>= k) dp[1]++;
    }

    st.push(1);
    while(!st.empty())
    {
        int cur = st.top(); st.pop();

        for (int child: tree[cur])
        {
            if (parent[child] != cur) continue;
            bool x = (s[child] >= k);
            bool y = (n- s[child] >= k);
            dp[child] = dp[cur] - x + y;
            st.push(child);
        }
    }

    ll ans = 0; 
    for (int i : dp)
    {
        ans += i;
    }
    cout << ans << "\n";

}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) solve();
}