// Binary search MEX z zapotrzebowaniem od wysokich poziomów
//
// Oryginał w zbiorze codeforces/2266/binary_search/2266F.cc
// https://codeforces.com/problemset/problem/2266/F
//
// Co oblicza kod
//
// Wyznaczyć największą liczbę, która może kiedykolwiek wystąpić w multizbiorze po dowolnej liczbie operacji zastąpienia niepustej wybranej kolekcji jednym elementem równym jej MEX-owi. wejście podaje pary wartość i liczność.
//
// Pomysł
//
// Oddziel największą wartość obecną od początku od wartości możliwych do wytworzenia. Dla celu val sprawdzaj od val-1 w dół, ile kopii każdego niższego poziomu potrzeba. Istniejące kopie zużywaj zachłannie, a każda brakująca kopia poziomu x wymaga dodatkowej kopii każdego poziomu 0..x-1. Przy całkowicie brakującym poziomie potrzeba się podwaja. duże luki przerywaj po przekroczeniu łącznej liczby elementów T. Na końcu potrzebne kopie zer i jedynek można utworzyć z dowolnych 2*need wolnych elementów.
//
// Stan i niezmiennik
//
// need jest wspólnym zapotrzebowaniem na każdy jeszcze nierozpatrzony niższy poziom. unused=T-liczba zużytych oryginalnych kopii nadal obejmuje wszystkie wolne elementy, także duże wartości. Przy liczności c poziomu zużywa się min(c,need), a nowa potrzeba wynosi need+max(0,need-c). Potrzeba nigdy nie maleje. Dla poziomów 0 i 1 singletony pozwalają zamieniać 0 na 1 i każdą liczbę dodatnią na 0, więc warunek unused>=2*need jest wystarczający i konieczny.
//
// Złożoność
//
// Sortowanie O(n log n). Jeden checker O(n+log T). wszystkie udane podwojenia łącznie są ograniczone przez log T, bo need nigdy nie maleje, a pierwsze przekroczenie kończy sprawdzenie. Całość O(n log n+(n+log T)*log T) czasu i O(n) pamięci, bez rozwijania sumy liczności T.
//
// Przypadki brzegowe
//
// val=0 jest zawsze osiągalne, val=1 wymaga co najmniej jednego elementu. oba przypadki obsłużono osobno. Nowo wytworzony MEX nie przekracza liczby elementów T, lecz największa wartość już obecna może przekraczać T, dlatego wynik to max(wynik wyszukiwania,max_x). Duże odstępy wartości nie powodują liniowej iteracji po całej luce. ograniczenie need<=T kończy podwajanie po O(log T) krokach.
//
// Kiedy rozpoznać ten wariant
//
// Multizbiór jest skompresowany, a wytworzenie poziomu potrzebuje po jednym elemencie wszystkich mniejszych poziomów. Zastąp pełne rozwijanie liczności malejącym skanem zapotrzebowania i potraktuj brakujące poziomy jako podwajanie.
//
// Warunki i uwagi
//
// - Dziedzina potwierdzona w oficjalnej treści: 1<=n<=200000, różne parami 0<=x_i<=10^9 oraz 1<=y_i<=10^9. Po sortowaniu różność poziomów gwarantuje nieujemne gap; duplikaty nie są poprawnym wejściem. T<=2*10^14, więc użyte long long i sprawdzanie need>total/2 zabezpieczają podwajanie.
//
// KONIEC OPISU
#include <bits/stdc++.h>
#define ll long long
#define vl vector<ll>
using namespace std;

ll total;
vector<pair<ll,ll>> a;

bool fill_gap(ll &need, ll gap)
{
    while (gap--)
    {
        if (need > total / 2) return false;
        need *= 2;
    }
    return true;
}

bool checker(ll val)
{
    if (val == 0) return true;
    if (val == 1) return total >= 1;
    ll need = 1, unused = total, cur = val-1;
    for (int i = (int)a.size() - 1; i >= 0; i--)
    {
        ll x = a[i].first;
        if (x >= val) continue;
        if (x < 2) break;

        ll fill = cur - x;
        if (!fill_gap(need, fill)) return false;
        ll take = min(a[i].second, need);
        unused -= take;

        if (a[i].second < need) need += need - a[i].second;
        if (need > total) return false;
        cur = x-1;
    }
    if (cur >= 2)
    {
        ll fill = cur-1;
        if (!fill_gap(need, fill)) return false;
    }
    return unused >= 2 * need;
}

void solve()
{
    int n; cin >> n;

    ll left = 0, right = 0, max_x = 0;
    for (int i = 0; i < n; i++)
    {
        ll xi, yi; cin >> xi >> yi;
        a.push_back({xi, yi});
        total += yi;
        max_x = max(max_x, xi);
    }

    sort(a.begin(), a.end());
    right = total;
    while(left < right)
    {
        ll mid = left + (right - left + 1) / 2;
        bool ch = checker(mid);
        if (ch) left = mid;
        else right = mid-1;
    }

    cout << max(left, max_x) << '\n';
    a.clear();
    total = 0;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}