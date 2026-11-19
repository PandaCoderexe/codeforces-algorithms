// Zakazane przedziały przez tablicę różnicową
//
// Oryginał w zbiorze codeforces/2259/string/2259E.cc
// https://codeforces.com/contest/2259
//
// Co oblicza kod
//
// Zbudować binarny napis, w którym dla każdego znanego b[i]=len najbliższa jedynka jest dokładnie w odległości len, albo zwrócić -1.
//
// Pomysł
//
// Zakazuj jedynek w odległości mniejszej niż len za pomocą dodania do przedziału [i-len+1,i+len-1]. Ustaw 1 wszędzie, gdzie nie ma zakazu, a następnie sprawdź kandydatów i-len oraz i+len.
//
// Stan i niezmiennik
//
// Po prefiksowaniu diff pozycja ma 1 wtedy i tylko wtedy, gdy nie łamie żadnego zakazu. Ustawienie wszystkich dozwolonych jedynek maksymalizuje szansę spełnienia każdej dodatniej potrzeby, więc końcowa walidacja jest rozstrzygająca.
//
// Złożoność
//
// O(n) czasu i O(n) pamięci.
//
// Przypadki brzegowe
//
// -1 oznacza brak warunku. Dla len=0 przedział zakazu jest pusty, a jedynka musi być w i. Wymaga len>=0 dla wszystkich znanych wartości i indeksów mieszczących się w int.
//
// Kiedy rozpoznać ten wariant
//
// Ograniczenia zabraniają wystąpień wewnątrz przedziałów i wymagają choć jednego wystąpienia na ich brzegu. połącz pokrycie różnicowe z weryfikacją.
//
// KONIEC OPISU
#include <bits/stdc++.h>
using namespace std;


void solve()
{
    int n; cin >> n;
    vector<int> b(n);
    vector<pair<int,int>> pairs;
    for (int i = 0; i < n; i++)
    {
        cin >> b[i];
        if (b[i] != -1) pairs.push_back({i, b[i]});
    }

    vector<int> diff(n + 1);
    for (auto [i, len] : pairs)
    {
        int l = max(0, i - len + 1), r = min(i + len - 1, n - 1);
        if (l <= r)
        {
            diff[l]++;
            diff[r + 1]--;
        }
    }

    for (int i = 1; i < n; i++) diff[i] += diff[i-1];
    
    string ans(n, '0');
    for (int i = 0; i < n; i++)
    {
        if (diff[i] == 0) ans[i] = '1';
    }

    for (auto [i, len] : pairs)
    {
        bool ok = false;

        int l = i - len, r = i + len;
        if (l >= 0 && ans[l] == '1') ok = true;
        if (r < n && ans[r] == '1') ok = true;

        if (!ok)
        {
            cout << -1 << "\n";
            return;
        }
    }

    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();
}