// Minima sufiksowe kosztów pod ograniczeniem końcowych zer
//
// Oryginał w zbiorze codeforces/2246/bits/2246D.cc
// https://codeforces.com/contest/2246
//
// Co oblicza kod
//
// Dla k=0..17 minimalizować sumę kosztów przekształcenia a[i] do x>=a[i] z co najmniej k końcowymi zerami, wymuszając dokładnie k zer dla przynajmniej jednego elementu, następnie odjąć k(n-1). Koszt to x-a+floor(log2 x)+popcount(x).
//
// Pomysł
//
// Jednorazowo policz x+floor(log2 x)+popcount(x) dla x<=2^18. Dla każdego k skanuj malejąco i zapisz minima dla wielokrotności 2^k oraz dla liczb z dokładnym v2(x)=k. Przy teście wybierz minimalny dodatkowy koszt wymuszenia dokładnej klasy na jednym elemencie.
//
// Stan i niezmiennik
//
// best_ktorys[k][a] jest minimalnym kosztem przy v2(x)>=k. best_dokladny przy v2(x)=k. Sumę luźnych minimów wystarczy podnieść o najmniejszą różnicę tych dwóch kosztów, aby przynajmniej jeden wybór był dokładny.
//
// Złożoność
//
// Jednorazowo O(18*2^18) czasu i O(18*100000) pamięci. każdy test O(18n) czasu i O(n) dodatkowej pamięci.
//
// Przypadki brzegowe
//
// Wymaga 1<=a[i]<=100000 i n>=1. Kod rozważa cele tylko do 2^18 i k<18. optymalność tych ograniczeń i znaczenie końcowego odjęcia wymagają treści zadania.
//
// Kiedy rozpoznać ten wariant
//
// Wspólny parametr bitowy rozdziela koszt na niezależne minima elementów, ale co najmniej jeden element musi osiągać dokładną klasę zamiast szerszego warunku.
//
// Warunki i uwagi
//
// - Zakłada 1<=a[i]<=100000; a[i]=0 trafia w nieuzupełnione komórki. Jednorazowo O(18*2^18) czasu i O(18*100000) pamięci, następnie O(18n). Znaczenie końcowego odjęcia k(n-1) wymaga treści zadania.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int max_a = 100000;
const int max_b = (1 << 18);
const int K = 18;
const int inf = 1e9;

void solve()
{

    static bool ready = false;
    static vector<vector<int>> best_ktorys(K, vector<int>(max_a + 1, inf));
    static vector<vector<int>> best_dokladny(K, vector<int>(max_a + 1, inf));

    if (!ready)
    {
        vector<int> val(max_b + 1);

        for (int x = 1; x <= max_b; x++)
        {
            int ruchy = 31 - __builtin_clz(x) + __builtin_popcount(x);
            val[x] = x + ruchy;
        }

        for (int k = 0; k < K; k++)
        {
            int mn_ktorys = inf;
            int mn_dokladny = inf;

            int pot = (1 << k);

            for (int x = max_b; x >= 1; x--)
            {
                if ((x & (pot - 1)) == 0)
                {
                    mn_ktorys = min(mn_ktorys, val[x]);

                    if (((x >> k) & 1) == 1)
                    {
                        mn_dokladny = min(mn_dokladny, val[x]);
                    }
                }

                if (x <= max_a)
                {
                    best_ktorys[k][x] = mn_ktorys - x;
                    best_dokladny[k][x] = mn_dokladny - x;
                }
            }
        }

        ready = true;
    }

    int n;
    cin >> n;

    vector<int> a(n);

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    ll ans = (1LL << 60);

    for (int k = 0; k < K; k++)
    {
        ll sum = 0;
        int extra = inf;

        for (int i = 0; i < n; i++)
        {
            int x = a[i];

            sum += best_ktorys[k][x];
            extra = min(extra, best_dokladny[k][x] - best_ktorys[k][x]);
        }

        ll curr = sum + extra - 1LL * k * (n - 1);

        ans = min(ans, curr);
    }

    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }

    return 0;
}