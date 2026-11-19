// Sprawdzanie nieujemnych prefiksów bilansu
//
// Oryginał w zbiorze codeforces/2241/suffixPrefix_sum/2241D.cc
// https://codeforces.com/contest/2241
//
// Co oblicza kod
//
// Sprawdzić, czy dla każdego prefiksu suma b jest co najmniej sumą a.
//
// Pomysł
//
// Dodawaj b[i]-a[i] do jednego licznika cur i zakończ wynikiem NO przy pierwszym ujemnym bilansie.
//
// Stan i niezmiennik
//
// Po pozycji i cur jest dokładnie sumą b[0..i]-sumą a[0..i]. Po przejściu kontroli wszystkie dotychczasowe prefiksy spełniają nierówność.
//
// Złożoność
//
// O(n) czasu, O(n) pamięci na dwie tablice, O(1) stanu bilansu.
//
// Przypadki brzegowe
//
// Końcowe cur nie musi być zerem. kod dopuszcza nadwyżkę. Pojedynczy ujemny prefiks oznacza NO nawet przy dodatnim bilansie końcowym.
//
// Kiedy rozpoznać ten wariant
//
// Zasób może przechodzić tylko w jedną stronę albo wszystkie początkowe odcinki muszą spełniać nierówność.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve()
{
    int n;
    cin >> n;
    vector<ll> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    

    ll cur = 0;
    for (int i = 0; i < n; i++)
    {
        cur += b[i] - a[i];


        if (cur < 0)
        {
            cout << "NO\n";
            return;
        }

    }

    cout << "YES\n";

}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }

    return 0;
}