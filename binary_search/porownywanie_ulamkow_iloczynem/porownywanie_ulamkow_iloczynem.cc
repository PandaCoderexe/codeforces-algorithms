// Sortowanie ułamków bez błędów zmiennoprzecinkowych
//
// Oryginał w zbiorze codeforces/2224/bruteForce/2224D.cc
// https://codeforces.com/contest/2224
//
// Co oblicza kod
//
// Obliczyć modulo 998244353 sumę po i<j liczby uporządkowanych par p!=q z b[q]/b[p]<a[i]/a[j], podzieloną przez n(n-1).
//
// Pomysł
//
// Wygeneruj n(n-1) ułamków b[q]/b[p], posortuj przez iloczyny krzyżowe w __int128, a każde a[i]/a[j] obsłuż lower_bound. Normalizację wykonaj odwrotnością modularną.
//
// Stan i niezmiennik
//
// Przy dodatnich mianownikach comparator porównuje dokładnie wartości ułamków. lower_bound zwraca liczbę wartości ściśle mniejszych. równe ilorazy nie są wliczane.
//
// Złożoność
//
// O(n² log n) czasu i O(n²) pamięci, dodatkowo O(log MOD) na jedną odwrotność.
//
// Przypadki brzegowe
//
// n=1 jest osobno zwracane jako 0. Wszystkie mianowniki muszą być dodatnie. zerowe lub ujemne niszczą znaczenie porównań. n(n-1) nie może być 0 modulo MOD.
//
// Kiedy rozpoznać ten wariant
//
// Masz dużo porównań stosunków i zależy ci na ścisłej nierówności bez użycia double.
//
// KONIEC OPISU
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long MOD = 998244353;

struct Fraction
{
    long long numerator;
    long long denominator;
};

bool smallerFraction(const Fraction& x, const Fraction& y)
{
    return (__int128)x.numerator * y.denominator < (__int128)y.numerator * x.denominator;
}

long long fastPower(long long base, long long exp)
{
    long long result = 1;

    while (exp > 0)
    {
        if (exp % 2 == 1)
        {
            result = result * base % MOD;
        }

        base = base * base % MOD;
        exp /= 2;
    }

    return result;
}

long long inverseModulo(long long x)
{
    return fastPower(x, MOD - 2);
}

vector<Fraction> buildAllRatios(const vector<long long>& b)
{
    int n = b.size();

    vector<Fraction> ratios;
    ratios.reserve(1LL * n * (n - 1));

    for (int first = 0; first < n; first++)
    {
        for (int second = 0; second < n; second++)
        {
            if (first == second)
            {
                continue;
            }

            Fraction current;
            current.numerator = b[second];
            current.denominator = b[first];

            ratios.push_back(current);
        }
    }

    sort(ratios.begin(), ratios.end(), smallerFraction);

    return ratios;
}

long long countSmallerRatios(const vector<Fraction>& ratios, long long top, long long bottom)
{
    Fraction target;
    target.numerator = top;
    target.denominator = bottom;

    return lower_bound(
        ratios.begin(),
        ratios.end(),
        target,
        smallerFraction
    ) - ratios.begin();
}

void solveSingleTest()
{
    int n;
    cin >> n;

    vector<long long> a(n);
    vector<long long> b(n);

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    for (int i = 0; i < n; i++)
    {
        cin >> b[i];
    }

    if (n == 1)
    {
        cout << 0 << '\n';
        return;
    }

    vector<Fraction> ratios = buildAllRatios(b);

    long long totalGood = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            long long goodForPair = countSmallerRatios(ratios, a[i], a[j]);

            totalGood += goodForPair % MOD;
            totalGood %= MOD;
        }
    }

    long long denominator = 1LL * n * (n - 1) % MOD;
    long long answer = totalGood * inverseModulo(denominator) % MOD;

    cout << answer << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
    {
        solveSingleTest();
    }

    return 0;
}