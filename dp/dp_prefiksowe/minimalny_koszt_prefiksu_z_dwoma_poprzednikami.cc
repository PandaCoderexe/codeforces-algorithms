// Liniowe minimum po dwóch poprzednich prefiksach
//
// Oryginał w zbiorze codeforces/2133/dp/2133D.cc
// https://codeforces.com/problemset/problem/2133/D
//
// Co oblicza kod
//
// Minimalizuje liczbę bezpośrednich ataków zadających po jednym obrażeniu, potrzebnych do zniszczenia stosu potworów o zdrowiach h[i]. Uwzględnia dodatkowe obrażenia powstające przy spadaniu stosu.
//
// Pomysł
//
// Rozpatrzyć dwa sposoby zakończenia prefiksu i. rozszerzenie rozwiązania dla i-1 za koszt max(0,h[i]-1) albo rozwiązania dla i-2 za koszt h[i-1]+max(0,h[i]-i+1). Brać minimum i przechowywać wynik w pełnej tablicy.
//
// Stan i niezmiennik
//
// Po obliczeniu pozycji i tablica dp[j] dla 0<=j<=i zawiera minimalny koszt kompozycji przejść kończących się w j. Dla i>=2 zachodzi dokładnie dp[i]=min(dp[i-1]+max(0,h[i]-1),dp[i-2]+h[i-1]+max(0,h[i]-i+1)). Przetwarzanie rosnących i zapewnia gotowość obu poprzedników.
//
// Złożoność
//
// Czas O(n), pamięć O(n) dla h i dp. same stany dp można byłoby ograniczyć do dwóch ostatnich, ale ta implementacja zachowuje całą tablicę.
//
// Przypadki brzegowe
//
// n>=1, bo kod zawsze zapisuje dp[1]. Dla n=1 wynik h[1]. dla n=2 po raz pierwszy porównuje obie alternatywy. max(0,...) ucina wyłącznie dwa wskazane składniki, nie cały koszt. h[i]-i+1 oraz sumy muszą mieścić się w long long.
//
// Kiedy rozpoznać ten wariant
//
// Najlepszy koszt prefiksu, którego ostatni krok zużywa jedną albo dwie pozycje. najprostszy schemat dp[i] zależnego od dp[i-1] i dp[i-2].
//
// Warunki i uwagi
//
// - Znaczenie wysokości h i dopuszczalnych operacji wymaga treści zadania; dokumentacja podaje literalne obliczenie implementacji, bez dopisywania niepotwierdzonej interpretacji.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll inf = 4e18; 

void solve()
{
    int n; cin >> n;
    vector<ll> h(n+1);
    for (int i = 1; i <= n; i++) cin >> h[i];

    vector<ll> dp(n+1, inf);
    dp[0] = 0; dp[1] = h[1];
    for (int i = 2; i < n+1; i++)
    {
        dp[i] = min(dp[i-1] + max(0LL, h[i]-1), dp[i-2] + h[i-1] + max(0LL, h[i] - i + 1));
    }

    cout << dp[n] << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) solve();
}