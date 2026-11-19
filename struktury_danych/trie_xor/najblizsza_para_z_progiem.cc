// Binarne trie xor z indeksem
//
// Oryginał w zbiorze codeforces/2093/tree/2093G.cc
// https://codeforces.com/contest/2093
//
// Co oblicza kod
//
// Znajduje najkrótszy przedział zawierający parę o XOR co najmniej k. dla k=0 wypisuje 1, przy braku pary −1.
//
// Pomysł
//
// Gałąź dająca większy prefiks XOR spełnia próg w całości. gałąź równości wymaga dalszego zejścia bitami.
//
// Stan i niezmiennik
//
// Poddrzewo przechowuje największy indeks w skanie rosnącym lub najmniejszy w malejącym, co minimalizuje odległość.
//
// Złożoność
//
// O(31n) czasu i pamięci.
//
// Przypadki brzegowe
//
// k=0. duplikaty. brak pasującej pary. n=1.
//
// Kiedy rozpoznać ten wariant
//
// Rozpoznaj wzorzec. binarne trie XOR z indeksem. Gałąź dająca większy prefiks XOR spełnia próg w całości. gałąź równości wymaga dalszego zejścia bitami.
//
// Warunki i uwagi
//
// - Wymaga n≥1 i liczb nieujemnych mieszczących się w 31 bitach. Drugi skan jest redundantny dla globalnego minimum.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;

int k;

struct Node
{
    int children[2] = {-1,-1};
    int lastIdx = -1;
};

struct Trie
{
    vector<Node> trie;

    Trie()
    {
        trie.push_back(Node());
    }

    void add(int num, int i)
    {
        int cur = 0;
        for (int bit = 30; bit >= 0; bit--)
        {
            int b = (num >> bit) & 1;
            if (trie[cur].children[b] == -1)
            {
                trie[cur].children[b] = trie.size();
                trie.push_back(Node());
            }
            cur = trie[cur].children[b];
            trie[cur].lastIdx = i;
        }
    }

    int query(int x, bool left)
    {
        int cur = 0, ans;
        if (left) ans = -1;
        else ans = 1e9;
        for (int bit = 30; bit >= 0; bit--)
        {
            int bk = (k >> bit) & 1;
            int bx = (x >> bit) & 1;
            int need = bx ^ 1;

            if (bk)
            {
                if (trie[cur].children[need] == -1)
                {
                    if (!left && ans == 1e9) return -1;
                    return ans;
                }
                cur = trie[cur].children[need];
            }
            else
            {
                if (trie[cur].children[need] != -1)
                {
                    int next = trie[cur].children[need];
                    if (left) ans = max(ans, trie[next].lastIdx);
                    else ans = min(ans, trie[next].lastIdx);
                }

                if (trie[cur].children[bx] == -1)
                {
                    if (!left && ans == 1e9) return -1;
                    return ans;
                }

                cur = trie[cur].children[bx];
            }
        }

        if (left) ans = max(ans, trie[cur].lastIdx);
        else ans = min(ans, trie[cur].lastIdx);
        if (!left && ans == 1e9) return -1;
        return ans;
    }
};

void solve()
{
    int n; cin >> n >> k;
    vector<int> a(n);
    for (int i  = 0; i < n; i++) cin >> a[i];
    if (k == 0)
    {
        cout << 1 << "\n";
        return;
    }
    Trie trie_left, trie_right;
    int ans = 1e9;
    //left
    trie_left.add(a[0], 0);
    for (int i = 1; i < n; i++)
    {
        int idx = trie_left.query(a[i], true);
        if (idx != -1) ans = min(ans, i - idx + 1);
        trie_left.add(a[i], i);
    }

    //right
    trie_right.add(a[n-1], n-1);
    for (int i = n-2; i >= 0; i--)
    {
        int idx = trie_right.query(a[i], false);
        if (idx != -1) ans = min(ans, idx - i +1);
        trie_right.add(a[i], i);
    }

    if (ans == 1e9) cout << -1 << "\n";
    else cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();
}