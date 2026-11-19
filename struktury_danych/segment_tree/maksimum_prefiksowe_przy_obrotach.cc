// Suma i maksimum prefiksowe przy obrotach
//
// Oryginał w zbiorze codeforces/2249/segmenttree/2249C.cc
// https://codeforces.com/contest/2249
//
// Co oblicza kod
//
// Liczy obroty permutacji, których każdy prefiks jako zbiór wartości ma najwyżej dwie spójne składowe na ścieżce 1..n.
//
// Pomysł
//
// Wkład x to 1 minus liczba wcześniej dodanych sąsiadów x−1,x+1. Na podwojonej tablicy trzymać sumę i max prefiks. obrót zmienia tylko trzy wartości.
//
// Stan i niezmiennik
//
// Suma wkładów prefiksu jest liczbą jego spójnych przedziałów wartości. Merge. sum=a.sum+b.sum, pref=max(a.pref,a.sum+b.pref).
//
// Złożoność
//
// O(n log n) czasu i O(n) pamięci.
//
// Przypadki brzegowe
//
// n=1. wartości 1,n. połączenie dwóch składowych. obrót przez koniec.
//
// Kiedy rozpoznać ten wariant
//
// Rozpoznaj wzorzec. suma i maksimum prefiksowe przy obrotach. Wkład x to 1 minus liczba wcześniej dodanych sąsiadów x−1,x+1. Na podwojonej tablicy trzymać sumę i max prefiks. obrót zmienia tylko trzy wartości.
//
// Warunki i uwagi
//
// - Wymaga permutacji 1..n.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct Node
{
    ll sum, pref;
};

struct SegTree
{
    int n;
    vector<Node> tree;
    vector<int> contr;
    vector<int> pos;
    SegTree(int n_, const vector<int>& contr_, const vector<int>& pos_): contr(contr_), pos(pos_)
    {
        n = n_;
        tree.assign(n*8+8, Node());
        build(0, 2*n-1, 0);
    }

    void build(int l, int r, int v)
    {
        if (l == r)
        {
            tree[v] = {contr[l], contr[l]};
            return;
        }

        int m = l + (r - l) / 2;

        build(l, m, v * 2 + 1);
        build(m + 1, r, v * 2 + 2);

        tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
    }

    Node merge(const Node& a, const Node& b)
    {
        ll new_sum = a.sum+b.sum;
        ll new_pref = max(a.pref, b.pref + a.sum);
        return {
            new_sum,
            new_pref
        };
    }

    int relative(int x, int s) 
    {
        return (pos[x]-s+n)%n;
    }

    int new_val(int x, int s)
    {
        int rx = relative(x,s);
        int neighbour=0;
        if (x > 1 && relative(x-1, s) < rx) neighbour++;
        if (x < n && relative(x+1, s) < rx) neighbour++;
        return 1 - neighbour;
    }

    void update(int l, int r, int i, int idx, int new_value)
    {
        if (l == r && l == idx)
        {
            tree[i] = {
                new_value,
                new_value
            };
            return;
        }

        int m = l + (r-l)/2;
        if (idx > m) 
        {
            update(m+1, r, i * 2 + 2, idx, new_value);
        } 
        else 
        {
            update(l, m, i*2+1, idx, new_value);
        }
        
        Node left = tree[i*2+1], right = tree[i*2+2];
        tree[i] = merge(left, right);
    }

    Node query(int l, int r, int ql, int qr, int i)
    {
        if (ql <= l && r <= qr)return tree[i];

        int m = l + (r - l) / 2;
        if (qr <= m) return query(l, m, ql, qr, i*2+1);
        if (ql > m) return query(m + 1, r, ql, qr, i*2+2);

        Node left = query(l, m, ql, qr, i*2+1);
        Node right = query(m + 1, r, ql, qr, i*2+2);
        return merge(left, right);
    }
};

void solve()
{
    int n; cin >> n;
    vector<ll> p(n);
    vector<int> pos(n+1);
    for (int i = 0; i < n; i++) 
    {
        cin >> p[i];
        pos[p[i]] = i;
    }

    vector<int> contribution(2 * n);

    for (int i = 1; i <= n; i++)
    {
        int neighbours = 0;
        if (i > 1 && pos[i - 1] < pos[i]) neighbours++;
        if (i < n && pos[i + 1] < pos[i]) neighbours++;

        int con = 1 - neighbours;

        contribution[pos[i]] = con;
        contribution[pos[i] + n] = con;
    }

    SegTree seg = SegTree(n, contribution, pos);
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        Node node = seg.query(0, 2*n-1, i, i+n-1, 0);
        if (node.pref <= 2) ans++;

        if (i == n-1) break;

        int cur = p[i];
        int new_start = i+1;

        for (int x: {cur-1, cur, cur+1})
        {
            if (x < 1 || x > n)continue;

            int new_val = seg.new_val(x, new_start);

            seg.update(0, 2*n-1, 0, pos[x], new_val);
            seg.update(0, 2*n-1, 0, pos[x]+n, new_val);
        }
    }

    cout << ans << "\n";

}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) solve();
}