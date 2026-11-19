// Binary search sumy ilorazów i konstrukcja bloków
//
// Oryginał w zbiorze codeforces/2274/binary_search/2274C.cc
// https://codeforces.com/contest/2274
//
// Co oblicza kod
//
// Znaleźć minimalne k z sumą po i=1..k wartości i*floor(k/i)>=n, a potem utworzyć n etykiet w blokach długości i z co najwyżej floor(k/i) blokami danego rozmiaru.
//
// Pomysł
//
// Sprawdzaj sumę po i z wcześniejszym zakończeniem na n. Po znalezieniu k bierz rozmiary malejąco, dla każdego wybierając min(floor(k/i),rem/i) bloków, a etykietę powtarzaj i razy.
//
// Stan i niezmiennik
//
// Suma kontrolna jest niemalejąca w k, co uzasadnia wyszukiwanie pierwszej wartości. Podczas konstrukcji rem równa się liczbie jeszcze niewypisanych pozycji. wybrana liczba bloków nie przekracza ani limitu rozmiaru, ani rem.
//
// Złożoność
//
// Pesymistycznie O(n log n) na wyszukiwanie, bo checker kosztuje O(k)<=O(n). konstrukcja i wynik O(n), pamięć O(n). Nie ma tu harmonicznego grupowania równych ilorazów.
//
// Przypadki brzegowe
//
// Wymaga n>=1. Minimalne k może być dużo mniejsze od n, ale nie wolno opisywać całego algorytmu jako O(log n). Suma i*floor(k/i) i liczba etykiet muszą mieścić się w long long.
//
// Kiedy rozpoznać ten wariant
//
// Monotoniczna pojemność jest sumą dostępnych bloków różnych rozmiarów, a po wyszukaniu granicy trzeba jeszcze jawnie odtworzyć obiekt.
//
// Warunki i uwagi
//
// - Checker jest O(k), więc pesymistyczna granica całego wyszukiwania to O(n log n), dodatkowo O(n) na wynik, a nie samo O(log n). Nie grupuje równych ilorazów.
//
// KONIEC OPISU
#include <bits/stdc++.h>
#define ll long long
#define vl vector<ll>
using namespace std;

ll n;

bool checker(ll k)
{
    ll sum = 0;

    for (ll i = 1; i <= k; i++)
    {
        sum += i * (k / i);
        if (sum >= n) return true;
    }

    return false;
}

void solve()
{
    cin >> n;

    ll left = 1, right = n;

    while (left < right)
    {
        ll mid = left + (right - left) / 2;

        if (checker(mid)) right = mid;
        else left = mid + 1;
    }

    ll k = left;
    cout << k << '\n';

    vl ans;
    ll rem = n, id = 1;

    for (ll i = k; i >= 1; i--)
    {
        ll cnt = min(k / i, rem / i);
        for (ll j = 0; j < cnt; j++)
        {
            for (ll x = 0; x < i; x++) ans.push_back(id);
            id++;
        }

        rem -= cnt * i;
    }

    for (ll x : ans) cout << x << " ";
    cout << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int t; cin >> t;
    while (t--) solve();
}