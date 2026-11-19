// Zachłanny wybór globalnych maksimów i dwa końce
//
// Oryginał w zbiorze codeforces/2267/greedy/2267D.cc
// https://codeforces.com/contest/2267
//
// Co oblicza kod
//
// Sprawdzić, czy sekwencję elementów pobieranych malejąco z klas parzystości oryginalnego indeksu można przydzielać do dwóch końców, naprzemiennie wymagających klasy 0/1.
//
// Pomysł
//
// Posortować osobno dwie klasy indeksów. Zacząć od globalnego maksimum. oba końce wymagają potem przeciwnej klasy. Każde kolejne maksimum musi pasować do lewego albo prawego wymagania i odwraca wybrane wymaganie.
//
// Stan i niezmiennik
//
// need_l,need_r są wymaganymi klasami kolejnego elementu na obu końcach. Wskaźniki po,pe wskazują największe niewykorzystane wartości klas. każde powodzenie usuwa dokładnie jeden element.
//
// Złożoność
//
// Czas O(n log n), pamięć O(n).
//
// Przypadki brzegowe
//
// n=1 daje YES. Przy remisie wartości kod preferuje klasę 1. przy dopasowaniu obu końców preferuje lewy. Jeśli wartości mogą się powtarzać, kolejność remisów wymaga osobnego uzasadnienia.
//
// Kiedy rozpoznać ten wariant
//
// Malejące wartości określają kolejność dokładania, a jedyną pamięcią częściowej konstrukcji są wymagania na jej dwóch brzegach.
//
// Warunki i uwagi
//
// - Interpretacja YES/NO w pierwotnym zadaniu oraz dopuszczalność remisów wymagają jego treści; opisano literalny proces na klasach parzystości.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int n; cin>>n;
    vector<int> odd, even;
    for (int i = 0; i < n; i++)
    {
        int x; cin >> x;
        if (i % 2 == 0) odd.push_back(x);
        else even.push_back(x);
    }
    if (n == 1)
    {
        cout << "YES\n";
        return;
    }
    sort(odd.begin(), odd.end());
    sort(even.begin(), even.end());
    int po = odd.size() - 1, pe = even.size() - 1;

    int need_l,  need_r;
    if (odd[po] > even[pe])
    {
        need_l = need_r = 1;
        po--; 
    }
    else 
    {
        need_l = need_r = 0;
        pe--;
    }

    for (int i = 0; i < n-1; i++)
    {
        int biggest;
        if (po < 0) biggest =1;
        else if (pe<0 ) biggest = 0;
        else 
        {
            if (odd[po] > even[pe]) biggest = 0;
            else biggest=1;
        }

        if(biggest == need_l) need_l ^= 1;
        else if (biggest == need_r) need_r ^= 1;
        else
        {
            cout << "NO\n";
            return;
        }

        if (biggest == 0) po--;
        else pe--;


    }
    cout << "YES\n";

}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();
}