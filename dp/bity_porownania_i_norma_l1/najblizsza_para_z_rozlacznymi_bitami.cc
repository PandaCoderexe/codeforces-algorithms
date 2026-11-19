// Bitowe DP relacji porządku i odległości L1
//
// Oryginał w zbiorze codeforces/2187/dp/2187B.cc
// https://codeforces.com/contest/2187
//
// Co oblicza kod
//
// Znaleźć nieujemne p,q<2^31 z p&q=0 minimalizujące |x-p|+|y-q|.
//
// Pomysł
//
// Rozważyć cztery kombinacje p<=x/p>=x i q<=y/q>=y. W każdej odległość jest liniowa w p,q, więc można minimalizować sumę ważonych bitów i pamiętać porównania prefiksów.
//
// Stan i niezmiennik
//
// Stan (cmp_p,cmp_q) przechowuje minimalny koszt liniowy oraz p,q dla ustalonej pary ćwiartek. Bity (1,1) zabronione. relacja zmienia się tylko gdy prefiksy były równe. Na końcu odrzucić stan poza ćwiartką.
//
// Złożoność
//
// Dla B=31 czas O(4*B*9*4)=O(B), pamięć O(9)=O(1).
//
// Przypadki brzegowe
//
// 0<=x,y<2^31 to naturalna dziedzina. kod ogranicza również wyjście do 31 bitów. Remisy rozstrzygane kolejnością przejść, bez obietnicy leksykograficzności.
//
// Kiedy rozpoznać ten wariant
//
// Wartość bezwzględna blokuje addytywność. po rozbiciu na strony ograniczeń pozostaje bitowy koszt liniowy i mały stan porównania.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct Node
{
    ll ans = (1LL<<60);
    ll p = 0;
    ll q = 0;
    bool flag = false;
};

void solve()
{
    ll x, y;
    cin >> x >> y;
    ll best = (1LL << 60);
    ll ans_p = 0, ans_q = 0;

    for (int type_p = 0; type_p < 2; type_p++)
    {
        for (int type_q = 0; type_q < 2; type_q++)
        {
            vector<vector<Node>> dp(3, vector<Node>(3, Node()));
            dp[1][1].flag = true;
            dp[1][1].ans = 0;
            dp[1][1].p = 0;
            dp[1][1].q = 0;

            for (int bit = 30; bit >= 0; bit--)
            {
                ll value = (1LL << bit);
                int xb = (x >> bit) & 1;
                int yb = (y >> bit) & 1;
                vector<vector<Node>> ndp(3, vector<Node>(3, Node()));
                int coef_p = (type_p == 0 ? -1 : 1);
                int coef_q = (type_q == 0 ? -1 : 1);
        
                for (int cp = -1; cp < 2; cp++)
                {
                    for (int cq = -1; cq < 2; cq++)
                    {
                        Node cur = dp[cp+1][cq+1];
                        if (!cur.flag) continue;
        
                        for (int bp = 0; bp <= 1; bp++)
                        {
                            for (int bq = 0; bq <= 1; bq++)
                            {
                                if (bp == 1 && bq == 1) continue;
                
                                int new_cp = cp;
                                int new_cq = cq;
                                if (cp == 0)
                                {
                                    if (bp > xb) new_cp = 1; 
                                    if (bp < xb) new_cp = -1;
                                }
                                if (cq == 0)
                                {
                                    if (bq > yb) new_cq = 1;
                                    if (bq < yb) new_cq = -1;
                                }
        
                                ll np = cur.p + bp * value, nq = cur.q + bq * value;
                                ll ncost = cur.ans + coef_p * bp * value + coef_q * bq * value;
        
                                Node &to = ndp[new_cp+1][new_cq+1];
                                if (!to.flag || ncost < to.ans)
                                {
                                    to.flag = true;
                                    to.ans = ncost;
                                    to.p = np;
                                    to.q = nq;
                                }
        
                            }
                        }
                    }
                }
                dp = ndp;
            
            }

            for (int cp = -1; cp < 2; cp++)
            {
                for (int cq = -1; cq < 2; cq++)
                {
                    Node cur = dp[cp+1][cq+1];

                    if (!cur.flag) continue;

                    if (type_p == 0 && cp == 1) continue; 
                    if (type_p == 1 && cp == -1) continue;

                    if (type_q == 0 && cq == 1) continue;
                    if (type_q == 1 && cq == -1) continue;

                    ll score = abs(x - cur.p) + abs(y - cur.q);

                    if (score < best)
                    {
                        best = score;
                        ans_p = cur.p;
                        ans_q = cur.q;
                    }
                }
            }
        }

    }

    cout << ans_p << " " << ans_q << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) solve();
}