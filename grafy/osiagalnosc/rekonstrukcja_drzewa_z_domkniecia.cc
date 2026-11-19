// Rekonstrukcja z macierzy osiągalności
//
// Oryginał w zbiorze codeforces/2208/graph/2208D1.cc
// https://codeforces.com/contest/2208
//
// Co oblicza kod
//
// Usuwa relacje z pośrednikiem, sprawdza n−1 krawędzi i spójność podkładu, a następnie odtwarza osiągalność i porównuje całą macierz.
//
// Pomysł
//
// Usunąć relacje i→j z pośrednikiem i→k→j. sprawdzić n−1 krawędzi i spójność, następnie odtworzyć osiągalność wieloma DFS.
//
// Stan i niezmiennik
//
// n−1 krawędzi i spójność dowodzą drzewa podkładu. pełne porównanie reach z wejściem dowodzi wszystkich relacji.
//
// Złożoność
//
// O(n³) czasu i O(n²) pamięci. końcowa weryfikacja po drzewie O(n²).
//
// Przypadki brzegowe
//
// n=1. przekątna 1. niespójność. nadmiar relacji.
//
// Kiedy rozpoznać ten wariant
//
// Rozpoznaj wzorzec. rekonstrukcja z macierzy osiągalności. Usunąć relacje i→j z pośrednikiem i→k→j. sprawdzić n−1 krawędzi i spójność, następnie odtworzyć osiągalność wieloma DFS.
//
// Warunki i uwagi
//
// - Wymaga zwrotnej macierzy: algorytm ustawia przekątną osiągalności na 1.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve()
{
    int n;
    cin >> n;

    vector<string> edges(n);
    for (int i = 0; i < n; i++) cin >> edges[i];

    int cnt = 0;
    vector<vector<int>> directed(n);
    vector<vector<int>> undirected(n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j || edges[i][j] == '0') continue;

            bool direct = true;

            for (int k = 0; k < n; k++)
            {
                if (k == i || k == j) continue;

                if (edges[i][k] == '1' && edges[k][j] == '1')
                {
                    direct = false;
                    break;
                }
            }

            if (direct)
            {
                cnt++;

                directed[i].push_back(j);

                undirected[i].push_back(j);
                undirected[j].push_back(i);
            }
        }
    }

    if (cnt != n-1)
    {
        cout << "NO\n";
        return;
    }

    stack<int> st;
    vector<bool> visited(n, false);
    st.push(0);
    visited[0] = true;
    while (!st.empty())
    {
        int cur = st.top(); st.pop();
        for (int child : undirected[cur])
        {
            if (visited[child]) continue;
            visited[child] = true;
            st.push(child);
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            cout << "NO\n";
            return;
        }
    }

    vector<string> reach(n, string(n, '0'));

    for (int start = 0; start < n; start++)
    {
        stack<int> st2;
        st2.push(start);
        reach[start][start] = '1';

        while (!st2.empty())
        {
            int cur = st2.top();
            st2.pop();

            for (int child : directed[cur])
            {
                if (reach[start][child] == '1') continue;

                reach[start][child] = '1';
                st2.push(child);
            }
        }
    }

    if (reach != edges)
    {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";

    for (int i = 0; i < n; i++)
    {
        for (int j : directed[i]) cout << i + 1 << ' ' << j + 1 << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) solve();
}