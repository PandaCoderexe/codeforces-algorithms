// Wstawianie indeksów przy ograniczeniach liczby większych
//
// Oryginał w zbiorze codeforces/2217/greedy/2217E.cc
// https://codeforces.com/contest/2217
//
// Co oblicza kod
//
// Zbudować permutację q tak, by dla każdego i dokładnie d[i] indeksów j>i z p[j]>p[i] znajdowało się na prawo od i w kolejności wyznaczonej q.
//
// Pomysł
//
// Dodawać indeksy od n do 1. Policzyć cnt już obecnych z p większym niż p[i], a potem wstawić i po dokładnie cnt-d[i] takich elementach. Wcześniejszych warunków to nie narusza, bo nowy indeks jest mniejszy.
//
// Stan i niezmiennik
//
// ord zawiera uporządkowane indeksy >i z poprawnymi warunkami. Wstawienie i zapewnia dokładnie d[i] większych po prawej, nie zmienia względnej kolejności starych indeksów.
//
// Złożoność
//
// Czas O(n^2), pamięć O(n). zarówno skan, jak i insert są liniowe.
//
// Przypadki brzegowe
//
// Wymagane d[i]>=0. d[i]>cnt daje -1. Równe p nie są liczone jako większe.
//
// Kiedy rozpoznać ten wariant
//
// Wymagania dla i zależą tylko od elementów o większym indeksie. dodawanie w odwrotnej kolejności pozwala ustawić pozycję bez psucia wcześniejszych warunków.
//
// Warunki i uwagi
//
// - Nie sprawdza d[i]<0; założenie nieujemnych d. ord.insert i skany dają O(n^2), pamięć O(n).
//
// KONIEC OPISU
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> p(n + 1), d(n + 1);

    for (int i = 1; i <= n; i++) cin >> p[i];
    for (int i = 1; i <= n; i++) cin >> d[i];

    vector<int> ord; 

    for (int i = n; i >= 1; i--) 
    {
        int cnt = 0;
        for (int idx : ord) 
        {
            if (p[idx] > p[i]) cnt++;
        }

        if (d[i] > cnt) 
        {
            cout << -1 << '\n';
            return;
        }

        int need = cnt - d[i]; 

        int seen = 0;
        int pos = 0;

        while (pos < (int)ord.size()) 
        {
            if (p[ord[pos]] > p[i]) 
            {
                if (seen == need) break;
                seen++;
            }
            pos++;
        }

        ord.insert(ord.begin() + pos, i);
    }

    vector<int> q(n + 1);
    for (int i = 0; i < n; i++) 
    {
        q[ord[i]] = i + 1;
    }

    for (int i = 1; i <= n; i++) 
    {
        cout << q[i] << (i == n ? '\n' : ' ');
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();

    return 0;
}