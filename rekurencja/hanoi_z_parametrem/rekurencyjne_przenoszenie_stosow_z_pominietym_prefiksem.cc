// Rekurencja ruchów na trzech palikach
//
// Oryginał w zbiorze codeforces/2232/recursion/2232D.cc
// https://codeforces.com/contest/2232
//
// Co oblicza kod
//
// Wygenerować listę trójek (numer,s,t) przez podaną rekurencję dla parametrów 0<=a[i]<=i.
//
// Pomysł
//
// Dla a[k-1]=0 użyć klasycznego schematu dwóch wywołań k-1. W innym przypadku x=k-1-a[k-1]. przenieść x do pomocniczego, wykonać ruch k, cofnąć x i przenieść k-1.
//
// Stan i niezmiennik
//
// moveall(k,s,t) zapisuje konkatenację określonych podproblemów. trzeci palik u=6-s-t. Rozmiar. T(k)=2T(k-1)+1 albo 2T(x)+T(k-1)+1.
//
// Złożoność
//
// Czas i pamięć listy O(2^n) w najgorszym przypadku, stos O(n). koszt jest proporcjonalny do wygenerowanych ruchów.
//
// Przypadki brzegowe
//
// a[0]=0 konieczne. tablica a ma 20 elementów. Ujemne a nie są sprawdzane i mogą prowadzić do niepoprawnej rekurencji.
//
// Kiedy rozpoznać ten wariant
//
// Konstrukcja ruchów składa się z przeniesienia mniejszego podproblemu przed i po ruchu największego obiektu. odpowiedź sama może mieć wykładniczy rozmiar.
//
// Warunki i uwagi
//
// - Semantyka ograniczeń ruchu wymaga treści zadania; nie nazywać tego bezwarunkowo klasycznym Hanoi. Wymaga n<=20 oraz 0<=a[i]<=i; sprawdza jedynie górną granicę.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int n;
vector<int> a(20);
vector<vector<int>> op;

void moveall(int k, int s, int t)
{
    if (k == 0) return;

    int u = 6 - s - t;

    if (a[k - 1] == 0)
    {
        moveall(k - 1, s, u);
        op.push_back({k, s, t});
        moveall(k - 1, u, t);
    }
    else
    {
        int x = k - 1 - a[k - 1];
        moveall(x, s, u);
        op.push_back({k, s, t});
        moveall(x, u, s);
        moveall(k - 1, s, t);
    }
}

void solve()
{
    cin >> n;
    op.clear();
    for (int i = 0; i < n; i++) cin >> a[i];

    for (int i = 0; i < n; i++)
    {
        if (a[i] > i)
        {
            cout << "NO\n";
            return;
        }
    }

    moveall(n, 1, 3);
    cout << "YES\n";
    cout << op.size() << "\n";
    for (auto &p : op) cout << p[0] << " " << p[1] << " " << p[2] << "\n";

}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}