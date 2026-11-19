// Greedy podciągu naprzemiennego z bilansem usunięć
//
// Oryginał w zbiorze codeforces/2252/string/2252B.cc
// https://codeforces.com/contest/2252
//
// Co oblicza kod
//
// Wyznaczyć najdłuższy naprzemienny podciąg binarny, po którego usunięciu różnica liczby usuniętych zer i jedynek ma moduł najwyżej 1. wypisać liczbę usuniętych znaków lub -1.
//
// Pomysł
//
// Dla obu znaków początkowych greedy bierz najwcześniejszy oczekiwany znak. Sprawdź długość maksymalną i krótszą o 1. parzystość długości i pierwszy znak jednoznacznie wyznaczają bilans pozostawionych znaków.
//
// Stan i niezmiennik
//
// Najwcześniejszy wybór każdego znaku nie ogranicza żadnego dalszego wyboru, więc greedy maksymalizuje długość. Dla ustalonego początku istnieją tylko dwa możliwe bilanse pozostawionego podciągu. 0 dla długości parzystej lub +/-1 dla nieparzystej.
//
// Złożoność
//
// O(n) czasu i O(n) pamięci na napis, O(1) pomocniczo.
//
// Przypadki brzegowe
//
// Dopuszczony jest pusty podciąg, gdy cur=0. Sprawdzenie długości len i len-1 wystarcza, bo dalsze długości powtarzają już te same bilanse. Związek tego bilansu z dozwolonymi operacjami zadania wymaga jego treści.
//
// Kiedy rozpoznać ten wariant
//
// Warunek na usunięte znaki zależy wyłącznie od bilansu, a pozostawiony podciąg ma strukturę jednoznacznie określoną przez długość i znak początkowy.
//
// Warunki i uwagi
//
// - Wypisuje n-longest pod warunkiem |liczba usuniętych zer-jedynek|<=1. Zgodność tego kryterium z operacjami zadania wymaga jego treści.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve()
{
    int n; cin >> n;
    string s; cin >> s;

    int zeros = 0;
    for (char c : s)
    {
        if (c == '0') zeros++;
    }

    int balance = zeros-(n-zeros);
    int longest = -1;

    for (int first = 0; first <= 1; first++)
    {
        int need = first;
        int len = 0;

        for (char c : s)
        {
            if (c-'0' == need)
            {
                len++;
                need ^= 1;
            }
        }

        for (int removed = 0; removed <= 1; removed++)
        {
            int cur = len-removed;
            if (cur < 0) continue;

            int remainingBalance = 0;

            if (cur % 2 == 1)
            {
                if (first == 0) remainingBalance = 1;
                else remainingBalance = -1;
            }

            int deletedBalance = balance-remainingBalance;

            if (abs(deletedBalance) <= 1)
            {
                longest = max(longest, cur);
            }
        }
    }

    if (longest == -1)
    {
        cout << -1 << '\n';
        return;
    }

    cout << n-longest << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);

    int t; cin >> t;
    while (t--) solve();
}