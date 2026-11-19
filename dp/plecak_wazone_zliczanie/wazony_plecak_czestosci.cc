// Plecak 0/1 z mnożnikiem liczby wyborów
//
// Oryginał w zbiorze codeforces/2165/dp/2165B.cc
// https://codeforces.com/contest/2165
//
// Co oblicza kod
//
// Obliczyć sumę wag podzbiorów klas wartości, których łączna częstość jest >=M, gdzie M to największa częstość. waga podzbioru jest iloczynem częstości wybranych klas.
//
// Pomysł
//
// Każda klasa częstości c daje wybór niewzięcia albo wzięcia z mnożnikiem c. Aktualizować sumę malejąco, aby klasa wystąpiła najwyżej raz.
//
// Stan i niezmiennik
//
// dp[s] jest współczynnikiem x^s w iloczynie (1+c*x^c) dotychczasowych dodatnich częstości. dp[s]+=c*dp[s-c].
//
// Złożoność
//
// Czas O(n^2), dokładniej O(n*d) dla d obecnych wartości. pamięć O(n).
//
// Przypadki brzegowe
//
// Wartości wejścia muszą być w 1..n. puste klasy pomijane. dp[0]=1 oznacza pusty wybór. wszystko modulo 998244353.
//
// Kiedy rozpoznać ten wariant
//
// Obiekty mają zarówno rozmiar, jak i wiele sposobów wybrania reprezentanta. mnożnik przejścia różni ten wariant od samej osiągalności.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll mod = 998244353;

void solve()
{
    int n;
    cin >> n;
    vector<int> cnt(n+1);

    for (int i = 0; i < n; i++) 
    {
        int x;
        cin >> x;
        cnt[x]++;
    }
    int M = -1;
    for (int i = 1; i <= n; i++) M = max(M, cnt[i]);

    vector<ll> dp(n+1,0);
    dp[0] = 1;

    for (int i = 1; i < n+1; i++)
    {
        if (cnt[i] > 0)
        {
            for (int sum = n; sum >= cnt[i]; sum--)
            {
                dp[sum] += dp[sum - cnt[i]] * cnt[i];
                dp[sum] %= mod;
            }
        }
    }

    ll ans = 0;
    for (int i = M; i < n+1; i++)
    {
        ans += dp[i];
        ans %= mod;
    }

    cout << ans <<"\n";

}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) solve();
}