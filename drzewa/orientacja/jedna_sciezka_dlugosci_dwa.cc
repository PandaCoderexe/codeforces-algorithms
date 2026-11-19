// Orientacja przez wierzchołek stopnia dwa
//
// Oryginał w zbiorze codeforces/2112/tree/2112D.cc
// https://codeforces.com/contest/2112
//
// Co oblicza kod
//
// Wybiera wierzchołek stopnia 2 jako jedyne miejsce przejścia wejście-wyjście, a pozostałe wierzchołki orientuje jako źródła lub ujścia.
//
// Pomysł
//
// Środek stopnia 2 ma jedno wejście i jedno wyjście, a BFS obu stron nadaje role źródła i ujścia.
//
// Stan i niezmiennik
//
// Poza środkiem żaden wierzchołek nie ma jednocześnie wejścia i wyjścia. istnieje jedna ścieżka długości 2 i n osiągalnych par różnych wierzchołków.
//
// Złożoność
//
// O(n) czasu i pamięci.
//
// Przypadki brzegowe
//
// n=2. gwiazda bez stopnia 2. ścieżka.
//
// Kiedy rozpoznać ten wariant
//
// Rozpoznaj wzorzec. orientacja przez wierzchołek stopnia dwa. Środek stopnia 2 ma jedno wejście i jedno wyjście, a BFS obu stron nadaje role źródła i ujścia.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;

struct Edge
{
    int idx;
    int u;
    int v;
    int dir = -1;
};

struct new_edge
{
    int v;
    int dir;
};

void solve()
{
    int n;
    cin >> n;

    vector<int> in(n + 1);
    vector<vector<Edge>> tree(n + 1);

    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;

        tree[u].push_back({i, u, v});
        tree[v].push_back({i, v, u});
        in[u]++;
        in[v]++;
    }

    if (n == 2)
    {
        cout << "NO\n";
        return;
    }

    queue<int> q;

    for (int i = 1; i <= n; i++)
    {
        if ((int)tree[i].size() == 2)
        {
            q.push(i);
        }
    }

    if (q.empty())
    {
        cout << "NO\n";
        return;
    }

    vector<vector<new_edge>> correct_tree(n + 1);
    vector<bool> visited(n, false);
    int r = q.front();
    q.pop();

    int u = tree[r][0].v;
    int v = tree[r][1].v;

    int first_idx = tree[r][0].idx;
    int second_idx = tree[r][1].idx;

    visited[first_idx] = true;
    visited[second_idx] = true;

    correct_tree[r].push_back({u, 0});
    correct_tree[r].push_back({v, 1});

    queue<pair<int, bool>> q_;
    q_.push({u, true});
    q_.push({v, false});

    while (!q_.empty())
    {
        auto [cur, is_source] = q_.front();
        q_.pop();

        for (auto &[idx, from, to, dir] : tree[cur])
        {
            if (visited[idx]) continue;

            visited[idx] = true;
            if (is_source)
            {
                correct_tree[cur].push_back({to, 1});
            }
            else
            {
                correct_tree[cur].push_back({to, 0});
            }
            q_.push({to, !is_source});
        }
    }

    cout << "YES\n";
    for (int cur = 1; cur <= n; cur++)
    {
        for (auto &[to, dir] : correct_tree[cur])
        {
            if (dir == 1)
                cout << cur << ' ' << to << '\n';
            else
                cout << to << ' ' << cur << '\n';
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
        solve();
}