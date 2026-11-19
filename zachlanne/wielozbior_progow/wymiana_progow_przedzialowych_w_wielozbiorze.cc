// Wielozbiór progów i wymiana przez lower_bound
//
// Oryginał w zbiorze codeforces/2121/dp/iceBaby.cc
// https://codeforces.com/contest/2121
//
// Co oblicza kod
//
// Po każdej parze [l,r] podać rozmiar wielozbioru progów minus jeden zgodnie z regułą implementacji.
//
// Pomysł
//
// Wystartować z wartownikiem 0. Usunąć jedno najmniejsze q>=r, jeśli istnieje, i wstawić l. Wielozbiór zachowuje wielokrotności progów.
//
// Stan i niezmiennik
//
// Po j krokach wielozbiór jest dokładnie wynikiem j wymian. odpowiedź zwiększa się o 1 wtedy i tylko wtedy, gdy przed wstawieniem nie istniał próg >=r.
//
// Złożoność
//
// Czas O(n log n), pamięć O(n).
//
// Przypadki brzegowe
//
// Powtarzające się l/r. r równe istniejącemu progowi. brak następcy. dane mogące usunąć wartownik wymagają sprawdzenia modelu zadania.
//
// Kiedy rozpoznać ten wariant
//
// Przedziały aktualizują uporządkowane progi metodą zastąpienia najmniejszego dopuszczalnego. nie przypisywać automatycznie semantyki LIS.
//
// Warunki i uwagi
//
// - Brak treści zadania; nie należy utożsamiać implementacji ze standardowym LIS/LNDS bez wyjaśnienia modelu przedziałów. Początkowe 0 jest wartownikiem wymagającym właściwej dziedziny danych.
//
// KONIEC OPISU
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    
    int q;
    cin >> q;
    while(q--)
    {
        int x;
        cin >> x;
        multiset<int> dp;
        dp.emplace(0);
    
        for (int i = 0; i < x; i++)
        {
            int l,r;
            cin >> l >> r;
            auto it = dp.lower_bound(r);

            if (it != dp.end())
            {
                dp.erase(it);
            }
            dp.insert(l);

            cout << (int)dp.size()-1 << ' ';
            
        }
        cout << "\n";
    }

    return 0;
}