// Długości bloków, próg i kongruencja
//
// Oryginał w zbiorze codeforces/2242/suffixPrefix_sum/2242C.cc
// https://codeforces.com/contest/2242
//
// Co oblicza kod
//
// Policzyć różne długości bloku x, dla których k>=mn i (k-mn) mod ile=0, gdzie ile to liczba bloków długości co najmniej x, a mn=sum tych długości-ile*(x-1).
//
// Pomysł
//
// Skompresuj tablicę do długości stałych bloków, posortuj długości, zbuduj sumy sufiksowe i analizuj tylko pierwsze wystąpienie każdego progu x.
//
// Stan i niezmiennik
//
// Na indeksie i pozostałe długości cnt[i..m-1] są dokładnie blokami długości co najmniej x=cnt[i]. suf[i] daje ich sumę bez ponownego przechodzenia po blokach.
//
// Złożoność
//
// O(n+m log m) czasu i O(n+m) pamięci, gdzie m jest liczbą bloków.
//
// Przypadki brzegowe
//
// Każdy próg jest liczony raz mimo duplikatów. ile>=1, więc modulo jest bezpieczne. Nie wolno opisywać wyniku jako liczby wszystkich możliwych podziałów bez potwierdzenia treści zadania.
//
// Kiedy rozpoznać ten wariant
//
// Po kompresji równych sąsiadów warunek zależy tylko od histogramu długości i progów tych długości.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;


void solve()
{
    int n, k; cin >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> cnt;

    for (int i = 0; i < n; )
    {
        int j = i;
        while (j < n && a[j] == a[i]) j++;

        cnt.push_back(j - i);
        i = j;
    }

    sort(cnt.begin(), cnt.end());
    int m = (int)cnt.size();

    vector<long long> suf(m + 1, 0);

    for (int i = m - 1; i >= 0; i--) suf[i] = suf[i + 1] + cnt[i];

    int ans = 0;

    for (int i = 0; i < m; i++)
    {
        if (i > 0 && cnt[i] == cnt[i - 1]) continue;

        int x = cnt[i];

        int ile = m - i;
        long long sum = suf[i];
        long long mn = sum - 1LL * ile * (x - 1);

        if (k >= mn && (k - mn) % ile == 0) ans++;
    }

    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    int t;
    cin>>t;
    while(t--)
    {
        solve();
    }
}