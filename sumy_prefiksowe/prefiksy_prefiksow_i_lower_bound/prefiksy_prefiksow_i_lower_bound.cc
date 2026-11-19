// Minimalny koszt propagacji nadmiernej luki po usunięciu
//
// Oryginał w zbiorze codeforces/2259/suffixPrefix_sum/2259G.cc
// https://codeforces.com/problemset/problem/2259/G
//
// Co oblicza kod
//
// Dla każdego indeksu niezależnie usunąć a[i] i obliczyć minimalną liczbę operacji zmniejszenia elementu o 1, po których tablica ponownie jest niemalejąca i każda sąsiednia różnica nie przekracza k.
//
// Pomysł
//
// Po usunięciu pozycji wewnętrznej jedyną nową luką jest a[i+1]-a[i-1]. Jej nadmiar st ponad k trzeba zdjąć z a[i+1], a dalsze zmniejszenia są pochłaniane przez kolejne luzy k-(a[j+1]-a[j]). Prefiks luzów określa resztę zmniejszenia w każdej pozycji, lower_bound znajduje koniec dodatnich reszt, a prefiks tych prefiksów sumuje je jednym odejmowaniem.
//
// Stan i niezmiennik
//
// rest[j]=k-(a[j+1]-a[j]) jest nieujemne, więc pref jest niemalejący. Po usunięciu i minimalne konieczne zmniejszenie a[j], j>=i+1, wynosi max(0,st+pref[i+1]-pref[j]). Zachłannie pozostawiona wartość min(a[j],poprzednia+k) jest największą dopuszczalną, więc minimalizuje koszt także dalszego sufiksu. second_pref sumuje wartości pref w całym dodatnim zakresie.
//
// Złożoność
//
// O(n log n) czasu i O(n) pamięci. Każde wewnętrzne usunięcie wymaga jednego lower_bound oraz O(1) działań na dwóch prefiksach.
//
// Przypadki brzegowe
//
// Usunięcie pierwszego lub ostatniego elementu zawsze kosztuje 0. Gdy nowa luka nie przekracza k, koszt również wynosi 0. Równe wartości prefiksów są dozwolone. lower_bound odcina pierwszą resztę równą 0. Dla n=2 wszystkie wyniki są zerowe.
//
// Kiedy rozpoznać ten wariant
//
// Lokalna zmiana tworzy jeden nadmiar propagowany przez sufiks i absorbowany przez nieujemne luzy. Do kosztu wszystkich propagacji przydają się prefiksy luzów, wyszukiwanie pierwszego zera i drugi prefiks.
//
// Warunki i uwagi
//
// - Dziedzina potwierdzona w oficjalnej treści: 2<=n<=200000, 1<=k,a[i]<=10^9, tablica początkowo niemalejąca i a[i+1]-a[i]<=k. Gwarantuje to monotoniczność pref oraz bezpieczeństwo wyrażeń int; sumy i iloczyny wymagają zastosowanego long long.
//
// KONIEC OPISU
#include <bits/stdc++.h>
#define ll long long
using namespace std;

void solve()
{
    int n , k; cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<long long> rest(n - 1), pref(n), second_pref(n + 1);

    for (int i = 0; i < n - 1; i++)
    {
        rest[i] = k - a[i + 1] + a[i];
        pref[i + 1] = pref[i] + rest[i];
    }

    for (int i = 0; i < n; i++) second_pref[i + 1] = second_pref[i] + pref[i];

    vector<ll> ans(n);
    for (int i = 1;  i < n-1; i++)
    {
        ll st = a[i+1] - a[i-1] - k;
        if (st <= 0) continue;

        int idx = (lower_bound(pref.begin()+i+1, pref.end(), pref[i+1]+st) - pref.begin());
        int cnt = idx - i -1;
        ans[i] = cnt * (st+pref[i+1]) - (second_pref[idx] - second_pref[i+1]);
    }

    for (ll x : ans) cout << x << " ";
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();
}