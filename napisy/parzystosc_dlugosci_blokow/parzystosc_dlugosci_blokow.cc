// Parzystość bloków po odcięciu monotonicznych brzegów
//
// Oryginał w zbiorze codeforces/2241/bits/2241F.cc
// https://codeforces.com/contest/2241
//
// Co oblicza kod
//
// Wypisać Alice wtedy i tylko wtedy, gdy po pominięciu początkowych zer i końcowych jedynek pozostaje blok o nieparzystej długości. inaczej Bob.
//
// Pomysł
//
// Najpierw dwoma niezależnymi skanami ustal granice l,r. W środku przejdź po maksymalnych blokach równych znaków i zakończ na pierwszym nieparzystym.
//
// Stan i niezmiennik
//
// Odcięte fragmenty mają postać samych 0 po lewej i samych 1 po prawej. Skan [l,r] testuje parzystość każdej pełnej pozostałej serii, bez tworzenia nowego napisu.
//
// Złożoność
//
// O(n) czasu, O(n) pamięci na napis i O(1) pomocniczo.
//
// Przypadki brzegowe
//
// Dla napisu 0*1* l>r i wynikiem jest Bob. Dla jednego znaku środek jest pusty. Znaczenie nazw graczy i poprawność kryterium gry wymagają osobnego sprawdzenia treści zadania.
//
// Kiedy rozpoznać ten wariant
//
// Po usunięciu nieaktywnych brzegów wynik zależy od parzystości długości stałych bloków, a nie od liczby samych znaków.
//
// Warunki i uwagi
//
// - Interpretacja wyniku jako wygranej wymaga zasad gry; brak operacji bitowych.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int n;
    cin >> n;

    string s;
    cin >> s;

    int l = 0;
    int r = n - 1;

    while (l < n && s[l] == '0')
    {
        l++;
    }

    while (r >= 0 && s[r] == '1')
    {
        r--;
    }

    if (l > r)
    {
        cout << "Bob\n";
        return;
    }

    bool alice = false;

    for (int i = l; i <= r;)
    {
        int j = i;

        while (j <= r && s[j] == s[i]) j++;
        
        int len = j - i;

        if (len % 2 == 1)
        {
            alice = true;
            break;
        }


        i = j;
    }

    if (alice) cout << "Alice\n";
    else cout << "Bob\n";
    return;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }

    return 0;
}