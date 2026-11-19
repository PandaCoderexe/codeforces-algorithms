// Dp od liści i prefiksy ścieżek
//
// Oryginał w zbiorze codeforces/2195/graph/2195E.cc
// https://codeforces.com/contest/2195
//
// Co oblicza kod
//
// Dla liści wyznacza wagę 1, dla węzła wewnętrznego sumę wag obu synów plus 3. wypisuje sumę wag na ścieżce od korzenia do każdego wierzchołka modulo 1e9+7.
//
// Pomysł
//
// W odwróconym przejściu wyliczyć wagę liść=1 i wewnętrzny=lewy+prawy+3. w zwykłym ans[v]=ans[parent]+waga[v].
//
// Stan i niezmiennik
//
// Pierwszy przebieg ma gotowe dzieci, a drugi gotowego rodzica, więc sumy ścieżek są poprawnie propagowane.
//
// Złożoność
//
// O(n) czasu i pamięci.
//
// Przypadki brzegowe
//
// Pojedynczy liść. pełne lecz niesymetryczne drzewo. brak jednego syna niedopuszczalny.
//
// Kiedy rozpoznać ten wariant
//
// Rozpoznaj wzorzec. DP od liści i prefiksy ścieżek. W odwróconym przejściu wyliczyć wagę liść=1 i wewnętrzny=lewy+prawy+3. w zwykłym ans[v]=ans[parent]+waga[v].
//
// Warunki i uwagi
//
// - Zakłada zero lub dokładnie dwóch niezerowych synów. Nazwa depth oznacza wagę poddrzewa, nie głębokość.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll mod = 1e9 + 7;

void solve()
{
    int n; cin >> n;
    vector<pair<int,int>> tree(n+1, {0,0});
    vector<int> parent(n+1);
    parent[1] = 0;
    for (int i = 1; i <= n; i++)
    {
        int l,r;
        cin >> l >> r;

        if (l != 0)
        {
            tree[i].first = l;
            tree[i].second = r;

            parent[l] = i;
            parent[r] = i;
        }
    }

    vector<int> order;
    stack<int> st;
    st.push(1);
    while(!st.empty())
    {
        int cur = st.top(); st.pop();
        order.push_back(cur);

        if (tree[cur].first != 0)
        {
            st.push(tree[cur].first);
            st.push(tree[cur].second);
        }
    }

    vector<ll> depth(n+1, 1);
    for (int i = (int)order.size()-1; i >= 0; i--)
    {
        int cur = order[i];
        if (tree[cur].second == 0) continue;

        depth[cur] = (depth[tree[cur].first] + depth[tree[cur].second] + 3)%mod;
    }

    vector<ll> ans(n+1);
    ans[0] = 0;
    for (int i = 0; i < (int)order.size(); i++)
    {
        int cur = order[i];
        ans[cur] = (ans[parent[cur]] + depth[cur]) % mod;
    }

    for (int i = 1; i <= n; i++)
    {
        cout << ans[i] << " ";
    }

    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) solve();
}