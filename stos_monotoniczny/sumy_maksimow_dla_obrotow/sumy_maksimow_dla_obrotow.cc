// Stos monotoniczny i sumy maksimów dla wszystkich obrotów
//
// Oryginał w zbiorze codeforces/2234/suffixPrefix_sum/2234F.cc
// https://codeforces.com/contest/2234
//
// Co oblicza kod
//
// Dla każdego obrotu cyklicznej tablicy h obliczyć sumę min(max(h[0..k]),max(h[k+1..n-1])) po n-1 cięciach.
//
// Pomysł
//
// Wstaw globalne maksimum w środek rozwiniętego cyklu długości 2n-1. Po obu stronach stosem znajdź najbliższy większy element i skokowo zsumuj maksima na drodze do środka. Dla okna obrotu dodaj odpowiednie left i right.
//
// Stan i niezmiennik
//
// Stos przechowuje kandydatów o ściśle malejących wysokościach. left[i]=(j-i)*v[i]+left[j] grupuje odcinek, na którym maksimum od strony i wynosi v[i]. analogicznie działa prawa strona. Każde okno długości n zawiera środkowe maksimum.
//
// Złożoność
//
// O(n) czasu i O(n) pamięci. każdy indeks wchodzi i wychodzi ze stosu najwyżej raz.
//
// Przypadki brzegowe
//
// n=1 daje 0. Równe maksima są zdejmowane przez <= i prawidłowo łączone ze środkowym maksimum. Sumy iloczynów długości i wysokości muszą mieścić się w long long.
//
// Kiedy rozpoznać ten wariant
//
// Wiele obrotów ma wspólne maksimum. suma maksimów fragmentów daje się grupować przez najbliższy większy element.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve()
{
    int n; cin >> n;
    vector<ll> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];

    int global_max = max_element(h.begin(), h.end()) - h.begin();

    int p = n-1;
    int len = 2*n-1;

    vector<ll> v(len);

    for (int i = 0; i < len; i++)
    {
        int pos = (global_max - (n-1) + i) % n; 
        if (pos < 0) pos += n;
        v[i] = h[pos];
    }

    vector<ll> left(len), right(len);
    vector<int> st;
    st.push_back(p);
    for (int i = p-1; i >= 0; i--)
    {
        while(!st.empty() && v[st.back()] <= v[i]) st.pop_back();
        int j = st.empty() ? p : st.back();
        left[i] = 1LL * (j-i)*v[i] +left[j];
        st.push_back(i);
    }

    st.clear();
    st.push_back(p);
    for (int i = p+1; i < len; i++)
    {
        while(!st.empty() && v[st.back()] <= v[i]) st.pop_back();
        int j = st.empty() ? p : st.back();
        right[i] = 1LL * (i-j)*v[i] +right[j];
        st.push_back(i);
    }

    vector<ll> ans(n);
    for (int i = 0; i < n; i++)
    {
        int j = i + n-1;
        int start = (global_max - (n-1)+ i) % n;
        if (start < 0) start+= n;
        ans[start] = left[i] + right[j];
    }
    for (ll x:ans) cout << x << " ";
    cout << "\n";
    

}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) solve();
}