// Persistent segment tree
//
// Oryginał w zbiorze codeforces/tree/pst.cc
// Samodzielny fragment szablonu. Brak funkcji main jest zamierzony.
//
// Co oblicza kod
//
// Kopiuje ścieżkę aktualizacji, pyta o sumę różnicy dwóch wersji i wybiera k-ty element różnicy.
//
// Pomysł
//
// Węzeł 0 to puste drzewo. aktualizacja kopiuje ścieżkę, zapytania odejmują dwa korzenie i wybierają stronę według różnicy liczników.
//
// Stan i niezmiennik
//
// Stare wersje nie zmieniają się. cnt jest sumą zakresu, a poprawna różnica wersji nieujemnym histogramem.
//
// Złożoność
//
// Aktualizacja i każde zapytanie O(log(U+1)), gdzie U to długość dziedziny wartości. q aktualizacji tworzy O(q log(U+1)) węzłów. Konstruktor dodatkowo rezerwuje (n+1)*(ceil(log2(n))+2) miejsc. Łączna zaalokowana pamięć O(n log(n+1)+q log(U+1)), z dodatkową tablicą korzeni po stronie wywołującego.
//
// Przypadki brzegowe
//
// Puste wersje. duplikaty. k=1 i całkowita liczność. niepoprawne k niewalidowane.
//
// Kiedy rozpoznać ten wariant
//
// Rozpoznaj wzorzec. persistent segment tree. Węzeł 0 to puste drzewo. aktualizacja kopiuje ścieżkę, zapytania odejmują dwa korzenie i wybierają stronę według różnicy liczników.
//
// Warunki i uwagi
//
// - queryPoint jest wyszukiwaniem k-tego, nie zapytaniem punktowym. Wywołujący dostarcza korzenie i zakres; brak walidacji k i nieujemności różnicy. cnt jest int.
//
// KONIEC OPISU
#include <iostream>
#include <vector>

using namespace std;

struct PST
{
    struct Node
    {
        int lc,rc;
        int cnt;
    };

    int n;
    vector<Node> tree;

    PST(int n_): n(n_)
    {
        int LOGK = 1;
        while((1 << LOGK) < n) LOGK++;
        int reserveNodes = (n+1) * (LOGK+2);
        tree.reserve(reserveNodes);
        tree.push_back({0,0,0});
    }

    int addNode(const Node& node)
    {   
        tree.push_back(node);
        return tree.size()-1;
    }

    int update(int v, int tl, int tr, int pos, int addCnt)
    {
        int nv = addNode(tree[v]);
        tree[nv].cnt+=addCnt;
        if (tl == tr) return nv;
        int tm = (tr+tl) / 2;
        if (pos <= tm) tree[nv].lc = update(tree[nv].lc,tl,tm,pos,addCnt);
        else tree[nv].rc = update(tree[nv].rc, tm+1, tr, pos,addCnt);
        return nv;
    } 

    long long queryDiffRange(int vl, int vr, int tl, int tr, int l, int r)
    {
        if (r < tl || l > tr) return 0;
        if (l <= tl && r >= tr)
        {
            return (long long)(tree[vr].cnt - tree[vl].cnt);
        }
        int tm = (tl + tr) / 2;
        long long A = queryDiffRange(tree[vl].lc, tree[vr].lc, tl, tm, l,r);
        long long B = queryDiffRange(tree[vl].rc, tree[vr].rc, tm+1, tr, l,r);
        return A + B;
    }

    long long queryPoint(int vl, int vr, int tl, int tr, int k)
    {
        if (tl == tr) return tl;
        int leftCount = tree[ tree[vr].lc ].cnt - tree[ tree[vl].lc ].cnt;
        int tm = (tl + tr) / 2;
        if ( leftCount >= k)
        {
            return queryPoint(tree[vl].lc, tree[vr].lc, tl, tm, k);
        }
        else 
        {
            return queryPoint(tree[vl].rc, tree[vr].rc, tm+1, tr, k-leftCount);
        }
    }
};