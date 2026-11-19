// Usuwanie liści według parzystości
//
// Oryginał w zbiorze codeforces/2154/tree/2154D.cc
// https://codeforces.com/contest/2154
//
// Co oblicza kod
//
// Korzeni w n, utrzymuje liście w dwóch stosach według parzystości głębokości i generuje operacje 1 oraz 2 v, usuwając liście przeciwnego koloru do cat_color.
//
// Pomysł
//
// Korzenić w n, liście rozdzielić po parzystości głębokości. w razie potrzeby dodać przełączenie typu 1, następnie usunąć liść przeciwnego koloru.
//
// Stan i niezmiennik
//
// Usuwany wierzchołek jest aktualnym liściem, a po utracie ostatniego dziecka rodzic trafia do stosu właściwej parzystości.
//
// Złożoność
//
// O(n) czasu, pamięci i liczby operacji.
//
// Przypadki brzegowe
//
// Ścieżka. gwiazda. n=1. brak liścia właściwej parzystości.
//
// Kiedy rozpoznać ten wariant
//
// Rozpoznaj wzorzec. usuwanie liści według parzystości. Korzenić w n, liście rozdzielić po parzystości głębokości. w razie potrzeby dodać przełączenie typu 1, następnie usunąć liść przeciwnego koloru.
//
// Warunki i uwagi
//
// - To generator operacji, nie program interaktywny. Dokładna semantyka operacji wymaga treści zadania.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve()
{
    int n;
    cin >> n;

    vector<vector<int>> graph(n + 1);

    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<int> parent(n + 1);
    vector<int> depth(n + 1);
    vector<int> children(n + 1);

    stack<int> st;
    st.push(n);
    parent[n] = 0;

    while (!st.empty())
    {
        int cur = st.top();
        st.pop();

        for (int child : graph[cur])
        {
            if (child == parent[cur]) continue;

            parent[child] = cur;
            depth[child] = depth[cur] + 1;
            children[cur]++;

            st.push(child);
        }
    }

    vector<int> leaves[2];

    for (int i = 1; i <= n; i++)
    {
        if (i != n && children[i] == 0)
        {
            leaves[depth[i] % 2].push_back(i);
        }
    }

    vector<pair<int,int>> answer;

    int cat_color = depth[1] % 2;

    for (int removed = 0; removed < n - 1; removed++)
    {
        int needed_color = cat_color ^ 1;

        if (leaves[needed_color].empty())
        {
            answer.push_back({1, 0});
            cat_color ^= 1;
            needed_color = cat_color ^ 1;
        }

        int vertex = leaves[needed_color].back();
        leaves[needed_color].pop_back();

        answer.push_back({2, vertex});

        int p = parent[vertex];
        children[p]--;

        if (p != n && children[p] == 0)
        {
            leaves[depth[p] % 2].push_back(p);
        }

        answer.push_back({1, 0});
        cat_color ^= 1;
    }

    cout << answer.size() << '\n';

    for (auto [type, vertex] : answer)
    {
        if (type == 1)
        {
            cout << "1\n";
        }
        else
        {
            cout << "2 " << vertex << '\n';
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();
}