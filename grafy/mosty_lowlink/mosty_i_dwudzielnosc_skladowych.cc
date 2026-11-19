// Mosty tarjana lowlink i składowe bez mostów
//
// Oryginał w zbiorze codeforces/2135/graph/2135C.cc
// https://codeforces.com/contest/2135
//
// Co oblicza kod
//
// Policzyć modulo 998244353 przypisania nieustalonych wartości z zakresu 0..V−1 w balanced XOR graph. wewnątrz każdej składowej po usunięciu mostów ustalone wartości muszą być zgodne, składowa niedwudzielna wymusza 0, a nieustalona dwudzielna wnosi V możliwości.
//
// Pomysł
//
// Most to krawędź drzewa z low[dziecko]>tin[rodzic]. po pominięciu mostów drugi DFS sprawdza dwudzielność i zgodność ustalonych wartości.
//
// Stan i niezmiennik
//
// low jest najstarszym osiągalnym czasem wejścia z poddrzewa. ID krawędzi odróżnia rodzica od równoległej krawędzi.
//
// Złożoność
//
// O(n+m) czasu i pamięci. stos rekurencji O(n).
//
// Przypadki brzegowe
//
// Krawędzie równoległe. nieparzysty cykl. sprzeczne wartości. niespójność.
//
// Kiedy rozpoznać ten wariant
//
// Rozpoznaj wzorzec. mosty Tarjana lowlink i składowe bez mostów. Most to krawędź drzewa z low[dziecko]>tin[rodzic]. po pominięciu mostów drugi DFS sprawdza dwudzielność i zgodność ustalonych wartości.
//
// Warunki i uwagi
//
// - Oficjalne założenie zadania. graf jest spójny i prosty; pojedynczy start Tarjana od 1 jest zatem poprawny. Przy użyciu jako ogólnego szablonu dla grafu niespójnego potrzebna pętla startów DFS.
// - Oba DFS są rekurencyjne i na bardzo długim grafie mogą wymagać większego stosu lub wersji iteracyjnej.
// - To lowlink do mostów, nie SCC.
//
// KONIEC OPISU
#include <bits/stdc++.h>
#define ll long long
#define vi vector<int>

using namespace std;
const ll mod = 998244353;
struct Edge
{
    int to, id;
};

void solve()
{
    int n,m,V; cin >> n >> m >> V;
    vi a(n+1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    vector<vector<Edge>> graph(n+1);
    for (int i = 1; i <= m; i++)
    {
        int u ,v; cin >>u >> v;
        graph[u].push_back({v,i});
        graph[v].push_back({u, i});
    }

    int timer = 0;
    vector<bool> most(m+1);
    vi tin(n+1), low(n+1);

    auto tarjan = [&](auto&& self, int cur, int par_id) -> void 
    {   
        tin[cur] = low[cur] = ++timer;

        for (auto [to, id] : graph[cur])
        {
            if (id == par_id) continue;

            if (tin[to]) low[cur] = min(low[cur], tin[to]);
            else
            {
                self(self, to, id);
                low[cur] = min(low[cur], low[to]);
                if (low[to] > tin[cur]) most[id] = true;
            }
        }
    };  
    tarjan(tarjan,1,-1);

    ll ans= 1;
    vi color(n+1, -1);
    for (int i = 1; i <= n; i++)    
    {
        if (color[i] != -1) continue;
        
        color[i] = 1;
        bool cor = 1, bip = 1;
        int fixed_value = -1;

        auto dfs = [&](auto&& self, int v) -> void
        {
            if (a[v] != -1)
            {
                if (fixed_value == -1) fixed_value = a[v];
                else if (fixed_value != a[v]) cor = false;
            }

            for (auto [to,id] : graph[v])
            {
                if (most[id]) continue;

                if (color[to] == -1)
                {
                    color[to] = color[v]^1;
                    self(self,to);
                }
                else if (color[to] == color[v]) bip = false;
            }
        };
        dfs(dfs,i);

        if (!cor) ans = 0;
        else if (!bip)
        {
            if (fixed_value != -1 && fixed_value != 0) ans = 0;
        }
        else
        {
            if (fixed_value == -1) ans = ans * V % mod;
        }

    }

    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();
}