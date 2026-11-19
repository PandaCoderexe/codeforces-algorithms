// Sumy pól pod funkcją schodkową na dzielnikach
//
// Oryginał w zbiorze codeforces/2257/suffixPrefix_sum/2257D.cc
// https://codeforces.com/contest/2257
//
// Co oblicza kod
//
// Dla s>0 zdefiniować H(u)=s/d, gdzie d jest najmniejszym dzielnikiem s nie mniejszym niż u, i dla zapytania x,y policzyć sumę min(y,H(u)) po 1<=u<=min(x,s), przy y uciętym do s.
//
// Pomysł
//
// Wylicz i posortuj dzielniki s. każdy przedział między kolejnymi dzielnikami ma stałą wysokość s/d. Prefiksuj pola schodków, a upper_bound po s/y wyznacza część prostokąta o pełnej wysokości y.
//
// Stan i niezmiennik
//
// pref[i] to pole wszystkich pełnych schodków do d[i]. cnt(x) dodaje pełne pola i częściowy ostatni schodek. last jest ostatnim dzielnikiem o wysokości co najmniej y.
//
// Złożoność
//
// Preprocessing O(sqrt(s)+D log D), zapytanie O(log D), pamięć O(D), gdzie D to liczba dzielników s.
//
// Przypadki brzegowe
//
// Wymaga dodatnich x,y. y=0 powoduje dzielenie przez zero, x<0 nie ma poprawnej interpretacji. s/y>=1 przy 1<=y<=s gwarantuje istnienie last. i*i oraz pola muszą mieścić się w long long.
//
// Kiedy rozpoznać ten wariant
//
// Granice zmian funkcji są rzadkie i znane. do zapytań o pole wykorzystaj szerokości schodków, sumy prefiksowe i wyszukiwanie granicy.
//
// KONIEC OPISU
#include <bits/stdc++.h>
#define sz(x)  int(x.size())

using namespace std;
using ll = long long;

void solve()
{
    ll s,q; cin >> s >>q;

    vector<ll> d;
    for (ll i = 1; i * i <= s; i++)
    {
        if (s % i == 0)
        {
            d.push_back(i);
            if (i != s / i) d.push_back(s / i);
        }
    }
    sort(d.begin(), d.end());
    vector<ll>  w(sz(d)), h(sz(d)), pref(sz(d));
    for (int i = 0; i < sz(d); i++)
    {
        h[i] = s / d[i];
        if (i == 0) w[i] = d[i];
        else w[i] = d[i] - d[i-1];

        pref[i] = w[i] * h[i];
        if (i > 0) pref[i] += pref[i-1];
    }

    auto cnt = [&](ll x) -> ll
    {
        if (x <= 0) return 0;
        int i = lower_bound(d.begin(), d.end(), x) - d.begin();
        ll pd = 0, pp = 0;

        if (i > 0)
        {
            pd = d[i-1];
            pp = pref[i-1];
        }
        return pp + (x - pd) * h[i];
    };

    for (int i = 0; i < q; i++)
    {
        ll x,y; cin >> x >> y;
        x = min(x, s); y = min(y, s); 
        
        ll limit = s / y;
        int j= upper_bound(d.begin(), d.end(), limit) - d.begin(); j--;
        ll last = d[j], ans;

        if (last < x) 
        {
            ans = last * y;
            ans += cnt(x) - cnt(last);
        }
        else ans = x * y;
        cout << ans << "\n";
        
    }
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();
}