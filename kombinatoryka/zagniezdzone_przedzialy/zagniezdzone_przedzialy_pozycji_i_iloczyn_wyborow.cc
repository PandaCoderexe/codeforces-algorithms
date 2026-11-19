// Kombinatoryka zagnieżdżonych zakresów
//
// Oryginał w zbiorze codeforces/2250/dp/2250D.cc
// https://codeforces.com/contest/2250
//
// Co oblicza kod
//
// Obliczyć wynik 2 pomnożony przez czynniki swobody zagnieżdżonych zakresów pozycji wartości >=i, odrzucając niespójność albo dwustronne rozszerzenie.
//
// Pomysł
//
// Zebrać pierwsze i ostatnie wystąpienia wartości. Przy schodzeniu i utrzymywać liczbę i obwiednię pozycji wartości >=i. liczba musi równać się długości obwiedni. Sąsiednie zakresy mogą rosnąć tylko w jedną stronę.
//
// Stan i niezmiennik
//
// l[i],r[i] to końce zakresu wierzchołków obejmującego pozycje wartości >=i, z prawą granicą o 1 większą od ostatniej pozycji wejścia. Przy niezmienionym zakresie mnożnik wynosi (r[i]-l[i]+1)-n+i.
//
// Złożoność
//
// Czas O(n), pamięć O(n).
//
// Przypadki brzegowe
//
// n=1 zwraca 1. a[i]>=n zwraca 0. ujemne a nie są sprawdzane i psują indeksowanie. Brak wartości n-1 prowadzi do niespełnionego warunku zakresu.
//
// Kiedy rozpoznać ten wariant
//
// Przypadki kombinatoryczne określają rosnące zbiory progowe. ich geometria przedziałowa pozwala zastąpić DP iloczynem niezależnych wyborów.
//
// Warunki i uwagi
//
// - Nie DP mimo katalogu. Indeksy wymagają 0<=a[i]<n. Cel kombinatoryczny wymaga treści zadania. O(n) czasu i pamięci.
// - Bez treści zadania nie przypisywać iloczynowi niepotwierdzonej interpretacji obiektów; opisuje dokładnie kryteria oraz wartość implementacji.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll mod = 998244353;
const int inf = 1e9;

void solve()
{
    int n; cin >> n;
    vector<int> a(n-1);
    for(int i = 0; i <n-1; i++) cin >> a[i];
    if (n == 1)
    {
        cout << 1 << '\n'; 
        return; 
    }
    vector<pair<int,int>> segs(n, {inf, -1});
    vector<int> f(n);
    for (int i = 0; i < n-1; i++)
    {
        if (a[i] >= n) 
        {
            cout << 0 << "\n";
            return;
        }
        int el = a[i];
        segs[el].first = min(segs[el].first, i);
        segs[el].second = max(segs[el].second, i);
        f[a[i]]++;
    }

    vector<int> l(n),r(n);
    int li = inf, ri = -1, cnt = 0;
    for (int i = n-1;i > 0; i--)
    {
        if (segs[i].second!=-1)
        {
            li = min(li, segs[i].first);
            ri = max(ri, segs[i].second);
            cnt+= f[i];
        }


        if (li == inf || cnt != ri - li + 1)
        {
            cout << 0 << '\n';
            return;
        }
        l[i] = li; r[i] = ri+1;
    }

    ll ans = 2;
    for (int i = n-2; i > 0; i--)
    {
        bool if_l = l[i] < l[i + 1], if_r = r[i] > r[i + 1];

        if ((l[i] > l[i + 1] || r[i] < r[i + 1]) || (if_l && if_r))
        {
            cout << 0 << '\n';
            return;
        }

        if (!if_l && !if_r)
        {
            int len = r[i] - l[i] + 1;
            int ways = len - n+i;
            if (ways <= 0)
            {
                cout << 0 << '\n';
                return;
            }
            ans = ans * ways;
            ans %= mod;
        }
    }

    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) solve();
}