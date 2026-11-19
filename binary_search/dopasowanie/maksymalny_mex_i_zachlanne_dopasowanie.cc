// MEX i zachłanny warunek wykonalności
//
// Oryginał w zbiorze codeforces/2226/implementation/2226C.cc
// https://codeforces.com/contest/2226
//
// Co oblicza kod
//
// Znajduje największy MEX osiągalny przez pokrycie brakujących wartości za pomocą dostępnych duplikatów i większych liczb o progach floor((x-1)/2).
//
// Pomysł
//
// Dla kandydata zarezerwuj po jednym egzemplarzu każdej obecnej wartości poniżej niego. Pozostałe elementy zamień na maksymalne progi. Posortowane braki dopasuj do najmniejszych wystarczających progów.
//
// Stan i niezmiennik
//
// Po dopasowaniu kolejnego braku pozostawiasz możliwie duże progi dla większych braków. Wykonalność wszystkich wartości 0..m-1 jest monotoniczna względem m.
//
// Złożoność
//
// O(A+n log^2 n) czasu i O(A+n) pamięci, A=max(n,max(a)). Każdy test kandydata sortuje do n progów.
//
// Przypadki brzegowe
//
// - Duplikat wartości potrzebnej do MEX może zostać pomocnikiem.
// - Brak odpowiedniego progu natychmiast odrzuca kandydata.
// - Wartości służą jako indeksy histogramu, więc muszą być nieujemne i ograniczone.
//
// Kiedy rozpoznać ten wariant
//
// Gdy maksymalizację MEX można sprowadzić do monotonicznego pokrywania braków zasobami z progami.
//
// KONIEC OPISU
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool czyDaSie(int kandydat, vector<int>& ile, vector<int>& wartosci)
{
    vector<int> braki;
    vector<int> pomagacze;

    for (int i = 0; i < kandydat; i++)
    {
        if (ile[i] == 0)
        {
            braki.push_back(i);
        }
        else
        {
            for (int j = 1; j < ile[i]; j++)
            {
                int granica = (i - 1) / 2;

                if (granica >= 0)
                {
                    pomagacze.push_back(granica);
                }
            }
        }
    }

    for (int x : wartosci)
    {
        if (x >= kandydat)
        {
            int granica = (x - 1) / 2;

            for (int j = 0; j < ile[x]; j++)
            {
                pomagacze.push_back(granica);
            }
        }
    }

    sort(pomagacze.begin(), pomagacze.end());

    int wsk = 0;

    for (int brak : braki)
    {
        while (wsk < (int)pomagacze.size() && pomagacze[wsk] < brak)
        {
            wsk++;
        }

        if (wsk == (int)pomagacze.size())
        {
            return false;
        }

        wsk++;
    }

    return true;
}

void solve()
{
    int n;
    cin >> n;

    vector<int> zygzak(n);

    int najwiekszy = 0;

    for (int i = 0; i < n; i++)
    {
        cin >> zygzak[i];
        najwiekszy = max(najwiekszy, zygzak[i]);
    }

    int rozmiar = max(najwiekszy, n) + 5;

    vector<int> ile(rozmiar, 0);

    for (int x : zygzak)
    {
        ile[x]++;
    }

    vector<int> wartosci;

    for (int i = 0; i < rozmiar; i++)
    {
        if (ile[i] > 0)
        {
            wartosci.push_back(i);
        }
    }

    int lewy = 0;
    int prawy = n;
    int wynik = 0;

    while (lewy <= prawy)
    {
        int srodek = (lewy + prawy) / 2;

        if (czyDaSie(srodek, ile, wartosci))
        {
            wynik = srodek;
            lewy = srodek + 1;
        }
        else
        {
            prawy = srodek - 1;
        }
    }

    cout << wynik << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int testy;
    cin >> testy;

    while (testy--)
    {
        solve();
    }

    return 0;
}