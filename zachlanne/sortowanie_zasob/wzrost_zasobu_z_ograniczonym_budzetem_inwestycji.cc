// Zachłanny wzrost zasobu ze wspólnym budżetem
//
// Oryginał w zbiorze codeforces/2209/greedy/2209A.cc
// https://codeforces.com/contest/2209
//
// Co oblicza kod
//
// Po posortowaniu nieujemnych a zwiększać zasób c przez dostępne elementy a[i]<=c, inwestując w element najwyżej min(k,c-a[i]) jednostek wspólnego budżetu k. wypisać końcowe c.
//
// Pomysł
//
// Brać elementy od najmniejszego, bo ich dodanie nie zmniejsza zasobu i może odblokować kolejne. Każdy wykorzystany punkt budżetu zwiększa bieżący zasób o 1. wcześniejszy wzrost ułatwia dalsze kroki, dlatego wydawać możliwie dużo natychmiast.
//
// Stan i niezmiennik
//
// Przed i przetworzone elementy zostały dodane do c wraz z inwestycją, a k oznacza pozostały budżet. Gdy a[i]>c, żaden kolejny nie jest dostępny. use<=c-a[i] gwarantuje dostępność elementu również po zwiększeniu.
//
// Złożoność
//
// Czas O(n log n), pamięć O(n).
//
// Przypadki brzegowe
//
// c,k,a[i]>=0. Brak dostępnego elementu. zerowy budżet. a[i]=c nie pozostawia miejsca na inwestycję w ten element. Suma zasobu i wszystkie operacje muszą mieścić się w long long.
//
// Kiedy rozpoznać ten wariant
//
// Wspólny budżet można rozdzielać na dodatni przyrost zasobu, lecz pojemność każdej inwestycji zależy od aktualnego zasobu. To inny wariant niż wykonywanie dodatnio zyskownych pakietów bez budżetu.
//
// Warunki i uwagi
//
// - Interpretacja inwestowania wymaga operacji opisanych przez kod: najpierw można zwiększyć a[i] tylko do bieżącego c, następnie dodać całe zwiększone a[i] do c.
//
// KONIEC OPISU
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve()
{
    int n;
    long long c,k;
    cin >> n >> c >> k;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    sort(a.begin(), a.end());

    for (int i = 0; i < n; i++)
    {
        if (a[i] > c) break;

        long long use = min(k, c - a[i]);

        a[i] += use;
        k -= use;

        c += a[i];
    }

    cout << c << "\n";
}

int main()
{   
    int t;
    cin >> t;
    while(t--)
    {
        solve();
    }

    return 0;
}