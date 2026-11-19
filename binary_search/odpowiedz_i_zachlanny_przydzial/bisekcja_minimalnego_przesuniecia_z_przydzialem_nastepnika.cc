// Przydział wolnego następcy i bisekcja parametru
//
// Oryginał w zbiorze codeforces/2157/dp/2157E.cc
// https://codeforces.com/contest/2157
//
// Co oblicza kod
//
// Po wyznaczeniu różnych b[i]>=a[i] znaleźć minimalne t, dla którego liczby min(a[i]+t,b[i]) mają krotności <=k.
//
// Pomysł
//
// Posortować a. Przydzielać od największych a najmniejszy wolny element >=a[i] ze zbioru 1..A+n. Bisekcja sprawdza częstości wartości obciętych na b[i].
//
// Stan i niezmiennik
//
// b[i] jest wynikiem zachłannego przydziału różnych pozycji. right=max(b[i]-a[i]) daje wszystkie różne wartości, więc jest wykonalne dla k>=1. Sprawdzenie buduje dokładne częstości min(a[i]+t,b[i]).
//
// Złożoność
//
// Dla U=A+n. O(U log U+n log U+(U+n)log(n+1)) czasu i O(U+n) pamięci. koszt inicjalizacji zbioru i zerowania cnt zależy od wartości, nie tylko n.
//
// Przypadki brzegowe
//
// n>=1,a[i]>=1,k>=1. b[i]<=A+n-1, więc cnt rozmiaru A+n wystarcza. Dodawanie a[i]+t musi mieścić się w int.
//
// Kiedy rozpoznać ten wariant
//
// Parametr przesuwa elementy ku różnym przydzielonym pozycjom, a wykonalność zależy od maksymalnej liczby kolizji.
//
// Warunki i uwagi
//
// - Złożoność zależy od wartości A=max(a), bo zbiór zawiera 1..A+n; O((A+n)log(A+n)+(A+n)log n) górnie, nie samo O(n log n). Założenia a[i]>=1, k>=1, n>=1. Monotoniczność predykatu wymaga uzasadnienia konstrukcją b.
// - Monotoniczność predykatu jest własnością konkretnego zachłannego przydziału; do wykorzystania jako rozwiązania innego zadania potrzebny osobny dowód.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t; cin >> t;
    while(t--)
    {
        int n,k; cin >>n >> k;

        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        sort(a.begin(), a.end());

        int limit =  *(a.end() - 1) + n;
        set<int> free;
        for (int i = 1; i <= limit; i++) free.insert(i);

        vector<int> b(n);
        for (int i = n-1; i >= 0; i--)
        {
            auto low = free.lower_bound(a[i]);
            b[i] = *low;
            free.erase(low);
        }

        int maximum = -1;
        for (int i = 0; i < n; i++) maximum = max(b[i] - a[i], maximum);
        int left = 0, right = maximum;

        auto checker = [&](int middle) -> bool {
            vector<int> cnt(limit);

            for (int i = 0; i < n; i++)
            {
                int value = min(a[i] + middle, b[i]);
                cnt[value]++;
                if (cnt[value] > k) return false;
            }

            return true;
        };

        while(left < right)
        {
            int middle = left + (right - left) /2;
            if (checker(middle)) right = middle;
            else left = middle+1;
        }   


        cout << right << "\n";
    }


}