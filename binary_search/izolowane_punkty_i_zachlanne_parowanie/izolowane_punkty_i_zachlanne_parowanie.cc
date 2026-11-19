// Binary search z izolacją punktów i zachłannym parowaniem
//
// Oryginał w zbiorze codeforces/2272/bin_search/C.cc
// https://codeforces.com/contest/2272
//
// Co oblicza kod
//
// Dla posortowanych punktów a znaleźć najmniejsze k w 1..10^9, dla którego po usunięciu punktów mających sąsiada w odległości <=k pozostałe punkty da się podzielić na najwyżej x jedno- lub dwuosobowych grup. para wymaga odległości <=2k.
//
// Pomysł
//
// W checkerze wyodrębnij punkty izolowane względem obu sąsiadów. Przechodząc po nich od lewej, łącz pierwsze dwa, gdy mieszczą się w 2k. pozostały punkt jest singletonem. Następnie szukaj pierwszego dobrego k.
//
// Stan i niezmiennik
//
// Greedy użycie najbliższej dopuszczalnej pary minimalizuje liczbę grup izolowanych punktów. Przy zwiększeniu k izolowanych punktów ubywa i dopuszczalna odległość pary rośnie, więc minimalna liczba grup nie rośnie.
//
// Złożoność
//
// O(n log 10^9) czasu i O(n) pamięci roboczej.
//
// Przypadki brzegowe
//
// Tablica musi być już posortowana. kod jej nie sortuje. Zakres wyklucza k=0. Dla n=1 potrzeba x>=1, bo pojedynczy punkt pozostaje izolowany dla każdego k. Istnienie odpowiedzi w górnej granicy musi być gwarantowane.
//
// Kiedy rozpoznać ten wariant
//
// Monotoniczny parametr najpierw usuwa lokalnie obsłużone elementy, a koszt pozostałych obliczasz niezależnym greedy na uporządkowanym zbiorze.
//
// Warunki i uwagi
//
// - Zakłada posortowane a, ale go nie sortuje. 2*k*1LL najpierw oblicza 2*k w int; przy użytym k<=10^9 mieści się, lecz nie po rozszerzeniu zakresu. Wyszukiwanie nie obejmuje k=0.
//
// KONIEC OPISU
#include <bits/stdc++.h>


using namespace std;

bool checker(int k, int &x, const vector<int>& a)
{
    int n = a.size();
    vector<int> merge;
    for (int i = 0; i < n; i++)
    {
        bool left = (i == 0 || a[i] - a[i-1] > k), right = (i == n-1 || a[i+1] - a[i] > k);
        if (left&&right) merge.push_back(a[i]);

    }

    int cnt = 0;
    for (int i = 0; i < (int)merge.size();i++)
    {
        if (i + 1 < (int)merge.size() && merge[i+1] -  merge[i] <= 2*k*1LL)
        {
            i++;
            cnt++;
        }
        else cnt++;
    }

    return cnt <= x;
}

void solve()
{
    int n,x; cin >> n >> x;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    int l = 1, r= 1e9;
    while(l < r)
    {   
        int m = l + (r-l) / 2;
        if (checker(m, x, a)) r = m;
        else l = m+1;
    }
    cout << l <<"\n";
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();
}