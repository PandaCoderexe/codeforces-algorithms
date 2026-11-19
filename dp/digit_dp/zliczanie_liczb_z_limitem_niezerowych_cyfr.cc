// Digit DP. liczba niezerowych cyfr
//
// Oryginał w zbiorze codeforces/1036/dp/1036C.cc
// https://codeforces.com/contest/1036
//
// Co oblicza kod
//
// Policzyć liczby z [l,r] z najwyżej trzema niezerowymi cyframi.
//
// Pomysł
//
// Obliczyć F(r)-F(l-1). Stan (pos,cnt,tight). zera wiodące nie zmieniają cnt, więc started nie jest potrzebny. Memoizować wyłącznie nietight.
//
// Stan i niezmiennik
//
// F(pos,c,t) sumuje F(pos+1,c+[d!=0],t&&d==limit). c>3 daje 0, koniec cyfr daje 1. obejmuje liczbę zero. Stan logiczny obejmuje pos, non_zero i tight. Kod alokuje dp[pos][non_zero][2], lecz memoizuje tylko przy tight=false w komórce o trzecim indeksie 0. seen ma dwa wymiary.
//
// Złożoność
//
// Dla D cyfr. czas O(D*4*10), pamięć O(D*4). rekurencja O(D).
//
// Przypadki brzegowe
//
// l=0. granice potęg 10. zero jest dopuszczalne. n<0 zwraca 0. l-1 musi mieścić się w long long.
//
// Kiedy rozpoznać ten wariant
//
// Ograniczenie liczby wystąpień cechy cyfry i przedział liczbowy. brak potrzeby rozróżniania początku liczby.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct Digit_DP
{
    string s;
    vector<vector<vector<ll>>> dp;
    vector<vector<bool>> seen;

    ll digit_dp(int pos, int non_zero_nums, bool tight)
    {   
        if (non_zero_nums > 3) return 0;

        if (pos == (int)s.size()) return 1;

        if (!tight && seen[pos][non_zero_nums])
        {
            return dp[pos][non_zero_nums][0];
        }

        int limit;

        if (tight) limit = s[pos] - '0';
        else limit = 9;
        
        ll ans = 0;

        for (int digit = 0; digit <= limit; digit++)
        {
            int new_count = non_zero_nums;

            if (digit != 0)
            {
                new_count++;
            }

            bool new_tight = tight && (digit == limit);

            ans += digit_dp(pos + 1, new_count, new_tight);
        }

        if (!tight)
        {
            seen[pos][non_zero_nums] = true;
            dp[pos][non_zero_nums][0] = ans;
        }

        return ans;
    }

    ll solve(ll n)
    {
        if (n < 0) return 0;

        s = to_string(n);

        seen.assign((int)s.size(), vector<bool>(4, false));
        dp.assign((int)s.size(), vector<vector<ll>>(4, vector<ll>(2, 0)));

        return digit_dp(0, 0, true);
    }
};


void solve()
{
    ll l, r;
    cin >> l >> r;

    Digit_DP solver;

    cout << solver.solve(r) - solver.solve(l - 1) << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);

    int t; cin >> t;
    while(t--)
    {
        solve();
    }

    return 0;
}