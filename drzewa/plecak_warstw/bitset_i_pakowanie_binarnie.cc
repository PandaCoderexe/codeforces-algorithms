// Bitset plecaka i pakowanie binarne
//
// Oryginał w zbiorze codeforces/2138/tree/2138C2.cc
// https://codeforces.com/problemset/problem/2138/C2
//
// Co oblicza kod
//
// Maksymalizuje długość najdłuższego wspólnego podciągu wszystkich binarnych napisów na ścieżkach od korzenia do liścia, przy dokładnie k etykietach zero. Niech h oznacza najmniejszą głębokość liścia przy głębokości korzenia jeden. Kod wypisuje h, gdy suma s osiągalna plecakiem rozmiarów warstw spełnia 0<=k-s<=n-sum(cnt). W przeciwnym razie wypisuje h-1.
//
// Pomysł
//
// Biegi równych rozmiarów warstw pakować w 1,2,4,... i resztę. osiągalne sumy aktualizować przesunięciem bitsetu.
//
// Stan i niezmiennik
//
// Bit s oznacza osiągalną sumę. binarne paczki reprezentują każdą liczbę wybranych warstw z biegu.
//
// Złożoność
//
// O(n+(W/w) Σ log(r_j+1)) operacji słowowych, O(n+W/w) słów pamięci. W=200005, w=liczba bitów słowa, r_j=długości biegów.
//
// Przypadki brzegowe
//
// Stały limit bitsetu. wiele równych warstw. k=0,n.
//
// Kiedy rozpoznać ten wariant
//
// Rozpoznaj wzorzec. bitset plecaka i pakowanie binarne. Biegi równych rozmiarów warstw pakować w 1,2,4,... i resztę. osiągalne sumy aktualizować przesunięciem bitsetu.
//
// Warunki i uwagi
//
// - Bitset ma stałe 200005 bitów. Grupuje wyłącznie kolejne równe liczności, nie wszystkie równe liczności globalnie.
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

    bitset<200005> dp;
    dp[0] = true;
    int len = 1;
    int last = cnt[1];
    for (int i = 2; i <= minimum; i++)
    {
        int cur = cnt[i];

        if (cur == last) len++;
        else
        {
            int take = 1;

            while (len > 0)
            {
                int group = min(take, len);

                dp |= dp << (group * last);

                len -= group;
                take *= 2;
            }

            len = 1;
            last = cur;
        }
    }
    int take = 1;

    while (len > 0)
    {
        int group = min(take, len);

        dp |= dp << (group * last);

        len -= group;
        take *= 2;
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