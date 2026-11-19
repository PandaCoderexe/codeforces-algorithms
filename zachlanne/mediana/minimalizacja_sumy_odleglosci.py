# Mediana minimalizuje sumę odległości
#
# Oryginał w zbiorze codeforces/723/sorting/723A.py
# https://codeforces.com/contest/723
#
# Co oblicza kod
#
# Znajduje minimalną sumę odległości trzech punktów na osi do wspólnego miejsca spotkania.
#
# Pomysł
#
# Posortuj trzy współrzędne. Mediana minimalizuje sumę odległości bezwzględnych, więc dodaj odległości skrajnych punktów do środkowego.
#
# Stan i niezmiennik
#
# Przesunięcie miejsca spotkania na lewo od mediany zwiększa łączną odległość po prawej bardziej, niż zmniejsza po lewej. Symetrycznie dla prawej strony.
#
# Złożoność
#
# O(1) czasu i pamięci dla trzech punktów.
#
# Przypadki brzegowe
#
# - Powtarzające się współrzędne są dozwolone.
# - Wynik jest równy różnicy maksimum i minimum.
#
# Kiedy rozpoznać ten wariant
#
# Gdy minimalizujesz sumę bezwzględnych odległości na prostej.
#
# KONIEC OPISU
positions = list(map(int, input().split()))
positions.sort()

sum = abs(positions[1]-positions[0]) + abs(positions[1]-positions[2]) 

print(sum)