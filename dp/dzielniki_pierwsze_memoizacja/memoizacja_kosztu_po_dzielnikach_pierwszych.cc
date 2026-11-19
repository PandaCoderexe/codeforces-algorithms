// Top-down DP po dzielnikach i sito SPF
//
// Oryginał w zbiorze codeforces/2266/dp/2266E.cc
// https://codeforces.com/contest/2266
//
// Co oblicza kod
//
// Obliczyć sumę f(a[i]), gdzie f(x)=0 dla x<=k, a f(x)=min_{p pierwsze,p|x}(1+p*f(x/p)).
//
// Pomysł
//
// Zbudować najmniejszy dzielnik pierwszy do 200000. Dla stanu x wyznaczyć różne dzielniki pierwsze i rekurencyjnie przejść do x/p. pamięć dzielona jest pomiędzy wszystkimi wejściami w jednym teście.
//
// Stan i niezmiennik
//
// Memo[x] jest minimum zadanej rekurencji. Każdy podproblem ma mniejszą dodatnią wartość dla x>k>=1, więc zależności są acykliczne i kończą się w bazie.
//
// Złożoność
//
// Preprocessing SPF O(L log log L), pamięć O(L). Na test O(L+n+Σ_{x odwiedzone} log x) czasu jako bezpieczna granica z faktoryzacją. stos O(log L), L=200000.
//
// Przypadki brzegowe
//
// Wymagane k>=1 i 1<=a[i]<=200000. k=0 tworzy f(1)=INF i przepełnienia mnożników. Reset mem kosztuje O(L) nawet dla małego n.
//
// Kiedy rozpoznać ten wariant
//
// Przejścia zmniejszają liczbę przez dzielenie, różne ścieżki spotykają się w tych samych dzielnikach. memoizacja unika eksploracji całego drzewa rozkładów.
//
// Warunki i uwagi
//
// - Dla k=1 i x pierwszego f(x)=1; nie ma nieosiągalności przy k>=1. Dla k=0 f(1)=4e18, a mnożenie przez dzielnik przepełnia long long. Wejście x musi być <=200000. SPF O(L log log L), pamięć O(L); memoizacja odwiedza dzielniki wejść, nie po prostu n stanów.
//
// KONIEC OPISU
#include <bits/stdc++.h>
#define ll long long
#define vl vector<ll>
using namespace std;

int k;
const int lim = 200000;
vl spf(lim + 1), mem;

void build_spf()
{
    for (int i = 0; i <= lim; i++) spf[i] = i;
    for (int i = 2; i * i <= lim; i++)
    {
        if (spf[i] == i) 
        {
            for (int j = i * i; j <= lim; j += i)
            {
                if (spf[j] == j) spf[j] = i;
            }
        }
    }
}

vl prime_factors(int x)
{
    vl pf;

    while(x > 1)
    {
        int d = spf[x];
        pf.push_back(d);
        while(x % d == 0) x /= d;
    }

    return pf;
}

ll dp(int x)
{
    if ( x <= k) return 0;
    if (mem[x] != -1) return mem[x];

    vl pf = prime_factors(x);
    ll ans = 4e18;
    for (int divisor: pf)
    {
        ans = min(ans,1 +( divisor * dp(x/divisor)));
    }
    return mem[x]=ans;

}

void solve()
{
    int n; cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    mem.assign(lim + 1, -1);

    ll ans = 0;
    for (int x : a)
    {
        ans += dp(x);
    }

    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    build_spf();
    int t; cin >> t;
    while (t--) solve();
}