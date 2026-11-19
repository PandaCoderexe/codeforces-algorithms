// BFS z granicą przejścia
//
// Oryginał w zbiorze codeforces/2277/tree/2277C.cc
// https://codeforces.com/contest/2277
//
// Co oblicza kod
//
// BFS od n zapisuje odległość do 1 jako ans, ale nie kolejkuje 1. następnie maksymalizuje ans przez dist[v]+1 dla wskazanych osiągalnych v.
//
// Pomysł
//
// Uruchomić BFS od n. dojście do 1 aktualizuje ans, lecz 1 nie trafia do kolejki. Potem sprawdzić wskazane wierzchołki z osiągalnej części.
//
// Stan i niezmiennik
//
// Kolejka zawiera tylko wierzchołki części po stronie n bez przechodzenia przez 1. dist jest w niej poprawną odległością od n.
//
// Złożoność
//
// O(n+m) czasu i O(n) pamięci, m=liczba wskazanych wierzchołków, nie liczba krawędzi.
//
// Przypadki brzegowe
//
// n=1. wskazany wierzchołek 1. gałęzie za blokadą. wskazanie n. ścieżka.
//
// Kiedy rozpoznać ten wariant
//
// Przeszukiwanie ma traktować wyróżniony wierzchołek jako granicę, której osiągnięcie nie oznacza dalszego rozwijania.
//
// Warunki i uwagi
//
// - dist[1] pozostaje −1 poza n=1. To nie odległości w całym drzewie: gałęzie za 1 są celowo zablokowane.
//
// KONIEC OPISU
#include <bits/stdc++.h>
#define vvi vector<vector<int>>
using namespace std;

void solve()
{
    int n,m; cin >> n >> m;
    vvi tree(n+1);
    for (int i = 0; i < n-1; i++)
    {
        int x,y; cin >> x>>y;
        tree[x].push_back(y);
        tree[y].push_back(x);
    }

    queue<int>q;
    q.push(n);
    vector<int> dist(n+1,-1);
    dist[n] = 0;
    
    int ans = 0;
    while(!q.empty())
    {
        int cur = q.front(); q.pop();

        for (int child: tree[cur])
        {
            if (dist[child]!=-1) continue;
            if (child == 1)
            {   
                ans = dist[cur]+1;
                continue;
            }

            dist[child] = dist[cur]+1;
            q.push(child);

        }

    }


    for (int i = 0; i < m; i++)
    {
        int v; cin >> v;
        if (dist[v] != -1) ans = max(ans, dist[v]+1);
    }

    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();
     
}