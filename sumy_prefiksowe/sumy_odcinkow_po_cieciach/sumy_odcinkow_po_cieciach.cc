// Sumowanie odcinków wyznaczonych punktami cięcia
//
// Oryginał w zbiorze codeforces/2244/suffixPrefix_sum/2244D.cc
// https://codeforces.com/contest/2244
//
// Co oblicza kod
//
// Policzyć sumę modułów sum kolejnych fragmentów zakończonych w posortowanych punktach b oraz zwykłą sumę końcowego sufiksu.
//
// Pomysł
//
// Sortuj b i oblicz prefiksy a. Każdy następny fragment ma sumę pref[b[i]]-pref[poprzednie_cięcie]. końcówkę dodaj bez modułu.
//
// Stan i niezmiennik
//
// last_el jest końcem ostatniego zamkniętego fragmentu. answer zawiera jego wkład i wkłady wszystkich wcześniejszych fragmentów.
//
// Złożoność
//
// O(n+m log m) czasu i O(n+m) pamięci.
//
// Przypadki brzegowe
//
// Powtórzone punkty tworzą puste fragmenty o wkładzie 0. b musi należeć do 0..n. Przy m=0 wynikiem jest całkowita suma ze znakiem.
//
// Kiedy rozpoznać ten wariant
//
// Statyczne punkty cięcia dzielą tablicę na rozłączne odcinki. każdy wkład zależy wyłącznie od sumy segmentu.
//
// Warunki i uwagi
//
// - Końcowy sufiks jest traktowany inaczej; nie należy opisywać wyniku jako sumy modułów wszystkich segmentów.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve()
{
    int n, m;
    cin >> n >> m;

    vector<ll> a(n+1);
    vector<int> b(m);

    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) cin >> b[i];
    sort(b.begin(), b.end());

    vector<ll> pref(n+1, 0);
    for (int i = 1; i <= n; i++) pref[i] = pref[i-1] + a[i];
    
    ll answer = 0;
    int last_el = 0;

    for (int i = 0; i < m; i++)
    {
        int r = b[i];
        ll sum = pref[r] - pref[last_el];
        answer += abs(sum);
        last_el = r;
    }

    answer += pref[n] - pref[last_el];
    cout << answer << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) solve();
    return 0;
}