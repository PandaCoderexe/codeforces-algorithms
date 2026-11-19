// Przedziały zawierające punkt i zerowy XOR kolejnych liczb
//
// Oryginał w zbiorze codeforces/2225/bits/2225D.cc
// https://codeforces.com/contest/2225
//
// Co oblicza kod
//
// Policzyć modulo 998244353 pary 0<=l<x<=r<=n takie, że XOR kolejnych liczb l+1..r jest zerowy.
//
// Pomysł
//
// Prefiks XOR liczb 1..t ma cztery postacie zależne od t mod 4. Tylko wartości 0 i 1 powtarzają się dla różnych t. zero dla t=0 lub t=3 mod 4, jedynka dla t=1 mod 4. Policz te dwie klasy po obu stronach x i pomnóż liczności.
//
// Stan i niezmiennik
//
// Dla l<r równe prefiksy XOR dają zerowy XOR przedziału. Pozostałe wartości prefiksów są jednorazowe, więc nie mogą utworzyć pary przecinającej x. mod4_1(t) liczy klasę z prefiksem 0, a mod4_3(t) klasę z prefiksem 1. nazwy pomocnicze nie odpowiadają bezpośrednio tym resztom.
//
// Złożoność
//
// O(1) czasu i pamięci na test.
//
// Przypadki brzegowe
//
// Wymaga 1<=x<=n. Lewa strona uwzględnia pusty prefiks t=0, prawa zaczyna się od x. Arytmetyka x+3 wymaga zachowania zakresu long long.
//
// Kiedy rozpoznać ten wariant
//
// Przedziały dotyczą kolejnych liczb naturalnych, a nie dowolnej tablicy. znany cykl prefiksowego XOR usuwa konieczność histogramu.
//
// Warunki i uwagi
//
// - Wzory obejmują zero; wymagają n>=x>=1. Nie jest to ogólna operacja na bitach.
//
// KONIEC OPISU
#include <iostream>
#include <vector>

using namespace std;

const unsigned long long MOD = 998244353;

long long mod4_3(long long x)
{
    return (x + 3) / 4;
}

long long mod4_1(long long x)
{
    return (x + 1) / 4 + 1;
}



void solve()
{
    long long n,x;

    cin >> n >> x;

    long long countl0 = mod4_1(x - 1);
    long long countl1 = mod4_3(x - 1);

    long long countr0 = mod4_1(n) - mod4_1(x - 1);
    long long countr1 = mod4_3(n) - mod4_3(x - 1);

    unsigned long long ans = 0;
    ans = (ans + (countl0 % MOD) * (countr0 % MOD)) % MOD;
    ans = (ans + (countl1 % MOD) * (countr1 % MOD)) % MOD;

    cout << ans % MOD << '\n';
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--)
    {
        solve();
    }

    return 0;
}