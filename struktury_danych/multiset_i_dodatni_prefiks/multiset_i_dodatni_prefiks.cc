// Multiset i najmniejszy element utrzymujący dodatni prefiks
//
// Oryginał w zbiorze codeforces/2254/suffixPrefix_sum/2254E.cc
// https://codeforces.com/contest/2254
//
// Co oblicza kod
//
// Ułożyć elementy tak, aby każda suma prefiksowa była dodatnia, i wypisać te sumy. przy niepozytywnej sumie całkowitej wypisać -1.
//
// Pomysł
//
// Przy bieżącym pref wybierz lower_bound(1-pref), czyli najmniejszy pozostały element utrzymujący sumę przynajmniej 1. Usuń tylko jedno jego wystąpienie.
//
// Stan i niezmiennik
//
// Po wyborze pref>=1. Jeśli całkowita suma jest dodatnia, niemożliwość znalezienia elementu >-pref przeczyłaby dodatniości sumy pref+pozostałe. zachłanny najmniejszy dopuszczalny wybór nie blokuje ukończenia.
//
// Złożoność
//
// O(n log n) czasu i O(n) pamięci.
//
// Przypadki brzegowe
//
// Duplikaty wymagają multiset i erase(iterator). Wypisywane są sumy prefiksowe, nie sama permutacja. Arytmetyka 1-pref i sumy wymaga zakresu long long.
//
// Kiedy rozpoznać ten wariant
//
// Układasz sekwencję z dynamicznego zbioru, a dopuszczalność następnego elementu jest dolnym progiem zależnym od aktualnej sumy.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve()
{
    int n;
    cin >> n;

    multiset<ll> nums;
    ll sum_n = 0;
    for (int i = 0; i < n; i++)
    {
        ll x;
        cin >> x;
        nums.insert(x);
        sum_n += x;
    }

    if (sum_n <= 0)
    {
        cout << -1 << '\n';
        return;
    }

    vector<ll> a;
    ll pref = 0;
    while (!nums.empty())
    {
        auto it = nums.lower_bound(1 - pref);
        if (it == nums.end())
        {
            cout << -1 << '\n'; return;
        }

        pref +=*it; 
        a.push_back(pref); 
        nums.erase(it); 
    }

    for (ll x : a) cout << x << ' ';
    cout << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}