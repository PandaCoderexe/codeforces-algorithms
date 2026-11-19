// Dwa fenwicki, inwersje i wyszukiwanie rangi
//
// Oryginał w zbiorze codeforces/2240/bit/2240E.cc
// https://codeforces.com/contest/2240
//
// Co oblicza kod
//
// Od prawej rekonstruuje nieznane wartości na podstawie różnic s, liczb większych aktywnych elementów i inwersji bloków znanych wartości.
//
// Pomysł
//
// alive liczy aktywne wartości, cur blok znanych wartości. Z różnicy s i base wyliczyć target, szukać najmniejszego v z alive.sum(v)+cur.sum(v−1)≥target.
//
// Stan i niezmiennik
//
// cur zawiera tylko bieżący blok i jest potem zerowany. alive usuwa kolejne ukończone bloki od prawej.
//
// Złożoność
//
// O(n log² n) czasu i O(n) pamięci. wyszukiwanie binarne wykonuje O(log n) sum BIT.
//
// Przypadki brzegowe
//
// Brak niewiadomych. pusty blok. skrajna ranga. wartości 1,n.
//
// Kiedy rozpoznać ten wariant
//
// Rozpoznaj wzorzec. dwa Fenwicki, inwersje i wyszukiwanie rangi. alive liczy aktywne wartości, cur blok znanych wartości. Z różnicy s i base wyliczyć target, szukać najmniejszego v z alive.sum(v)+cur.sum(v−1)≥target.
//
// Warunki i uwagi
//
// - Brak treści zadania: nie przypisuję s konkretnej statystyki poza równaniami kodu. Wartości p muszą należeć do 1..n; BIT.add(0,...) zapętla się. Binary search po prefiksach daje O(n log² n), nie O(n log n).
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct BIT
{
    int n;
    vector<ll> bit;

    BIT() {}

    BIT(int n_)
    {
        n = n_;
        bit.assign(n + 1, 0);
    }

    void add(int idx, ll val)
    {
        while (idx <= n)
        {
            bit[idx] += val;
            idx += idx & -idx;
        }
    }

    ll sum(int idx)
    {
        ll res = 0;

        while (idx > 0)
        {
            res += bit[idx];
            idx -= idx & -idx;
        }

        return res;
    }
};

void solve()
{
    int n;
    cin >> n;

    vector<char> type(n + 1);
    vector<ll> x(n + 1);
    vector<int> ans(n + 1, 0);

    vector<int> pos;
    vector<ll> s;

    pos.push_back(0);
    s.push_back(0);

    for (int i = 1; i <= n; i++)
    {
        cin >> type[i] >> x[i];

        if (type[i] == 'p')
        {
            ans[i] = x[i];
        }
        else
        {
            pos.push_back(i);
            s.push_back(x[i]);
        }
    }

    if ((int)pos.size() == 1)
    {
        for (int i = 1; i <= n; i++)
        {
            cout << ans[i] << " ";
        }

        cout << "\n";
        return;
    }

    BIT alive(n), cur(n);

    for (int i = 1; i <= n; i++)
    {
        alive.add(i, 1);
    }

    int last = pos.back();

    for (int i = last + 1; i <= n; i++)
    {
        alive.add(ans[i], -1);
    }

    for (int id = (int)pos.size() - 1; id >= 1; id--)
    {
        int l = pos[id - 1];
        int r = pos[id];

        ll need = s[id] - s[id - 1];

        ll base = 0;
        ll inv = 0;
        ll cnt = r - l - 1;

        vector<int> added;

        for (int i = l + 1; i <= r - 1; i++)
        {
            int val = ans[i];

            base += alive.sum(n) - alive.sum(val);
            inv += cur.sum(n) - cur.sum(val);

            cur.add(val, 1);
            added.push_back(val);
        }

        base -= cnt * (cnt - 1) / 2;
        base += inv;

        ll k = need - base;
        ll target = r - k;

        int low = 1;
        int high = n;

        while (low < high)
        {
            int mid = (low + high) / 2;

            ll pref = alive.sum(mid) + cur.sum(mid - 1);

            if (pref >= target)
            {
                high = mid;
            }
            else
            {
                low = mid + 1;
            }
        }

        int val = low;
        ans[r] = val;

        alive.add(val, -1);

        for (int i = l + 1; i <= r - 1; i++)
        {
            alive.add(ans[i], -1);
        }

        for (int val : added)
        {
            cur.add(val, -1);
        }
    }

    for (int i = 1; i <= n; i++)
    {
        cout << ans[i] << " ";
    }

    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }

    return 0;
}