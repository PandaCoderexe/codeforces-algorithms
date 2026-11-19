// Bfs po parzystości długości
//
// Oryginał w zbiorze codeforces/2109/graph/2109D.cc
// https://codeforces.com/problemset/problem/2109/D
//
// Co oblicza kod
//
// Oblicza najkrótsze marszruty obu parzystości i porównuje je z sumą długości oraz sumą po odrzuceniu najmniejszej nieparzystej.
//
// Pomysł
//
// Stan (v,p) po krawędzi przechodzi do (u,p XOR 1). porównać odległości z sumą i sumą bez najmniejszej nieparzystej.
//
// Stan i niezmiennik
//
// depth[v][p] jest długością najkrótszej marszruty do v o parzystości p.
//
// Złożoność
//
// O(n+m+l) czasu i pamięci, l=liczba długości.
//
// Przypadki brzegowe
//
// Brak nieparzystej liczby. nieparzysty cykl. nieosiągalny cel. duża suma.
//
// Kiedy rozpoznać ten wariant
//
// Rozpoznaj wzorzec. BFS po parzystości długości. Stan (v,p) po krawędzi przechodzi do (u,p XOR 1). porównać odległości z sumą i sumą bez najmniejszej nieparzystej.
//
// Warunki i uwagi
//
// - Potwierdzone ograniczenia oficjalne: A_i≤10000 i l≤200000, więc sum≤2000000000. Typ int dla odd_sum jest bezpieczny w dziedzinie zadania; nie wymaga poprawki.
// - Przy uogólnieniu na większe długości lub większą ich liczbę odd_sum należy rozszerzyć do long long. Nie jest to błąd rozwiązania w oficjalnych ograniczeniach.
//
// KONIEC OPISU
#include <bits/stdc++.h>
#define sz(x) int(x.size())

using namespace std;
using ll = long long;

struct Node
{
    int vertex;
    ll len;
};

const int INF = 1e9 + 7;

void solve()
{
    int n, m, l; cin>>n>>m>>l;
    int min_odd = 1e9;
    ll sum = 0;
    vector<int> a(l);
    for (int i = 0; i < l; i++) 
    {
        cin >>  a[i];
        sum+=a[i];
        if (a[i]% 2 == 1) min_odd = min(min_odd, a[i]);
    }
    vector<vector<int>> graph(n+1);
    for (int i = 0; i < m; i++)
    {
        int u,v; cin >>u>>v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<vector<int>> depth(n + 1, vector<int>(2, INF));
    depth[1][0] = 0;
    queue<Node> q;
    q.push({1, 0});
    while(!q.empty())
    {
        auto [vertex, len] = q.front(); q.pop();


        for (int child: graph[vertex])
        {
            int parity = (len+1)%2;
            if (depth[child][parity] > len+1)
            {
                depth[child][parity] = len+1;
                q.push({child, len+1});
            }
        }
    }

    int init_par = sum%2;
    int odd_sum = sum - min_odd;
    string s = "";
    for (int i = 0; i <n;i++)
    {
        s.push_back('0');
        if ((depth[i+1][init_par] != INF && depth[i+1][init_par] <= sum) || (min_odd != 1e9 && depth[i+1][init_par^1] != INF && depth[i+1][init_par^1] <= odd_sum))
        {
            s[i] = '1';
        }
    }
    cout << s << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();
}