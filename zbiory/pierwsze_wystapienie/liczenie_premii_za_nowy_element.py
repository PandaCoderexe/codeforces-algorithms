# Premia za pierwsze wystąpienie
#
# Oryginał w zbiorze codeforces/1703/ds/1703B.py
# https://codeforces.com/contest/1703
#
# Co oblicza kod
#
# Sumuje 2 za pierwsze wystąpienie znaku i 1 za każde kolejne, czyli długość napisu plus liczbę różnych znaków.
#
# Pomysł
#
# Przejść po znakach, sprawdzać przynależność do zbioru i dopisywać nowy znak po pierwszym wystąpieniu.
#
# Stan i niezmiennik
#
# Zbiór zawiera dokładnie znaki wcześniejszego prefiksu. każdy znak wnosi jedną premię za pierwsze pojawienie.
#
# Złożoność
#
# O(n) oczekiwanego czasu i O(σ) pamięci, σ=liczba różnych znaków. koszt haszowania znaku jest stały.
#
# Przypadki brzegowe
#
# Pusty napis, jeśli dopuszczony. jeden powtarzany znak. wszystkie znaki różne.
#
# Kiedy rozpoznać ten wariant
#
# Wynik zależy od odróżnienia pierwszego wystąpienia od kolejnych, bez potrzeby pełnej liczności.
#
# KONIEC OPISU
t = int(input())  # Wczytujemy liczbę testów
for _ in range(t):
    n = int(input())  # Wczytujemy długość ciągu (nie musimy jej używać, ale jest w danych)
    s = input().strip()  # Wczytujemy ciąg rozwiązywanych problemów
    
    res = 0  # Zmienna do przechowywania liczby balonów
    problems = set()  # Zbiór, aby śledzić rozwiązane problemy
    
    for i in s:
        if i in problems:
            res += 1  # Jeśli problem już rozwiązany, dostajemy 1 balon
        else:
            res += 2  # Jeśli problem rozwiązany po raz pierwszy, dostajemy 2 balony
            problems.add(i)  # Dodajemy problem do zbioru rozwiązanych
    
    print(res)  # Wypisujemy wynik dla bieżącego testu