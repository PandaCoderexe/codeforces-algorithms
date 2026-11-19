// Zachłanny skan dla ustalonej długości podciągu
//
// Oryginał w zbiorze codeforces/2250/greedy/2250C.cc
// https://codeforces.com/contest/2250
//
// Co oblicza kod
//
// Znaleźć największe m zaakceptowane przez skan. wybierany element i na pozycji cnt+1 od lewej i m-cnt od prawej musi leżeć poza zakazami [l[i],r[i]] i [u[i],v[i]].
//
// Pomysł
//
// Enumerować m malejąco. Przy skanie wejścia wybrać pierwszy element, który jest dopuszczalny na aktualnie wymaganej pozycji. po m wyborach natychmiast zwrócić m.
//
// Stan i niezmiennik
//
// Dla ustalonego m licznik cnt jest liczbą dotychczas wybranych elementów, a następne wymagane pozycje to cnt+1 i m-cnt. Po każdym wyborze wszystkie wybrane pozycje spełniają swój lokalny warunek.
//
// Złożoność
//
// Czas O(n^2), pamięć O(n).
//
// Przypadki brzegowe
//
// Brak dopuszczalnego elementu daje 0. Warunki są negacjami przynależności do domkniętych przedziałów. Algorytm nie używa bisekcji ani nie zakłada monotoniczności wyniku checkera po m.
//
// Kiedy rozpoznać ten wariant
//
// Ograniczenie zależy od pozycji elementu w odpowiedzi od obu końców. ustalenie długości pozwala obie pozycje wyliczyć z jednego licznika.
//
// Warunki i uwagi
//
// - Skan implementuje wybór najwcześniejszego dopuszczalnego elementu; poprawność dla pierwotnego modelu wymaga uzasadnienia dominacji wcześniejszego wyboru. Nie dopisywać niepotwierdzonej monotoniczności po m.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve()
{
    int n; cin >> n;

    vector<int> l(n), r(n), u(n), v(n);
    for (int i = 0; i < n; i++) cin >> l[i] >> r[i] >> u[i] >> v[i];
    for (int m = n; m > 0; m--)
    {
        int cnt = 0; 
        for (int i = 0; i < n; i++)
        {
            int lr = cnt + 1, rr = m - cnt;
            bool ok_l = !(l[i] <= lr && lr <= r[i]), ok_r = !(u[i] <= rr && rr <= v[i]);
            if (ok_l && ok_r) cnt++; 
            if (cnt == m)
            {
                cout << m << '\n';
                return;
            }
        }
    }

    cout << 0 << '\n';
}


int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) solve(); 
} 