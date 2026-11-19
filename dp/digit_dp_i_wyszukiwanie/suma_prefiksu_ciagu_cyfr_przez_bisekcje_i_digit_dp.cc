// Digit DP sum cyfr i wyszukiwanie pozycji w konkatenacji
//
// Oryginał w zbiorze codeforces/2132/dp/2132D.cc
// https://codeforces.com/contest/2132
//
// Co oblicza kod
//
// Obliczyć sumę pierwszych k cyfr nieskończonej konkatenacji dodatnich liczb dziesiętnych.
//
// Pomysł
//
// len(x) sumuje liczby cyfr blokami długości d. Bisekcja znajduje największe x z len(x)<=k. digit DP sumuje cyfry wszystkich liczb <=x, a brakujące cyfry bierze z początku x+1.
//
// Stan i niezmiennik
//
// Stan (pos,tight,started) zwraca count i sumę cyfr sufiksów. Każdy wybór d dodaje child.sum+d*child.count bez mnożnika pozycyjnego. Bisekcja zachowuje len(l)<=k<len(r).
//
// Złożoność
//
// Czas O(log^2 k), pamięć O(log k). pojedynczy digit DP O(log k*10).
//
// Przypadki brzegowe
//
// k=0. koniec dokładnie na granicy liczby. przekroczenie 9/99/999. long long musi pomieścić len(m), start*10 i sumę.
//
// Kiedy rozpoznać ten wariant
//
// Pytanie o pozycję w konkatenacji liczb. najpierw odwrócić funkcję długości, potem agregować kompletne liczby DP, a krótki ogon policzyć bezpośrednio.
//
// Warunki i uwagi
//
// - len(x), start*10 i suma cyfr mogą przepełnić long long dla zbyt dużego k; wymaga ograniczeń. Czas O(log^2 k), pamięć O(log k).
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

ll len(ll x)
{
    if (x <= 0) return 0;

    ll res = 0;
    ll start = 1;

    for (int d = 1; start <= x; d++)
    {
        ll end = start * 10 - 1;
        ll last = min(x, end);

        ll count = last - start + 1;
        res += count * d;

        start *= 10;
    }

    return res;
}

ll bin_search(ll k)
{
    ll l = 0;
    ll r = k + 1;

    while (l + 1 < r)
    {
        ll m = l + (r - l) / 2;
        if (len(m) <= k) l = m;
        else r = m;
    }

    return l;
}

struct State
{
    ll count=0, sum=0;
};

struct Digit_DP
{
    int n;
    string last_num;
    vector<vector<vector<State>>> dp;
    vector<vector<vector<bool>>> seen;

    Digit_DP(ll num)
    {
        last_num = to_string(num);
        n = last_num.size();

        dp.resize(n+1, vector<vector<State>>(2, vector<State>(2)));
        seen.resize(n+1, vector<vector<bool>>(2, vector<bool>(2)));
    }

    State digit(int pos, bool tight, bool started)
    {
        if (pos == n) return {1,0};
        if (seen[pos][tight][started]) return dp[pos][tight][started];

        int limit;
        if (tight) limit = last_num[pos] - '0';     
        else limit = 9;

        ll ans_count = 0, ans_sum = 0;

        for (int i = 0; i <= limit; i++)
        {
            bool new_tight = tight && (i == (last_num[pos]-'0'));
            if (started)
            {
                bool new_started = true;
                State child = digit(pos+1, new_tight, new_started);
                ans_sum += child.sum + i * child.count;
                ans_count += child.count;
            }
            else
            {

                if (i == 0)
                {
                    bool new_started = false;
                    State child = digit(pos+1, new_tight, new_started);

                    ans_sum += child.sum;
                    ans_count += child.count;
                }
                else
                {
                    bool new_started = true;
                    State child = digit(pos+1, new_tight, new_started);

                    ans_sum += child.sum + i * child.count;
                    ans_count += child.count;
                }

            }
        }

        dp[pos][tight][started] = {ans_count, ans_sum};
        seen[pos][tight][started] = true;

        return {ans_count, ans_sum};
    }

};

ll remain(ll k, ll last_num)
{
    ll remaining = 0;

    string new_last_num = to_string(last_num+1);
    int diff = k - len(last_num);

    for (int i = 0; i < diff; i++)
    {
        remaining += new_last_num[i] - '0';
    }

    return remaining;
}

void solve()
{
    ll k;
    cin >> k;

    ll last_num = bin_search(k);
    Digit_DP digit_dp = Digit_DP(last_num);



    cout << digit_dp.digit(0,1,0).sum + remain(k, last_num) << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int t; cin >> t;
    while(t--)
    {
        solve();
    }

    return 0;
}