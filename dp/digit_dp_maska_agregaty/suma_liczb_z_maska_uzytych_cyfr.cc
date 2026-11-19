// Digit DP. maska cyfr, started i para count/sum
//
// Oryginał w zbiorze codeforces/1073/dp/1073E.cc
// https://codeforces.com/contest/1073
//
// Co oblicza kod
//
// Zsumować modulo 998244353 liczby z [l,r] używające najwyżej k różnych cyfr.
//
// Pomysł
//
// Maska rozpoznaje użyte cyfry, started odróżnia zera wiodące od rzeczywistej cyfry 0. Dla dziecka o count sposobach wkład cyfry d to d*10^remaining*count.
//
// Stan i niezmiennik
//
// Stan (pos,mask,tight,started) zwraca liczbę dopuszczalnych sufiksów oraz sumę ich wartości. Sumę powiększa child.sum i wkład wybranej cyfry. popcount(mask)>k odrzuca stan. Memo dp[pos][mask][started] ma trzy wymiary. tight jest przekazywany rekurencyjnie, a zapamiętywane są stany tight=false. Każda komórka zawiera parę count i sum.
//
// Złożoność
//
// Czas O(D*1024*2*10), pamięć O(D*1024*2), stos O(D).
//
// Przypadki brzegowe
//
// k=0. liczba zero ma pustą maskę, ale sumie daje 0. rzeczywiste zera po pierwszej cyfrze wchodzą do maski. odjęcie prefiksów modulo.
//
// Kiedy rozpoznać ten wariant
//
// Potrzebna suma wartości zamiast liczności. ograniczenie zbioru cyfr i znaczenie zer wiodących.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll mod = 998244353;

struct Node
{
    ll count;
    ll sum;
};

struct Digit_DP
{
    string s;
    int k;

    vector<ll> power10;

    vector<vector<vector<Node>>> dp;
    vector<vector<vector<bool>>> seen;

    Node digit_dp(int pos, int mask, bool tight, bool started)
    {
        if (__builtin_popcount(mask) > k)
        {
            return {0, 0};
        }

        if (pos == (int)s.size())
        {
            return {1, 0};
        }

        if (!tight && seen[pos][mask][started])
        {
            return dp[pos][mask][started];
        }

        int limit;

        if (tight)
        {
            limit = s[pos] - '0';
        }
        else
        {
            limit = 9;
        }

        Node ans = {0, 0};

        int remaining = (int)s.size() - pos - 1;

        for (int digit = 0; digit <= limit; digit++)
        {
            bool new_tight = tight && (digit == limit);

            bool new_started = started;
            int new_mask = mask;

            if (!started && digit == 0)
            {
                new_started = false;
                new_mask = mask;
            }
            else
            {
                new_started = true;
                new_mask = mask | (1 << digit);
            }

            if (__builtin_popcount(new_mask) <= k)
            {
                Node child = digit_dp(pos + 1, new_mask, new_tight, new_started);

                ans.count += child.count;
                ans.count %= mod;

                ll contribution = digit;
                contribution *= power10[remaining];
                contribution %= mod;
                contribution *= child.count;
                contribution %= mod;

                ans.sum += child.sum;
                ans.sum %= mod;

                ans.sum += contribution;
                ans.sum %= mod;
            }
        }

        if (!tight)
        {
            seen[pos][mask][started] = true;
            dp[pos][mask][started] = ans;
        }

        return ans;
    }

    ll solve(ll n, int k_)
    {
        if (n < 0)
        {
            return 0;
        }

        k = k_;
        s = to_string(n);

        int len = (int)s.size();
        int max_mask = 1 << 10;

        power10.assign(len + 1, 1);

        for (int i = 1; i <= len; i++)
        {
            power10[i] = power10[i - 1] * 10 % mod;
        }

        dp.assign(
            len,
            vector<vector<Node>>(
                max_mask,
                vector<Node>(2, {0, 0})
            )
        );

        seen.assign(
            len,
            vector<vector<bool>>(
                max_mask,
                vector<bool>(2, false)
            )
        );

        return digit_dp(0, 0, true, false).sum;
    }
};

void solve()
{
    ll l, r;
    int k;

    cin >> l >> r >> k;

    Digit_DP solver;

    ll right_sum = solver.solve(r, k);
    ll left_sum = solver.solve(l - 1, k);

    ll ans = (right_sum - left_sum + mod) % mod;

    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}