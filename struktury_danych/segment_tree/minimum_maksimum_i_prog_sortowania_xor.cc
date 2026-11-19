// Segment tree z minimum, maksimum i progiem XOR
//
// Oryginał w zbiorze codeforces/2247/segmenttree/2247D.cc
// https://codeforces.com/problemset/problem/2247/D2
//
// Co oblicza kod
//
// Po każdej zmianie punktowej wyznacza minimalny próg k, dla którego można posortować tablicę zamianami indeksów i,j spełniających i XOR j<=k.
//
// Pomysł
//
// Dopełnij długość do potęgi dwójki i przechowuj minimum, maksimum oraz wymagany próg opt. Jeśli maksimum lewej połowy przekracza minimum prawej, do przeniesienia wartości między połowami potrzeba bitu odpowiadającego połowie długości zakresu.
//
// Stan i niezmiennik
//
// opt jest maksimum progów dzieci i połowy długości segmentu, jeśli między połowami istnieje inwersja. Sztuczne liście mają min=LLONG_MAX i max=LLONG_MIN, więc są neutralne dla porównań.
//
// Złożoność
//
// O(n) budowy i pamięci, O(log n) na zmianę punktową, O(1) odczytu odpowiedzi z korzenia.
//
// Przypadki brzegowe
//
// - Indeksy zadania i struktury są od zera.
// - Powtarzające się wartości są dopuszczalne.
// - n=1 oraz n niebędące potęgą dwójki.
// - Kod wypisuje odpowiedź także dla początkowej tablicy.
//
// Kiedy rozpoznać ten wariant
//
// Gdy łączenie dwóch sąsiednich segmentów wymaga kilku statystyk i wykrycia inwersji między ich skrajnymi wartościami.
//
// Warunki i uwagi
//
// - Oryginalny lokalny plik nazywa się D, lecz opis odpowiada oficjalnej wersji D2 z indeksami 0..n-1.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

ll power2 = 1;

struct Node 
{
    ll minimum;
    ll maximum;
    ll opt;
};

struct Seg
{
    int n;
    vector<Node> tree;
    vector<ll> nums;
    Seg(int n_, const vector<ll> nums_)
    {
        n = n_;
        while (power2 < n) power2 *=2;
        tree.assign(power2*4+4, Node());
        nums = nums_;
        Node node = build(0, power2-1, 0);
        cout << node.opt << "\n";
    }

    Node build(int l, int r, int i)
    {
        if (l == r) 
        {
            if (l < n) tree[i] = {nums[l], nums[l], 0};
            else tree[i] = {LLONG_MAX, LLONG_MIN, 0};
            return tree[i];
        }
        int m = l + (r-l) /2;

        Node left = build(l, m, i*2+1);
        Node right = build(m+1, r, i*2+2);
        Node ans;

        ans.minimum = min(left.minimum, right.minimum);
        ans.maximum = max(left.maximum, right.maximum);
        ans.opt = max(left.opt, right.opt);

        if (left.maximum > right.minimum) ans.opt = max(ans.opt, (ll)(r - l + 1) / 2);
        tree[i] = ans;
        return tree[i];
    }

    void update(int i, int l, int r, int i_update, ll val)
    {
        if (l == r)
        {
            nums[i_update] = val;
            tree[i] = {val, val, 0};
            return;
        }

        int m = l + (r - l) / 2;

        if (i_update <= m) update(i * 2 + 1, l, m, i_update, val);
        else update(i * 2 + 2, m + 1, r, i_update, val);

        Node left = tree[i * 2 + 1];
        Node right = tree[i * 2 + 2];
        Node ans;

        ans.minimum = min(left.minimum, right.minimum);
        ans.maximum = max(left.maximum, right.maximum);
        ans.opt = max(left.opt, right.opt);

        if (left.maximum > right.minimum) ans.opt = max(ans.opt, (ll)(r - l + 1) / 2);

        tree[i] = ans;
    }
};

void solve()
{
    ll n, q; cin >> n >> q;
    vector<ll> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];
    power2 = 1;

    Seg seg = Seg(n, nums);

    for (int i = 1; i <= q; i++)
    {
        ll j, val;
        cin >> j >> val;
        seg.update(0, 0, power2-1, j, val);
        cout << seg.tree[0].opt << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t; cin>>t;
    while(t--) solve();
}