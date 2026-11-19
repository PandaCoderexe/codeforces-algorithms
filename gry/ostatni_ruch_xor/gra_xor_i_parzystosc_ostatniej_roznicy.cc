// Gra binarna. ostatnia skuteczna decyzja
//
// Oryginał w zbiorze codeforces/2171/greedy/2171C1.cc
// https://codeforces.com/contest/2171
//
// Co oblicza kod
//
// Dla binarnych tablic i modelu naprzemiennych zamian a[i],b[i] wyznaczyć wynik gry przez XOR-y i ostatnią różniącą pozycję.
//
// Pomysł
//
// Jeśli XOR-y równe, zamiana zmienia oba jednakowo i pozostaje remis. Przy różnych XOR-ach ostatni indeks a[i]!=b[i] daje właścicielowi ruchu ostateczny wybór zwycięzcy.
//
// Stan i niezmiennik
//
// Równość dwóch XOR-ów jest zachowana przez zamiany. Po ostatnim różniącym indeksie żaden kolejny ruch nie zmienia wyniku. indeks 1-based nieparzysty należy Ajisai, parzysty Mai.
//
// Złożoność
//
// Czas O(n), pamięć O(n).
//
// Przypadki brzegowe
//
// Tablice binarne. dla wielobitowych wartości nie można zastąpić analizy decydującego bitu zwykłym a[i]!=b[i]. Równe tablice zawsze dają Tie.
//
// Kiedy rozpoznać ten wariant
//
// Naprzemienna gra, w której każdy ruch przełącza ten sam globalny bit i liczy się ostatnia pozycja umożliwiająca przełączenie.
//
// Warunki i uwagi
//
// - Wniosek o zwycięzcy zakłada model zadania i najpewniej wartości binarne; sam test nierówności nie wystarcza do ogólnej gry na wielobitowych liczbach.
// - Model ruchów i binarność to założenia wymagane do interpretacji jako rozwiązania gry; kod sam wykonuje wyłącznie testy XOR i parytetu.
//
// KONIEC OPISU
#include <iostream>
#include <vector>

using namespace std;

void solve()
{
    int len;
    cin >> len;

    vector<int> a(len);
    vector<int> b(len);

    int xa = 0, xb = 0;
    for (int i = 0; i < len; i++)
    {
        cin >> a[i];
        xa ^= a[i];
    }
    for (int i = 0; i < len; i++)
    {
        cin >> b[i];
        xb ^= b[i];
    }

    if (xa == xb)
    {
        cout << "Tie\n";
        return;
    }

    int lastOp = -1;
    for (int i = 0; i < len; i++)
    {
        if (a[i] != b[i]) lastOp = i;
    }

    lastOp++;
    if (lastOp % 2 == 0)
    {
        cout << "Mai\n";
    }
    else
    {
        cout << "Ajisai\n";
    }


    //cout << "\n";
}

int main()
{
    int n;
    cin >> n;

    while(n--)
    {
        solve();
    }
}