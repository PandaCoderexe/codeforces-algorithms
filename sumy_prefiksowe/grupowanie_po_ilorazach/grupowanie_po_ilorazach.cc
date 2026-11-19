// Histogram i harmoniczne grupowanie ilorazów
//
// Oryginał w zbiorze codeforces/2258/suffixPrefix_sum/2258B2.cc
// https://codeforces.com/contest/2258
//
// Co oblicza kod
//
// Dla kolejnych k>=1, j=2^k, obliczyć maksimum po y=1..m sumy min(floor(a/y),j-1)+[a=j*y]. po j>m wynikiem jest suma a.
//
// Pomysł
//
// Histogram i prefiksy zliczeń pozwalają sumować jednakowe ilorazy na przedziałach [z*y,(z+1)*y-1]. Preoblicz val[y]=sum floor(a/y) i maksima sufiksowe. dla y>m/j ograniczenie nie działa, a pozostałe y oblicz jawnie po grupach.
//
// Stan i niezmiennik
//
// Każdy przedział histogramu ma stały iloraz z. Dla y<=m/j osobno sumowane są ilorazy 1..j-2, ogon z>=j-1 i premia za dokładną wartość j*y.
//
// Złożoność
//
// O(n+m log m) czasu i O(n+m) pamięci. Preobliczenie ma sumę m/y, a każda z O(log m) wartości j kosztuje O((m/j)*j)=O(m).
//
// Przypadki brzegowe
//
// Wymaga 1<=a[i]<=m. Wyników jest m. po przekroczeniu j>m wszystkie dalsze są sumą a. j*=2 wymaga m w zakresie bez przepełnienia int.
//
// Kiedy rozpoznać ten wariant
//
// Wartości są ograniczone przez m, występują sumy dzielenia całkowitego, a progi rosną geometrycznie.
//
// KONIEC OPISU
#include <bits/stdc++.h>
#define ll long long
using namespace std;

void solve()
{
    int n,m; cin >> n >> m;
    ll sum = 0;
    vector<int> cnt(m+1), a(n), pref(m+1);

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        cnt[a[i]]++;
        sum += a[i];
    }

    for (int i = 1; i <= m; i++) pref[i] = pref[i-1] + cnt[i];

    vector<ll> val(m+2), suf(m+2), ans(m+1);

    for (int y = 1; y <= m; y++)
    {
        ll x = 0;

        for (int l = y, z = 1; l <= m; l += y, z++)
        {
            int r = min(m, l+y-1);
            x += 1LL*z*(pref[r]-pref[l-1]);
        }

        val[y] = x;
    }

    for (int i = m; i >= 1; i--) suf[i] = max(suf[i+1], val[i]);

    int j = 2;
    for (int k = 1; k <= m; k++)
    {
        if (j > m)
        {
            for (int i = k; i <= m; i++) ans[i] = sum;
            break;
        }

        int limit = m/j;
        ll best = suf[limit+1];

        for (int y = 1; y <= limit; y++)
        {
            ll x = 0;

            for (int z = 1; z <= j-2; z++)
            {
                int l = z*y, r = (z+1)*y-1;
                x += 1LL*z*(pref[r]-pref[l-1]);
            }

            int b = (j-1)*y;

            x += 1LL*(j-1)*(n-pref[b-1]);
            x += cnt[j*y];

            best = max(best, x);
        }

        ans[k] = best;
        j *= 2;
    }

    for (int i = 1; i <= m; i++) cout << ans[i] << " ";
    cout << "\n";
}
int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();
}