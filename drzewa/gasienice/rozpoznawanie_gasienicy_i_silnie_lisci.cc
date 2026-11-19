// Drzewo-gąsienica i silnie liści
//
// Oryginał w zbiorze codeforces/2127/graph/2127D.cc
// https://codeforces.com/problemset/problem/2127/D
//
// Co oblicza kod
//
// Liczy uporządkowania wierzchołków na dwóch brzegach bez przecinania krawędzi. Rozpoznaje spójne drzewo-gąsienicę i mnoży liczby ustawień liści przy jego kręgosłupie.
//
// Pomysł
//
// Spójny graf z m>=n odrzuć. Dla każdego nieliścia policz sąsiadów będących liśćmi. Pozostałych może być najwyżej dwóch, więc nieliście tworzą ścieżkę. Pomnóż silnie liczb sąsiednich liści oraz czynnik orientacji.
//
// Stan i niezmiennik
//
// Po usunięciu liści każdy wierzchołek ma stopień najwyżej dwa. W spójnym drzewie otrzymany rdzeń jest ścieżką lub pojedynczym wierzchołkiem. W kodzie ans=2*produkt(fact[leafs]), dodatkowo razy dwa, gdy liczba liści jest mniejsza od n-1.
//
// Złożoność
//
// O(n+m) czasu na przypadek i O(n+m) pamięci. Silnie do 200004 przygotowywane są raz.
//
// Przypadki brzegowe
//
// - Wymagane n>=2 oraz prosty spójny graf.
// - Gwiazda i pojedyncza krawędź mają szczególny czynnik orientacji.
// - Co najmniej trzech niebędących liśćmi sąsiadów odrzuca graf.
//
// Kiedy rozpoznać ten wariant
//
// Gdy po usunięciu liści reszta ma tworzyć ścieżkę, a kolejność niezależnych liści przy każdym wierzchołku wnosi silnię.
//
// Warunki i uwagi
//
// - Spójność jest gwarancją zadania. Dla niespójnego wejścia kod nie jest ogólnym testem drzewa.
//
// KONIEC OPISU
#include <bits/stdc++.h>
#define sz(x) int(x.size())
using namespace std;
using ll = long long;

int fact[int(2e5+5)];
const ll mod = 1e9+7;

void solve()
{
    int n,m; cin >> n>>m;
    vector<vector<int>> graph(n+1);
    for (int i = 1; i <= m; i++)
    {
        int u, v; cin >>u>>v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    ll ans =2;
    int l = 0;
    if (m >= n)
    {
        cout << 0 << "\n";
        return;
    }

    for (int i = 1; i <= n; i++)
    {
        if (graph[i].size() >1)
        {
            int leafs = 0;
            for (int v:graph[i]) leafs+= (sz(graph[v]) == 1);
            
            if (leafs >= sz(graph[i])-2) (ans *= fact[leafs]) %= mod;
            else 
            {
                cout << 0 << "\n";
                return;
            } 
        }
        else l++;
    }
    if (l < n-1) ans *= 2;
    ans %= mod;
    cout << ans << "\n";

}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t; cin>>t;
    fact[0] = 1;
    for (int i = 1; i < 2e5+5; i++) fact[i] = (1ll * fact[i-1] * i) % mod;
    while(t--) solve();
}