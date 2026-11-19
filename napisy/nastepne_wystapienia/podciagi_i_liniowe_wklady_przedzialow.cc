// Następne wystąpienia i liniowe wkłady przedziałów
//
// Oryginał w zbiorze codeforces/2276/math/2276E.cc
// https://codeforces.com/contest/2276
//
// Co oblicza kod
//
// Dla każdej pozycji liczy pokrywające ją podnapisy, w których występowanie 2025 jako podciągu implikuje występowanie 2026 jako podciągu.
//
// Pomysł
//
// Tablica next pozwala znaleźć najwcześniejszy koniec podciągu 202 oraz pierwszą późniejszą cyfrę 5 lub 6. Dla ustalonego początku niedozwolone końce tworzą przedział [r25,r26), gdy r25<r26. Wkład dla pozycji jest odcinkami liniowy. Dodaj jego współczynnik i wyraz wolny tablicami różnicowymi.
//
// Stan i niezmiennik
//
// next[i][d] jest pierwszą pozycją cyfry d od i, albo n. Po zsumowaniu różnic A*i+B liczy dopuszczalne końce dla wszystkich początków nie większych niż i.
//
// Złożoność
//
// O(10*n) czasu i O(10*n) pamięci.
//
// Przypadki brzegowe
//
// - Brak jednego lub obu podciągów daje pozycję n.
// - Gdy 2026 kończy się wcześniej niż 2025, żaden koniec nie jest niedozwolony.
// - next ma dodatkowy wiersz n dla pustego sufiksu.
//
// Kiedy rozpoznać ten wariant
//
// Gdy podciąg ma stały krótki wzorzec, a odpowiedź dla każdego punktu można zsumować przez przedziałowe funkcje liniowe.
//
// KONIEC OPISU
#include <bits/stdc++.h>
#define ll long long
using namespace std;

void solve()
{
    int n; cin >> n;
    string s; cin >> s;

    vector<vector<int>> next(n+1, vector<int>(10, n));
    for (int i = n-1; i >= 0; i--)
    {
        next[i] = next[i+1];
        int d = s[i]-'0';
        next[i][d] = min(next[i][d], i);
    }


    int digits[3] = {2, 0, 2};
    vector<ll> a(n + 1), b(n + 1);
    for (int i = n - 1; i >= 0; i--)
    {
        int j = i;
        bool found = true;

        for (int dig = 0; dig < 3; dig++)
        {
            int d = digits[dig];
            int pos = next[j][d];

            if (pos == n)
            {
                found = false;
                break;
            }

            j = pos + 1;
        }

        int r25 = n, r26 = n;

        if (found)
        {
            r25 = next[j][5];
            r26 = next[j][6];
        }

        if (r25 >= r26)
        {
            a[i] -= 1; a[n] += 1;

            b[i] += n; b[n] -= n;
        }
        else
        {
            a[i] -= 1; a[r25] += 1;
            b[i] += r25+n-r26; b[r25] -= r25+n-r26;
            b[r25] += n-r26; b[r26] -= n-r26;
            a[r26] -= 1; a[n] += 1;
            b[r26] += n; b[n] -= n;
        }
    }

    vector<ll> ans(n);
    ll A = 0, B = 0;
    for (int i = 0; i < n; i++)
    {
        A += a[i]; B += b[i];
        ans[i] = A * i + B;
        cout << ans[i] << " ";
    }
    cout << "\n";

}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();
}