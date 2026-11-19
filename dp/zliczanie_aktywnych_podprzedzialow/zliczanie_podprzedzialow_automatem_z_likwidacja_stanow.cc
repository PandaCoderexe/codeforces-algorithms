// Liniowe zliczanie aktywnych podprzedziałów
//
// Oryginał w zbiorze codeforces/2230/dp/2230D.cc
// https://codeforces.com/contest/2230
//
// Co oblicza kod
//
// Zliczyć podprzedziały, których stan nie zostaje zlikwidowany. start w 0, przy a=b przejście a-1->a, przy a!=b zakaz stanów a-1 i b-1.
//
// Pomysł
//
// Dla każdego prawego końca dodać nowy początek w dp[0]. Grupować wszystkie początki według stanu i aktualizować wyłącznie dotknięte liczniki.
//
// Stan i niezmiennik
//
// dp[s] to liczba aktywnych początków w stanie s. curr=sum_s dp[s]. Równe a,b przenoszą cały licznik bez zmiany curr, różne odejmują dwa rozłączne liczniki. ans+=curr.
//
// Złożoność
//
// Czas O(n), pamięć O(n).
//
// Przypadki brzegowe
//
// Wymagane 1<=a[i],b[i]<=n. Gdy a=b, nie wolno podwójnie usuwać tego samego stanu. Wynik do n(n+1)/2 wymaga long long.
//
// Kiedy rozpoznać ten wariant
//
// Przedziały przechodzą ten sam deterministyczny automat, a operacja dotyczy jedynie stałej liczby stanów. wystarczy liczyć początki, nie symulować każdego.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int n;
    cin >> n;

    vector<int> a(n+1),b(n+1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    long long curr = 0, ans = 0; 
    vector<long long> dp(n+1, 0);
    for (int day = 1; day <= n; day++)
    {   
        dp[0]++;
        curr++;

        if (a[day] == b[day]) {
            dp[a[day]] += dp[a[day]-1];
            dp[a[day]-1] = 0;
        } else {
            curr -= dp[a[day]-1];
            curr -= dp[b[day]-1];

            dp[a[day]-1] = 0;
            dp[b[day]-1] = 0;
        } 
        
        ans += curr;
    }

    cout << ans << "\n";
    return;
} 

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }

    return 0;
}