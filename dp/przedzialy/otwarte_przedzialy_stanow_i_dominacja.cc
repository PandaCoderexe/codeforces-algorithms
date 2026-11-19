// DP z przedziałami i dominacją
//
// Oryginał w zbiorze codeforces/2180/math/2180D.cc
// https://codeforces.com/contest/2180
//
// Co oblicza kod
//
// Dla kolejnych odległości d między punktami wybiera dodatnie wartości r_i, spełniające r_(i-1)+r_i<=d, i maksymalizuje liczbę wybranych równości.
//
// Pomysł
//
// Stan ma licznik cnt i otwarty przedział (L,U) osiągalnych wartości ostatniego r. Każda odległość generuje przejście bez nowej równości i z równością. Łącz zachodzące przedziały z równym cnt, potem usuń stany zdominowane.
//
// Stan i niezmiennik
//
// Stan A dominuje B, gdy ma co najmniej tyle równości i zawiera cały jego przedział. Daje wtedy wszystkie możliwości B z niegorszym wynikiem.
//
// Złożoność
//
// O(sum_i (s_i log s_i+s_i^2)) czasu dla liczby s_i stanów na kolejnych etapach i O(max s_i) pamięci. Kod nie uzasadnia liniowego ograniczenia liczby stanów.
//
// Przypadki brzegowe
//
// - Przedziały są otwarte, więc łączenie wymaga L<curU.
// - Promienie są dodatnie.
// - Punkty muszą być podane w rosnącej kolejności.
//
// Kiedy rozpoznać ten wariant
//
// Gdy ciągła wartość stanu jest zbiorem przedziałów, a koszt można porządkować relacją dominacji.
//
// Warunki i uwagi
//
// - Liczba zachowanych stanów i koszt porównań dominacji zależą od danych. Brak dowodu ograniczenia stanów.
//
// KONIEC OPISU
#include <bits/stdc++.h>
using namespace std;

struct State {
    int cnt;
    long long L, U; // open interval (L, U)
};

static bool dominates(const State& a, const State& b) {
    return a.cnt >= b.cnt && a.L <= b.L && a.U >= b.U;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    const long long INF = (long long)4e18;

    while (T--) {
        int n;
        cin >> n;

        long long prevX;
        cin >> prevX;

        vector<State> states;
        states.push_back({0, 0LL, INF}); 

        for (int i = 2; i <= n; i++) 
        {
            long long x;
            cin >> x;
            long long d = x - prevX;
            prevX = x;

            vector<State> cand;
            cand.reserve(states.size() * 2);

            for (auto st : states) {

                if (st.L < d) 
                {
                    cand.push_back({st.cnt, 0LL, d - st.L});
                }


                long long Ut = min(st.U, d);

                if (st.L < Ut) 
                {
                    cand.push_back({st.cnt + 1, d - Ut, d - st.L});
                }
            }

            sort(cand.begin(), cand.end(), [](const State& a, const State& b) 
            {
                if (a.cnt != b.cnt) return a.cnt < b.cnt;
                if (a.L != b.L) return a.L < b.L;
                return a.U < b.U;
            });

            vector<State> merged;
            for (int idx = 0; idx < (int)cand.size(); ) 
            {

                int c = cand[idx].cnt;

                long long curL = cand[idx].L;
                long long curU = cand[idx].U;

                idx++;

                
                while (idx < (int)cand.size() && cand[idx].cnt == c) 
                {
                    long long L = cand[idx].L, U = cand[idx].U;
                    if (L < curU) 
                    {
                        curU = max(curU, U);
                    } 
                    else 
                    {
                        if (curL < curU) merged.push_back({c, curL, curU});
                        curL = L; curU = U;
                    }

                    idx++;
                }

                if (curL < curU) merged.push_back({c, curL, curU});

            }

            sort(merged.begin(), merged.end(), [](const State& a, const State& b) {
                if (a.cnt != b.cnt) return a.cnt > b.cnt; // higher cnt first
                if (a.L != b.L) return a.L < b.L;         // smaller L first
                return a.U > b.U;                          // larger U first
            });

            vector<State> pruned;
            for (auto st : merged) {
                bool dom = false;
                for (auto &kept : pruned) {
                    if (dominates(kept, st)) { dom = true; break; }
                }
                if (!dom) pruned.push_back(st);
            }

            states.swap(pruned);

        }

        int ans = 0;
        for (auto st : states) ans = max(ans, st.cnt);
        cout << ans << "\n";
    }

    return 0;
}
