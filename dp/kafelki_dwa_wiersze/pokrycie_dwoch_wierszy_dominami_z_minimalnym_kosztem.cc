// DP kafelkowania 2xn z pamięcią stałą
//
// Oryginał w zbiorze codeforces/2225/dp/2225C.cc
// https://codeforces.com/contest/2225
//
// Co oblicza kod
//
// Pokryć planszę 2xm dominami, minimalizując liczbę domin obejmujących dwie różne litery.
//
// Pomysł
//
// Ostatnia kolumna jest pokryta jednym pionowym dominem albo wraz z poprzednią dwoma poziomymi. Każdy klocek kosztuje 1 przy różnych końcach.
//
// Stan i niezmiennik
//
// dp[i]=min(dp[i-1]+[up[i-1]!=down[i-1]],dp[i-2]+[up[i-1]!=up[i-2]]+[down[i-1]!=down[i-2]]). prev1/prev2 trzymają dwie potrzebne wartości.
//
// Złożoność
//
// Czas O(m), dodatkowa pamięć DP O(1), pamięć wejścia O(m).
//
// Przypadki brzegowe
//
// m>=1. podstawa pustego prefiksu 0 i pierwszej kolumny. poziome kafle zawsze występują parą.
//
// Kiedy rozpoznać ten wariant
//
// Plansza ma stałą wysokość i tylko dwa sposoby zamknięcia ostatnich kolumn. można uniknąć ogólnego profilowego DP.
//
// Warunki i uwagi
//
// - m>=1. Czas O(m), pamięć O(m) dla napisów, O(1) dodatkowej pamięci DP.
//
// KONIEC OPISU
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void solution()
{
    int m;
    cin >> m;

    string up, down;
    cin >> up >> down;

    int prev2 = 0;
    int prev1 = (up[0] != down[0]);

    for (int col = 1; col < m; col++)
    {
        int use_vertical = prev1 + (up[col] != down[col]);
        int use_horizontal = prev2 + (up[col] != up[col - 1]) + (down[col] != down[col - 1]);

        int now = min(use_vertical, use_horizontal);
        prev2 = prev1;
        prev1 = now;

    }

    cout << prev1 << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tests;

    cin >> tests;

    while (tests--) solution();
    

    return 0;
}