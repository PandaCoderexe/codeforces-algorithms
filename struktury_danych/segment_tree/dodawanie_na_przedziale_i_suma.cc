// Dodawanie na przedziale i suma przedziału
//
// Oryginał w zbiorze codeforces/tree/segTree.cc
// Samodzielny fragment szablonu. Brak funkcji main jest zamierzony.
//
// Co oblicza kod
//
// Dodaje wartość do wszystkich elementów zakresu i odpowiada na sumy dowolnych przedziałów.
//
// Pomysł
//
// Użyj lazy propagation. Pełne pokrycie zwiększa sumę o przyrost razy długość zakresu. Przed zejściem przekaż znacznik dzieciom.
//
// Stan i niezmiennik
//
// tree[v] zawiera aktualną sumę zakresu. lazy[v] oznacza przyrost uwzględniony w tej sumie, ale jeszcze nieprzekazany do dzieci.
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
// Wiele dodawań do przedziałów i zapytań o ich sumy.
//
// Warunki i uwagi
//
// - Wymagane n>0 i poprawne granice 0..n-1. Szablon do dołączenia do programu.
//
// KONIEC OPISU
#include <iostream>
#include <vector>
using namespace std;
struct SegTree_RangeRange
{
    int n;
    vector<long long> tree;
    vector<long long> lazy;
    SegTree_RangeRange(int n_, vector<long long>& vals): n(n_)
    {
        tree.resize(4*n, 0);
        lazy.resize(4*n,0);
        build(vals,1,0, n-1);
    }

    void build(vector<long long>& vals, int v, int tl, int tr)
    {
        if (tl == tr) {tree[v] = vals[tl]; return;}
        int tm  = (tr+tl) /2;
        build(vals, v*2, tl, tm);
        build(vals,v*2+1, tm+1, tr);
        tree[v] = tree[v*2]+ tree[v*2+1];
    }

    void push(int v, int tl, int tr)
    {
        if (lazy[v] == 0 || tl == tr) return;
        int tm = (tr+tl) / 2;
        long long add = lazy[v];

        lazy[v*2] += add;
        lazy[2*v+1] += add;

        tree[2*v] += add * (tm - tl + 1);
        tree[2*v+1] += add * (tr - (tm + 1) +1);

        lazy[v] = 0;
    }

    void update(int l, int r, long long add)
    {
        update(1, 0, n-1, l,r, add);
    }

    void update(int v, int tl, int tr, int l, int r, long long add)
    {
        if (l > r) return;
        if (l == tl && tr == r)
        {
            tree[v] += add * (tr - tl + 1);
            lazy[v] += add;
            return;
        }

        push(v,tl,tr);
        int tm = (tr+tl) / 2;
        update(v*2,tl,tm,l,min(r,tm), add);
        update(v*2+1,tm+1,tr,max(tm+1,l), r, add);

        tree[v] = tree[v*2] + tree[v*2+1];
    }

    long long rangeQuery(int l, int r)
    {
        return rangeQuery(1,0,n-1,l,r);
    }

    long long rangeQuery(int v, int tl, int tr, int l, int r)
    {
        if (l > r) return 0;
        if (l == tl && r == tr) return tree[v];
        push(v,tl,tr);
        int tm = (tr + tl) /2;
        return rangeQuery(v*2, tl, tm, l, min(r,tm)) + rangeQuery(2*v+1, tm+1, tr, max(l,tm+1), r);
    }
};
