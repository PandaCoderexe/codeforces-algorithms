# Pierwszy dzień przekroczenia sumy cyklicznej
#
# Oryginał w zbiorze codeforces/2051/binary_search/2051B.py
# https://codeforces.com/contest/2051
#
# Co oblicza kod
#
# Znaleźć najmniejszy dzień d z sumą cyklicznych przyrostów a,b,c co najmniej n.
#
# Pomysł
#
# Policz pełne cykle d//3 oraz najwyżej dwa składniki reszty, a potem szukaj pierwszego prawdziwego predykatu total_distance(d)>=n.
#
# Stan i niezmiennik
#
# Dla nieujemnych przyrostów suma nie maleje. ans przechowuje znany dzień spełniający warunek, a wyszukiwanie usuwa wyłącznie dni, które nie mogą być pierwszym rozwiązaniem.
#
# Złożoność
#
# O(log 10^9) czasu na test i O(1) dodatkowej pamięci.
#
# Przypadki brzegowe
#
# Dolna granica wynosi 1. n<=0 nie zwróci dnia 0. Wymaga osiągalności progu najpóźniej w 10^9 dni. bez tego zwraca 10^9 mimo braku rozwiązania. Ujemne przyrosty łamią monotoniczność.
#
# Kiedy rozpoznać ten wariant
#
# Narastająca wielkość ma cykliczny wzór i da się ją policzyć w O(1), a odpowiedzią jest najwcześniejszy moment osiągnięcia progu.
#
# KONIEC OPISU
def total_distance(day, a, b, c):
    full_cycles = day // 3
    remainder = day % 3
    total = full_cycles * (a + b + c)
    if remainder >= 1:
        total += a
    if remainder == 2:
        total += b
    return total

def find_min_day(n, a, b, c):
    lo, hi = 1, 10**9
    ans = hi
    while lo <= hi:
        mid = (lo + hi) // 2
        if total_distance(mid, a, b, c) >= n:
            ans = mid
            hi = mid - 1
        else:
            lo = mid + 1
    return ans

t = int(input())
for _ in range(t):
    n, a, b, c = map(int, input().split())
    print(find_min_day(n, a, b, c))