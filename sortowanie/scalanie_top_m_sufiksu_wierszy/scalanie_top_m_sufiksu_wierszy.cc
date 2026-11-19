// Utrzymywanie m największych elementów przez scalanie
//
// Oryginał w zbiorze codeforces/2252/suffixPrefix_sum/2252C.cc
// https://codeforces.com/contest/2252
//
// Co oblicza kod
//
// Dla każdego sufiksu wierszy znaleźć najmniejszą dodatnią liczbę największych wartości potrzebną do osiągnięcia progu v[r] i zwrócić minimum po wierszach, z domyślnym wynikiem m.
//
// Pomysł
//
// Sortuj każdy wiersz malejąco. Scal jego m wartości z posortowanymi m najlepszymi z dalszych wierszy, zachowując tylko m największych. następnie przejdź po ich sumach prefiksowych.
//
// Stan i niezmiennik
//
// Przed oceną r best zawiera m największych wartości ze wszystkich wierszy od r do n-1 w porządku malejącym. Element spoza poprzedniego top m nie może wejść do nowego top m.
//
// Złożoność
//
// O(n*m log m) czasu, O(n*m) pamięci na wejście i O(m) pamięci roboczej.
//
// Przypadki brzegowe
//
// Wynik inicjalizowany m oznacza, że brak osiągalnego progu nie jest sygnalizowany osobno. Liczone są tylko dodatnie liczby wybranych elementów. próg<=0 nie zwróci 0.
//
// Kiedy rozpoznać ten wariant
//
// Kolejne zbiory powstają przez dopisywanie całych posortowanych porcji, a interesuje cię wyłącznie ograniczone top k.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve()
{
    int n, m; cin >> n >> m;
    vector<ll> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    vector<ll> a(n*m);
    for (int i = 0; i < n*m; i++) cin >> a[i];

    vector<ll> best;
    best.reserve(m);
    int ans = m;

    for (int r = n-1; r >= 0; r--)
    {
        int start = r*m;

        sort(a.begin()+start, a.begin()+start+m, greater<ll>());

        vector<ll> next;
        next.reserve(m);

        int i = 0, j = 0;

        while ((int)next.size() < m)
        {
            if (i < (int)best.size() &&
                (j >= m || best[i] >= a[start+j]))
            {
                next.push_back(best[i]);
                i++;
            }
            else
            {
                next.push_back(a[start+j]);
                j++;
            }
        }
        best.swap(next);
        ll sum = 0;

        for (int cnt = 0; cnt < m; cnt++)
        {
            sum += best[cnt];
            if (sum >= v[r])
            {
                ans = min(ans, cnt+1);
                break;
            }
        }
    }

    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr); 
    int t; cin >> t;    
    while (t--) solve();
}