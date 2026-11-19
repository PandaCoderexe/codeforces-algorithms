// Plecak dwuwymiarowy z rekonstrukcją bloków
//
// Oryginał w zbiorze codeforces/2145/dp/2145D.cc
// https://codeforces.com/contest/2145
//
// Co oblicza kod
//
// Zbudować permutację n elementów o dokładnie k inwersjach w rodzinie rosnących bloków ustawionych malejąco według wartości.
//
// Pomysł
//
// target=n(n-1)/2-k liczy pary wewnątrz bloków. DP wybiera dodatnie długości o sumie n i sumie trójkątnej target. zapisuje ostatnią długość.
//
// Stan i niezmiennik
//
// dp[i][j] oznacza istnienie podziału i elementów z sumą len(len-1)/2=j. Przejście dodaje dowolny blok. rekonstrukcja odejmuje długość i jej liczbę par. Pary między blokami są inwersjami, wewnątrz nie.
//
// Złożoność
//
// Czas O(n^2*target), pamięć O(n*target). przy target=O(n^2) odpowiednio O(n^4) i O(n^3).
//
// Przypadki brzegowe
//
// 0<=k<=n(n-1)/2. ujemny target psuje rozmiar wektora. Brak podziału daje 0. Nie wszystkie k muszą być osiągalne w tej ograniczonej rodzinie.
//
// Kiedy rozpoznać ten wariant
//
// Konstrukcja sprowadza się do sumy parametrów bloków i sumy ich kosztów. potrzebne jest także odtworzenie świadectwa.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve()
{
    int n, k; cin >> n >> k;
    int total = n * (n-1) / 2;
    int target = total-k;

    vector<vector<bool>> dp(n+1, vector<bool>(target+1));
    vector<vector<int>> length_(n+1,vector<int>(target+1));
    dp[0][0] = 1;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= target; j++)
        {
            if (!dp[i][j]) continue;

            for (int len = 1; len+i <= n; len++)
            {
                int ni = len+i;
                int nj = j + (len*(len-1)/2);

                if (nj > target) break;
                if (dp[ni][nj] == 0)
                {
                    dp[ni][nj] = 1;
                    length_[ni][nj] = len; 
                }
            }
        }
    }

    if (dp[n][target] == 0)
    {
        cout << 0 << "\n";
        return;
    }

    vector<int> b;
    int len = n;
    int t = target;
    while (len > 0)
    {
        int l = length_[len][t];
        b.push_back(l);
        len -= l;
        t -= l*(l-1)/2;
    }

    reverse(b.begin(), b.end());
    
    vector<int> ans;
    int maximum = n;

    for (int len: b)
    {
        for (int val = maximum - len +1; val <= maximum; val++) ans.push_back(val);
        maximum -=len;

    }

    for (int val: ans) cout << val << " ";
    cout << "\n";

}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t; cin>>t;
    while(t--) solve();
}