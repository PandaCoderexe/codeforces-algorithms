// Dwukolorowanie wszystkich składowych
//
// Oryginał w zbiorze codeforces/2204/graph/2204D.cc
// https://codeforces.com/contest/2204
//
// Co oblicza kod
//
// Sumuje większą klasę dwudzielności dwudzielnych składowych, izolowane wierzchołki liczy jako 1, a niedwudzielne składowe jako 0.
//
// Pomysł
//
// Iteracyjny DFS każdej składowej nadaje przeciwne kolory i liczy obie klasy. konflikt zeruje wkład całej składowej.
//
// Stan i niezmiennik
//
// Każda poprawna krawędź łączy przeciwne kolory. izolowany wierzchołek daje klasę rozmiaru 1.
//
// Złożoność
//
// O(n+m) czasu i pamięci.
//
// Przypadki brzegowe
//
// Izolowane wierzchołki. graf niespójny. pętla. nieparzysty cykl.
//
// Kiedy rozpoznać ten wariant
//
// Rozpoznaj wzorzec. dwukolorowanie wszystkich składowych. Iteracyjny DFS każdej składowej nadaje przeciwne kolory i liczy obie klasy. konflikt zeruje wkład całej składowej.
//
// Warunki i uwagi
//
// - Nie jest to ogólny największy zbiór niezależny w grafie dwudzielnym: wybiera tylko całą większą klasę.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve()
{
    int n,m;
    cin >> n >> m;
    vector<vector<int>> graph(n+1);
    for (int i = 0; i < m; i++)
    {
        int x,y;
        cin >>x>>y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    ll ans = 0;
    vector<int> visited(n+1, -1);

    for (int i = 1; i <= n; i++)
    {
        if (visited[i] != -1) continue;
        if (graph[i].empty())
        {
            ans++;
            visited[i] = 0;
            continue;
        }


        int cnt[2] = {0,0};
        bool flag = true;

        stack<int> st;
        st.push(i);
        visited[i] = 0;
        cnt[0]++;
        while(!st.empty())
        {
            int cur = st.top(); st.pop();

            for (int child : graph[cur])
            {
                if (visited[child] == -1)
                {
                    visited[child] = 1 - visited[cur];
                    cnt[visited[child]]++;
                    st.push(child);
                }   
                else if (visited[child] == visited[cur]) flag = 0;
                
            }
        }

        if (!flag) continue;
        ans += max(cnt[0], cnt[1]);
    }

    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) solve();
}