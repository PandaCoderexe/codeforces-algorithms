// Digit DP najbliższej liczby z relacją mniejsza/równa/większa
//
// Oryginał w zbiorze codeforces/2228/dp/2228C2.cc
// https://codeforces.com/problemset/problem/2228/C2
//
// Co oblicza kod
//
// Dla nieujemnego a<=10^17 i niepustego zbioru dozwolonych cyfr znaleźć najmniejszą odległość |a-b| po nieujemnych b zapisanych wyłącznie dozwolonymi cyframi, bez zer wiodących poza liczbą zero.
//
// Pomysł
//
// Dla tej samej liczby cyfr uruchomić top-down DP (pos,relation). Jeśli prefiks jest już mniejszy, maksymalizować sufiks. jeśli większy, minimalizować sufiks. przy równości porównać odległości do docelowego sufiksu. Dodatkowo porównać zero, największą liczbę krótszą o jedną cyfrę i najmniejszą dłuższą o jedną cyfrę, z ochroną zakresu przy 18 cyfrach.
//
// Stan i niezmiennik
//
// recursion(pos,0) zwraca największy dozwolony sufiks, gdy wybrany prefiks jest już mniejszy od a. relation=2 zwraca najmniejszy, relation=1 najbliższy docelowemu suff[pos]. Pierwsza nierówna cyfra ustala relację na stałe. Przy relation=1 odległość sufiksów jest równa pełnej odległości, bo dotychczasowe prefiksy są równe. Przy zmianie relacji ekstremalny sufiks jest optymalny z powodu ustalonej strony nierówności. Tablice dp[pos][relation] oraz seen mają dwa wymiary. relation ma trzy wartości, odpowiadające prefiksowi mniejszemu, równemu lub większemu od prefiksu a.
//
// Złożoność
//
// Dla D cyfr a i K dozwolonych cyfr. czas O(D*K), pamięć O(D+K), stos O(D). Są tylko 3*(D+1) stanów, każdy przegląda K cyfr. konstrukcje sąsiednich długości także kosztują O(D+K).
//
// Przypadki brzegowe
//
// Zbiór {0}. jedna dozwolona cyfra. a już zapisane dozwolonymi cyframi. brak niezerowej cyfry. zero na pierwszej pozycji jest zabronione tylko dla długości>1. Przy remisach implementacja zachowuje pierwszy rozpatrzony sufiks, ale wypisuje wyłącznie odległość. Dla a o 18 cyfrach nie budować liczby 19-cyfrowej. a<=10^17, a każdy taki kandydat jest >=10^18 i gorszy od bezpiecznej krótszej liczby albo zera.
//
// Kiedy rozpoznać ten wariant
//
// Optymalizujemy odległość od liczby, a dozwolone cyfry narzucają ograniczenie leksykograficzne. Gdy prefiks odejdzie od celu, pozostaje wyłącznie skrajny sufiks. równość wymaga dalszej rekurencji i porównania obu stron.
//
// Warunki i uwagi
//
// - Oryginał ma bezwarunkowy signed overflow w power10[19] i możliwe przepełnienie przy budowie 19-cyfrowej liczby. Źródła nie zmieniać; oba patches są obowiązkowe wyłącznie w kopii przeznaczonej do biblioteki.
// - Gwarancje bezpieczeństwa oraz pominięcia długości 19 opierają się na a<=10^17. Po rozszerzeniu zakresu trzeba przeprojektować typy i wartowniki, nie usuwać mechanicznie warunku len<18.
// - Dla tego zakresu każdy budowany kandydat ma najwyżej 18 cyfr, czyli jest <10^18<inf/2; filtr wartownika nie odrzuca zatem żadnego bezpiecznego kandydata.
//
// Zmiany kopii względem oryginału
//
// - Największa potrzebna potęga to 10^18; obliczenie 10^19 bezwarunkowo przepełnia signed long long, także dla małego wejścia.
// - Nie budować 19-cyfrowego kandydata, który może przepełnić long long. Dla a<=10^17 jest on >=10^18, więc nie pobije bezpiecznej krótszej liczby z dozwolonych cyfr, a przy samym zerze kandydatem jest zero.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll inf = (1LL << 62);

struct Solve
{
    int n;
    ll a;
    string s;
    vector<int> nums;
    vector<ll> suff;
    vector<vector<ll>> dp;
    vector<vector<bool>> seen;
    ll power10[20];
    Solve(ll a_, int n_, const vector<int>& nums_)
    {
        n = n_;
        a = a_;
        s = to_string(a);
        nums = nums_;
        dp.assign((int)s.size()+1, vector<ll>(3, 0));
        seen.assign((int)s.size()+1, vector<bool>(3, 0));
        power10[0] = 1;
        for (int i = 1; i < 19; i++) 
        {
            power10[i] = power10[i-1] * 10; 
        }
        suff.assign((int)s.size() + 1, 0);
        for (int i = (int)s.size()-1; i >= 0; i--)
        {
            int num = s[i]-'0';
            ll cur = num * power10[(int)s.size() - i - 1];
            suff[i] = suff[i+1] + cur;
        }
    }

    ll recursion(int pos, int relation)
    {
        if (pos == (int)s.size()) return 0;
        if (seen[pos][relation]) return dp[pos][relation];

        ll p = power10[(int)s.size() - pos - 1];
        ll ans;

        if (relation == 0) ans = -inf;
        else if (relation == 1) ans = -1;
        else ans = inf;

        ll target_suff = suff[pos];
        int cur = s[pos] - '0';

        for (int num : nums)
        {
            if (pos == 0 && s.size() > 1 && num == 0) continue;

            int new_rel = relation;

            if (relation == 1)
            {
                if (num > cur) new_rel = 2;
                else if (num < cur) new_rel = 0;
                else new_rel = 1;
            }

            ll child = recursion(pos + 1, new_rel);
            
            if (child <= -inf / 2 || child >= inf / 2)
            {
                continue;
            }

            ll cand = num * p + child;

            if (relation == 0) ans = max(ans, cand);
            else if (relation == 2) ans = min(ans, cand);
            else
            {
                if (ans == -1 || llabs(target_suff - cand) < llabs(target_suff - ans))
                {
                    ans = cand;
                }
            }
        }

        dp[pos][relation] = ans;
        seen[pos][relation] = true;

        return dp[pos][relation];
    }

    bool buildMaxNumberWithLength(int len, ll& result)
    {
        if (len <= 0)
        {
            return false;
        }

        int max_digit = -1;
        int max_non_zero = -1;

        for (int digit : nums)
        {
            max_digit = max(max_digit, digit);

            if (digit != 0)
            {
                max_non_zero = max(max_non_zero, digit);
            }
        }

        if (len == 1)
        {
            result = max_digit;
            return true;
        }

        if (max_non_zero == -1)
        {
            return false;
        }

        result = max_non_zero;

        for (int i = 1; i < len; i++)
        {
            result = result * 10 + max_digit;
        }

        return true;
    }

    bool buildMinNumberWithLength(int len, ll& result)
    {
        if (len <= 0)
        {
            return false;
        }

        int min_digit = 10;
        int min_non_zero = 10;

        for (int digit : nums)
        {
            min_digit = min(min_digit, digit);

            if (digit != 0)
            {
                min_non_zero = min(min_non_zero, digit);
            }
        }

        if (len == 1)
        {
            result = min_digit;
            return true;
        }

        if (min_non_zero == 10)
        {
            return false;
        }

        result = min_non_zero;

        for (int i = 1; i < len; i++)
        {
            result = result * 10 + min_digit;
        }

        return true;
    }

    void relax(ll candidate, ll& answer)
    {
        if (candidate < 0)
        {
            return;
        }

        if (candidate <= -inf / 2 || candidate >= inf / 2)
        {
            return;
        }

        answer = min(answer, llabs(a - candidate));
    }

    ll getAnswer()
    {
        int len = (int)s.size();

        ll answer = inf;

        bool has_zero = false;

        for (int digit : nums)
        {
            if (digit == 0)
            {
                has_zero = true;
            }
        }

        if (has_zero)
        {
            relax(0, answer);
        }

        ll same_length_candidate = recursion(0, 1);
        relax(same_length_candidate, answer);

        ll shorter_candidate;

        if (buildMaxNumberWithLength(len - 1, shorter_candidate))
        {
            relax(shorter_candidate, answer);
        }

        ll longer_candidate;

        if (len < 18 && buildMinNumberWithLength(len + 1, longer_candidate))
        {
            relax(longer_candidate, answer);
        }

        return answer;
    }
};

void solve()
{
    int n;
    ll a;
    cin >> a >> n;

    vector<int> digits(n);
    for (int i = 0; i < n; i++) cin >> digits[i];

    Solve solver(a, n, digits);
    cout << solver.getAnswer() << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    int t;
    cin >> t;
    while(t--) solve();
    return 0;
}