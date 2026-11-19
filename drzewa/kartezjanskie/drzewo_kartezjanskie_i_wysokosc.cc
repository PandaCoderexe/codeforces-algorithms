// Drzewo kartezjańskie i wysokość
//
// Oryginał w zbiorze codeforces/2205/tree/2205D.cc
// https://codeforces.com/contest/2205
//
// Co oblicza kod
//
// Buduje maksymalne drzewo kartezjańskie tablicy i wypisuje n minus wysokość liczona w wierzchołkach.
//
// Pomysł
//
// Stos przechowuje prawy grzbiet maksymalnego drzewa. zdjęty fragment staje się lewym synem nowego elementu. Wysokość obliczyć od liści.
//
// Stan i niezmiennik
//
// Inorder zachowuje indeksy, rodzic ma wartość nie mniejszą od dziecka. każdy indeks wchodzi i schodzi ze stosu najwyżej raz.
//
// Złożoność
//
// O(n) czasu i pamięci.
//
// Przypadki brzegowe
//
// Rosnąca tablica. malejąca. równe wartości. n=1.
//
// Kiedy rozpoznać ten wariant
//
// Rozpoznaj wzorzec. drzewo kartezjańskie i wysokość. Stos przechowuje prawy grzbiet maksymalnego drzewa. zdjęty fragment staje się lewym synem nowego elementu. Wysokość obliczyć od liści.
//
// Warunki i uwagi
//
// - Wymaga n>0. Przy równościach wcześniejszy równy element pozostaje przodkiem.
//
// KONIEC OPISU
#include <bits/stdc++.h>

using namespace std;

struct CartesianTree
{
    int root;
    vector<int> left_child, right_child, parent;
};

CartesianTree cartesianTreeInit(const vector<int> &a)
{
    int n = (int)a.size();

    vector<int> left_child(n, -1), right_child(n, -1), parent(n, -1);
    vector<int> st;

    for (int i = 0; i < n; i++)
    {
        int last = -1;

        while(!st.empty() && a[st.back()] < a[i])
        {
            last = st.back();
            st.pop_back();
        }

        if (last != -1)
        {
            left_child[i] = last;
            parent[last] = i;
        }

        if (!st.empty())
        {
            right_child[st.back()] = i;
            parent[i] = st.back();
        }

        st.push_back(i);
    }

    int root = -1;


    for (int i = 0; i < n; i++)
    {
        if (parent[i] == -1)
        {
            root = i;
            break;
        }
    }

    return {root, left_child, right_child, parent};
}

void solve()
{
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    CartesianTree car_tree = cartesianTreeInit(a);

    vector<int> order;
    vector<int> st;
    st.push_back(car_tree.root);
    
    while (!st.empty())
    {
        int cur = st.back(); st.pop_back(); 
        order.push_back(cur);
        
        if (car_tree.left_child[cur] != -1) st.push_back(car_tree.left_child[cur]);
        if (car_tree.right_child[cur] != -1) st.push_back(car_tree.right_child[cur]);
    }
    
    vector<int> dp(n+1, 0);
    for (int i = (int)order.size()-1; i >= 0; i--)
    {
        int cur = order[i];

        if (car_tree.left_child[cur] != -1 && car_tree.right_child[cur] != -1) dp[cur] = 1 + max(dp[car_tree.left_child[cur]], dp[car_tree.right_child[cur]]);
        else if (car_tree.left_child[cur] != -1) dp[cur] = 1 + dp[car_tree.left_child[cur]];
        else if (car_tree.right_child[cur] != -1) dp[cur] = 1 + dp[car_tree.right_child[cur]];
        else dp[cur] = 1;
    }

    cout << n - dp[car_tree.root] << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) solve();
    return 0;
}