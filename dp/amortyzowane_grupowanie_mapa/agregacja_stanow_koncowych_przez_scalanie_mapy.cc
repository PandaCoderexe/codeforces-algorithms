// Amortyzowane DP grup stanów w mapie
//
// Oryginał w zbiorze codeforces/2201/dp/2201A2.cc
// https://codeforces.com/contest/2201
//
// Co oblicza kod
//
// Zsumować po wszystkich końcach r wartości aktywnych stanów początków, aktualizowanych regułą progową zależną od a[r] i a[r-1].
//
// Pomysł
//
// Każdy klucz ma liczbę stanów i sumę ich wyników. Jeśli x>prev+1, scalić wszystkie grupy. w przeciwnym razie tylko klucze >=x. Każdemu scalonemu stanowi dodać 1, pozostałe zostawić, następnie dołożyć nowy stan wyniku 1.
//
// Stan i niezmiennik
//
// total_sum jest sumą wyników wszystkich aktywnych początków dla r. Para (cnt,sum_f) opisuje grupę identycznego klucza. scalenie dodaje cnt do sum_f i total_sum. ans gromadzi total_sum po kolejnych r.
//
// Złożoność
//
// Czas O(n log n) amortyzowany. każdy utworzony wpis można usunąć raz. pamięć O(n).
//
// Przypadki brzegowe
//
// n=0 daje 0. powtórzone wartości scalają się pod tym samym kluczem. prev+1 i suma O(n^3) w najgorszym wzroście muszą mieścić się w long long.
//
// Kiedy rozpoznać ten wariant
//
// Wiele początków ma identyczną dalszą reakcję, a aktualizacja obejmuje cały sufiks uporządkowanych kluczy. usuwanie i scalenie zastępuje przechodzenie po każdym początku.
//
// Warunki i uwagi
//
// - Semantyka pierwotnego wyniku wymaga treści zadania; opisano dokładnie agregowaną rekurencję, bez przypisywania niepotwierdzonej nazwy statystyki.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve()
{
    int n; cin>>n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    map<long long, pair<long long, long long>> mp;

    ll total_sum = 0, ans = 0;

    for (int r = 0; r < n; r++)
    {
        ll x = a[r];

        if (r > 0)
        {
            ll prev = a[r-1];

            ll merged_cnt = 0, merged_sum = 0;

            if (x > prev+1)
            {
                auto it = mp.begin();

                while(it != mp.end())
                {
                    ll cnt = it->second.first;
                    ll sum_f = it->second.second;
                    merged_cnt+=cnt; merged_sum+= sum_f + cnt;
                    
                    total_sum += cnt;

                    it = mp.erase(it);
                    
                }
            }
            else
            {
                auto it = mp.lower_bound(x);

                while(it != mp.end())
                {
                    ll cnt = it->second.first;
                    ll sum_f = it->second.second;
                    merged_cnt+=cnt; merged_sum+= sum_f + cnt;
                    
                    total_sum += cnt;

                    it = mp.erase(it);
                    
                }
            }

            if (merged_cnt > 0)
            {
                mp[x].first += merged_cnt;
                mp[x].second += merged_sum;
            }
        }


        mp[x].first += 1;
        mp[x].second += 1;

        total_sum += 1;
        ans += total_sum;
    }

    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--) solve();

    return 0;
}