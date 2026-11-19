// DP na rosnącym grafie liczb
//
// Oryginał w zbiorze codeforces/2284/math/C2.cc
// https://codeforces.com/contest/2284
//
// Co oblicza kod
//
// Znajduje najkrótszy rosnący ciąg od a do b, którego sąsiednie liczby są względnie pierwsze, i wypisuje długości kolejnych kroków.
//
// Pomysł
//
// Najpierw sprawdź rozwiązanie jedno- i dwuodcinkowe. W pozostałych przypadkach zbuduj DP w naturalnym porządku liczb, z krawędzią j->i dla gcd(a+j,a+i)=1. Zapamiętaj poprzednika.
//
// Stan i niezmiennik
//
// dp[i] jest minimalną liczbą krawędzi od a do a+i. Każda krawędź prowadzi do większej liczby, więc kolejność indeksów jest topologiczna.
//
// Złożoność
//
// W najgorszym razie O((b-a)^2 log b) czasu i O(b-a) pamięci. Wstępne próby skracają część przypadków, lecz nie zmieniają granicy najgorszego przypadku.
//
// Przypadki brzegowe
//
// - Dla a=b wynik ma zero kroków.
// - Wymagane b>=a.
// - Przejścia między kolejnymi liczbami gwarantują istnienie ścieżki.
//
// Kiedy rozpoznać ten wariant
//
// Gdy można ustawić wierzchołki w rosnącym porządku, przejścia są acykliczne i potrzebna jest rekonstrukcja optimum.
//
// Warunki i uwagi
//
// - Kwadratowy fallback może być zbyt wolny przy dużym b-a.
//
// Zmiany kopii względem oryginału
//
// - Zamieniono GNU __gcd na standardowe std::gcd dostępne przez using namespace std. Umożliwia kompilację z Clang i GCC.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;


void solve()
{
    int a,b; cin >> a >> b;
    if (a==b)
    {
        cout << 0 << "\n";
        return;
    }

    if (gcd(a,b) == 1)
    {
        cout << 1 << "\n" << b-a << "\n";
        return;
    }

    for (int i = a+1; i < b && i <= a+4096; i++)
    {
        if (gcd(a,i) == 1 && gcd(i,b) == 1)
        {
            cout << 2 << "\n" << i-a << " " << b-i << "\n";
            return;
        }
    }

    int d = b-a;
    vector<int> dp(d+1, INT_MAX);
    vector<int> parent(d+1, -1);

    dp[0] = 0;

    for (int i = 1; i <= d; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (gcd(j+a, i+a) == 1 && dp[j] != INT_MAX)
            {
                if (dp[j]+1 < dp[i])
                {
                    dp[i] = dp[j]+1;
                    parent[i] = j;
                }
            }
        }
    }

    vector<int> ans;
    int pos = d;

    while(pos > 0)
    {
        ans.push_back(pos-parent[pos]);
        pos = parent[pos];
    }

    reverse(ans.begin(), ans.end());

    cout << ans.size() << "\n";
    for (int x : ans) cout << x << " ";
    cout << "\n";
}


int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; 
    while(t--) solve();
}