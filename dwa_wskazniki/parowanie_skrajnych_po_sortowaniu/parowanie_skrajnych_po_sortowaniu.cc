// Sortowanie i zużywanie par skrajnych
//
// Oryginał w zbiorze codeforces/2245/two_pointers/2245B.cc
// https://codeforces.com/contest/2245
//
// Co oblicza kod
//
// Obliczyć sum(a)-n*c powiększoną o dodatnie niedobory c-a[i] dla co najwyżej floor(n/2) najmniejszych wartości poniżej c.
//
// Pomysł
//
// Posortuj tablicę, trzymaj l,r i za każde a[l]<c dodawaj niedobór, po czym przesuwaj oba końce. Gdy najmniejszy niewykorzystany element nie ma niedoboru, zakończ.
//
// Stan i niezmiennik
//
// Po t iteracjach zużyto t najmniejszych i t największych elementów. Do wyniku dodano dokładnie niedobory pierwszych t elementów. dzięki sortowaniu pozostały lewy element bez niedoboru wyklucza wszystkie dalsze.
//
// Złożoność
//
// O(n log n) czasu i O(n) pamięci. sam etap dwóch wskaźników O(n).
//
// Przypadki brzegowe
//
// Przy nieparzystym n środkowy element nie bierze udziału. Dla n=1 wynikiem jest a[0]-c. Opis dotyczy dokładnej formuły, bo cel parowania wymaga treści zadania.
//
// Kiedy rozpoznać ten wariant
//
// Po sortowaniu wybór skrajnych elementów zamyka jednocześnie dwa miejsca i potrzebujesz tylko ograniczonej liczby najmniejszych niedoborów.
//
// Warunki i uwagi
//
// - Czas O(n log n), pamięć O(n). W praktyce dodaje dodatnie niedobory najwyżej floor(n/2) najmniejszych wartości; brak treści zadania uniemożliwia ocenę interpretacji par.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int n; long long c; cin >> n >> c;
    vector<int> a(n);
    long long sum=0; 
    for (int i = 0; i < n; i++) 
    {
        cin >> a[i];
        sum += a[i];
    }

    long long base_case = sum- (1LL*n*c);
    sort(a.begin(), a.end());
    
    int l=0,r=n-1;
    while (l < r)
    {
        if (a[l] < c)
        {
            base_case += c - a[l];
            l+=1;r-=1;
        }
        else break;
    }

    cout << base_case << "\n";

}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) solve();
}