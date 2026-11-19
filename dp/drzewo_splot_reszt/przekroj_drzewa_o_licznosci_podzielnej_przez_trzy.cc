// DP drzewa i splot osiągalnych reszt
//
// Oryginał w zbiorze codeforces/2184/dp/2184F.cc
// https://codeforces.com/contest/2184
//
// Co oblicza kod
//
// Sprawdzić istnienie przekroju korzeniowego drzewa o liczności podzielnej przez 3. wybieramy v albo przekroje wszystkich dzieci v.
//
// Pomysł
//
// Przetworzyć iteracyjny porządek DFS od końca. Zawsze można wybrać sam v, co daje resztę 1. alternatywa scala zbiory reszt dzieci przez dodawanie modulo 3.
//
// Stan i niezmiennik
//
// dp[v][r] oznacza osiągalną resztę liczności przekroju poddrzewa v. cur[0]=true jest neutralnym elementem splotu, lecz alternatywę dzieci dopisuje się tylko gdy v ma dzieci.
//
// Złożoność
//
// Czas O(n*3^2)=O(n), pamięć O(n).
//
// Przypadki brzegowe
//
// Pojedynczy liść ma wyłącznie resztę 1. nie wolno dopisać pustego przekroju przez cur[0] dla liścia. Iteracyjne przetwarzanie unika głębokiego stosu.
//
// Kiedy rozpoznać ten wariant
//
// Każde dziecko wnosi niezależny wybór do globalnej liczności modulo mała stała.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int n; cin >> n;
    vector<vector<int>> tree(n+1);

    for (int i = 0; i < n-1; i++)
    {
        int x,y;
        cin >> x >> y;

        tree[x].push_back(y);
        tree[y].push_back(x);
    }

    vector<int> order, parent(n+1, -1), st;
    parent[1] = 0;
    st.push_back(1);

    while(!st.empty())
    {
        int cur = st.back(); st.pop_back();

        order.push_back(cur);
        for (int child : tree[cur])
        {
            if (parent[child] == -1)
            {
                parent[child] = cur;
                st.push_back(child);
            }
        }
    }

    vector<vector<bool>> dp(n+1, vector<bool>(3));

    for (int i = (int)order.size()-1; i >= 0; i--)
    {
        int v = order[i];
        dp[v][1] = 1;
        int cur[] = {true, false, false};
        bool has_child = false;
        for (int child : tree[v])
        {
            if (parent[child] == v)
            {
                int now[]= {false, false, false};
                has_child = 1;

                for (int a = 0; a < 3; a++)
                {
                    for (int b = 0; b < 3; b++)
                    {
                        if (cur[a] && dp[child][b]) now[(a+b)%3] = 1;
                        
                    }
                }

                for (int a = 0; a < 3; a++) cur[a] = now[a];
            }
        }

        if (has_child)
        {
            for (int a = 0; a < 3; a++) dp[v][a] = dp[v][a] || cur[a];
            
            
        }

    }

    if (dp[1][0]) cout << "YES\n";
    else cout << "NO\n";
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) solve();
}