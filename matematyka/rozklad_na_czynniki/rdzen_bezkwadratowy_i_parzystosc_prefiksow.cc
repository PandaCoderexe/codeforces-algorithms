// Rdzeń bezkwadratowy i prefiksy
//
// Oryginał w zbiorze codeforces/2275/math/2275F.cc
// https://codeforces.com/contest/2275
//
// Co oblicza kod
//
// Dla każdego niepustego prefiksu liczy elementy całej tablicy, których iloczyn z iloczynem prefiksu jest kwadratem. Sumuje te liczby.
//
// Pomysł
//
// Sito SPF rozkłada liczby. Zostaw tylko pierwsze o nieparzystych wykładnikach. Dla prefiksu przełączaj obecność każdego takiego pierwszego i porównuj otrzymany rdzeń z histogramem elementów.
//
// Stan i niezmiennik
//
// active[p] jest parzystością wykładnika p w iloczynie bieżącego prefiksu. Dwa identyczne rdzenie pomnożone dają kwadrat.
//
// Złożoność
//
// Sito O(M log log M) czasu i O(M) pamięci, M=10^6. Przypadek O(n log M), bo rdzenie rozkładają się na czynniki, a obliczenie małego rdzenia używa najwyżej siedmiu aktywnych pierwszych.
//
// Przypadki brzegowe
//
// - Kwadraty mają rdzeń jeden.
// - Gdy rdzeń prefiksu przekracza M, żadna wartość z histogramu nie pasuje.
// - Po przypadku trzeba wyczyścić cnt i aktywne pierwsze.
//
// Kiedy rozpoznać ten wariant
//
// Gdy o kwadratowości iloczynu decyduje parzystość wykładników pierwszych, a iloczyn sam nie mieści się w typie.
//
// KONIEC OPISU
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAXA = 1e6;
vector<int> spf(MAXA + 1), cnt(MAXA+1,0), active(MAXA+1,0), pos(MAXA+1,-1);

void sieve()
{
    for(int i = 0; i <= MAXA; i++) spf[i] = i;

    for(int i = 2; 1LL * i * i <= MAXA; i++)
    {
        if(spf[i] == i)
        {
            for(int j = i * i; j <= MAXA; j += i)
            {
                if(spf[j] == j) spf[j] = i;
            }
        }
    }
}

int left(int num)
{
    int res = 1;
    while(num > 1)
    {
        int s_ = spf[num], cnt = 0;
        while(num % s_ == 0)
        {
            num /= s_;
            cnt++;
        }

        if(cnt % 2) res *= s_;
    }

    return res;
}

void solve()
{
    int n; cin >> n;
    vector<int> a(n), left_(n), primes, used;
    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
        left_[i] = left(a[i]);

        if(cnt[left_[i]] == 0) used.push_back(left_[i]);
        cnt[left_[i]]++;
    }

    ll ans = 0;
    for(int i = 0; i < n; i++)
    {
        int x = left_[i];

        while(x > 1)
        {
            int p = spf[x];
            if(active[p])
            {
                int id = pos[p], last = primes.back();
                primes[id] = last;
                pos[last] = id;
                primes.pop_back();
                pos[p] = -1;
                active[p] = 0;
            }
            else
            {
                pos[p] = primes.size();
                primes.push_back(p);
                active[p] = 1;
            }

            x /= p;
        }

        if(primes.size() <= 7)
        {
            ll kernel = 1;
            for(int p : primes)
            {
                if(kernel > MAXA / p)
                {
                    kernel = MAXA + 1;
                    break;
                }
                kernel *= p;
            }

            if(kernel <= MAXA) ans += cnt[kernel];
        }
    }

    cout << ans << "\n";

    for(int x : used) cnt[x] = 0;

    for(int p : primes)
    {
        active[p] = 0;
        pos[p] = -1;
    }
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    sieve();
    int t; cin >> t;
    while(t--) solve();
}