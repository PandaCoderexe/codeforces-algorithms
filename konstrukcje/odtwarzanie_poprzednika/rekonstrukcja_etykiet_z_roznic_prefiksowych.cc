// Odtwarzanie etykiet po wskazaniu poprzednika
//
// Oryginał w zbiorze codeforces/2160/greedy/2160B.cc
// https://codeforces.com/contest/2160
//
// Co oblicza kod
//
// Odtworzyć ciąg etykiet według prev=i-(b[i]-b[i-1]). nowa etykieta dla prev=0, inaczej etykieta pozycji prev.
//
// Pomysł
//
// Różnicą prefiksów odzyskać lokalne wskazanie. Tablica pos_to_val pozwala w O(1) skopiować już utworzoną klasę. nowe klasy numerować rosnąco.
//
// Stan i niezmiennik
//
// Po kroku i wszystkie pozycje <=i mają etykiety. prev musi być w [0,i-1], zatem odwołanie prowadzi wyłącznie do znanego prefiksu.
//
// Złożoność
//
// Czas O(n), pamięć O(n).
//
// Przypadki brzegowe
//
// Pierwsza pozycja musi wskazywać 0. Wskazanie wcześniejszej pozycji tej samej etykiety nie dowodzi, że jest ostatnim wystąpieniem. Wykryty błąd przerywa cały program.
//
// Kiedy rozpoznać ten wariant
//
// Dane prefiksowe po odjęciu są odległością do wcześniejszego elementu lub reprezentanta klasy. użyć odtwarzania od lewej.
//
// Warunki i uwagi
//
// - Nie sprawdza, czy prev jest rzeczywiście ostatnim wystąpieniem etykiety; wejście musi gwarantować realizowalność. Przy błędzie return 0 kończy wszystkie testy. Konwersja long long do int może zawężać.
//
// KONIEC OPISU
#include <iostream>
#include <vector>
using namespace std;
     
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
        
    int t;
    cin >> t;
     
    while (t--)
    {
        int n;
        if (!(cin >> n)) return 0;
        vector<long long> b(n+1); 
        b[0] = 0;
        for (int i = 1; i <= n; ++i) cin >> b[i];
        
        vector<int> a(n+1, 0);        
        vector<int> pos_to_val(n+1, 0); 
        int next_val = 0; 
        
        for (int i = 1; i <= n; ++i) {
            long long d = b[i] - b[i-1];
            int prev = int(i - d); 
        
            if (prev < 0 || prev > i-1) {
                cout << "-1\n";
                return 0;
            }
        
            if (prev == 0) {
                ++next_val;
                a[i] = next_val;
                pos_to_val[i] = next_val;
            } else {
                int v = pos_to_val[prev];
                if (v == 0) {
                    cout << "-1\n";
                    return 0;
                }
                a[i] = v;
                pos_to_val[i] = v;
            }
        }
        
        for (int i = 1; i <= n; ++i) {
            if (i > 1) cout << ' ';
            cout << a[i];
        }
        cout << '\n';
    }
    return 0;
}