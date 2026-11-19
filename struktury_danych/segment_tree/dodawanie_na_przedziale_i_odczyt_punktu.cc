// Dodawanie na przedziale i odczyt punktu
//
// Oryginał w zbiorze codeforces/tree/segTree.cc
// Samodzielny fragment szablonu. Brak funkcji main jest zamierzony.
//
// Co oblicza kod
//
// Dodaje wartość do przedziału i odczytuje aktualną wartość wskazanego elementu.
//
// Pomysł
//
// Aktualizacja przechowuje znaczniki lazy jak w wersji sumowej. Odczyt schodzi jedną ścieżką, przekazując znaczniki do dzieci.
//
// Stan i niezmiennik
//
// Leniwy przyrost zakresu trafia do dzieci dopiero podczas zejścia. Przy dojściu do liścia wszystkie znaczniki z jego ścieżki zostały rozliczone.
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
// Wiele aktualizacji zakresów, gdy pytania dotyczą pojedynczych indeksów.
//
// Warunki i uwagi
//
// - Wymagane n>0 i poprawne granice 0..n-1. Szablon do dołączenia do programu.
//
// KONIEC OPISU
#include <iostream>
#include <vector>
using namespace std;
struct SegTree_RangePoint
{
    int n;
    vector<long long> tree;
    vector<long long> lazy;

    SegTree_RangePoint(int n_, vector<long long>& a): n(n_)
    {
        tree.resize(4*n, 0);
        lazy.resize(4*n, 0);
        build(a,0,n-1,1);
    }

    void build(vector<long long>& a, int tl, int tr, int v)
    {
        if (tl == tr) {tree[v] = a[tl]; return;}
        int tm = (tr + tl) / 2;
        build(a,tl,tm,v*2);
        build(a,tm+1, tr, 2*v+1);
        tree[v] = tree[2*v] + tree[2*v+1];
    }

    void push(int v, int tl, int tr)
    {
        if (lazy[v] == 0 || tl == tr) return;
        long long add = lazy[v];
        int tm = (tr + tl) / 2;

        lazy[2*v] += add;
        lazy[2*v+1] += add;

        tree[2*v] += add * (tm - tl + 1);
        tree[2*v+1] += add * (tr - (tm + 1) + 1);

        lazy[v] = 0;
    }

    void update(int l, int r, long long add)
    {
        update(1, 0, n-1, l, r, add);
    }

    void update(int v, int tl, int tr, int l, int r, long long add)
    {
        if (l > r) return;
        if (tl == l && tr == r)
        {
            tree[v] += add * (tr - tl + 1);
            lazy[v] += add;
            return;
        }
        push(v,tl,tr);
        int tm = (tl + tr) / 2;
        update(2*v, tl, tm, l, min(r,tm), add);
        update(2*v+1, tm+1, tr, max(l, tm+1), r, add);
        tree[v] = tree[2*v] + tree[2*v+1];
    }

    long long query(int pos)
    {
        return query(1,0,n-1,pos);
    }

    long long query(int v, int tl, int tr, int pos)
    {
        if (tl == tr) return tree[v];
        push(v,tl,tr);
        int tm = (tr + tl) / 2;
        if (pos <= tm) return query(2*v, tl, tm, pos);
        else return query(2*v+1, tm+1, tr, pos);
    }
};
