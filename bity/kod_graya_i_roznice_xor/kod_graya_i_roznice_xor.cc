// Kod Graya i pojedyncze przełączenia bitu
//
// Oryginał w zbiorze codeforces/2271/bits/2271C.cc
// https://codeforces.com/contest/2271
//
// Co oblicza kod
//
// Dla b=minimalnego z 2^b>n wygenerować różnice XOR kolejnych kodów Graya, ostatni kod oraz ponownie te same różnice.
//
// Pomysł
//
// Użyj g(i)=i^(i>>1). Sąsiednie kody różnią się dokładnie jednym bitem, więc g(i)^g(i-1) wskazuje pojedynczą potęgę dwójki. Środkowy g(2^b-1) zamyka pierwszy obchód do zera.
//
// Stan i niezmiennik
//
// Prefiksowy XOR pierwszej części odtwarza kolejne kody Graya. po środkowej wartości wraca do 0 i druga część odtwarza obchód.
//
// Złożoność
//
// O(2^b)=O(n+1) czasu i pamięci. wynik ma 2^(b+1)-1 elementów.
//
// Przypadki brzegowe
//
// Dla n będącego potęgą dwójki wybierany jest dodatkowy bit, ponieważ nierówność jest ostra. Duże n może przepełnić 1<<b. Nie jest to drukowanie samych kodów Graya, lecz ich różnic XOR.
//
// Kiedy rozpoznać ten wariant
//
// Potrzebujesz sekwencji przełączeń pojedynczych bitów obejmującej wszystkie maski.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;

vector<int> generateGrayCodes(int max_b) 
{
    vector<int> res;
    for (int i = 0; i < (1 << max_b); i++)  res.push_back(i ^ (i >> 1));
    return res;
}

void solve()
{
    int n, b = 0; cin >> n;
    while ((1 << b) <= n) b++;

    vector<int> gray = generateGrayCodes(b), ans;
    for (int i = 1; i < (int)gray.size(); i++) ans.push_back(gray[i] ^ gray[i-1]);
    ans.push_back(gray[(int)gray.size()-1]);
    for (int i = 1; i < (int)gray.size(); i++) ans.push_back(gray[i] ^ gray[i-1]);
    cout << (int)ans.size() << "\n";
    for (int x: ans) cout << x << " ";
    cout << "\n";

}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();
}