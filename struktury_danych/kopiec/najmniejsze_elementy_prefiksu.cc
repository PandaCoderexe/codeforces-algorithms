// Kopiec k najmniejszych prefiksu
//
// Oryginał w zbiorze codeforces/2263/dataStructures/2263B.cc
// https://codeforces.com/contest/2263
//
// Co oblicza kod
//
// Maksymalizuje m*a[i] minus sumę m−1 najmniejszych poprzedników a[i]. dla m=1 zwraca maksimum.
//
// Pomysł
//
// Max-heap o rozmiarze m−1 i jego suma pozwalają zastąpić największą wybraną wartość przez mniejszą nową.
//
// Stan i niezmiennik
//
// Przed oceną a[i] kopiec zawiera m−1 najmniejszych wcześniejszych wartości.
//
// Złożoność
//
// O(n log m) czasu dla m>1, O(n) dla m=1. O(n+m) pamięci programu, kopiec O(m).
//
// Przypadki brzegowe
//
// m=1,n. remisy. ujemne wartości. m>n niedopuszczalne.
//
// Kiedy rozpoznać ten wariant
//
// Rozpoznaj wzorzec. kopiec k najmniejszych prefiksu. Max-heap o rozmiarze m−1 i jego suma pozwalają zastąpić największą wybraną wartość przez mniejszą nową.
//
// Warunki i uwagi
//
// - Wymaga 1≤m≤n; dla m>n pozostaje sentinel −4e18.
//
// KONIEC OPISU
#include <bits/stdc++.h>
#define ll long long
using namespace std;

void solve()
{
    int n,m; cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    if (m == 1)
    {
        cout << *max_element(a.begin(), a.end()) << "\n";
        return;
    }

    ll ans = -4e18;
    ll sum = 0;
    priority_queue<int> pq;
    for (int i = 0; i < n; i++)
    {
        if (pq.size() >= m-1)
        {
            ans = max(ans, 1LL * m * a[i] - sum);

            if (pq.top() > a[i])
            {
                int deleted = pq.top(); pq.pop();
                sum -= deleted;
                sum+= a[i];
                pq.push(a[i]);

            }
        }
        else 
        {
            pq.push(a[i]);
            sum += a[i];
        }
    }

    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();
}