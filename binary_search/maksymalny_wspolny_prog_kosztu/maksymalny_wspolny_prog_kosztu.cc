// Maksymalizacja wspólnego progu z sumowanym kosztem
//
// Oryginał w zbiorze codeforces/2275/binary_search/2275D.cc
// https://codeforces.com/contest/2275
//
// Co oblicza kod
//
// Zmaksymalizować x w zakresie [minimum sum trójek, minimum+k], gdy suma kosztów trójek jest najwyżej k. koszt dla sumy<x określają jawne gałęzie check.
//
// Pomysł
//
// Użyj binary search z górnym środkiem. Trójka z sumą>=x nic nie kosztuje, równa trójka uniemożliwia przekroczenie swojej sumy, nieuporządkowana kosztuje x-sum, a rosnąca dodatkowo 2*(min(b-a,c-b)+1).
//
// Stan i niezmiennik
//
// Dla każdej trójki koszt jest niemalejący w x, łącznie z nieosiągalnym wzrostem równych trójek. left pozostaje dopuszczalnym progiem, a right ogranicza możliwą odpowiedź z góry.
//
// Złożoność
//
// O(n log(k+1)) czasu i O(n) pamięci. kopiowanie pojedynczej trójki w check ma stały koszt.
//
// Przypadki brzegowe
//
// Zakłada n>=1, k>=0 i brak przepełnienia sum oraz minimum+k. Brak treści zadania pozwala potwierdzić monotoniczność widocznej funkcji kosztu, ale nie jej interpretację operacyjną.
//
// Kiedy rozpoznać ten wariant
//
// Chcesz maksymalizować wspólny poziom, a koszt dojścia do poziomu jest sumą niezależnych niemalejących kosztów elementów.
//
// Warunki i uwagi
//
// - Checker jest O(n), binary search O(n log(k+1)); for(auto lab:labors) kopiuje każdą trójkę. Znaczenie kosztu wymaga treści zadania.
//
// KONIEC OPISU
#include <bits/stdc++.h>
#define ll long long

using namespace std;

int n;
ll k;
vector<vector<ll>> labors;

bool check(long long x)
{
    long long need = 0;

    for(auto lab: labors)
    {
        ll a = lab[0], b = lab[1], c = lab[2];
        ll sum = a+b+c;

        if(sum >= x) continue;
        if(a == b && b == c) return false;
        if(a > b || a > c || b > c) need += x-sum;
        else need += 2*(min(b-a, c-b)+1) + (x-sum);
        if(need > k) return false;
    }

    return true;
}

void solve()
{
    cin >> n >> k;
    labors.assign(n,vector<ll>(3,0));
    ll minimum = 4e18;
    for (int i = 0; i < n; i++) 
    {   
        cin >> labors[i][0] >> labors[i][1] >> labors[i][2];
        minimum = min(minimum, 1LL * labors[i][0]+labors[i][1]+labors[i][2]);
    }


    ll left = minimum, right = minimum +k;
    while(left < right)
    {
        ll mid = left + (right - left + 1) / 2;

        if(check(mid)) left = mid;
        else right = mid - 1;
    }

    cout << left << "\n";
    
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();
}