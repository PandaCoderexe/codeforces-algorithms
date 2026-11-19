// Minimalny koszt cięcia napisu
//
// Oryginał w zbiorze codeforces/2233/searching/2233C.cc
// https://codeforces.com/contest/2233
//
// Co oblicza kod
//
// Znaleźć granicę minimalizującą liczbę znaków ( po lewej i ) po prawej, a potem oznaczyć do min(k,koszt) takich pozycji maską 1.
//
// Pomysł
//
// Zacznij z liczbą wszystkich ) po prawej. Przesuwając cięcie o jeden znak, zwiększ bad_left dla ( albo zmniejsz bad_right dla ). Zapamiętaj pierwsze minimum i odtwórz maskę.
//
// Stan i niezmiennik
//
// Dla aktualnego cięcia bad_left to liczba ( przed granicą, a bad_right to liczba ) za granicą. Ich suma jest kosztem zmiany napisu w ciąg samych ) po lewej i samych ( po prawej.
//
// Złożoność
//
// O(n) czasu i O(n) pamięci na napis oraz maskę. stan kosztu O(1).
//
// Przypadki brzegowe
//
// Dopuszczalne są puste części. Remisy zachowują najwcześniejsze cięcie, bo aktualizacja używa <. Jeśli k przewyższa koszt, kod oznacza tylko koszt pozycji.
//
// Kiedy rozpoznać ten wariant
//
// Koszt rozwiązania zależy od jednej granicy i dwóch liczników aktualizowanych przy jej przesuwaniu.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;

const int INF = 1e6;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--)
    {

        int n,k;
        cin >> n >> k;
        string s;
        cin >> s;
    
        int cost = INF;
        int bad_left  = 0, bad_right = 0;
        int bad_position = 0;
        
        for (int i = 0; i < (int)s.size(); i++)
        {
            if (s[i] == ')') bad_right++;
        }
    
        cost = min(cost, bad_right);
    
        for (int i = 1; i <= int(s.size()); i++)
        {
            if (s[i-1] == '(') bad_left++;
            else bad_right--;
    
            if (bad_left+bad_right < cost)
            {
                cost = bad_left+bad_right;
                bad_position = i;
            }
        }
    
        string res;
        res.resize(int(s.size()), '0');
        int limit = min(k, cost);
        int usunieto = 0;
    
        for (int i = 0; i < bad_position; i++)
        {
            if (s[i] == '(' && usunieto < limit)
            {
                usunieto++;
                res[i] = '1';
            }
        }
    
        for (int i = bad_position; i < int(s.size()); i++)
        {
            if (s[i] == ')' && usunieto < limit)
            {
                usunieto++;
                res[i] = '1';
            }
        }
    
        cout << res << "\n";
    }

    return 0;
}