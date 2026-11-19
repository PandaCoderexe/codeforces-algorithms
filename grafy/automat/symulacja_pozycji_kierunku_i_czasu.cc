// Symulacja automatu ze znacznikiem zapytania
//
// Oryginał w zbiorze codeforces/2118/graph/2118D1.cc
// https://codeforces.com/contest/2118
//
// Co oblicza kod
//
// Skacze między kolejnymi światłami i wykrywa powtórzenie stanu (indeks,kierunek,czas modulo k). odpowiada, czy ruch opuści zakres świateł.
//
// Pomysł
//
// Skakać między światłami i oznaczać trójkę indeks,kierunek,czas modulo k numerem zapytania.
//
// Stan i niezmiennik
//
// Powtórzony stan ma identyczną przyszłość, zatem drugie odwiedzenie dowodzi cyklu.
//
// Złożoność
//
// O(nk+q(log n+nk)) czasu i O(nk+n+q) pamięci.
//
// Przypadki brzegowe
//
// Start za ostatnim światłem. k=1. wyjście w lewo. cykl.
//
// Kiedy rozpoznać ten wariant
//
// Rozpoznaj wzorzec. symulacja automatu ze znacznikiem zapytania. Skakać między światłami i oznaczać trójkę indeks,kierunek,czas modulo k numerem zapytania.
//
// Warunki i uwagi
//
// - Wymaga uporządkowanych pozycji i dodatniego k; tablica 2nk może być ogromna.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using State = tuple<ll, int, int>;

void solve()
{
    int n, k;
    cin >>n>>k;

    vector<ll> p(n), d(n);
    for(int i = 0; i < n; i++) cin >>p[i];
    for(int i = 0; i < n; i++) cin >> d[i];

    int q;cin>>q;
    vector<ll> queries(q);
    for(int i = 0; i < q; i++) 
    {
        cin >> queries[i]; 

        
    }


    vector<int> visited(n*2*k, 0);
    for (int i = 0; i < q; i++)
    {
        ll query = queries[i];

        int nearest = lower_bound(p.begin(), p.end(), query)-p.begin();

        if (nearest == n)
        {
            cout << "YES\n";
            continue;
        }
        bool finish = false;
        ll cost = p[nearest]-query;
        int time = cost % k;
        int dir = 1;
        int i_ = i+1;
        while(1)
        {
            ll state = (nearest *2+dir)*k+time;
            if (visited[state] == i_) break;

            visited[state] = i_;
            if (time == d[nearest]) dir ^= 1;
            int next = nearest+(dir == 0 ? -1 : 1);
            if (next< 0 || next >= n)
            {
                finish = 1;
                break;
            }

            time = (time+abs(p[next]-p[nearest])) % k;
            nearest = next;
            
        }
        if (finish) cout << "YES\n";
        else cout << "NO\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) solve();
}