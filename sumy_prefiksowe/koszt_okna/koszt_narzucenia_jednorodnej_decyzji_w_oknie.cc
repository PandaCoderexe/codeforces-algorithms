// Bazowy niezależny wybór i najtańsza naprawa okna
//
// Oryginał w zbiorze codeforces/2215/dp/2215A.cc
// https://codeforces.com/contest/2215
//
// Co oblicza kod
//
// Zminimalizować sumę wyników modulo p, wybierając przed nim opcjonalne modulo q na każdej pozycji, z warunkiem istnienia okna długości k o jednakowej decyzji.
//
// Pomysł
//
// Policzyć gain=(a%p)-((a%q)%p). Bez ograniczenia brać dodatnie gain. koszt narzucenia zer w oknie to suma dodatnich gain, a jedynek suma -ujemnych gain. Znaleźć najtańsze okno i wariant.
//
// Stan i niezmiennik
//
// positive_sum jest zyskiem niezależnego optimum. pref_pos/pref_neg podają koszt usunięcia odpowiednio korzystnych wyborów lub dodania niekorzystnych. Wynik base-positive_sum+min_koszt_naprawy.
//
// Złożoność
//
// Czas O(n), pamięć O(n).
//
// Przypadki brzegowe
//
// p,q>0. 1<=k<=n. zerowe gain nie kosztują żadnej decyzji. Przy k>n pozostaje wartownik i wynik nie ma sensu.
//
// Kiedy rozpoznać ten wariant
//
// Lokalne wybory są niezależne poza jednym wymaganym jednolitym fragmentem. optymalizować stratę względem swobodnego optimum.
//
// Warunki i uwagi
//
// - p,q>0 i 1<=k<=n. Gdy k>n, best_cost zostaje ogromnym wartownikiem. Czas O(n), pamięć O(n).
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

void solve()
{
    int n, k;
    ll p, q;
    cin >> n >> k >> p >> q;

    vector<ll> a(n + 1);

    ll base = 0;
    vector<ll> gain(n + 1);

    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];

        ll only_p = a[i] % p;
        ll q_then_p = (a[i] % q) % p;

        base += only_p;
        gain[i] = only_p - q_then_p;
    }

    ll positive_sum = 0;

    vector<ll> pref_pos(n + 1, 0);
    vector<ll> pref_neg(n + 1, 0);

    for (int i = 1; i <= n; i++)
    {
        positive_sum += max(0LL, gain[i]);

        pref_pos[i] = pref_pos[i - 1] + max(0LL, gain[i]);
        pref_neg[i] = pref_neg[i - 1] + max(0LL, -gain[i]);
    }

    ll best_cost = (1LL << 60);

    for (int r = k; r <= n; r++)
    {
        int l = r - k + 1;

        ll cost_make_zero = pref_pos[r] - pref_pos[l - 1];
        ll cost_make_one = pref_neg[r] - pref_neg[l - 1];

        best_cost = min(best_cost, min(cost_make_zero, cost_make_one));
    }

    ll best_gain = positive_sum - best_cost;

    cout << base - best_gain << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }

    return 0;
}