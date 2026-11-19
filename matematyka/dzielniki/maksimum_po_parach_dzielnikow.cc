// Enumeracja par dzielników
//
// Oryginał w zbiorze codeforces/2137/implementation/2137C.cc
// https://codeforces.com/contest/2137
//
// Co oblicza kod
//
// Znajduje największą parzystą wartość a*d+b/d po dodatnich dzielnikach d liczby b.
//
// Pomysł
//
// Dzielniki występują w parach i oraz b/i. Sprawdź oba podczas pętli do pierwiastka, a osobno d=1 i d=b.
//
// Stan i niezmiennik
//
// Po przetworzeniu i wynik obejmuje wszystkie dotychczas znalezione dzielniki i ich dopełnienia.
//
// Złożoność
//
// O(sqrt(b)) czasu i O(1) dodatkowej pamięci. Przy bardzo dużym b enumeracja może być zbyt wolna.
//
// Przypadki brzegowe
//
// - Kwadrat liczby wymaga uniknięcia podwójnego sprawdzania pierwiastka.
// - Brak parzystej wartości daje -1.
// - Iloczyn a*b musi mieścić się w long long.
//
// Kiedy rozpoznać ten wariant
//
// Gdy warunek obejmuje iloczyn równy stałej i obie strony zależą od dzielnika.
//
// KONIEC OPISU
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

void solve()
{
    long long a, b, result = -1;
    cin >> a >> b;
    
    // Sprawdź (a*b) + 1
    if (((a * b) + 1) % 2 == 0)
    {
        result = (a * b) + 1;
    }
    
    // Sprawdź a + b
    if ((a + b) % 2 == 0)
    {
        result = max(result, a + b);
    }
    
    // Optymalizacja: iteruj tylko do sqrt(b)
    long long sqrt_b = sqrt(b);
    for (long long i = 2; i <= sqrt_b; i++)
    {
        if (b % i == 0)
        {
            // Sprawdź dzielnik i
            long long num = (a * i) + (b / i);
            if (num % 2 == 0)
            {
                result = max(result, num);
            }
            
            // Sprawdź dzielnik b/i (jeśli różny od i)
            if (i != b / i)
            {
                long long complement = b / i;
                num = (a * complement) + i;
                if (num % 2 == 0)
                {
                    result = max(result, num);
                }
            }
        }
    }
    
    cout << result << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    while (t--)
    {
        solve();
    }
    
    return 0;
}