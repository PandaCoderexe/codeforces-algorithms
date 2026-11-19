// Zachłanne bity ze stanem tight/loose
//
// Oryginał w zbiorze codeforces/2180/dp/2180C.cc
// https://codeforces.com/contest/2180
//
// Co oblicza kod
//
// Zbudować k nieujemnych liczb <=n o XOR-ze n i możliwie największej sumie.
//
// Pomysł
//
// Dla bitu n=1 trzeba nieparzystej liczby jedynek. przy nieparzystym k ustawić wszystkie. przy parzystym pominąć jedną jeszcze tight, uwalniając ją. Dla n=0 ustawić największą parzystą liczbę bitów w loose.
//
// Stan i niezmiennik
//
// tight ma prefiks równy n, loose mniejszy, więc tylko loose może dostać 1 tam, gdzie n ma 0. W każdym bicie parytet ustawień jest równy bitowi n. liczby pozostają <=n.
//
// Złożoność
//
// Czas O(k*log n), pamięć O(k).
//
// Przypadki brzegowe
//
// n>0 z powodu clz. k>=1. Nieparzyste k daje k kopii n. dla parzystego k priorytet uwalniania tight wpływa na dalsze bity.
//
// Kiedy rozpoznać ten wariant
//
// Trzeba jednocześnie spełnić XOR i górne ograniczenie każdej liczby. ważniejsza jest parzystość liczby ustawień niż tożsamość identycznych jeszcze prefiksów.
//
// Warunki i uwagi
//
// - __builtin_clzll(0) ma niezdefiniowane zachowanie; wymagane n>0. n musi mieścić się w dodatnim long long.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve()
{
    ll n, k;
    cin >> n >> k;

    vector<bool> loose(k + 1, false);
    vector<ll> nums(k + 1, 0);

    int bits_cnt = 64 - __builtin_clzll(n);
    int count_of_loose = 0;

    for (int bit = bits_cnt - 1; bit >= 0; bit--)
    {
        bool active = (n & (1LL << bit)) != 0;

        if (active)
        {
            if (k % 2 == 1)
            {
                for (int i = 1; i <= k; i++)
                {
                    nums[i] |= (1LL << bit);
                }
            }
            else
            {
                int skip = -1;

                for (int i = 1; i <= k; i++)
                {
                    if (!loose[i])
                    {
                        skip = i;
                        break;
                    }
                }

                if (skip == -1)
                {
                    skip = 1;
                }
                else
                {
                    loose[skip] = true;
                    count_of_loose++;
                }

                for (int i = 1; i <= k; i++)
                {
                    if (i == skip) continue;
                    nums[i] |= (1LL << bit);
                }
            }
        }
        else
        {
            int skip = count_of_loose % 2;

            for (int i = 1; i <= k; i++)
            {
                if (!loose[i]) continue;

                if (skip > 0)
                {
                    skip--;
                    continue;
                }

                nums[i] |= (1LL << bit);
            }
        }
    }

    for (int i = 1; i <= k; i++)
    {
        cout << nums[i] << " ";
    }
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();
}