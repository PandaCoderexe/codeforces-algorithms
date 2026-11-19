// Kompresja składowych implicitnej siatki
//
// Oryginał w zbiorze codeforces/2106/dp/2106F.cc
// https://codeforces.com/contest/2106
//
// Co oblicza kod
//
// Obliczyć maksimum rozmiaru składowej zer macierzy n*n, której kolumna i zawiera s[i] poza odwróconą przekątną.
//
// Pomysł
//
// Zerowa kolumna dzieli się na górny odcinek długości i i dolny n-i-1. jedynkowa ma tylko pojedyncze zero na przekątnej. Łączą się tylko sąsiednie odcinki zgodnie z przejściami.
//
// Stan i niezmiennik
//
// Dla s[i]=0. up=i+(s[i-1]=0?up_prev:single_prev), down=n-i-1+(s[i-1]=0?down_prev:0). Dla s[i]=1. single=1+(s[i-1]=0?down_prev:0). ans jest maksimum dotychczasowych rozmiarów.
//
// Złożoność
//
// Czas O(n), O(1) stanów pomocniczych, O(n) pamięci napisu.
//
// Przypadki brzegowe
//
// n=1. same zera. same jedynki. przejście 010 łączy dolną część lewej kolumny z górną prawej przez singleton. Liczność może być kwadratowa, użyto long long.
//
// Kiedy rozpoznać ten wariant
//
// Kwadratowa macierz ma kolumny z jednym wyjątkiem i sąsiedztwo zależy wyłącznie od kilku typów fragmentów.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve()
{
    int n; cin >> n;
    string s; cin >> s;


    ll ans = 0, up = 0, down = 0, single = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '0')
        {
            ll nup = i, ndown = n-i-1;

            if (i > 0)
            {
                if (s[i-1] == '0')
                {
                    nup+=up;
                    ndown+=down;
                }
                else nup+=single;
            }

            up = nup;
            down = ndown;
            ans = max(up, ans);
            ans = max(down, ans);
        }
        else
        {
            ll nsingle = 1;
            if (i>0 && s[i-1] == '0') nsingle += down;
            single = nsingle;
            ans = max(ans, single);        
        }


    }

    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();
}