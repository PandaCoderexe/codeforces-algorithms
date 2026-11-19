// Zamiana istnienia drugiego cięcia na maksimum sufiksowe
//
// Oryginał w zbiorze codeforces/2242/suffixPrefix_sum/2242B.cc
// https://codeforces.com/contest/2242
//
// Co oblicza kod
//
// Sprawdzić istnienie 1<=x<y<=n-1 z p1[x]>=0 i p2[y]>=p2[x], dla wag p1. 1 daje +1, reszta -1. p2. 3 daje -1, reszta +1.
//
// Pomysł
//
// Zbuduj oba prefiksy. Zamiast próbować wszystkie y dla x, przechowuj maksimum p2 na sufiksie indeksów i sprawdzaj suf[x+1]>=p2[x].
//
// Stan i niezmiennik
//
// suf[i]=max p2[j] dla i<=j<=n-1. Prefiks p2[n] jest celowo wykluczony, dzięki czemu trzecia część podziału pozostaje niepusta.
//
// Złożoność
//
// O(n) czasu i O(n) pamięci.
//
// Przypadki brzegowe
//
// Dla n<3 pętla nie znajduje rozwiązania. Nierówności są nieostre, więc bilans 0 jest dozwolony. Interpretacja wag jako warunków mediany wymaga treści zadania.
//
// Kiedy rozpoznać ten wariant
//
// Szukasz dwóch uporządkowanych granic, a warunek na drugą porównuje wartość prefiksu z progiem zależnym od pierwszej.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;


void solve()
{
    int n; cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> p1(n + 1, 0);
    vector<int> p2(n + 1, 0);

    for (int i = 0; i < n; i++)
    {
        if (a[i] == 1) p1[i + 1] = p1[i] + 1;
        else p1[i + 1] = p1[i] - 1;

        if (a[i] == 3) p2[i + 1] = p2[i] - 1;
        else p2[i + 1] = p2[i] + 1;
    }

    vector<int> suf(n + 2, -1e9);

    for (int i = n - 1; i >= 0; i--)
    {
        suf[i] = max(suf[i + 1], p2[i]);
    }

    bool ok = false;

    for (int x = 1; x <= n - 2; x++)
    {
        if (p1[x] < 0) continue;

        if (suf[x + 1] >= p2[x])
        {
            ok = true;
            break;
        }
    }

    if (ok) cout << "YES\n";
    else cout << "NO\n";
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t;
    cin>>t;
    while(t--)
    {
        solve();
    }
}