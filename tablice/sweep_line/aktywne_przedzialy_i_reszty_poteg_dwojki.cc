// Sweep line z klasami reszt
//
// Oryginał w zbiorze codeforces/2179/implementation/2179H.cc
// https://codeforces.com/contest/2179
//
// Co oblicza kod
//
// Dla każdej pozycji i sumuje po przedziałach [l,r] zawierających i wartość (i-l+1)*lowbit(i-l+1). lowbit(x) jest największą potęgą dwójki dzielącą x.
//
// Pomysł
//
// Dodawaj przedział w l i usuwaj po obliczeniu r. Dla każdej potęgi dwójki przechowuj liczność i sumę lewych końców według reszt. Użyj lowbit(x)=1+sum_(t=1..v2(x)) 2^(t-1), aby sumować tylko klasy reszt zgodne z i+1.
//
// Stan i niezmiennik
//
// Dla aktywnych l zgodnych z i+1 modulo 2^t suma odległości to count*(i+1)-sumL. Tablice zawierają dokładnie przedziały obejmujące bieżącą pozycję.
//
// Złożoność
//
// O((n+q) log n) czasu i O(n+q) pamięci, ponieważ suma wielkości tablic dla potęg dwójki jest O(n).
//
// Przypadki brzegowe
//
// - Przedziały kończące się w i usuwaj po obliczeniu odpowiedzi.
// - Dla t=0 wszyscy należą do jednej klasy.
// - Liczności i sumy lewych końców aktualizuj tym samym znakiem.
//
// Kiedy rozpoznać ten wariant
//
// Gdy wkład aktywnego przedziału zależy od odległości od początku i podzielności tej odległości przez potęgi dwójki.
//
// KONIEC OPISU
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;

        vector<vector<int>> startAt(n + 2), endAt(n + 2);
        for (int i = 0; i < q; i++) {
            int l, r;
            cin >> l >> r;
            startAt[l].push_back(l);
            endAt[r].push_back(l);  
        }

        // maksymalne t takie, że 2^t <= n
        int tmax = 0;
        while ((1 << tmax) <= n) tmax++;
        tmax--;

        vector<vector<int>> cnt(tmax + 1);
        vector<vector<ll>> sumL(tmax + 1);
        for (int t = 0; t <= tmax; t++) {
            int m = 1 << t;
            cnt[t].assign(m, 0);
            sumL[t].assign(m, 0LL);
        }

        auto upd = [&](int l, int delta) {
            for (int t = 0; t <= tmax; t++) {
                int mask = (1 << t) - 1;     
                int rem = l & mask;         
                cnt[t][rem] += delta;
                sumL[t][rem] += 1LL * delta * l;
            }
        };

        vector<ll> ans(n + 1, 0);

        for (int i = 1; i <= n; i++) {

            for (int l : startAt[i]) upd(l, +1);

            ll x = (ll)i + 1; 

            ll res = 1LL * cnt[0][0] * x - sumL[0][0]; 

            for (int t = 1; t <= tmax; t++) {
                int m = 1 << t;
                int rem = (int)x & (m - 1); // (i+1) % 2^t
                ll term = 1LL * cnt[t][rem] * x - sumL[t][rem]; // suma (i+1 - l) dla tych l
                res += (1LL << (t - 1)) * term;
            }

            ans[i] = res;

            // zdejmij przedziały kończące się w i (po policzeniu i)
            for (int l : endAt[i]) upd(l, -1);
        }

        for (int i = 1; i <= n; i++) {
            if (i > 1) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }

    return 0;
}
