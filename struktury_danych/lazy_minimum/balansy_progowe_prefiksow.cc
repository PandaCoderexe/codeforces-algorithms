// Lazy. dodawanie przedziałowe i minimum
//
// Oryginał w zbiorze codeforces/2226/segmenttree/2226E.cc
// https://codeforces.com/contest/2226
//
// Co oblicza kod
//
// Dla każdego prefiksu utrzymuje balansy progów i zwiększa mex, gdy próbne odjęcie przedziału zachowuje nieujemne minimum na [0,mex].
//
// Pomysł
//
// Dodawać na progowych prefiksach. awans mex testować przez próbne odjęcie i minimum, cofając zmianę przy wyniku ujemnym.
//
// Stan i niezmiennik
//
// Węzeł przechowuje minimum balansów, lazy jest wspólnym przesunięciem już wliczonym w minimum. Awans zatwierdza się tylko przy minimum≥0.
//
// Złożoność
//
// O(n log n+M) czasu i O(n+M) pamięci, M=max(n,max a). awansów łącznie ≤n, nieudanych prób ≤n.
//
// Przypadki brzegowe
//
// Zero. powtórzenia. duże wartości. wiele awansów po jednym elemencie.
//
// Kiedy rozpoznać ten wariant
//
// Rozpoznaj wzorzec. lazy. dodawanie przedziałowe i minimum. Dodawać na progowych prefiksach. awans mex testować przez próbne odjęcie i minimum, cofając zmianę przy wyniku ujemnym.
//
// Warunki i uwagi
//
// - mex nie jest zwykłym MEX wejściowego prefiksu. Interpretacja balansów i operacji na liczbach wymaga treści zadania. Pamięć zależy również od maksimum wartości, dane muszą być nieujemne.
//
// KONIEC OPISU
#include <iostream>
#include  <vector>
#include <algorithm>
#include <climits>   
using namespace std;

struct DrzewoPrzedzialowe
{
    int rozmiar;
    vector<int> minimum;
    vector<int> leniwe;

    DrzewoPrzedzialowe(int n)
    {
        rozmiar = 1;

        while (rozmiar < n)
        {
            rozmiar *= 2;
        }

        minimum.assign(2 * rozmiar, 0);
        leniwe.assign(2 * rozmiar, 0);
    }

    void dodajLeniwie(int wierzcholek, int wartosc)
    {
        minimum[wierzcholek] += wartosc;
        leniwe[wierzcholek] += wartosc;
    }

    void przepchnij(int wierzcholek)
    {
        if (leniwe[wierzcholek] != 0)
        {
            dodajLeniwie(2 * wierzcholek, leniwe[wierzcholek]);
            dodajLeniwie(2 * wierzcholek + 1, leniwe[wierzcholek]);
            leniwe[wierzcholek] = 0;
        }
    }

    void dodaj(int wierzcholek, int lewy, int prawy, int zapLewy, int zapPrawy, int wartosc)
    {
        if (zapLewy > prawy || zapPrawy < lewy)
        {
            return;
        }

        if (zapLewy <= lewy && prawy <= zapPrawy)
        {
            dodajLeniwie(wierzcholek, wartosc);
            return;
        }

        przepchnij(wierzcholek);

        int srodek = (lewy + prawy) / 2;

        dodaj(2 * wierzcholek, lewy, srodek, zapLewy, zapPrawy, wartosc);
        dodaj(2 * wierzcholek + 1, srodek + 1, prawy, zapLewy, zapPrawy, wartosc);

        minimum[wierzcholek] = min(minimum[2 * wierzcholek], minimum[2 * wierzcholek + 1]);
    }

    void dodaj(int lewy, int prawy, int wartosc)
    {
        if (lewy > prawy)
        {
            return;
        }

        dodaj(1, 0, rozmiar - 1, lewy, prawy, wartosc);
    }

    int zapytajMinimum(int wierzcholek, int lewy, int prawy, int zapLewy, int zapPrawy)
    {
        if (zapLewy > prawy || zapPrawy < lewy)
        {
            return INT_MAX;
        }

        if (zapLewy <= lewy && prawy <= zapPrawy)
        {
            return minimum[wierzcholek];
        }

        przepchnij(wierzcholek);

        int srodek = (lewy + prawy) / 2;

        return min(
            zapytajMinimum(2 * wierzcholek, lewy, srodek, zapLewy, zapPrawy),
            zapytajMinimum(2 * wierzcholek + 1, srodek + 1, prawy, zapLewy, zapPrawy)
        );
    }

    int zapytajMinimum(int lewy, int prawy)
    {
        return zapytajMinimum(1, 0, rozmiar - 1, lewy, prawy);
    }
};

void solve()
{
    int n;
    cin >> n;

    vector<int> tablica(n);

    int najwiekszaLiczba = n;

    for (int i = 0; i < n; i++)
    {
        cin >> tablica[i];
        najwiekszaLiczba = max(najwiekszaLiczba, tablica[i]);
    }

    vector<int> ileRazy(najwiekszaLiczba + 5, 0);

    DrzewoPrzedzialowe drzewo(n + 2);

    int mex = 0;

    vector<int> odpowiedzi;

    for (int liczba : tablica)
    {
        bool bylaWczesniej = ileRazy[liczba] > 0;
        ileRazy[liczba]++;

        int granica = -1;

        if (liczba > 0)
        {
            granica = (liczba - 1) / 2;
            granica = min(granica, n);
        }

        if (liczba < mex)
        {
            if (!bylaWczesniej)
            {
                drzewo.dodaj(0, liczba, 1);
            }
            else
            {
                drzewo.dodaj(0, granica, 1);
            }
        }
        else
        {
            drzewo.dodaj(0, granica, 1);
        }

        while (mex < n)
        {
            if (ileRazy[mex] > 0)
            {
                int granicaMex = -1;

                if (mex > 0)
                {
                    granicaMex = (mex - 1) / 2;
                    granicaMex = min(granicaMex, n);
                }

                drzewo.dodaj(0, granicaMex, -1);

                if (drzewo.zapytajMinimum(0, mex) >= 0)
                {
                    mex++;
                }
                else
                {
                    drzewo.dodaj(0, granicaMex, 1);
                    break;
                }
            }
            else
            {
                drzewo.dodaj(0, mex, -1);

                if (drzewo.zapytajMinimum(0, mex) >= 0)
                {
                    mex++;
                }
                else
                {
                    drzewo.dodaj(0, mex, 1);
                    break;
                }
            }
        }

        odpowiedzi.push_back(mex);
    }

    for (int i = 0; i < n; i++)
    {
        cout << odpowiedzi[i] << " ";
    }

    cout << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int liczbaTestow;
    cin >> liczbaTestow;

    while (liczbaTestow--)
    {
        solve();
    }

    return 0;
}