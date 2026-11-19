// Eliminacja dwóch typów krawędzi
//
// Oryginał w zbiorze codeforces/2245/graph/2245D2.cc
// https://codeforces.com/contest/2245
//
// Co oblicza kod
//
// Usuwa wierzchołki, przy których zanika jeden z dwóch typów krawędzi, przypisując znak oraz malejący moduł. pozostawiony rdzeń powoduje NO.
//
// Pomysł
//
// Utrzymywać liczniki obu typów, usuwać wierzchołki z zerem w którymś liczniku, nadając znak i moduły n,n−1,...
//
// Stan i niezmiennik
//
// W chwili usuwania aktywne krawędzie incydentne mają co najwyżej jeden typ. wcześniejszy wierzchołek otrzymuje większy moduł.
//
// Złożoność
//
// O(n+m) czasu i pamięci, powtórzenia w stosie filtruje processed.
//
// Przypadki brzegowe
//
// Izolowane wierzchołki. jeden typ. rdzeń obu typów. duplikaty stosu.
//
// Kiedy rozpoznać ten wariant
//
// Rozpoznaj wzorzec. eliminacja dwóch typów krawędzi. Utrzymywać liczniki obu typów, usuwać wierzchołki z zerem w którymś liczniku, nadając znak i moduły n,n−1,...
//
// Warunki i uwagi
//
// - Znaczenie typów operacji wymaga treści zadania. Nie utożsamiać z sortowaniem topologicznym zwykłego skierowanego grafu.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int n,m; cin >>n>>m;
    vector<vector<int>> op1(n+1), op2(n+1);
    vector<int> cnt1(n+1), cnt2(n+1);
    for (int i = 0; i < m; i++)
    {
        int op, x,y; cin >> op >> x >> y;
        if (op == 1)
        {
            op1[x].push_back(y);
            op1[y].push_back(x);
            cnt1[x]++; cnt1[y]++;
        }
        else
        {
            op2[x].push_back(y);
            op2[y].push_back(x);
            cnt2[x]++; cnt2[y]++;
        }

    }

    vector<bool> processed(n+1, 0);
    vector<int> sign(n+1), st;

    for (int i = 1;i <=n; i++)
    {
        if (op1[i].empty() || op2[i].empty()) st.push_back(i);
    }

    if (st.empty())
    {
        cout << "NO\n";
        return;
    }
    vector<int> order;

    while (!st.empty())
    {
        int cur = st.back();
        st.pop_back();

        if (processed[cur]) continue;
        processed[cur] = 1;
        order.push_back(cur);

        if (cnt1[cur] == 0) sign[cur] = -1;
        else sign[cur] = 1;

        for (int child : op1[cur])
        {
            if (processed[child]) continue;
            cnt1[child]--;
            if (cnt1[child] == 0 || cnt2[child] == 0) st.push_back(child);
        }

        for (int child : op2[cur])
        {
            if (processed[child]) continue;
            cnt2[child]--;
            if (cnt1[child] == 0 || cnt2[child] == 0) st.push_back(child);
        }
    }

    for (int i = 1; i <= n; i++)
    {
        if (!processed[i])
        {
            cout << "NO\n";
            return;
        }
    }

    vector<int> a(n + 1);

    for (int i = 0; i < n; i++)
    {
        int v = order[i], value = n - i;
        a[v] = sign[v] * value;
    }
    cout << "YES\n";
    for (int i = 1; i <= n; i++)
    {
        cout << a[i] << " ";
    }
    cout << "\n";

}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();
}