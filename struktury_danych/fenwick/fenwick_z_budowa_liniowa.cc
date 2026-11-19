// Fenwick z liniową budową
//
// Oryginał w zbiorze codeforces/tree/fenqick.cc
// Samodzielny fragment szablonu. Brak funkcji main jest zamierzony.
//
// Co oblicza kod
//
// Udostępnić wyłącznie poprawną strukturę Fenwick2. liniową budowę z a[1..n], dodawanie punktowe oraz sumę prefiksową.
//
// Pomysł
//
// Wybrać wyłącznie poprawny struct Fenwick2. Skopiować a[1..n] do bit, następnie każdy bit[i] dodać do i+lowbit(i). add i sum są standardowymi przejściami po indeksach.
//
// Stan i niezmiennik
//
// bit[i] przechowuje sumę przedziału [i−lowbit(i)+1,i]. Propagacja w rosnącej kolejności przesyła już zsumowany blok do jego nadrzędnego bloku.
//
// Złożoność
//
// O(n) budowy, O(log n) na aktualizację i sumę prefiksową, O(n) pamięci.
//
// Przypadki brzegowe
//
// a ma indeksy 1..n. add wymaga 1≤i≤n. sum(0)=0. n=1. ujemne przyrosty.
//
// Kiedy rozpoznać ten wariant
//
// Wiele sum prefiksowych i punktowych przyrostów oraz potrzeba liniowego przygotowania zamiast n wywołań add.
//
// Warunki i uwagi
//
// - Eksport obejmuje poprawny Fenwick2. Tablica a ma indeksy 1..n, a add wymaga indeksu dodatniego. Wadliwy pierwszy struct pozostaje wyłącznie w oryginale.
//
// KONIEC OPISU
#include <iostream>
#include <vector>

using namespace std;
struct Fenwick2
{
    int n;
    vector<long long> bit;

    Fenwick2(int n_, vector<long long>& a): n(n_)
    {
        bit.resize(n+1, 0);
        build(a);
    }

    void build(vector<long long>& a)
    {
        for (int i = 1; i <= n; i++) bit[i] = a[i];
        for (int i = 1; i <= n; i++)
        {
            int j = i + (i&-i);
            if (j <= n) bit[j] += bit[i];
        }
    }

    void add(int i, int v)
    {
        for (; i <= n; i+= i&-i) bit[i] += v;
    }

    long long sum(int i)
    {
        long long s = 0;
        for (; i > 0; i-=i&-i) s += bit[i];
        return s;
    }
};