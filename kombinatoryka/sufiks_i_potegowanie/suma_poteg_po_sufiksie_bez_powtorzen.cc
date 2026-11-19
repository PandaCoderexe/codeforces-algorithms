// Suma potęg modularnych na unikalnym sufiksie
//
// Oryginał w zbiorze codeforces/2285/combinatorics/C.cc
// https://codeforces.com/contest/2285
//
// Co oblicza kod
//
// Obliczyć 1+sum (a[i]-1)^(n-i) modulo 1e9+7 dla indeksów i od n-1 w dół do pierwszego indeksu z a[i]==a[i-1], z wyłączeniem tego indeksu.
//
// Pomysł
//
// Posortować tablicę, przechodzić od największych wartości. każdy składnik liczyć potęgowaniem binarnym. Powtórzenie zatrzymuje dalsze dodawanie, nie jest po prostu pomijane.
//
// Stan i niezmiennik
//
// ans zawiera 1 i składniki dla już odwiedzonych indeksów większych od bieżącego. pot utrzymuje res*a^b zgodne z początkową potęgą modulo MOD.
//
// Złożoność
//
// Czas O(n log n+n log n)=O(n log n), pamięć O(n).
//
// Przypadki brzegowe
//
// Brak powtórzeń przetwarza także i=0. powtórzona największa wartość daje natychmiast wynik 1. Oczekiwane a[i]>=1 i a[i] dostatecznie małe, bo początkowa baza nie jest redukowana przed a*a.
//
// Kiedy rozpoznać ten wariant
//
// Kombinatoryczny wynik ma postać sumy niezależnych potęg po uporządkowanych poziomach. bez treści zadania nie dopisywać znaczenia liczonych obiektów.
//
// Warunki i uwagi
//
// - Nie potwierdzono interpretacji zadaniowej; udokumentowano wyłącznie sumę obliczaną przez kod. Gdy |a[i]-1|>sqrt(LLONG_MAX), a*a może przepełnić long long przed modulo.
//
// KONIEC OPISU
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const long long MOD = 1e9 + 7;

ll pot(ll a, int b)
{
    ll res = 1;
    while (b > 0)
    {
        if (b % 2 == 1) res = res * a % MOD;
        a = a * a % MOD;
        b /= 2;
    }

    return res;
}

void solve()
{
    int n; cin >> n;
    vector<ll> a(n);

    for (int i = 0; i < n; i++) cin >> a[i];

    sort(a.begin(), a.end());
    ll ans = 1;
    for (int i = n-1; i >= 0; i--)
    {
        if (i > 0 && a[i] == a[i-1]) break;
        int cnt = n-i;
        ll ways = pot(a[i]-1, cnt);
        ans = (ans + ways) % MOD;
    }

    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();
}