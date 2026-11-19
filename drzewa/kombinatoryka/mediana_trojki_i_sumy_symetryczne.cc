// Mediana trójki i sumy symetryczne
//
// Oryginał w zbiorze codeforces/2241/tree/2241E.cc
// https://codeforces.com/contest/2241
//
// Co oblicza kod
//
// Liczy trójki różnych wierzchołków, których mediana w drzewie ma kwadratową wartość a. sumuje iloczyny rozmiarów trzech różnych gałęzi wraz z singletonem mediany.
//
// Pomysł
//
// Dla mediany brać grupy. jej singleton i składowe po usunięciu. sum1,sum2,sum3 aktualizowane w tej kolejności od najwyższego stopnia sumują iloczyny trzech różnych grup.
//
// Stan i niezmiennik
//
// Trójka ma medianę v dokładnie przy wyborze trzech różnych grup. sum3 liczy wszystkie takie wybory bez trzech pętli.
//
// Złożoność
//
// O(n) czasu i pamięci, bo łączna liczba grup jest liniowa.
//
// Przypadki brzegowe
//
// Mediana należy do trójki. ścieżka. gwiazda. n<3. a=0.
//
// Kiedy rozpoznać ten wariant
//
// Rozpoznaj wzorzec. mediana trójki i sumy symetryczne. Dla mediany brać grupy. jej singleton i składowe po usunięciu. sum1,sum2,sum3 aktualizowane w tej kolejności od najwyższego stopnia sumują iloczyny trzech różnych grup.
//
// Warunki i uwagi
//
// - sqrt nie ma korekty zaokrąglenia; dla dużych long long potrzebna kontrola dokładności i r*r. Wymaga a≥0 i wyniku mieszczącego się w long long.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

ll sum_on_three(const vector<ll> & group )
{   
    ll sum1 = 0, sum2 = 0, sum3 = 0;

    for (ll g : group)
    {
        sum3 += sum2 * g;
        sum2 += sum1 * g;
        sum1 += g;
    }

    return sum3;
}

bool isit_square(ll x)
{
    ll r = sqrt(x);
    return r * r == x;
}

void solve()
{
    int n;
    cin >> n;
    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }

    vector<vector<int>> tree(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        int x, y;
        cin >> x >> y;

        tree[x].push_back(y);
        tree[y].push_back(x);
    }

    vector<int> parent(n + 1, -1), order;
    vector<ll> sub(n + 1, 0);
    parent[1] = 0;
    stack<int> st;
    st.push(1);

    while (!st.empty())
    {
        int cur = st.top();
        st.pop();

        order.push_back(cur);

        for (int child : tree[cur])
        {
            if (parent[child] == -1)
            {
                parent[child] = cur;
                st.push(child);
            }
        }
    }

    for (int i = (int)order.size() - 1; i >= 0; i--)
    {
        int cur = order[i];

        sub[cur] = 1;

        for (int child : tree[cur])
        {
            if (child == parent[cur]) continue;

            sub[cur] += sub[child];
        }
    }


    ll ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (isit_square(a[i]))
        {
            vector<ll> group;
            group.push_back(1);

            for (int child : tree[i])
            {
                if (child == parent[i])
                {
                    group.push_back(n - sub[i]);
                }
                else
                {
                    group.push_back(sub[child]);
                }
            }

            ans += sum_on_three(group);
        }
    }

    cout << ans << "\n";
    return;
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--)
    {
        solve();
    }

    return 0;
}