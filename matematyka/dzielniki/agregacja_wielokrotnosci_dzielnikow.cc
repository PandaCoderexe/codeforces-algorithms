// Agregacja po dzielnikach
//
// Oryginał w zbiorze codeforces/2267/math/2267C.cc
// https://codeforces.com/contest/2267
//
// Co oblicza kod
//
// Liczy największą sumę elementów tablicy podzielnych przez wybrany dzielnik x większy niż jeden.
//
// Pomysł
//
// Wygeneruj dzielniki x parami do pierwiastka. Dla każdej liczby dodaj jej wartość do wszystkich pasujących dzielników i wybierz największą sumę.
//
// Stan i niezmiennik
//
// sum[j] jest sumą przetworzonych wartości podzielnych przez divisors[j].
//
// Złożoność
//
// O(sqrt(x)+n*tau(x)) czasu oraz O(n+tau(x)) pamięci. tau(x) oznacza liczbę dzielników.
//
// Przypadki brzegowe
//
// - Dla x=1 lista dzielników jest pusta i wynik wynosi zero.
// - Pierwiastek kwadratu dodawany jest raz.
// - Kod zaczyna maksimum od zera i zakłada nieujemny sens sum.
//
// Kiedy rozpoznać ten wariant
//
// Gdy potencjalne wspólne czynniki ogranicza rozkład jednej ustalonej liczby.
//
// KONIEC OPISU
#include <bits/stdc++.h>
#define ll long long
using namespace std;

void solve()
{
    int n, x; cin >> n >> x;
    vector<int> a(n), divisors;
    for (int i = 0; i < n; i++) cin >> a[i];

    for (int i = 2; i * i <= x; i++)
    {
        if (x % i == 0)
        {
            divisors.push_back(i);

            if (i != x / i)
                divisors.push_back(x / i);
        }
    }
    if (x > 1) divisors.push_back(x);

    vector<ll> sum((int)divisors.size());
    for (int i = 0; i < n; i++)
    {
        int cur = a[i];
        for (int j = 0; j < (int)divisors.size(); j++)
        {
            int divisor  = divisors[j];
            if (cur % divisor == 0) sum[j]+=cur;
        }
    }

    ll maximum = 0;
    for (ll q : sum) maximum = max(maximum, q);

    cout << maximum << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();
}