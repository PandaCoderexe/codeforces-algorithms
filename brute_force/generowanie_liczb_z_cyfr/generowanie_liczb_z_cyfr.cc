// Rekurencyjne generowanie liczb z alfabetu cyfr
//
// Oryginał w zbiorze codeforces/2228/bruteForce/2228C1.cc
// https://codeforces.com/contest/2228
//
// Co oblicza kod
//
// Zminimalizować odległość |a-v| wśród nieujemnych liczb zapisanych wyłącznie dozwolonymi cyframi, bez zer wiodących poza liczbą 0.
//
// Pomysł
//
// Wypróbuj długości od 1 do L+1, gdzie L jest długością a, i doklejaj kolejne dozwolone cyfry. Każdy kompletny zapis aktualizuje minimum.
//
// Stan i niezmiennik
//
// value jest wartością już wybranego prefiksu. gen(pos,len,value) enumeruje wszystkie dopuszczalne dopełnienia tego prefiksu.
//
// Złożoność
//
// Dla d dostępnych cyfr czas O(sum_{l=1}^{L+1} d^l), stos O(L), lista cyfr O(d). Jest to wariant wykładniczy, przeznaczony dla małych ograniczeń.
//
// Przypadki brzegowe
//
// Zakłada a>=0, cyfry w 0..9 i co najmniej jedną cyfrę. Powtarzające się cyfry dublują gałęzie. value*10 i |a-value| mogą się przepełnić dla dużych długości.
//
// Kiedy rozpoznać ten wariant
//
// Mały alfabet i krótki zapis pozwalają wyliczyć wszystkie kandydaty. warunek zer wiodących obsługuj już przy generowaniu.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll INF = (1LL << 62);

ll a;
int n;
vector<int> digits;
ll ans;

void gen(int pos, int len, ll value)
{
    if (pos == len)
    {
        ans = min(ans, llabs(a - value));
        return;
    }

    for (int digit : digits)
    {
        if (pos == 0 && len > 1 && digit == 0)
        {
            continue;
        }

        gen(pos + 1, len, value * 10 + digit);
    }
}

void solve()
{
    cin >> a >> n;

    digits.resize(n);

    for (int i = 0; i < n; i++)
    {
        cin >> digits[i];
    }

    int len = (int)to_string(a).size();

    ans = INF;

    for (int current_len = 1; current_len <= len + 1; current_len++)
    {
        gen(0, current_len, 0);
    }

    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) solve();
    return 0;
}