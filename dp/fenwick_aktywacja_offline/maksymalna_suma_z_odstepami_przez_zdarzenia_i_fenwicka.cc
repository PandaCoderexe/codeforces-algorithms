// DP, aktywacja offline i maksimum prefiksowe
//
// Oryginał w zbiorze codeforces/2244/dp/2244G.cc
// https://codeforces.com/contest/2244
//
// Co oblicza kod
//
// Znaleźć maksymalną sumę a po wybranych rosnących indeksach, gdzie sąsiednie wybrane j<i spełniają i-j>max(a[i],a[j]). pusty wybór dopuszcza wynik 0.
//
// Pomysł
//
// Warunek i>j+a[j] obsłużyć aktywacją dp[j] dopiero w chwili j+a[j]+1. Drugi warunek j<i-a[i] obsłużyć zapytaniem Fenwicka do i-a[i]-1.
//
// Stan i niezmiennik
//
// W chwili i Fenwick zawiera dokładnie już aktywne dp[j] na pozycji j. dp[i]=a[i]+max(0,max_aktywnych_j<=i-a[i]-1 dp[j]). implementacja bierze max z samotnym a[i].
//
// Złożoność
//
// Czas O(n log n), pamięć O(n).
//
// Przypadki brzegowe
//
// a[i]>=0 zapewnia przyszłe terminy aktywacji. ujemne wartości mogą indeksować stare lub ujemne zdarzenia. Strict > wymaga +1 i -1. Brak aktywnych stanów oznacza -INF.
//
// Kiedy rozpoznać ten wariant
//
// Przejście DP ma dwie nierówności zależne oddzielnie od kandydata i bieżącego elementu. jedna staje się czasem aktywacji, druga granicą zapytania.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll inf = -4e18;

struct Fenwick
{
    int n;
    vector<ll> bit;

    Fenwick(int _n)
    {
        n = _n;
        bit.assign(n+1, inf);
    }

    void update(int i, ll val)
    {
        while(i <= n)
        {
            bit[i] = max(bit[i], val);  
            i += i & -i;
        }
    }

    ll query(int i)
    {
        ll res = inf;

        while(i > 0)
        {
            res = max(res, bit[i]);
            i -= i & -i;
        }

        return res;
    }
};


void solve()
{
        int n;
    cin >> n;

    vector<ll> a(n+1), dp(n+1);
    vector<vector<int>> add(n+2);
    for (int i = 1; i <= n; i++) cin >> a[i];

    Fenwick fen(n);
    ll ans = 0;

    for (int i = 1; i <= n; i++)
    {
        for (int x: add[i]) fen.update(x, dp[x]);

        dp[i] = a[i];
        ll limit = i- a[i] -1;

        if (0 < limit)
        {
            ll cur = fen.query(min<ll>(n, limit));
            if (cur != inf) dp[i] = max(cur+ a[i], dp[i]);
        }

        ans = max(ans, dp[i]);
        ll from = i + a[i] + 1;
        if (from <= n) add[(int)from].push_back(i);
    }

    cout << ans << "\n";

}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) solve();

}