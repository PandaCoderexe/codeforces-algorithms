// Okresowa konstrukcja o stałej sumie okna
//
// Oryginał w zbiorze codeforces/2247/suffixPrefix_sum/2247B.cc
// https://codeforces.com/contest/2247
//
// Co oblicza kod
//
// Dla k<=m utworzyć dodatni ciąg długości n, w którym każde pełne okno długości k ma sumę m. dla k>m wypisać NO.
//
// Pomysł
//
// Powtarzaj okres długości k złożony z k-1 jedynek i jednej wartości m-k+1. Każde okno długości k zawiera dokładnie jeden cały zestaw reszt modulo k.
//
// Stan i niezmiennik
//
// Wszystkie elementy są dodatnie, gdy m>=k. Przesunięcie okna usuwa i dodaje elementy o tym samym indeksie modulo k, więc suma pozostaje m.
//
// Złożoność
//
// O(n) czasu i O(1) pamięci dodatkowej poza wyjściem.
//
// Przypadki brzegowe
//
// Wymaga k>=1. Jeśli n<k nie ma pełnych okien, ale kod nadal odrzuca k>m, co może być mocniejszym wymaganiem niż sam cel okien. Indeks pętli jest int przy n typu long long.
//
// Kiedy rozpoznać ten wariant
//
// Równość sum wszystkich okien tej samej długości sugeruje okresowość a[i]=a[i+k].
//
// Warunki i uwagi
//
// - Wymaga k>0; brak sum prefiksowych. Każde pełne okno długości k ma sumę m.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve()
{
    ll n, k, m; cin >> n >> k >> m;
    if (k > m)
    {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";
    for (int i = 1; i <= n; i++)
    {
        if (i % k == 0) cout << m-k+1 << " ";
        else cout << 1 << " ";
    }
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) solve();
}