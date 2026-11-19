// Pakiety dodatniego zysku i kolejka progów
//
// Oryginał w zbiorze codeforces/2257/greedy/2257E.cc
// https://codeforces.com/contest/2257
//
// Co oblicza kod
//
// Dla wielu łańcuchów transakcji i kapitału x znaleźć największy osiągalny prefiks jednego łańcucha po możliwości korzystania z pozostałych. wypisać długość i pierwszy indeks osiągający maksimum.
//
// Pomysł
//
// Z każdego łańcucha wydzielić najkrótsze kolejne fragmenty z dodatnim łącznym zyskiem. Pakiet ma minimalny kapitał need=max(a[j]-dotychczasowy_zysk). Realizować dostępne następne pakiety z min-kolejki, potem osobno sprawdzić resztę każdego łańcucha.
//
// Stan i niezmiennik
//
// Pakiet z progiem <=money jest wykonalny bez ujemnego kapitału i zwiększa money, więc jego wykonanie nie szkodzi innym. W kolejce jest tylko pierwszy niewykonany pakiet każdego łańcucha, zachowując kolejność.
//
// Złożoność
//
// Dla M wszystkich transakcji. czas O(M log n+M), pamięć O(M+n).
//
// Przypadki brzegowe
//
// Brak zyskownych pakietów. transakcje zerowego zysku. progi mogą być 0. po zbiorczej fazie końcowa symulacja każdego łańcucha startuje z tym samym money i nie zapisuje strat na inne próby.
//
// Kiedy rozpoznać ten wariant
//
// Zależne działania wymagają zasobu, ale fragmenty o dodatnim łącznym zysku można bezpiecznie wykonywać zawsze, gdy są osiągalne.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve()
{
    int n;
    ll x;
    cin >> n >> x;

    vector<vector<ll>> a(n), b(n);
    vector<vector<array<ll,3>>> v(n);
    for (int i = 0; i < n; i++)
    {
        int m; cin >> m;

        a[i].resize(m);
        b[i].resize(m);
        for (int j = 0; j < m; j++) cin >> a[i][j];
        for (int j = 0; j < m; j++) cin >> b[i][j];

        ll sum = 0, need = 0;
        for (int j = 0; j < m; j++)
        {
            need = max(need, a[i][j] - sum);
            sum += b[i][j] - a[i][j];

            if (sum > 0)
            {
                v[i].push_back({need, sum, j});
                sum = 0;
                need = 0;
            }
        }
    }

    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
    vector<int> pos(n), done(n);
    for (int i = 0; i < n; i++)
    {
        if (!v[i].empty()) pq.push({v[i][0][0], i});
    }

    ll money = x;
    while (!pq.empty() && pq.top().first <= money)
    {
        auto [need, id] = pq.top();
        pq.pop();

        auto cur = v[id][pos[id]];
        money += cur[1];
        done[id] = cur[2] + 1;
        pos[id]++;

        if (pos[id] < (int)v[id].size()) pq.push({v[id][pos[id]][0], id});
    }

    int best = -1, who = -1;
    for (int i = 0; i < n; i++)
    {
        ll cur = money, h = done[i];

        for (int j = done[i]; j < (int)a[i].size(); j++)
        {
            if (cur < a[i][j]) break;
            cur -= a[i][j];
            cur += b[i][j];
            h++;
        }

        if (h > best)
        {
            best = h;
            who = i + 1;
        }
    }

    cout << best << " " << who << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while(t--) solve();
}