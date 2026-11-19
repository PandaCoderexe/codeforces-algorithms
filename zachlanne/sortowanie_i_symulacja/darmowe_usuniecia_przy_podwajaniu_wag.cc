// Malejąca kolejność i terminy darmowych usunięć
//
// Oryginał w zbiorze codeforces/2128/greedy/2128A.cc
// https://codeforces.com/contest/2128
//
// Co oblicza kod
//
// Dla dodatnich wag i progu c zminimalizować liczbę płatnych usunięć, gdy pozostałe wagi podwajają się po każdym usunięciu, a wagę >c usuwa się płatnie.
//
// Pomysł
//
// Wszystkie płatne usunięcia można odłożyć na koniec. skanować początkowo dopuszczalne wagi malejąco. Jeśli aktualna waga <=c, usunąć ją darmowo i podwoić cały przyszły sufiks. zbyt duże wagi odłożyć do płatnej części bez konsumowania czasu darmowych usunięć.
//
// Stan i niezmiennik
//
// Przed każdym udanym darmowym usunięciem nieprzetworzony sufiks pozostaje malejący i zawiera wagi po dokładnie tej samej liczbie podwojeń. Największa dostępna waga ma najwcześniejszy termin, więc wcześniejsze jej usunięcie nie zmniejsza liczby darmowych usunięć. Elementy już przekraczające c nigdy ponownie nie staną się darmowe.
//
// Złożoność
//
// Czas O(n^2), pamięć O(n). W kodzie y początkowo zawiera n zer i następnie dopisuje właściwe wagi, więc rozmiar wynosi najwyżej 2n, bez zmiany rzędu złożoności.
//
// Przypadki brzegowe
//
// Wymagane dodatnie a oraz 0<c<=INT_MAX/2. W chwili podwojenia cały nieprzetworzony sufiks <=bieżąca waga<=c, więc jego podwojenie mieści się w int. Zera dodane przez vector<int> y(n) po rzeczywistych wagach dają tylko zbędne darmowe kroki i nie zwiększają wyniku.
//
// Kiedy rozpoznać ten wariant
//
// Jednakowe operacje mają terminy zależne od wartości. im większa waga, tym wcześniej traci darmową wykonalność. Uporządkować po pilności i odrzucać spóźnione operacje.
//
// Warunki i uwagi
//
// - Zachować źródło: początkowe n zer w y jest nadmiarowe, lecz w podanym dodatnim zakresie nie zmienia odpowiedzi. Biblioteka powinna jawnie wskazywać koszt kwadratowej symulacji.
// - Bez ograniczenia c<=INT_MAX/2 podwajanie int może przepełnić typ. Bezpośrednia zgodność zakresu z treścią zadania wymaga weryfikacji; dokumentacja kandydata podaje warunek wystarczający do bezpieczeństwa.
//
// KONIEC OPISU
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() 
{
    int x;
    cin >> x;

    while (x--) {
        int n, c, coins = 0;
        int mnoznik = 1;
        cin >> n >> c;
        vector<int> v(n);
        vector<int> y(n);

        for (int i = 0; i < n; ++i) {
            cin >> v[i];
            if (v[i] <=c) {
                y.push_back(v[i]);
            } 
        }

        sort(y.begin(), y.end(), greater<int>());

        for (int i = 0; i<n; ++i) {
            if (v[i] > c) {
                coins++;
            }
        }

        for (int i = 0; i<y.size(); ++i) {
            if (y[i] > c) {
                coins++;
                continue;
            }
            else {
                for (int j = i; j<y.size(); ++j) {
                    y[j] *= 2;
                }
            }
        }
        cout << coins << "\n";


    }
    return 0;
}