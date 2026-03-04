#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
using namespace std;

// Union-Find
struct UnionFind
{
    vector<int> par, siz;

    UnionFind(int n) : par(n, -1), siz(n, 1) {}

    int root(int x)
    {
        if (par[x] == -1)
            return x;
        else
            return par[x] = root(par[x]);
    }

    bool issame(int x, int y)
    {
        return root(x) == root(y);
    }

    bool unite(int x, int y)
    {
        x = root(x);
        y = root(y);

        if (x == y)
            return false;

        if (siz[x] < siz[y])
            swap(x, y);

        par[y] = x;
        siz[x] += siz[y];
        return true;
    }

    int size(int x)
    {
        return siz[root(x)];
    }

    void print()
    {
        const int n = static_cast<int>(par.size());

        // 経路圧縮して、表示を分かりやすくする
        for (int v = 0; v < n; ++v)
        {
            root(v);
        }

        vector<vector<int>> children(n);
        vector<int> roots;
        for (int v = 0; v < n; ++v)
        {
            if (par[v] == -1)
                roots.push_back(v);
            else
                children[par[v]].push_back(v);
        }

        sort(roots.begin(), roots.end());
        for (int v = 0; v < n; ++v)
        {
            sort(children[v].begin(), children[v].end());
        }

        function<void(int, const string &, bool)> dfs =
            [&](int v, const string &prefix, bool is_last)
        {
            cout << prefix << (is_last ? "`-- " : "|-- ")
                 << v << " (size=" << siz[v] << ")" << endl;

            const string next_prefix = prefix + (is_last ? "    " : "|   ");
            for (int i = 0; i < static_cast<int>(children[v].size()); ++i)
            {
                const bool child_last = (i + 1 == static_cast<int>(children[v].size()));
                dfs(children[v][i], next_prefix, child_last);
            }
        };

        cout << "UnionFind forest" << endl;
        for (int r : roots)
        {
            cout << r << " (size=" << siz[r] << ")" << endl;
            for (int j = 0; j < static_cast<int>(children[r].size()); ++j)
            {
                const bool child_last = (j + 1 == static_cast<int>(children[r].size()));
                dfs(children[r][j], "", child_last);
            }
        }
    }
};

// [w, (u, v)]
using Edge = pair<int, pair<int, int>>;

int main()
{
    // 頂点数を固定
    const int N = 7;

    // 無向重み付きグラフの辺を固定で作る
    vector<Edge> edges = {
        Edge(7, make_pair(0, 1)),
        Edge(5, make_pair(0, 3)),
        Edge(8, make_pair(1, 2)),
        Edge(9, make_pair(1, 3)),
        Edge(7, make_pair(1, 4)),
        Edge(5, make_pair(2, 4)),
        Edge(15, make_pair(3, 4)),
        Edge(6, make_pair(3, 5)),
        Edge(8, make_pair(4, 5)),
        Edge(9, make_pair(4, 6)),
        Edge(11, make_pair(5, 6)),
    };
    const int M = static_cast<int>(edges.size());

    // == クラスカル法 ==

    // 辺の重みが小さい順にソート
    sort(edges.begin(), edges.end());

    long long res = 0;
    UnionFind uf(N);

    // Union-Findの状態を表示
    cout << "---初期状態---" << endl;
    uf.print();

    for (int i = 0; i < M; ++i)
    {
        int w = edges[i].first;
        int u = edges[i].second.first;
        int v = edges[i].second.second;

        // 既に同じグループの場合サイクルが生成されてしまうためスキップ
        if (uf.issame(u, v))
            continue;

        // 木としての重みを更新
        res += w;

        // グループを併合
        uf.unite(u, v);
    }
    cout << endl
         << "最小全域木の重み: " << res << endl
         << endl;

    // Union-Findの状態を表示
    cout << "---最終状態---" << endl;
    uf.print();
}
