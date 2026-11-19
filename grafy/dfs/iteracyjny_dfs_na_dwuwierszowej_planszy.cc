// DFS z jawnym stosem
//
// Oryginał w zbiorze codeforces/1598/graph/1598dfs.cc
// https://codeforces.com/contest/1598
//
// Co oblicza kod
//
// Sprawdza osiągalność dowolnej komórki ostatniej kolumny ze startu (0,0), dopuszczając pion oraz ruch do następnej kolumny.
//
// Pomysł
//
// Trzymać pary współrzędnych na stosie, sprawdzać pięć dozwolonych przesunięć, a odwiedzanie oznaczać już przy dodaniu.
//
// Stan i niezmiennik
//
// Każda komórka trafia na stos najwyżej raz. wszystkie dołożone komórki są osiągalne od przyjętego startu.
//
// Złożoność
//
// O(n) czasu i O(n) pamięci dla planszy 2×n, ponieważ każda komórka ma najwyżej pięciu kandydatów na sąsiadów.
//
// Przypadki brzegowe
//
// Wymagany wolny start. n=1. zablokowana kolumna. przejście po przekątnej. dowolny wiersz celu.
//
// Kiedy rozpoznać ten wariant
//
// Osiągalność w małym grafie niejawnym, którego krawędzie wynikają z przesunięć współrzędnych.
//
// Warunki i uwagi
//
// - Start jest przyjmowany bez sprawdzenia blokady; cel to dowolny wiersz ostatniej kolumny.
//
// KONIEC OPISU
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <stack>
#include <utility>

void solve() {
    int n,q;
    std::cin >> n;
    std::string a,b;
    std::cin >> a >> b;
    std::vector<std::string> matrix = {a,b};

    std::stack<std::pair<int,int>> stack;
    stack.push({0,0});
    std::vector<std::vector<bool>> visited(2, std::vector<bool>(n, false));
    visited[0][0] = true;

    std::vector<int> dx = {-1,-1, 1, 1, 0};
    std::vector<int> dy = { 0, 1, 0, 1, 1};

    while (!stack.empty()) {
        auto [x,y] = stack.top();
        stack.pop();

        if ( y==n-1) {
            std::cout << "YES" << std::endl;
            return;
        }

        for (int i = 0; i < 5; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < 2 && ny < n && matrix[nx][ny] != '1' && visited[nx][ny] == false ) {
                visited[nx][ny] = true;
                stack.push({nx,ny});
            }
        }

    }
    std::cout << "NO" << std::endl;
}

int main() {
    int x;
    std::cin >> x;

    while (x--) solve();
}