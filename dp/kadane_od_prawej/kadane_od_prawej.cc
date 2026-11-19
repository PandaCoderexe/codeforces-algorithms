// Kadane od prawej i zliczanie dobrych początków
//
// Oryginał w zbiorze codeforces/2224/bruteForce/2224A.cc
// https://codeforces.com/contest/2224
//
// Co oblicza kod
//
// Policzyć indeksy i, dla których istnieje j>=i z dodatnią sumą a[i..j].
//
// Pomysł
//
// Przejdź od prawej i przechowuj najlepszą sumę niepustego odcinka zaczynającego się w bieżącym miejscu. Zwiększ licznik, gdy ta suma jest dodatnia.
//
// Stan i niezmiennik
//
// Po przetworzeniu i, best=max_{j>=i} suma(a[i..j]). Składnik a[i]+a[i+1] w kodzie jest nadmiarowy, bo poprzedni best>=a[i+1].
//
// Złożoność
//
// O(n) czasu, O(n) pamięci na tablicę i O(1) stanu.
//
// Przypadki brzegowe
//
// Wymaga n>=1. zero nie jest dodatnie. Wszystkie ujemne elementy dają 0, ale ujemny początek może być policzony dzięki dodatniemu dalszemu fragmentowi.
//
// Kiedy rozpoznać ten wariant
//
// Pytasz o możliwość uzyskania dodatniej sumy dla każdego początku, a nie tylko o jedno globalne maksimum Kadane’a.
//
// KONIEC OPISU
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
    {
        int n;
        cin >> n;

        vector<long long> a(n + 1, 0);

        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
        }

        int answer = 0;

        long long best = a[n];

        if (best > 0)
        {
            answer++;
        }

        for (int i = n - 1; i >= 1; i--)
        {
            best = max(a[i], max(a[i] + a[i + 1], a[i] + best));

            if (best > 0)
            {
                answer++;
            }
        }

        cout << answer << '\n';
    }

    return 0;
}