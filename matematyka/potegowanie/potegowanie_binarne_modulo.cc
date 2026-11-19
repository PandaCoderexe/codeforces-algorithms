// Potęgowanie binarne modulo
//
// Oryginał w zbiorze codeforces/2240/math/2240B.cc
// https://codeforces.com/contest/2240
//
// Co oblicza kod
//
// Oblicza 2^(rows*columns-(rows-scanRows+1)*(columns-scanColumns+1)) modulo 998244353.
//
// Pomysł
//
// Przetwarzaj wykładnik binarnie. Przy nieparzystym bicie pomnóż wynik przez bieżącą podstawę, potem podnieś podstawę do kwadratu.
//
// Stan i niezmiennik
//
// Iloczyn answer*number^degree jest równy pierwotnej potędze modulo MODULO.
//
// Złożoność
//
// O(log E) czasu dla wykładnika E>0 i O(1) pamięci.
//
// Przypadki brzegowe
//
// - Wykładnik zero daje jeden.
// - Rozmiar skanowanego prostokąta musi mieścić się w planszy.
// - Iloczyny rozmiarów muszą mieścić się w long long.
//
// Kiedy rozpoznać ten wariant
//
// Gdy trzeba policzyć dużą potęgę modulo, np. liczbę przypisań niezależnym zmiennym binarnym.
//
// KONIEC OPISU
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll MODULO = 998244353;

ll mod_power(ll number, ll degree) 
{
    ll answer = 1;

    while (degree > 0) 
    {
        if (degree % 2 == 1) 
        {
            answer = answer * number % MODULO;
        }

        number = number * number % MODULO;
        degree /= 2;


    }

    return answer;
}

void solve_case() 
{
    ll rows, columns, scanRows, scanColumns;
    cin >> rows >> columns >> scanRows >> scanColumns;

    ll allCells = rows * columns;
    ll scanPositions = (rows-scanRows + 1)*(columns-scanColumns+1);
    ll freeVariables = allCells - scanPositions;

    cout << mod_power(2, freeVariables) << '\n';
}

int main() 
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int tests;
    cin >> tests;

    while (tests--) 
    {
        solve_case();
    }

    return 0;
}