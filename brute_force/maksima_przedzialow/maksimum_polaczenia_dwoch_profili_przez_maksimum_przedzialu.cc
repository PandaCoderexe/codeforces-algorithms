// Kwadratowy przegląd z bieżącym maksimum przedziału
//
// Oryginał w zbiorze codeforces/2207/dp/2207C.cc
// https://codeforces.com/contest/2207
//
// Co oblicza kod
//
// Obliczyć max(0,max_{i<=j}(cnt[i]+cnt[j]-cnt[argmax a[i..j]])), gdzie cnt[i]=sum_t(h-max a[min(i,t)..max(i,t)]).
//
// Pomysł
//
// Dla każdego środka i rozwinąć obie strony, utrzymując bieżące maksimum i sumując h-maksimum. Potem dla każdego lewego końca rozszerzać prawy i aktualizować pozycję maksimum, dzięki czemu wyrażenie dla pary kosztuje O(1).
//
// Stan i niezmiennik
//
// W pętli wyznaczającej cnt[i] cur jest maksimum od i do bieżącej pozycji. W pętli po parach mx=max(a[i..j]), a cur jest indeksem osiągającym to maksimum. równe maksima zachowują wcześniejszy indeks.
//
// Złożoność
//
// Czas O(n^2), pamięć O(n).
//
// Przypadki brzegowe
//
// Gdy występują równe maksima, implementacja wybiera pierwsze. jeśli cnt dla tych pozycji różni się, ma to znaczenie dla literalnego wyniku. best startuje od 0. Typowe założenie a[i]<=h zapewnia nieujemne wkłady.
//
// Kiedy rozpoznać ten wariant
//
// Podwójny przegląd wszystkich przedziałów może być kwadratowy, jeżeli statystykę przedziału da się aktualizować przy przesunięciu końca w O(1).
//
// Warunki i uwagi
//
// - To nie DP. Interpretacja geometryczna sum i odejmowania wspólnego profilu wymaga treści zadania; dokumentacja podaje literalną formułę.
//
// KONIEC OPISU
#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, h; cin >> n >> h;
    vector<int> a(n); 
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> cnt(n);
    for (int i = 0; i < n; i++)
    {
        int cur = a[i];
        cnt[i] = h - a[i];
        for (int j = i+1; j < n; j++)
        {
            cur = max(cur, a[j]), cnt[i] += h - cur;
        }
        cur = a[i];
        for (int j = i-1; j >= 0; j--)
        {
            cur = max(cur, a[j]), cnt[i] += h-cur;
        }
    }

    int best = 0;
    for (int i = 0; i < n; i++)
    {
        int mx = a[i], cur = i;
        for (int j = i; j < n; j++)
        {
            if (mx < a[j])
            {
                cur = j;
                mx = a[j];
            }

            best = max(best, cnt[i] + cnt[j] - cnt[cur]);
        }
    }

    cout << best << "\n";
}

signed main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--)
    {
        solve();
    }

    return 0;
}