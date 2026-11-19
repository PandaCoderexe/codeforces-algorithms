# Multizbiory znaków przez sortowanie
#
# Oryginał w zbiorze codeforces/141/sorting/141A.py
# https://codeforces.com/contest/141
#
# Co oblicza kod
#
# Czy litery trzeciego napisu są dokładnie połączeniem liter dwóch pierwszych napisów?
#
# Pomysł
#
# Posortuj znaki połączonych imion i znaki rozsypanki. Równość posortowanych list oznacza równość częstości wszystkich znaków.
#
# Stan i niezmiennik
#
# Każda litera zachowuje swoją liczbę wystąpień podczas sortowania. Kolejność w danych wejściowych przestaje mieć znaczenie.
#
# Złożoność
#
# O(L log L) czasu i O(L) pamięci dla łącznej długości L.
#
# Przypadki brzegowe
#
# - Powtarzające się litery muszą mieć zgodne liczności.
# - Różna łączna długość automatycznie wyklucza równość.
#
# Kiedy rozpoznać ten wariant
#
# Gdy kolejność znaków jest dowolna, lecz liczba kopii każdej litery musi się zgadzać.
#
# KONIEC OPISU
first_name = input()
second_name = input()
mixed_names = input()

combined = list(first_name+second_name)
combined.sort()

sorted_mixed = sorted(list(mixed_names))

if combined == sorted_mixed:
    print("YES")
else:
    print("NO")