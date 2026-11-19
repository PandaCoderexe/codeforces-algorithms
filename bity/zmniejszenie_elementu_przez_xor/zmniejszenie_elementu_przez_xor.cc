// Porównanie elementu z XOR pozostałych
//
// Oryginał w zbiorze codeforces/2240/bits/2240C.cc
// https://codeforces.com/contest/2240
//
// Co oblicza kod
//
// Odtworzyć dokładny wynik kodu. dla n=1 zwrócić 0. dla n>1 i X=0 zwrócić 1. inaczej policzyć a[i] większe od XOR pozostałych.
//
// Pomysł
//
// Wylicz XOR X całej tablicy, a XOR pozostałych uzyskaj jako X^a[i]. Sprawdź nierówność bez ponownego skanowania tablicy.
//
// Stan i niezmiennik
//
// X^a[i] usuwa pojedynczy wkład a[i], bo v^v=0. Przy X!=0 kierunek porównania zależy od najwyższego ustawionego bitu X.
//
// Złożoność
//
// O(n) czasu i O(n) pamięci na przechowane elementy. porównania bitowe mają stały koszt.
//
// Przypadki brzegowe
//
// Specjalne wyniki n=1 i X=0 są częścią implementacji, nie liczbą elementów spełniających tę samą nierówność. Znaczenie tych wyników w zadaniu wymaga potwierdzenia jego reguł.
//
// Kiedy rozpoznać ten wariant
//
// Potrzebujesz XOR wszystkich elementów oprócz jednego lub porównania a[i] z takim XOR.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll mod = 998244353;

void solve()
{
    int n;
    cin >> n;
    
    vector<ll> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    if (n == 1)
    {
        cout << 0 << "\n";
        return;
    }

    ll ans = 0;

    ll X = 0;

    for (int i = 0; i < n; i++)
    {
        X ^= a[i];
    }
    
    if (X == 0) 
    {
        cout << 1 << "\n";
        return;
    }

    for (int i = 0; i < n; i++)
    {
        if ((X ^ a[i]) < a[i])
        {
            ans++;
            ans%=mod;
        }
    }

    cout << ans%mod << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    int t;
    cin >> t;

    while(t--)
    {
        solve();
    }

    return 0;
}