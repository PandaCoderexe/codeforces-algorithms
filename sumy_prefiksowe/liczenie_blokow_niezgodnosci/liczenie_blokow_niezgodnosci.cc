// Zapytania o liczbę bloków niezgodności
//
// Oryginał w zbiorze codeforces/2244/suffixPrefix_sum/2244E.cc
// https://codeforces.com/contest/2244
//
// Co oblicza kod
//
// Dla fragmentu [l,r] stwierdzić, czy minimum liczby bloków niezgodności z globalnymi wzorcami 0101... i 1010... jest najwyżej k.
//
// Pomysł
//
// Dla obu wzorców oznacz błędne pozycje i zbuduj prefiksy liczby początków bloków błędów. Zapytanie odejmuje prefiksy i dodaje blok przecinający lewą granicę, gdy bad[l]=1.
//
// Stan i niezmiennik
//
// pref[r]-pref[l] liczy początki bloków błędów ściśle po l i do r. dodanie bad[l] dokładnie uwzględnia blok zawierający l.
//
// Złożoność
//
// O(n+q) czasu i O(n) pamięci. każde zapytanie O(1).
//
// Przypadki brzegowe
//
// Jednoelementowy fragment jest obsługiwany przez bad[l]. Minimum dwóch przeciwnych wzorców usuwa zależność od parzystości globalnego indeksu l. Nie utożsamiaj liczby bloków z liczbą błędnych znaków.
//
// Kiedy rozpoznać ten wariant
//
// Zapytania dotyczą liczby serii zdarzeń w przedziale, więc prefiksuj początki serii zamiast samych zdarzeń.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve()
{
    int n, q;
    cin >> n >> q;
    string s; cin >> s;
    s = " " + s;

    vector<int> bad0(n+1), bad1(n+1), pref0(n+1), pref1(n+1);
    for (int i = 1; i <= n; i++)
    {
        char need0 = (i % 2 ? '0' : '1');
        char need1 = (i % 2 ? '1' : '0');

        if (s[i] != need0) bad0[i] = 1;
        if (s[i] != need1) bad1[i] = 1;
    }

    for (int i = 1; i <= n; i++)
    {
        pref0[i] = pref0[i-1];
        pref1[i] = pref1[i-1];

        if (bad0[i] && !bad0[i-1]) pref0[i]++;
        if (bad1[i] && !bad1[i-1]) pref1[i]++;
    }

    while(q--)
    {
        int l, r, k;
        cin >> l >> r >> k;

        int cnt0 = pref0[r] - pref0[l];
        if (bad0[l]) cnt0++;
        int cnt1 = pref1[r] - pref1[l];
        if (bad1[l]) cnt1++;

        int ans = min(cnt0, cnt1);
        if (ans <= k) cout << "YES\n";
        else cout << "NO\n";
    }
} 


int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) solve();
}