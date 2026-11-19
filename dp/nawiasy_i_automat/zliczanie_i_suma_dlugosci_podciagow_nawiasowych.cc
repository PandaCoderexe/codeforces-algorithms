// Zliczanie i suma długości podciągów nawiasowych z automatem
//
// Oryginał w zbiorze codeforces/2190/dp/2190B2.cc
// https://codeforces.com/contest/2190
//
// Co oblicza kod
//
// Obliczyć modulo 998244353 sumę (długość podciągu-2) po wszystkich podciągach wejściowego napisu nawiasowego, które mają nieujemny bilans każdego prefiksu, bilans końcowy 0 i osiągają stan automatu opt=3. po pierwszym wybranym zamknięciu występują co najmniej dwa późniejsze wybrane otwarcia. Podciągi rozróżnia się przez wybrane indeksy.
//
// Pomysł
//
// Skanować wejście od lewej. Kopia poprzedniej warstwy reprezentuje pominięcie znaku. Wzięcie znaku zmienia bilans i automat oraz dopisuje cnt do sumy długości, ponieważ każda z cnt starych możliwości wydłuża się o 1. Na końcu wziąć wyłącznie bilans 0 i opt3, po czym od sumy długości odjąć dwukrotną liczbę podciągów.
//
// Stan i niezmiennik
//
// dp[balance][opt] jest licznością podciągów po przetworzonym prefiksie, a score[balance][opt] sumą ich długości, oba modulo MOD. opt0 oznacza brak wybranego zamknięcia. pierwsze wybrane zamknięcie zmienia 0->1. Pierwsze późniejsze otwarcie zmienia 1->2, drugie 2->3. stan 3 jest absorbujący. Zamknięcia po stanie 0 oraz otwarcia w stanie 0/3 nie zmieniają opt. Wzięcie znaku przenosi cnt do nowej liczności i sum+cnt do nowego score. zamknięcie przy balance=0 jest zabronione. Końcowe dp[0][3],score[0][3] dotyczą dokładnie podciągów z bilansem końcowym 0 i wzorcem ")((" jako podciągiem wybranego ciągu, bez wymogu sąsiedztwa znaków wzorca.
//
// Złożoność
//
// Czas O(n^2), pamięć O(n). Dla każdej z n pozycji przeglądane są n+1 bilansów i 4 stany automatu. kopiowanie obu pełnych warstw również kosztuje O(n) na pozycję.
//
// Przypadki brzegowe
//
// Pusty podciąg ma count=1 i score=0 w stanie (0,0), lecz nie trafia do wyniku. Podciągi bez zamknięcia albo z tylko jednym późniejszym otwarciem nie osiągają opt3. Bilans nie może stać się ujemny. znak otwierający zwiększa go o 1. Zera modulo w count i score rozpatrywać osobno. Remisy indeksów nie są scalane jako identyczne napisy. różne wybory pozycji są różnymi podciągami.
//
// Kiedy rozpoznać ten wariant
//
// Trzeba zsumować statystykę wszystkich podciągów spełniających jednocześnie warunek stosowy redukowalny do bilansu oraz warunek rozpoznawany małym automatem. Para count/sum pozwala dopisywać lokalny wkład do sumy długości bez przechowywania każdej długości jako stanu.
//
// Warunki i uwagi
//
// - Źródło pozostaje niezmienione. Warunek z patches zastosować wyłącznie w kopii bibliotecznej.
// - Nie wskazano kontrprzykładu w oficjalnych ograniczeniach; zmiana guarda chroni ogólny niezmiennik count+score modulo, nie stanowi twierdzenia o potwierdzonym błędzie na danych zadania.
// - Opis dotyczy literalnej semantyki implementacji. Wzorzec to zamknięcie oraz dwa późniejsze otwarcia jako podciąg, niekoniecznie sąsiadujące znaki ani substring ")((". Suma końcowa wynosi sum(length-2) dla bilansu 0 i opt3.
//
// Zmiany kopii względem oryginału
//
// - Naprawa ogólnego niezmiennika pary agregatów modulo: liczność równa 0 modulo MOD nie oznacza, że suma długości jest 0 modulo MOD. Pominięcie przejścia jest bezpieczne dopiero, gdy oba agregaty są zerowe; pozostałe przejścia są liniowe w count i score.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll mod = 998244353;

void solve()
{
    int n; cin >> n;
    string s; cin >> s;

    vector<vector<ll>> score(n+1, vector<ll>(4, 0)), dp (n+1, vector<ll>(4, 0)); 
    dp[0][0] = 1;
    for (int pref = 0; pref < n; pref++)
    {

        vector<vector<ll>> new_score = score, new_dp = dp;

        for (int count = 0; count <= n; count++)
        {
            for (int opt = 0; opt < 4; opt++)
            {
                if (dp[count][opt] == 0 && score[count][opt] == 0) continue;

                ll cnt = dp[count][opt], sum = score[count][opt];

                if (s[pref] == ')')
                {
                    ll new_count = count-1;
                    if (new_count<0) continue;

                    int new_opt = opt;

                    if (new_opt == 0) new_opt = 1;

                    new_dp[new_count][new_opt] += cnt;
                    new_dp[new_count][new_opt] %= mod;

                    new_score[new_count][new_opt] +=  sum + cnt;
                    new_score[new_count][new_opt] %= mod;
                }
                else 
                {
                    ll new_count = count+1;
                    if (new_count>n) continue;

                    int new_opt = opt;

                    if (new_opt == 1) new_opt = 2;
                    else if (new_opt == 2) new_opt = 3;

                    new_dp[new_count][new_opt] += cnt;
                    new_dp[new_count][new_opt] %= mod;

                    new_score[new_count][new_opt] +=  sum + cnt;
                    new_score[new_count][new_opt] %= mod;
                }
            }

        }

        dp = new_dp;
        score = new_score;
    }

    ll good_count = dp[0][3];
    ll good_len_sum = score[0][3];

    ll ans = good_len_sum - 2 * good_count;
    ans %= mod;
    if (ans < 0) ans += mod;

    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t; cin>> t;
    while(t--) solve();
}