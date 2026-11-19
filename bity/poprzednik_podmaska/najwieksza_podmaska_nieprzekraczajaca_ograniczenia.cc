// Zachłanny poprzednik w zbiorze podmasek
//
// Oryginał w zbiorze codeforces/2260/greedy/2260C.cc
// https://codeforces.com/contest/2260
//
// Co oblicza kod
//
// Dla s=x+y znaleźć największą podmaskę a liczby s nieprzekraczającą x i wypisać s oraz x-a.
//
// Pomysł
//
// Znaleźć najwyższy bit x=1,s=0. Jeżeli go brak, x jest podmaską. W przeciwnym razie zachować wyższy prefiks x, wyzerować ten bit, a niższy sufiks wypełnić wszystkimi jedynkami dozwolonymi przez s.
//
// Stan i niezmiennik
//
// Wyższy prefiks jest zgodny z s, bo wybrano najwyższy konflikt. Wyzerowanie pierwszego konfliktu daje a<x. poniżej można zachłannie ustawić wszystkie bity s i uzyskać największą dopuszczalną wartość.
//
// Złożoność
//
// Czas O(63)=O(log zakresu), pamięć O(1).
//
// Przypadki brzegowe
//
// x,y>=0 i x+y<=LLONG_MAX. x=0. x już podmaską s. konflikt na bicie 0 nie ma niższego sufiksu.
//
// Kiedy rozpoznać ten wariant
//
// Maksymalizacja liczby pod ograniczeniem górnym i dozwoloną maską. pierwszy niedozwolony bit wymusza zejście poniżej granicy.
//
// Warunki i uwagi
//
// - Wymagane x,y>=0 oraz brak przepełnienia x+y. O(log(x+y)) czasu i O(1) pamięci.
//
// KONIEC OPISU
#include <bits/stdc++.h>

#define ll long long

using namespace std;

void solve()
{
    ll x, y; cin >> x >> y;

    ll s = x + y;

    int pos = -1;

    for (int i = 62; i >= 0; i--)
    {
        if ((x & (1LL << i)) && !(s & (1LL << i)))
        {
            pos = i;
            break;
        }
    }

    ll a;
    if (pos == -1) a = x;
    else
    {
        a = 0;
        for (int i = 62; i > pos; i--)
        {
            if (x & (1LL << i)) a |= (1LL << i);
        }


        for (int i = pos - 1; i >= 0; i--)
        {
            if (s & (1LL << i)) a |= (1LL << i);
        }
    }

    cout << s << " " << x - a << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}