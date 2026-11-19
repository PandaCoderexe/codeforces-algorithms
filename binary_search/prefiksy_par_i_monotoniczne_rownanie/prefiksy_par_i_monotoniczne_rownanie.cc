// Prefiksy sąsiednich par i binary search w zapytaniu
//
// Oryginał w zbiorze codeforces/2260/binary_search/2260E.cc
// https://codeforces.com/contest/2260
//
// Co oblicza kod
//
// Dla każdego fragmentu domkniętego w cykl znaleźć najmniejsze m>=c01 spełniające m-c01>=max(0,c00-m)+max(0,c11-m) i wypisać 4*m-długość.
//
// Pomysł
//
// Zbuduj cztery prefiksy liczby par 00,01,10,11. W zapytaniu odejmij prefiksy par wewnętrznych, dodaj parę ostatni-pierwszy i wyszukaj minimalne m.
//
// Stan i niezmiennik
//
// Wraz ze wzrostem m lewa strona rośnie, a prawa nie rośnie, więc predykat jest monotoniczny. Częstości obejmują dokładnie długość fragmentu par cyklicznych.
//
// Złożoność
//
// O(n+q log n) czasu i O(n) pamięci.
//
// Przypadki brzegowe
//
// l=r tworzy jedną parę znaku z nim samym. Prefiksy par kończą się na n-1, a odejmowanie r-1 i l-1 jest celowe. Interpretacja 4*m-długość wymaga treści zadania. tu zapisano dokładną formułę.
//
// Kiedy rozpoznać ten wariant
//
// Statyczny napis daje stały rozmiar statystyk zapytania, po których można tanio testować monotoniczny warunek na odpowiedź.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n,q; cin >> n >> q;
    string t; cin >> t;

    vector<vector<int>> pref(4, vector<int>(n + 1, 0));
    for(int i = 1; i < n; i++)
    {
        for(int j = 0; j < 4; j++) pref[j][i] = pref[j][i - 1];
        int x = (t[i - 1] - '0') *2+ (t[i]-'0');
        pref[x][i]++;
    }

    for (int i = 0; i < q; i++)
    {
        int l,r; cin >> l >> r;
        int cnt[4] = {0, 0, 0, 0};
        for(int j = 0; j < 4; j++) cnt[j] = pref[j][r - 1] - pref[j][l - 1];
        int x = (t[r-1]- '0') *2+ (t[l-1]- '0');
        cnt[x]++;
        
        int left = cnt[1], right = r-l+1;
        while(left < right)
        {
            int mid = (left+right)/2;
            if (mid-cnt[1] >= max(0, cnt[0]-mid) + max(0, cnt[3]-mid)) right = mid;
            else left = mid+1;
        } 

        cout << 4 * left - (r-l+1) << "\n"; 


    }
}