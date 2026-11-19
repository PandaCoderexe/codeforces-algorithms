// DP ostatniej pozycji z przesuwaną granicą
//
// Oryginał w zbiorze codeforces/2263/dp/2263C2.cc
// https://codeforces.com/contest/2263
//
// Co oblicza kod
//
// Policzyć podzbiory S zbioru 0..n-1, dla których mex zbioru {floor(x/k):x w S} jest równy a[k] dla każdego k.
//
// Pomysł
//
// Zakazać bloku ilorazu a[k] tablicą różnicową. Dla każdego j<a[k] wymagać wybranego elementu w bloku [jk,(j+1)k-1], zapisując need na prawym końcu. DP zlicza podzbiory według ostatniej wybranej pozycji i usuwa za stare końce.
//
// Stan i niezmiennik
//
// Przed wyborem i sum zawiera dopuszczalne dotychczas podzbiory. Jeśli i niezakazane, dp[i]=sum dodaje i do każdego z nich. Po zamknięciu wymaganego bloku usuwa pusty podzbiór i stany z ostatnią pozycją <need[i]. removed rośnie monotonnie.
//
// Złożoność
//
// Czas O(n+sum_k a[k]), pamięć O(n). Przy poprawnych 0<=a[k]<=ceil(n/k) suma to O(n log n). bez tej gwarancji nie twierdzić O(n log n).
//
// Przypadki brzegowe
//
// a[k]=0 zakazuje pierwszy blok bez obowiązków wcześniejszych. pusty podzbiór jest osobnym stanem. Gdy a[k]>ceil(n/k), need może wyjść poza dziedzinę i usuwanie indeksować poza dp. Iloczyny wymagają braku overflow.
//
// Kiedy rozpoznać ten wariant
//
// Warunki typu traf każdy wymagany przedział i omijaj zakazane. przy skanie wystarczy ostatnia wybrana pozycja oraz monotonicznie przesuwana granica.
//
// KONIEC OPISU
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MOD = 1e9 + 7;

void solve()
{
    int n;
    cin >> n;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<int> diff(n + 1), need(n, -1);
    for (int k = 1; k <= n; k++)
    {
        int val = a[k];

        int l = val * k;
        if (l < n)
        {
            int r = min(n - 1, (val + 1) * k - 1);
            diff[l]++;
            if (r + 1 < n) diff[r + 1]--;
        }

        for (int j = 0; j < val; j++)
        {
            int l = j * k, r = min(n - 1, (j + 1) * k - 1);
            need[r] = max(need[r], l);
        }
    }

    vector<int> bad(n);
    int cur = 0;

    for (int i = 0; i < n; i++)
    {
        cur += diff[i];
        bad[i] = (cur > 0);
    }

    
    ll sum = 1;
    int removed = -1;
    bool empty = true;
    vector<ll> dp(n);
    for (int i = 0; i < n; i++)
    {
        if (!bad[i])
        {
            dp[i] = sum;
            sum += dp[i];
            sum %= MOD;
        }

        if (need[i] != -1)
        {
            if (empty)
            {
                sum--;
                if (sum < 0) sum += MOD;
                empty = false;
            }

            while (removed < need[i] - 1)
            {
                removed++;
                sum -= dp[removed];
                if (sum < 0) sum += MOD;
            }
        }
    }

    cout << sum << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int t; cin >> t;
    while (t--) solve();
}