# Maksimum po wykluczeniu elementu
#
# Oryginał w zbiorze codeforces/1760/ds/1760C.py
# https://codeforces.com/contest/1760
#
# Co oblicza kod
#
# Oblicza największy element i maksimum po usunięciu jego pierwszego wystąpienia. dla każdego elementu wypisuje różnicę do maksimum pozostałych.
#
# Pomysł
#
# Obliczyć maksimum i maksimum po usunięciu jednego jego wystąpienia. każdy element porównać do właściwego z tych dwóch ekstremów.
#
# Stan i niezmiennik
#
# Dla elementu mniejszego od maksimum najlepszy przeciwnik to maksimum. dla maksymalnego trzeba uwzględnić drugie maksimum z krotnościami.
#
# Złożoność
#
# O(n) czasu i O(n) dodatkowej pamięci. index i wycinki wykonują skończoną liczbę liniowych operacji, nie występuje pętla wyszukiwań.
#
# Przypadki brzegowe
#
# Domena n≥2. powtórzone maksimum. dwa elementy. wartości ujemne.
#
# Kiedy rozpoznać ten wariant
#
# Wynik dla pozycji zależy od ekstremum wszystkich pozostałych pozycji.
#
# Warunki i uwagi
#
# - Kontrakt: n≥2, aby po wykluczeniu elementu pozostawał co najmniej jeden przeciwnik. Powtórzone maksimum obsługiwane jest z krotnością.
#
# KONIEC OPISU
t = int(input())
for _ in range(t):
    n = int(input())
    s = list(map(int, input().split()))


    max_val = max(s)
    second_big = max(s[:s.index(max_val)] + s[s.index(max_val)+1:])
    result = []
    for num in s:
            if num == max_val:
                result.append(num - second_big)
            else:
                result.append(num - max_val)


    print(*result)