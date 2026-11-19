// Przedziały stałej wartości ceil(a/x)
//
// Oryginał w zbiorze codeforces/2144/dp/2144D.cc
// https://codeforces.com/contest/2144
//
// Co oblicza kod
//
// Maksymalizować po całkowitym x w [2,A] wartość sum_j j*c_j-y*max(0,c_j-freq[j]), gdzie c_j zlicza ceny z ceil(a/x)=j.
//
// Pomysł
//
// Z histogramu i prefiksów policzyć c_j na [(j-1)x+1,min(A,jx)]. Przejść wszystkie x. liczby grup tworzą sumę harmoniczną.
//
// Stan i niezmiennik
//
// Dla ustalonego x przedziały rozdzielają wszystkie dodatnie ceny. cnt z prefiksów to dokładna liczba elementów nowej ceny. ans przechowuje największą wartość po rozpatrzonych x.
//
// Złożoność
//
// Czas O(n+A log A), pamięć O(n+A).
//
// Przypadki brzegowe
//
// A=1 obsłużone wynikiem n. ceny dodatnie. y może wymagać long long. iloczyny granic przedziałów muszą mieścić się w int.
//
// Kiedy rozpoznać ten wariant
//
// Wiele zapytań o zaokrąglony iloraz wartości z małej dziedziny. histogram i prefiksy usuwają pętlę po wszystkich elementach dla każdego dzielnika.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve()
{
    int n; cin >> n;
    ll y; cin >> y;

    int A = 0;
    vector<int> prices(n);

    for (int i = 0; i < n; i++)
    {
        cin >> prices[i];
        A = max(A, prices[i]);
    }
    if (A == 1)
    {
        cout << n << '\n';
        return;
    }
    vector<int> count(A+1), prefix_sum(A+1);
    for (int price : prices) count[price]++;
    for (int i = 1; i <= A; i++) prefix_sum[i] = prefix_sum[i-1] + count[i];

    ll ans = LLONG_MIN;
    for (int x = 2; x <= A; x++)
    {
        ll ans_x = 0;

        int maximum_new_price = (A+x-1)/x;
        for (int new_p = 1; new_p <= maximum_new_price; new_p++)
        {
            int left = (new_p-1)*x+1;
            int right = min(A, new_p*x);

            int cnt = prefix_sum[right] - prefix_sum[left-1];

            ans_x += 1LL*new_p*cnt;
            ans_x -= 1LL*y*max(0, cnt-count[new_p]);
        }

        ans = max(ans, ans_x);
    }

    cout << ans << "\n";

}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) solve();
}