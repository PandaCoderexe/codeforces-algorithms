// Przedziały liści i cykliczny porządek dzieci
//
// Oryginał w zbiorze codeforces/2244/tree/2244F.cc
// https://codeforces.com/contest/2244
//
// Co oblicza kod
//
// Sprawdza max−min+1=liczba liści w każdym poddrzewie oraz najwyżej jeden cykliczny spadek minimów dzieci.
//
// Pomysł
//
// Scalać minimum,maksimum,liczbę liści. sprawdzać długość przedziału i spadki kolejnych minimów dzieci wraz z ostatnim→pierwszym.
//
// Stan i niezmiennik
//
// Przy różnych etykietach max−min+1=cnt dowodzi pełnego przedziału, a najwyżej jeden spadek dopuszcza obrót rosnącej kolejności.
//
// Złożoność
//
// O(n) czasu i pamięci.
//
// Przypadki brzegowe
//
// Jeden liść. jeden syn. luki. obrót. dwa spadki.
//
// Kiedy rozpoznać ten wariant
//
// Rozpoznaj wzorzec. przedziały liści i cykliczny porządek dzieci. Scalać minimum,maksimum,liczbę liści. sprawdzać długość przedziału i spadki kolejnych minimów dzieci wraz z ostatnim→pierwszym.
//
// Warunki i uwagi
//
// - Potrzebne różne etykiety liści; przy duplikatach równość długości przedziału nie dowodzi braku luk. Wewnętrzne a są ignorowane.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int inf = 1e9;

void solve()
{
    int n; cin >> n;
    vector<vector<int>> tree(n+1);
    vector<int> parent(n+1), a(n+1);

    for (int i = 2; i <= n; i++)
    {
        cin >> parent[i];
        tree[parent[i]].push_back(i);
    }

    for (int i = 1; i <= n; i++) cin >> a[i];
    
    vector<int> order, st;
    st.push_back(1);

    while(!st.empty())
    {
        int v = st.back();
        st.pop_back();

        order.push_back(v);

        for (int child : tree[v])
        {
            st.push_back(child);
        }
    }
    bool flag = 0;
    vector<int> minimum(n+1, inf), maximum(n+1, -inf), cnt(n+1, 0);
    for (int i = (int)order.size()-1; i >= 0; i--)
    {
        int v = order[i];

        if (tree[v].empty())
        {
            minimum[v] = a[v];
            maximum[v] = a[v];
            cnt[v] = 1;
        }
        else
        {
            for (int child : tree[v])
            {
                cnt[v] += cnt[child];
                minimum[v] = min(minimum[v], minimum[child]);
                maximum[v] = max(maximum[v], maximum[child]);
            }

            if (maximum[v]-minimum[v]+1 != cnt[v]) flag = 1;

            int zle = 0;
            int n_ = tree[v].size();

            for (int j = 0; j < n_; j++)
            {
                int fir_child = tree[v][j];
                int sec_child = tree[v][(j+1)%n_];
                if (minimum[fir_child] > minimum[sec_child]) zle++;
            }

            if (zle > 1) flag = true; 
        }
    }

    if (!flag) cout << "YES\n";
    else cout << "NO\n";
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) solve();
}