// Równe reszty prefiksów z opóźnionym dopuszczaniem
//
// Oryginał w zbiorze codeforces/2276/pref/C.cc
// https://codeforces.com/contest/2276
//
// Co oblicza kod
//
// Policzyć spójne podtablice długości co najmniej k+1, których suma jest podzielna przez k.
//
// Pomysł
//
// Zapisuj reszty prefiksów modulo k, ale do licznika cnt dodawaj dopiero te prefiksy, które są oddalone od bieżącego końca o co najmniej k+1. Pusty prefiks reszty 0 jest dodany od początku, a odpowiedzi aktualizowane od i>=k.
//
// Stan i niezmiennik
//
// Przy końcu i>=k cnt zawiera pusty prefiks i prefiksy o indeksach j<=i-k-1. Równa reszta prefiksów oznacza podzielność sumy różnicy przez k. opóźnienie gwarantuje minimalną długość.
//
// Złożoność
//
// O(n+k) czasu i O(n+k) pamięci.
//
// Przypadki brzegowe
//
// Wymaga k>0 i nieujemnych wartości lub nieujemnych prefiksów modulo k. kod nie normalizuje ujemnych reszt. n<=k daje 0. Długość dokładnie k jest celowo wykluczona.
//
// Kiedy rozpoznać ten wariant
//
// Łączysz klasyczne liczenie równych reszt prefiksów z dolnym ograniczeniem długości podtablicy.
//
// Warunki i uwagi
//
// - Wymaga k>0 i nieujemnych reszt; ujemne sumy dają ujemny indeks cnt. Nie liczy podtablic długości dokładnie k.
//
// KONIEC OPISU
#include <bits/stdc++.h>
#define ll long long

using namespace std;

void solve()
{
    int n,k; cin >> n >> k;
    vector<ll> a(n), pref(n), reszta(n), cnt(k);
    ll ans = 0;
    cnt[0] = 1;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        pref[i] = a[i];
        if (i > 0) pref[i ] += pref[i-1];
        reszta[i] = pref[i] % k;
        if (i > k) cnt[reszta[i-k-1]]++;
        if (i >= k) ans += cnt[reszta[i]];
    } 

    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();

}