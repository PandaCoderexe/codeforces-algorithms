// Zachłanne pakowanie jednakowych bloków w serie zer
//
// Oryginał w zbiorze codeforces/2126/dp/2126BB.cc
// https://codeforces.com/contest/2126
//
// Co oblicza kod
//
// Zsumować maksymalną liczbę bloków długości k w seriach zer przy co najmniej jednym dniu przerwy między blokami.
//
// Pomysł
//
// Seria długości L mieści t bloków wtedy i tylko wtedy, gdy t*k+(t-1)<=L, czyli t<=floor((L+1)/(k+1)). Wartownik jedynki zamyka ostatnią serię.
//
// Stan i niezmiennik
//
// len jest długością bieżącej serii zer. po jedynce dodawany jest dokładny wynik dla całej rozłącznej serii, a len zerowane.
//
// Złożoność
//
// Czas O(n), pamięć O(n) dla wejścia.
//
// Przypadki brzegowe
//
// k>=1. brak zer. seria kończąca się na ostatniej pozycji. obowiązkowa przerwa nie jest wymagana po ostatnim bloku.
//
// Kiedy rozpoznać ten wariant
//
// Jednakowe zadania mieszczą się w rozłącznych dostępnych przedziałach. stała przerwa daje prostą nierówność pakowania.
//
// KONIEC OPISU
#include <iostream>
#include <vector>

using namespace std;

void solve()
{
    int n,k;
    cin >> n >> k;
    vector<char> weather(n+1);
    for (int i = 0; i < n; i++)
    {
        cin >> weather[i];
    }
    weather[n] = '1';

    int len = 0, trips = 0;
    for (int i = 0; i <= n; i++)
    {
        if (weather[i] == '0')
        {
            len++;
        }
        else
        {
            trips += (len+1) / (k+1);
            //cout << len+1 << " / " << k+1 << " = " << len+1 / k+1 << "\n";
            len = 0;
        }
    }

    cout << trips << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) solve();
    return 0;
}