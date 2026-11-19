// Plecak 0/1 rozmiarów warstw
//
// Oryginał w zbiorze codeforces/2138/tree/2138C1.cc
// https://codeforces.com/problemset/problem/2138/C2
//
// Co oblicza kod
//
// Maksymalizuje długość najdłuższego wspólnego podciągu wszystkich binarnych napisów na ścieżkach od korzenia do liścia, przy dokładnie k etykietach zero. Niech h oznacza najmniejszą głębokość liścia przy głębokości korzenia jeden. Kod wypisuje h, gdy suma s osiągalna plecakiem rozmiarów warstw spełnia 0<=k-s<=n-sum(cnt). W przeciwnym razie wypisuje h-1.
//
// Pomysł
//
// Po wyznaczeniu najpłytszego liścia h rozmiary warstw potraktować jako wagi plecaka 0/1. głębsze wierzchołki dobierane są w liczbie od 0 do free.
//
// Stan i niezmiennik
//
// dp[s] oznacza sumę całych wybranych warstw. test końcowy wymaga 0≤k−s≤free.
//
// Złożoność
//
// O(nh) czasu i O(n) pamięci, h=minimalna głębokość liścia.
//
// Przypadki brzegowe
//
// Ścieżka. gwiazda. k=0,n. jeden poziom.
//
// Kiedy rozpoznać ten wariant
//
// Rozpoznaj wzorzec. plecak 0/1 rozmiarów warstw. Po wyznaczeniu najpłytszego liścia h rozmiary warstw potraktować jako wagi plecaka 0/1. głębsze wierzchołki dobierane są w liczbie od 0 do free.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve()
{
    int n,k; cin >>n>>k;
    vector<vector<int>> tree(n+1);
    vector<int> parent(n+1);

    for (int i = 2; i <= n; i++)
    {
        cin >> parent[i];
        tree[parent[i]].push_back(i);
    }

    vector<int> leafs, depth(n+1, -1);
    depth[1] = 1;
    stack<int> st;
    st.push(1);
    while(!st.empty())
    {
        int cur = st.top(); st.pop();

        if (tree[cur].empty())
        {
            leafs.push_back(cur);
        }

        for (int child : tree[cur])
        {
            depth[child] = depth[cur] + 1;
            st.push(child);
        }
    }

    int minimum = n;

    for (int leaf : leafs) minimum = min(minimum, depth[leaf]);

    vector<int> cnt(minimum + 1);
    for (int i = 1; i <= n; i++)
    {
        if (depth[i] <= minimum) cnt[depth[i]]++;
    }

    vector<bool> dp(n + 1, false);
    dp[0] = true;

    for (int i = 0; i <= minimum; i++)
    {
        int cur = cnt[i];

        for (int j = n - cur; j >= 0; j--)
        {
            if (dp[j]) dp[j + cur] = true;
        }
    }

    int sum = 0;
    for (int i : cnt) sum += i;
    int free = n - sum;
    bool can = 0;

    for (int i = 0; i <= sum; i++)
    {
        if (!dp[i]) continue;
        int remaining = k - i;
        if (0 <= remaining && remaining <= free)
        {
            can = 1;
            break;
        }
    }

    if (can) cout << minimum<< "\n";
    else cout << minimum-1 << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) solve();
}