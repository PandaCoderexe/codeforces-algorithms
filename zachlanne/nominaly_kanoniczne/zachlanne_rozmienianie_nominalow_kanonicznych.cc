// Kanoniczny zestaw nominałów
//
// Oryginał w zbiorze codeforces/996/greedy/996C.cc
// https://codeforces.com/contest/996
//
// Co oblicza kod
//
// Wyznaczyć minimalną liczbę nominałów 100,20,10,5,1 sumujących się do nieujemnego x.
//
// Pomysł
//
// Brać maksymalną liczbę największego nominału, przechodząc do reszty. Dla tego zestawu wymiany 5 jedynek->5,2 piątki->10,2 dziesiątki->20,5 dwudziestek->100 zmniejszają liczbę banknotów.
//
// Stan i niezmiennik
//
// Po rozpatrzeniu nominału pozostała kwota jest od niego mniejsza, a wybrane większe banknoty można zawrzeć w pewnym rozwiązaniu optymalnym dzięki wymianom.
//
// Złożoność
//
// Czas O(5)=O(1), pamięć O(1).
//
// Przypadki brzegowe
//
// x=0 daje 0. x równe nominałowi ma osobną, zbędną optymalizację. x>=0. Nie uogólniać dowodu na dowolne nominały.
//
// Kiedy rozpoznać ten wariant
//
// Przed zastosowaniem zachłanności w rozmienianiu trzeba wykazać kanoniczność konkretnego zestawu.
//
// Warunki i uwagi
//
// - ID pliku nie potwierdza treści zadania; kod wykonuje rozmienianie pieniędzy. Zachłanność działa dla tego zestawu, nie dla dowolnych nominałów.
//
// KONIEC OPISU
#include <iostream>
#include <algorithm>
#include <vector>

int main() 
{
    int x;
    std::cin >> x;
    std::vector<int> v = {100,20,10,5,1};
    int result = 0;

    if (std::count(v.begin(), v.end(), x) == 1) {
        std::cout << 1;
        return 0;
    }

    for (int bill : v) {
        if (x >= bill) {
            int count = x / bill;
            result += count;
            x %= bill;
        }
    }
    std::cout << result;
    return 0;
}