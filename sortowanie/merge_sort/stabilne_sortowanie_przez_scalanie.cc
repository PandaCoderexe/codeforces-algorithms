// Stabilny merge sort
//
// Oryginał w zbiorze codeforces/648/sorting/648B.cc
// https://codeforces.com/contest/648
// Samodzielny fragment szablonu. Brak funkcji main jest zamierzony.
//
// Co oblicza kod
//
// Sortuje tablicę przez rekurencyjny podział na połowy i stabilne scalanie.
//
// Pomysł
//
// Posortuj obie połowy, następnie scal je dwoma wskaźnikami do bufora. Przy równości wybieraj element z lewej połowy, aby zachować stabilność.
//
// Stan i niezmiennik
//
// Przed scalaniem obie połowy są posortowane. Bufor zawiera najmniejsze dotychczas wybrane elementy obu połówek w porządku niemalejącym.
//
// Złożoność
//
// O(n log n) czasu, O(n) pamięci na bufor i O(log n) stosu rekurencji.
//
// Przypadki brzegowe
//
// - Pusta tablica wymaga wywołania merge(a,0,-1), które od razu wraca.
// - Duplikaty zachowują kolejność między lewą i prawą połową.
// - Zakres sortowania jest domknięty.
//
// Kiedy rozpoznać ten wariant
//
// Klasyczne dziel i zwyciężaj, gdy można rozwiązać połowy i połączyć je w czasie liniowym.
//
// KONIEC OPISU
#include <iostream>
#include <vector>
using namespace std;

template<typename T>
void merge_sections(vector<T>& arr, int start_idx, int middle_idx, int end_idx) {
    vector<T> merged;
    int left_idx = start_idx;
    int right_idx = middle_idx;

    while (left_idx < middle_idx && right_idx <= end_idx) {
        if (arr[left_idx] <= arr[right_idx]) {
            merged.push_back(arr[left_idx]);
            ++left_idx;
        } else {
            merged.push_back(arr[right_idx]);
            ++right_idx;
        }
    }

    while (left_idx < middle_idx) {
        merged.push_back(arr[left_idx]);
        ++left_idx;
    }

    while (right_idx <= end_idx) {
        merged.push_back(arr[right_idx]);
        ++right_idx;
    }

    for (int i = 0; i < merged.size(); ++i) {
        arr[start_idx + i] = merged[i];
    }
}

template<typename T>
void merge(vector<T>& arr, int start_idx, int end_idx) {
    if (start_idx >= end_idx) return;

    int middle_idx = start_idx + (end_idx - start_idx + 1) / 2;

    merge(arr, start_idx, middle_idx - 1);
    merge(arr, middle_idx, end_idx);
    merge_sections(arr, start_idx, middle_idx, end_idx);
}
