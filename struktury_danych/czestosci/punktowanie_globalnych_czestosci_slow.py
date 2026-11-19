# Globalne częstości słów
#
# Oryginał w zbiorze codeforces/1722/ds/1722C.py
# https://codeforces.com/contest/1722
#
# Co oblicza kod
#
# Dla trzech list słów liczy globalne wystąpienia i przyznaje każdej pozycji 3 punkty za częstość 1, 1 za częstość 2, w pozostałych przypadkach 0.
#
# Pomysł
#
# Najpierw zliczyć wszystkie wystąpienia w słowniku, potem drugi raz przejść trzy listy i przyznawać punkty według globalnej częstości.
#
# Stan i niezmiennik
#
# Słownik po pierwszym przebiegu zawiera pełne częstości, więc drugi przebieg nie zależy od kolejności osób ani słów.
#
# Złożoność
#
# O(L) oczekiwanego czasu, L=łączna długość słów. O(L+n) pamięci na listy i klucze. Pesymistyczne kolizje słownika mogą zwiększyć czas.
#
# Przypadki brzegowe
#
# Jedno słowo we wszystkich listach. słowo w dwóch listach. wyłączne słowa. brak powtórzeń wewnątrz listy, jeśli punktować osoby.
#
# Kiedy rozpoznać ten wariant
#
# Ocena elementu wymaga globalnej liczności znanej dopiero po wczytaniu wszystkich grup.
#
# Warunki i uwagi
#
# - Jeśli zadanie dotyczy liczby osób mających słowo, wymagany brak duplikatów wewnątrz każdej listy.
#
# KONIEC OPISU
t = int(input())
for _ in range(t):
    n = int(input())
    lines = [input().split() for _ in range(3)]  

    hashMap = {}


    for i in range(3):
        for word in lines[i]:
            hashMap[word] = 1 + hashMap.get(word, 0)

    res = [0,0,0]

    for i in range(3):
        for word in lines[i]:
            if hashMap[word] == 1:
                res[i] += 3
            elif hashMap[word] == 2:
                res[i] += 1

    print(*res)
