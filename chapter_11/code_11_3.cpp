#include <iostream>
#include <vector>
using namespace std;

// Union-Find
struct UnionFind {
    vector<int> par, siz; // 親，頂点数

    UnionFind(int n) : par(n, -1) , siz(n, 1) { }
    
    // 経路圧縮しながらrootを求める
    int root(int x) {
        if (par[x] == -1) return x; // x が根
        else return par[x] = root(par[x]); // 経路圧縮しつつ親を辿る
    }

    // xとyが同じグループに属するか
    bool issame(int x, int y) {
        return root(x) == root(y);
    }

    // x の属するグループと y の属するグループを併合する
    bool unite(int x, int y) {
        x = root(x);
        y = root(y);

        if (x == y) return false; 

        // yが小さい側
        if (siz[x] < siz[y]) swap(x, y);

        // y の親を x にする
        par[y] = x;
        siz[x] += siz[y];
        return true;
    }

    // x が属するグループのサイズ
    int size(int x) {
        return siz[root(x)];
    }
};

int main() {
    UnionFind uf(7); // {0}, {1}, {2}, {3}, {4}, {5}, {6}

    uf.unite(1, 2); // {0}, {1, 2}, {3}, {4}, {5}, {6}
    uf.unite(2, 3); // {0}, {1, 2, 3}, {4}, {5}, {6}
    uf.unite(5, 6); // {0}, {1, 2, 3}, {4}, {5, 6}
    cout << uf.issame(1, 3) << endl; // True
    cout << uf.issame(2, 5) << endl; // False

    uf.unite(1, 6); // {0}, {1, 2, 3, 5, 6}, {4}
    cout << uf.issame(2, 5) << endl; // True
}
