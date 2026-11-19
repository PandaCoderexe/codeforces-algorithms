// Normalizacja przez odjęcie indeksu
//
// Oryginał w zbiorze codeforces/2266/sorting/2266D.cc
// https://codeforces.com/contest/2266
//
// Co oblicza kod
//
// Znajduje długość najdłuższego łańcucha kolejnych różnych wartości w multizbiorze a[i]-i.
//
// Pomysł
//
// Odejmij indeks od każdej wartości i posortuj malejąco. Powtórzenia pomiń, a przy różnicy jeden przedłuż bieżący łańcuch.
//
// Stan i niezmiennik
//
// cur_len opisuje długość łańcucha kończącego się na last_el. Duplikaty nie zmieniają końca ani długości.
//
// Złożoność
//
// O(n log n) czasu i O(n) pamięci.
//
// Przypadki brzegowe
//
// - Wszystkie znormalizowane wartości równe dają jeden.
// - Przerwa większa niż jeden rozpoczyna nowy łańcuch.
//
// Kiedy rozpoznać ten wariant
//
// Gdy zależność wartości od indeksu da się usunąć transformacją a[i]-i.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int n; cin >> n; 
    vector<int> a(n),b(n);
    for (int i = 0; i < n; i++) 
    {
        cin >> a[i];
        b[i] = a[i]-i;
    }

    sort(b.begin(), b.end(), greater<int>());

    int max_len = 1, last_el = b[0], cur_len = 1;
    for (int i = 1; i < n; i++)
    {
        if(b[i] == last_el) continue;
        if (b[i] == last_el-1)
        {
            cur_len++;
            last_el = b[i];
            max_len = max(max_len, cur_len);
        }
        else
        {
            cur_len = 1;
            last_el = b[i];
        }
    }

    cout << max_len << "\n";

}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();
}