// Gwiazdki i kreski dla bloków
//
// Oryginał w zbiorze codeforces/2256/math/2256D.cc
// https://codeforces.com/contest/2256
//
// Co oblicza kod
//
// Liczy napisy binarne z takimi samymi licznościami znaków oraz taką samą naprzemienną sekwencją bloków jak wejście.
//
// Pomysł
//
// Rozdziel cnt zer na g niepustych bloków na C(cnt-1,g-1) sposobów. Zrób to niezależnie dla zer i jedynek, a wyniki pomnóż.
//
// Stan i niezmiennik
//
// Granice między dodatnimi długościami bloków wybiera się w przerwach między znakami. Rodzaje bloków i początkowy znak są ustalone.
//
// Złożoność
//
// O(n+log MOD) czasu na przypadek, w tym silnie i odwrotna modularna, oraz O(n) pamięci.
//
// Przypadki brzegowe
//
// - Brak jednego rodzaju znaków wnosi czynnik jeden.
// - Każdy blok musi mieć dodatnią długość.
// - Wzór na odwrotność wymaga pierwszego modułu i n<MOD.
//
// Kiedy rozpoznać ten wariant
//
// Gdy liczności grup są ustalone, a długości niepustych kolejnych bloków można zmieniać.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll mod = 998244353;

vector<ll> fact, invfact;

ll power(ll a, ll b)
{
    ll result = 1;

    while (b > 0)
    {
        if (b & 1) result = result * a % mod;
        a = a * a % mod;
        b >>= 1;
    }

    return result;
}

void prepare_factorials(int n)
{
    fact.resize(n + 1);
    invfact.resize(n + 1);

    fact[0] = 1;
    for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i % mod;

    invfact[n] = power(fact[n], mod - 2);
    for (int i = n; i >= 1; i--) invfact[i - 1] = invfact[i] * i % mod;
}

ll C(int n, int k)
{
    if (k < 0 || k > n) return 0;

    return fact[n] * invfact[k] % mod * invfact[n - k] % mod;
}

void solve()
{
    int n; cin >> n;
    string s; cin >> s;

    int cnt[] = {0,0};
    int cnt_groups[] = {0,0}; 
    char last_char = s[0];
    if (last_char == '0') 
    {
        cnt[0]++;
        cnt_groups[0]++;
    }
    else 
    {
        cnt[1]++;
        cnt_groups[1]++;
    }
    for (int i = 1; i < n; i++)
    {
        if (s[i] == last_char)
        {
            int num = last_char - '0';
            cnt[num]++;
        }
        else
        {
            int num = s[i] - '0';
            last_char = s[i];
            cnt[num]++;
            cnt_groups[num]++;
        }
    }

    prepare_factorials(n);
    ll ways_zero = 1, ways_one = 1;
    if (cnt[0] > 0) ways_zero = C(cnt[0] - 1, cnt_groups[0] - 1);
    if (cnt[1] > 0) ways_one = C(cnt[1] - 1, cnt_groups[1] - 1);
    cout << ways_zero * ways_one % mod << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) solve();
}