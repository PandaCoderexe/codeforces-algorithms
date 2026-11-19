// Aktualizacja punktowa licznika parzystych popcount
//
// Oryginał w zbiorze codeforces/2269/bits/2269D.cc
// https://codeforces.com/contest/2269
//
// Co oblicza kod
//
// Utrzymywać liczbę elementów, których 32-bitowy popcount jest parzysty, i wypisać ją przed aktualizacjami oraz po każdej z nich.
//
// Pomysł
//
// Przed nadpisaniem pozycji odejmij wkład starej wartości, potem dodaj wkład nowej. Pozostałe elementy nie zmieniają odpowiedzi.
//
// Stan i niezmiennik
//
// ans jest sumą wskaźników parzystości popcount wszystkich aktualnych a[i]. Każda aktualizacja zmienia dokładnie jeden składnik.
//
// Złożoność
//
// O(n+q) czasu i O(n) pamięci przy stałej szerokości int.
//
// Przypadki brzegowe
//
// Zera mają popcount 0, więc są wliczane. Pozycje wejściowe są 1-indeksowane. Dla liczb ujemnych builtin liczy bity po konwersji do unsigned int. znaczenie zadania zwykle wymaga nieujemnych liczb.
//
// Kiedy rozpoznać ten wariant
//
// Globalna statystyka jest sumą niezależnych wkładów, a operacje zmieniają pojedyncze elementy.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int n,q; cin >> n >> q;
    vector<int> a(n);
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        if (__builtin_popcount(a[i]) % 2 == 0) ans++;
    }
    cout << ans << " ";
    for (int i = 0; i < q; i++)
    {
        int p,x; cin>>p>>x;
        p--;
        if (__builtin_popcount(a[p]) % 2 == 0) ans--;
        a[p] = x;
        if (__builtin_popcount(a[p]) % 2 == 0) ans++; 
        cout << ans << " ";
    }

    cout << "\n";
}   

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();
}