// Zachłanne dołączanie słów
//
// Oryginał w zbiorze codeforces/2180/implementation/2180B.cc
// https://codeforces.com/contest/2180
//
// Co oblicza kod
//
// Buduje leksykograficznie najmniejszy napis przez dołączanie kolejnych słów na początku lub końcu.
//
// Pomysł
//
// Dla kolejnego słowa a porównaj a+s z s+a i zachowaj mniejszy napis. Po obu wyborach długość napisu jest taka sama.
//
// Stan i niezmiennik
//
// Jeżeli s<=t i długości są równe, to a+s<=a+t oraz s+a<=t+a. Zachowanie mniejszego prefiksowego wyniku wystarcza dla kolejnych etapów.
//
// Złożoność
//
// O(sumy L_i) czasu, gdzie L_i to długość napisu po i-tym słowie, oraz O(L) pamięci. W najgorszym razie czas O(n*L).
//
// Przypadki brzegowe
//
// - Równe kandydaty można rozstrzygnąć dowolnie.
// - Długie wspólne prefiksy zwiększają koszt porównania.
//
// Kiedy rozpoznać ten wariant
//
// Gdy każdy krok daje kilka wyników tej samej długości, a późniejsze operacje zachowują porządek leksykograficzny.
//
// KONIEC OPISU
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s = "";

        for (int i = 0; i < n; i++) {
            string a;
            cin >> a;

            string c1;
            c1.reserve(a.size() + s.size());
            c1 += a;
            c1 += s;

            string c2;
            c2.reserve(a.size() + s.size());
            c2 += s;
            c2 += a;

            s = (c1 < c2 ? std::move(c1) : std::move(c2));
        }

        cout << s << "\n";
    }
    return 0;
}
