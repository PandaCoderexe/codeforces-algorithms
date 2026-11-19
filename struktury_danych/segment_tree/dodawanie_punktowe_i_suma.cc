// Dodawanie punktowe i suma przedziału
//
// Oryginał w zbiorze codeforces/tree/segTree.cc
// Samodzielny fragment szablonu. Brak funkcji main jest zamierzony.
//
// Co oblicza kod
//
// Dodaje wartość do jednego elementu i odpowiada na sumy przedziałów.
//
// Pomysł
//
// Zejdź do liścia wskazanego indeksu, dodaj przyrost i odtwórz sumy w drodze do korzenia. Zapytanie rozdziel na przecięte połowy.
//
// Stan i niezmiennik
//
// Każdy węzeł jest sumą swoich dzieci. Po aktualizacji jednego liścia zmieniają się tylko jego przodkowie.
//
// Złożoność
//
// O(n) budowy i pamięci, O(log n) na aktualizację lub zapytanie.
//
// Przypadki brzegowe
//
// - n=1.
// - Ujemne przyrosty i wielokrotne pokrycie całego zakresu.
// - Indeksy 0..n-1, zakresy domknięte.
//
// Kiedy rozpoznać ten wariant
//
// Punktowe przyrosty wartości i wiele sum zakresowych.
//
// Warunki i uwagi
//
// - Wymagane n>0 i poprawne granice 0..n-1. Szablon do dołączenia do programu.
//
// KONIEC OPISU
#include <iostream>
#include <vector>
using namespace std;
struct SegTree_PointRange
{
    int n;
    vector<long long> tree;

    SegTree_PointRange(int n_, vector<long long>& a): n(n_)
    {
        tree.resize(4*n, 0);
        build(a,0,n-1,1);
    }

    void build(vector<long long>& a, int tl, int tr, int v)
    {
        if (tl == tr) {tree[v] = a[tl]; return;}
        int tm = (tl + tr) / 2;
        build(a, tl, tm, 2*v);
        build(a, tm+1, tr, 2*v+1);
        tree[v] = tree[v*2] + tree[v*2+1];
    }

    void update(int pos, long long add)
    {
        update(1,0,n-1,pos,add);
    }

    void update(int v, int tl, int tr, int pos, long long add)
    {
        if (tl == tr) { tree[v] += add; return; }
        int tm = (tl + tr) / 2;
        if (pos <= tm) update(v*2,tl,tm,pos,add);
        else update(2*v+1, tm+1,tr,pos,add);
        tree[v] = tree[2*v] + tree[2*v+1];
    }

    long long query(int l, int r)
    {
        return query(1,0,n-1,l,r);
    }

    long long query(int v, int tl, int tr, int l, int r)
    {
        if (l > r) return 0;
        if (tl == l && tr == r) return tree[v];
        int tm = (tl+tr) /2;
        return query(2*v, tl, tm, l, min(r,tm)) + query(2*v+1, tm+1, tr, max(l,tm+1), r);
    }
};
