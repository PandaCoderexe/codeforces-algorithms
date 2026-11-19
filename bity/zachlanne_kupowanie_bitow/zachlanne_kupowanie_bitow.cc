// Kupowanie najtańszych ustawionych bitów
//
// Oryginał w zbiorze codeforces/2240/bits/2240A.cc
// https://codeforces.com/contest/2240
//
// Co oblicza kod
//
// Zmaksymalizować sumę popcount length nieujemnych liczb, gdy suma ich wartości nie przekracza limitSum.
//
// Pomysł
//
// Każdy ustawiony bit poziomu b kosztuje 2^b, a takich bitów można użyć najwyżej length. Kupuj od najmniejszej wagi, odejmując koszt od budżetu.
//
// Stan i niezmiennik
//
// Po przetworzeniu wag mniejszych od bitValue kupiono maksymalną liczbę tańszych bitów. Żaden droższy bit nie daje większego zysku niż pojedynczy tańszy bit, więc wymiana nie pogarsza wyniku.
//
// Złożoność
//
// O(log(S+1)) czasu dla początkowego budżetu S i O(1) pamięci.
//
// Przypadki brzegowe
//
// S=0 daje 0. Przy wejściach dopuszczających dojście bitValue do 2^62 następne bitValue*=2 przepełnia signed long long, nawet jeśli budżet właśnie spadł do zera. wymagane są mniejsze ograniczenia. Dla length=0 budżet nie maleje. To budżet najwyżej S, nie wymóg sumy równej S.
//
// Kiedy rozpoznać ten wariant
//
// Jednostkowe zyski mają koszty będące potęgami dwójki i ograniczoną, jednakową dostępność na każdym poziomie.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

ll maximumSetBits(ll limitSum, ll length) {
    ll result = 0;
    ll bitValue = 1;

    while (bitValue <= limitSum) {
        ll affordableBits = limitSum / bitValue;
        ll usedBits = min(length, affordableBits);

        result += usedBits;
        limitSum -= usedBits * bitValue;

        bitValue *= 2;
    }

    return result;
}

int main() 
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int testCases;
    cin >> testCases;

    while (testCases--) 
    {
        ll maxSum, sequenceLength;
        cin >> maxSum >> sequenceLength;
        cout << maximumSetBits(maxSum, sequenceLength) << '\n';
    }

    return 0;
}