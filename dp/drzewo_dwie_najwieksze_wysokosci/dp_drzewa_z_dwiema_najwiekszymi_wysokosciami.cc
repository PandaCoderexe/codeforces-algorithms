// DP drzewa z najlepszą gałęzią poza dzieckiem
//
// Oryginał w zbiorze codeforces/2192/dp/2192D.cc
// https://codeforces.com/problemset/problem/2192/D
//
// Co oblicza kod
//
// Dla korzenia rozważanego poddrzewa maksymalizuje sumę a[u]*dist(korzen,u) po co najwyżej jednym odcięciu i podłączeniu gałęzi do wierzchołka nadal połączonego z korzeniem.
//
// Pomysł
//
// Najpierw wyznaczyć sum[v],base[v],height[v]. Dwie największe wysokości dzieci pozwalają w O(1) znaleźć height_poza_c dla każdego dziecka. przetwarzać odwrotny porządek DFS.
//
// Stan i niezmiennik
//
// sum[v]=a[v]+Σsum[c], base[v]=Σ(base[c]+sum[c]). dp[v]=max(base[v],max_c(base[v]-base[c]+dp[c]),max_c(base[v]+sum[c]*height_poza_c)). height_poza_c uwzględnia też sam v o wysokości 0.
//
// Złożoność
//
// Czas O(n), pamięć O(n).
//
// Przypadki brzegowe
//
// Liść. base=dp=height=0. Dwie równe największe wysokości muszą być zachowane jako dwa osobne wyniki. Inicjalizacja alternatyw 0 zakłada nieujemne koszty/wagi dla typowej interpretacji.
//
// Kiedy rozpoznać ten wariant
//
// Każde dziecko potrzebuje najlepszego wyniku ze wszystkich pozostałych dzieci. zachowanie dwóch maksimów usuwa kwadratowy przegląd rodzeństwa.
//
// Warunki i uwagi
//
// - Dokładna rekurencja: dp[v]=max(base[v],max_c(base[v]-base[c]+dp[c]),max_c(base[v]+sum[c]*height_poza_c)). Czas i pamięć O(n). Dla ujemnych wag inicjalizowane zerem alternatywy mogą zmieniać interpretację.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int n; cin >> n;

    vector<int> a(n+1, 0);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<vector<int>> tree(n+1);
    for (int i = 0; i < n-1; i++)
    {
        int x, y;
        cin >> x >> y;

        tree[x].push_back(y);
        tree[y].push_back(x);
    }

    vector<int> depth(n+1, -1), order, parent(n+1, -1), st;
    st.push_back(1);
    parent[1] = 0;
    depth[1] = 0;

    while(!st.empty())
    {
        int cur = st.back(); st.pop_back();

        order.push_back(cur);
        for (int child : tree[cur])
        {
            if (parent[child] == -1)
            {
                parent[child] = cur;
                depth[child] = depth[cur]+1;

                st.push_back(child);
            }
        }
    }

    vector<long long> base(n + 1, 0), sum(n + 1, 0), dp(n+1, 0), height(n+1, 0);

    for (int i = (int)order.size() - 1; i >= 0; i--)
    {
        int cur = order[i];

        sum[cur] = a[cur];
        base[cur] = 0;

        for (int child : tree[cur])
        {
            if (parent[child] == cur)
            {
                sum[cur] += sum[child];
                base[cur] += base[child] + sum[child];
                height[cur] = max(height[cur], height[child]+1);
            }
        }

        int first_depth = 0, second_depth = 0;
        for (int child : tree[cur])
        {
            if (parent[child] != cur) continue;
            int cand = height[child] + 1;
            if (cand >= first_depth)
            {
                second_depth = first_depth;
                first_depth = cand;
            }
            else if (cand > second_depth) second_depth = cand;
        }

        long long inside_child = 0, outside_child = 0;

        for (int child : tree[cur])
        {
            if (parent[child] != cur) continue;
            int cand = height[child] + 1;
            int height_used = (cand == first_depth ? second_depth : first_depth); 
            inside_child = max(inside_child, base[cur] - base[child] + dp[child]);
            outside_child = max(outside_child, base[cur] + sum[child] * height_used);
        }

        dp[cur] = max({base[cur], inside_child, outside_child});

    }

    for (int i = 1; i <= n; i++) cout << dp[i] << " ";
    cout << "\n";
    
    return;
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) solve();
    return 0;
}