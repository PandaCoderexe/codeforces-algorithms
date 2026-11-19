// Enumeracja początku deterministycznego ciągu
//
// Oryginał w zbiorze codeforces/2256/dp/2256B.cc
// https://codeforces.com/contest/2256
//
// Co oblicza kod
//
// Policzyć uzupełnienia znaków ? spełniające a[i]=a[i-2] xor 1.
//
// Pomysł
//
// Każda z dwóch klas parzystości indeksu jest naprzemienna, więc pierwsze min(n,2) bity determinują cały ciąg. Wygenerować najwyżej cztery możliwości i sprawdzić zgodność.
//
// Stan i niezmiennik
//
// Po ustaleniu pierwszych bitów każda kolejna pozycja jest jednoznaczna. Każdy poprawny ciąg odpowiada dokładnie jednej masce początkowej.
//
// Złożoność
//
// Czas O(n), pamięć O(n). liczba masek <=4.
//
// Przypadki brzegowe
//
// n>=1. n=1 ma tylko dwie maski. brak ?. sprzeczne ustalone znaki. modulo zbędne, bo wynik <=4.
//
// Kiedy rozpoznać ten wariant
//
// Rekurencja o stałym rzędzie determinuje całą odpowiedź z kilku pozycji początkowych. pełne DP byłoby nadmiarowe.
//
// Warunki i uwagi
//
// - n>=1. Wynik <=4, modulo jest zbędne. O(n) czasu i pamięci.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll mod = 998244353;

void solve()
{
    int n;
    string s;
    cin >> n >> s;

    ll ans = 0;
    int first = min(n, 2);  
    for (int mask = 0; mask < (1 << first); mask++)
    {
        vector<int> a(n); 

        a[0] = mask & 1; 
        if (n >= 2) a[1] = (mask >> 1) & 1; 
        for (int i = 2; i < n; i++) a[i] = a[i - 2] ^ 1; 

        bool ok = true;
        for (int i = 0; i < n; i++) 
        {
            if (s[i] != '?' && s[i] - '0' != a[i])
            {
                ok = false;
                break;

            }
        }
        if (ok) ans++;
    }

    cout << ans % mod << '\n';

}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();
}