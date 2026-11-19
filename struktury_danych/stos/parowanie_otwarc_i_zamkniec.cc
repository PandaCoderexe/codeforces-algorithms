// Parowanie przez stos indeksów
//
// Oryginał w zbiorze codeforces/2275/dataStructures/2275B.cc
// https://codeforces.com/contest/2275
//
// Co oblicza kod
//
// Paruje 1 z późniejszym 2, wypisując dopasowane zamknięcia i niedopasowane otwarcia. pomija sparowane otwarcia, samotne zamknięcia i pozostałe znaki.
//
// Pomysł
//
// Indeksy znaków 1 odkładać na stos. znak 2 usuwa ostatnie otwarcie, gdy ono istnieje. Flagi wybierają dopasowane zamknięcia oraz niedopasowane otwarcia.
//
// Stan i niezmiennik
//
// Stos zawiera dokładnie jeszcze niesparowane otwarcia bieżącego prefiksu. parowanie zawsze wybiera najnowsze.
//
// Złożoność
//
// O(n) czasu i O(n) pamięci. każdy indeks wchodzi i schodzi ze stosu najwyżej raz.
//
// Przypadki brzegowe
//
// Same otwarcia. same zamknięcia. naprzemienny ciąg. inne znaki. niedomknięty stos.
//
// Kiedy rozpoznać ten wariant
//
// Dopasowanie najnowszego niewykorzystanego otwarcia do bieżącego zamknięcia.
//
// Warunki i uwagi
//
// - Nie wypisuje wyłącznie niedopasowanych nawiasów: dopasowane zamknięcie pozostaje w odpowiedzi.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int n; cin >> n;
    string s; cin >> s;

    vector<int> st;
    vector<int> ok(n+1,0);
    for(int i = 1; i <= n; i++)
    {
        if(s[i-1] == '1') st.push_back(i);
        else if(s[i-1] == '2')
        {
            if(st.empty()) ok[i] = 1;
            else
            {
                ok[st.back()] = 1;
                st.pop_back();
            }
        }
        else ok[i] = 1;
    }

    vector<int> ans;
    for(int i = 1; i <= n; i++) if(!ok[i]) ans.push_back(i);

    cout << ans.size() << "\n";
    for(int x : ans) cout << x << " ";
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();
}