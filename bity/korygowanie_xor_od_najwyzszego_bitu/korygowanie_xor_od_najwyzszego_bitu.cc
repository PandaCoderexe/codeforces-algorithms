// Korygowanie bitów XOR przez podwajanie potęg dwójki
//
// Oryginał w zbiorze codeforces/2283/bits/C.cc
// https://codeforces.com/contest/2283
//
// Co oblicza kod
//
// Wybrać oznaczenia podwojenia liczb 1..n według procedury, która zaczyna od podwojenia n, a następnie od najwyższego bitu koryguje zera aktualnego XOR podwojeniem wybranych potęg dwójki.
//
// Pomysł
//
// Wylicz XOR 1..n-1 i połącz z 2n. Dla i od floor(log2 n) do 1, gdy bit i jest zerem, zaznacz x=2^(i-1) i zastąp jego wkład x wkładem 2x przez XOR obu wartości.
//
// Stan i niezmiennik
//
// Podwojenie potęgi dwójki x przełącza wyłącznie dwa sąsiednie bity i-1 oraz i. Przejście od góry do dołu nie zmienia już naprawionych wyższych bitów. Po pętli wszystkie bity 1..floor(log2 n) są ustawione.
//
// Złożoność
//
// O(n+log n) czasu i O(n) pamięci.
//
// Przypadki brzegowe
//
// Wymaga n>=1 dla __builtin_clz i bezpiecznego 2*n. Kod wypisuje flagi podwojenia, nie gotowe wartości. Nie dowodzi optymalności dla niewskazanego celu zadania. opisuje konkretną konstrukcję bitową.
//
// Kiedy rozpoznać ten wariant
//
// Operacja przełącza sąsiednie poziomy bitowe, więc można ustalać docelowe bity od najwyższego do najniższego bez psucia wcześniejszych decyzji.
//
// Warunki i uwagi
//
// - Wymaga n>0 dla clz; wynik to wektor bool, a nie sam zmodyfikowany ciąg. Znaczenie docelowego wzorca XOR wymaga treści zadania.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int n, m = 0; cin >> n;
    for (int i = 1; i < n; i++) m ^= i;


    vector<bool> multiply(n+1);
    multiply[n] = 1;
    int actual_xor = m ^ (n*2), h = 31 - __builtin_clz(n);
    for (int i = h; i >= 1; i--)
    {
        if (actual_xor & (1 << i)) continue;
        int x = 1 << (i-1);
        multiply[x] = 1;
        actual_xor ^= x;
        actual_xor ^= (2*x);
    }

    for (int i = 1; i <=n; i++) cout << multiply[i] << " ";
    cout << "\n";
    
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();
}