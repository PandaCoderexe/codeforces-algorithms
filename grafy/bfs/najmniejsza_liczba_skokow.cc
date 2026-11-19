// BFS minimalnej liczby skoków
//
// Oryginał w zbiorze codeforces/910/graph/910A.cc
// https://codeforces.com/contest/910
//
// Co oblicza kod
//
// Liczy najmniejszą liczbę skoków o 1..j pozycji w prawo po znakach 1.
//
// Pomysł
//
// Ze stanu pozycji dodawać nieodwiedzone pozycje odległe o 1..j w prawo, gdy znak celu wynosi 1.
//
// Stan i niezmiennik
//
// Warstwy kolejki odpowiadają rosnącej liczbie skoków, więc pierwsze odwiedzenie ustala najkrótszą odległość.
//
// Złożoność
//
// O(len·j) czasu w najgorszym przypadku i O(len) pamięci. kod skanuje j kandydatów także blisko końca.
//
// Przypadki brzegowe
//
// Wymagany poprawny start. nieosiągalny koniec. j=1. duży j. len=1.
//
// Kiedy rozpoznać ten wariant
//
// Najmniejsza liczba jednakowo kosztujących ruchów w grafie niejawnym.
//
// Warunki i uwagi
//
// - Poprawka kopii. dodać #include <queue>, wymagane przez queue<int>. Źródło pozostaje nietknięte.
// - Kontrakt: len≥1, prawidłowa długość napisu i poprawny znak pozycji startowej.
//
// Zmiany kopii względem oryginału
//
// - Dodano brakujący nagłówek <queue>. Logika BFS zachowuje postać oryginału.
//
// KONIEC OPISU
#include <queue>
#include <iostream>
#include <vector>
#include <string>
#include <vector>

using namespace std;

int main() {
    int len, j;
    string x;
    cin >> len >> j;
    cin >> x;

    vector<int> v(len, -1);
    v[0] = 0;
    queue<int> q;
    q.push(0);

    while(!q.empty()) {
        int current_vertex = q.front();
        q.pop();

        for (int i = 1; i <= j; ++i) {
            int next = current_vertex + i;
            if (next < len && x[next] == '1' && v[next] == -1) {
                v[next] = v[current_vertex] + 1;
                q.push(next);
            }
        }
    }

    cout << v[len-1];
}