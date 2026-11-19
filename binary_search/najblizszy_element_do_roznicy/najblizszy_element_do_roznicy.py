# Najbliższy element do różnicy pary
#
# Oryginał w zbiorze codeforces/1904/two_pointers/1904C.py
# https://codeforces.com/contest/1904
#
# Co oblicza kod
#
# Obliczyć minimum dostępnego elementu po jednej lub dwóch operacjach dopisania bezwzględnej różnicy dwóch liczb. dla k>=3 kod zwraca zero.
#
# Pomysł
#
# Sortowanie daje minimalną różnicę po jednym ruchu wśród sąsiadów. Dla k=2 każdą różnicę a[i]-a[j] porównaj z elementem na pozycji lower_bound i jego poprzednikiem.
#
# Stan i niezmiennik
#
# Dla ustalonej różnicy najbliższa wartość w posortowanej tablicy jest jednym z dwóch sąsiadów miejsca wstawienia. d zawiera minimum pierwotnych elementów, różnic jednego ruchu i sprawdzonych odległości drugiego ruchu.
#
# Złożoność
#
# k=1. O(n log n). k=2. O(n² log n). k>=3. sortowanie nadal O(n log n). Pamięć O(n), pomocniczo wyszukiwanie O(1).
#
# Przypadki brzegowe
#
# Wymaga nieujemnych wartości i zakresu k>=1. Duplikaty dają zero. Kod zachowuje d=a[0], więc uwzględnia pozostawienie pierwotnego minimum. martwe próby w początkowym wieloliniowym napisie nie są wykonywane.
#
# Kiedy rozpoznać ten wariant
#
# Enumerowane wartości pochodne porównujesz z niezmienną tablicą. potrzebujesz najbliższego elementu, a nie tylko dokładnej równości.
#
# KONIEC OPISU
'''
n = int(input())
for _ in range(n):
    len_ops = list(map(int, input().split()))
    nums = list(map(int, input().split()))

    for _ in range(len_ops[-1]):
        if 0 in nums:
            print(0)
            exit()
        l,r=1,len(nums)-2
        val = float('inf')
        while l <= r:
            if abs(nums[l-1] - nums[l]) > abs(nums[r+1] - nums[r]):
                val = min(abs(nums[r+1] - nums[r]), val)
                l += 1
            else:
                val = min(abs(nums[l-1] - nums[l]),val) 
                r -= 1
        nums.append(val)
        
    print(min(nums))


n = int(input())
for _ in range(n):
    len_ops = list(map(int, input().split()))
    nums = list(map(int, input().split()))


    nums.sort()
    for _ in range(len_ops[-1]):

        if 0 in nums:
            print(0)
            exit()

        val = float('inf')
        for i in range(len(nums)-2):
            val = min(abs(nums[i]-nums[i+1]), val)
        nums.append(val)
    print(min(nums))
'''

def binary_search(arr, x):
    # ręcznie, najprostszy szybki bisect_left
    low, high = 0, len(arr)
    while low < high:
        mid = (low + high) // 2
        if arr[mid] < x:
            low = mid + 1
        else:
            high = mid
    return low

def main():
    t = int(input())
    for _ in range(t):
        n, k = map(int, input().split())
        a = list(map(int, input().split()))
        a.sort()

        if k >= 3:
            print(0)
            continue

        # minimalna różnica między sąsiadami
        d = a[0]
        for i in range(n - 1):
            d = min(d, a[i + 1] - a[i])

        if k == 1:
            print(d)
            continue

        # zamiast pełnego podwójnego for, robimy tak:
        for i in range(n):
            for j in range(i):
                v = a[i] - a[j]
                # szukamy najbliższej wartości do v
                p = binary_search(a, v)
                if p < n:
                    d = min(d, a[p] - v)
                if p > 0:
                    d = min(d, v - a[p - 1])

        print(d)

if __name__ == "__main__":
    main()