// Teleskopowanie sumy różnic
//
// Oryginał w zbiorze codeforces/2171/math/2171B.cc
// https://codeforces.com/contest/2171
//
// Co oblicza kod
//
// Uzupełnia nieznane wartości tak, aby zminimalizować wartość bezwzględną sumy sąsiednich różnic.
//
// Pomysł
//
// Suma (a[1]-a[0])+...+(a[n-1]-a[n-2]) wynosi a[n-1]-a[0]. Wybierz zgodne końce, jeśli można, a wewnętrzne braki uzupełnij zerami.
//
// Stan i niezmiennik
//
// Wynik zależy wyłącznie od pierwszego i ostatniego elementu. Wewnętrzne wyrazy skracają się parami.
//
// Złożoność
//
// O(n) czasu i O(n) pamięci.
//
// Przypadki brzegowe
//
// - Oba końce nieznane ustaw na zero.
// - Przy jednym znanym końcu drugi skopiuj.
// - Wartość -1 oznacza brak, a nie zwykły element.
//
// Kiedy rozpoznać ten wariant
//
// Gdy suma sąsiednich różnic ma przeciwne znaki przy tych samych wewnętrznych elementach.
//
// KONIEC OPISU
#include <iostream>
#include <vector>

using namespace std;

void solve()
{
    int len;
    cin >> len;

    vector<int> nums(len);

    for (int i = 0; i < len; i++)
    {
        cin >> nums[i];
    }

    if (nums[0] == -1 && nums[len-1] == -1) {
        nums[0] = nums[len-1] = 0;
    } else if (nums[0] == -1) {
        nums[0] = nums[len-1];
    } else if (nums[len-1] == -1) {
        nums[len-1] = nums[0];
    }

    cout << abs(nums[0] - nums[len-1]) << "\n";
    for (int i = 0; i < len; i++)
    {
        if (nums[i] == -1)
        {
            cout << 0 << " ";
        }
        else
        {
            cout << nums[i] << " ";
        }
    }
    cout << "\n";
}

int main()
{
    int n;
    cin >> n;

    while(n--)
    {
        solve();
    }
}