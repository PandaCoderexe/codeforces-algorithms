// Graf funkcyjny skompresowanych odbić
//
// Oryginał w zbiorze codeforces/2118/graph/2118D2.cc
// https://codeforces.com/contest/2118
//
// Co oblicza kod
//
// Grupuje światła według d−p i d+p modulo k, buduje 2n stanów zmiany kierunku i propaguje osiągalność wyjścia po odwróconych krawędziach.
//
// Pomysł
//
// Grupy reszt d−p oraz d+p wyznaczają kolejne odbicia. BFS od wyjść po krawędziach odwróconych zastępuje analizę cykli.
//
// Stan i niezmiennik
//
// good[v] zachodzi dokładnie wtedy, gdy łańcuch nxt kończy się na −1.
//
// Złożoność
//
// O((n+q) log n) czasu i O(n+q) pamięci.
//
// Przypadki brzegowe
//
// Brak grupy. start na świetle. cykl i jego poprzednicy.
//
// Kiedy rozpoznać ten wariant
//
// Rozpoznaj wzorzec. graf funkcyjny skompresowanych odbić. Grupy reszt d−p oraz d+p wyznaczają kolejne odbicia. BFS od wyjść po krawędziach odwróconych zastępuje analizę cykli.
//
// Warunki i uwagi
//
// - Wymaga rosnących pozycji i k>0. To nie SCC, lecz BFS od stanów bez następcy.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve()
{
    int n;
    ll k;
    cin >> n >> k;

    vector<ll> p(n), d(n);
    for (int i = 0; i < n; i++) cin >> p[i];
    for (int i = 0; i < n; i++) cin >> d[i];

    int q; cin >> q;
    vector<ll> queries(q);
    for (int i = 0; i < q; i++) cin >> queries[i];

    auto norm = [&](ll x) -> ll
    {
        return ((x % k)+k) % k;
    };

    map<ll, vector<pair<ll,int>>> rightGroup;
    map<ll, vector<pair<ll,int>>> leftGroup;

    for (int i = 0; i < n; i++)
    {
        ll rightKey = norm(d[i]-p[i]);
        ll leftKey = norm(d[i]+p[i]);

        rightGroup[rightKey].push_back({p[i], i});
        leftGroup[leftKey].push_back({p[i], i});
    }

    vector<int> nxt(2*n, -1);

    for (int i = 0; i < n; i++)
    {
        ll leftKey = norm(d[i]+p[i]);
        auto &left = leftGroup[leftKey];

        auto leftIt = lower_bound(
            left.begin(),
            left.end(),
            make_pair(p[i], -1)
        );

        if (leftIt != left.begin())
        {
            leftIt--;

            int nextLight = leftIt->second;
            nxt[i*2] = nextLight*2+1;
        }

        ll rightKey = norm(d[i]-p[i]);
        auto &right = rightGroup[rightKey];

        auto rightIt = upper_bound(
            right.begin(),
            right.end(),
            make_pair(p[i], n)
        );

        if (rightIt != right.end())
        {
            int nextLight = rightIt->second;
            nxt[i*2+1] = nextLight*2;
        }
    }

    vector<vector<int>> rev(2*n);
    vector<bool> good(2*n, false);
    queue<int> que;

    for (int state = 0; state < 2*n; state++)
    {
        if (nxt[state] == -1)
        {
            good[state] = true;
            que.push(state);
        }
        else
        {
            rev[nxt[state]].push_back(state);
        }
    }

    while (!que.empty())
    {
        int state = que.front();
        que.pop();

        for (int prev : rev[state])
        {
            if (good[prev]) continue;

            good[prev] = true;
            que.push(prev);
        }
    }

    for (ll query : queries)
    {
        ll key = norm(-query);

        auto groupIt = rightGroup.find(key);

        if (groupIt == rightGroup.end())
        {
            cout << "YES\n";
            continue;
        }

        auto &group = groupIt->second;

        auto it = lower_bound(
            group.begin(),
            group.end(),
            make_pair(query, -1)
        );

        if (it == group.end())
        {
            cout << "YES\n";
            continue;
        }

        int firstLight = it->second;
        int firstState = firstLight*2;

        if (good[firstState]) cout << "YES\n";
        else cout << "NO\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);

    int t; cin >> t;
    while (t--) solve();
}