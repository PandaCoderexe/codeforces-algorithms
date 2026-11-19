// Tablica różnicowa dla pokrycia przedziałami
//
// Oryginał w zbiorze codeforces/2263/greedy/2263C1.cc
// https://codeforces.com/contest/2263
//
// Co oblicza kod
//
// Wypisać wszystkie x z 0..n-1, które nie należą do żadnego przedziału [a[k]*k,min(n-1,(a[k]+1)*k-1)].
//
// Pomysł
//
// Każdy zakaz dodać jako +1 na początku i -1 za końcem. Jednym skanem prefiksowym znaleźć pozycje z pokryciem zero.
//
// Stan i niezmiennik
//
// cur po aktualizacji diff[i] jest liczbą zakazanych przedziałów zawierających i. do wyniku trafiają dokładnie cur==0.
//
// Złożoność
//
// Czas O(n), pamięć O(n).
//
// Przypadki brzegowe
//
// a[k]>=0. l>=n pomija przedział. r=n-1 nie wymaga odejmowania poza dziedziną. Iloczyny int muszą mieścić się w typie.
//
// Kiedy rozpoznać ten wariant
//
// Wiele statycznych przedziałów w jednej dyskretnej dziedzinie i potrzebne tylko zbiorcze pokrycie. prefiks różnic jest prostszy niż drzewo.
//
// Warunki i uwagi
//
// - Nie rozwiązuje dodatkowych obowiązków trafiania bloków z C2. Indeksy i iloczyny wymagają ograniczonego nieujemnego a.
//
// KONIEC OPISU
#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n;
    cin >> n;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<int> diff(n + 1);
    for (int k = 1; k <= n; k++)
    {
        int l = a[k] * k, r = min(n - 1, (a[k] + 1) * k - 1);
        if (l >= n) continue;

        diff[l]++;
        if (r + 1 < n) diff[r + 1]--;
    }

    vector<int> ans;
    int cur = 0;

    for (int i = 0; i < n; i++)
    {
        cur += diff[i];
        if (cur == 0) ans.push_back(i);
    }

    cout << ans.size() << '\n';
    for (int x : ans) cout << x << ' ';
    cout << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int t; cin >> t;
    while (t--) solve();
}