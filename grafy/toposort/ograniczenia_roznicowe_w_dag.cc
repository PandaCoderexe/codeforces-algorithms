// Kahn i najdłuższe ścieżki wag 0/1
//
// Oryginał w zbiorze codeforces/2245/graph/2245D1.cc
// https://codeforces.com/contest/2245
//
// Co oblicza kod
//
// Z przekątnej wyznacza znaki, z par tworzy dolne ograniczenia modułów i wylicza je topologicznie. sprzeczności lub cykl dają NO.
//
// Pomysł
//
// Znaki wynikają z przekątnej. pary przeciwnych znaków tworzą łuki z nierównością nums[to]≥nums[from]+w. Kahn propaguje maksymalne dolne ograniczenia.
//
// Stan i niezmiennik
//
// Po zdjęciu z kolejki wszystkie poprzedniki są gotowe i nums[v] jest ostateczne.
//
// Złożoność
//
// O(n²) czasu i pamięci dla pełnej tabeli.
//
// Przypadki brzegowe
//
// Sprzeczna para. cykl. same wagi 0. izolowany wierzchołek.
//
// Kiedy rozpoznać ten wariant
//
// Rozpoznaj wzorzec. Kahn i najdłuższe ścieżki wag 0/1. Znaki wynikają z przekątnej. pary przeciwnych znaków tworzą łuki z nierównością nums[to]≥nums[from]+w. Kahn propaguje maksymalne dolne ograniczenia.
//
// Warunki i uwagi
//
// - Czyta n(n+1)/2 trójek niezależnie od m: wymaga pełnej tabeli. Odrzuca każdy cykl, nawet samych wag 0; nie jest ogólnym solverem ograniczeń różnicowych.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct Edge 
{
    int to;
    int weight = 0;
};

void solve()
{
    int n,m; cin >>n>>m;
    vector<vector<int>> dependencies(n+1, vector<int>(n+1, 0));
    for (int x = 1; x <= (n*(n+1))/2; x++)
    {
        int o,i,j;
        cin >> o >> i >> j;
        dependencies[i][j] = o;
    }
    vector<int> sign(n+1);
    for (int i = 1; i <= n; i++)
    {
        if (dependencies[i][i] == 1) sign[i] = 1;
        else sign[i] = -1;
    }

    vector<vector<Edge>> graph(n+1);
    vector<int> in(n+1);
    stack<int> st;

    for (int i = 1; i <= n; i++)
    {
        for (int j = i+1; j <= n; j++)
        {
            if (sign[i] == 1 && sign[j] == 1)
            {
                if (dependencies[i][j] == 2)
                {
                    cout << "NO\n";
                    return;
                }
            }
            else if (sign[i] == -1 && sign[j] == -1)
            {
                if (dependencies[i][j] == 1)
                {
                    cout << "NO\n";
                    return;
                }
            }
            else
            {
                int positive = i, negative = j;
                if (sign[j] == 1) swap(positive, negative);
                
                if (dependencies[i][j] == 1)
                {
                    graph[negative].push_back({positive,0});
                    in[positive]++;

                }
                else
                {
                    graph[positive].push_back({negative,1});
                    in[negative]++;
                }
            }
        }
    }

    queue<int> q;
    for (int i = 1; i <= n; i++)
    {
        if (in[i] == 0) q.push(i);
    }

    vector<int> nums(n+1, 1);
    int processed = 0;
    while(!q.empty())
    {
        int cur = q.front(); q.pop();

        processed++;
        for (auto [to, w] : graph[cur])
        {
            nums[to] = max(nums[to], nums[cur]+w);
            in[to]--;
            if (in[to] == 0) q.push(to);
        }
    }

    if (processed < n)
    {
        cout << "NO\n";
        return;
    }  

    cout << "YES\n";
    for (int i = 1; i <= n; i++)
    {
        cout << nums[i] * sign[i] << " ";
    }
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) solve();
}