#include <iostream>
#include <vector>
using namespace std;
using Graph = vector<vector<int>>;

vector<int> depth;        // 各ノードの深さ
vector<int> subtree_size; // サブツリーのサイズ
void dfs(const Graph &G, int v, int p = -1, int d = 0)
{
    depth[v] = d;
    for (auto c : G[v])
    {
        if (c == p)
            continue; // 親ノードをスキップ
        dfs(G, c, v, d + 1);
    }

    // サブツリーのサイズをカウント
    subtree_size[v] = 1; // 自分自身
    for (auto c : G[v])
    {
        if (c == p)
            continue;

        // 子が成すサブツリーのサイズを加算
        subtree_size[v] += subtree_size[c];
    }
    cout << "done: dfs(G, " << v << ")" << endl;
}

int main()
{
    // 頂点数を固定
    const int N = 7;

    // 木を固定で作る (辺数は N - 1)
    const vector<pair<int, int>> edges = {
        {0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5}, {5, 6}};

    // 隣接リストを作成
    Graph G(N);
    for (auto [a, b] : edges)
    {
        G[a].push_back(b);
        G[b].push_back(a);
    }

    // 0を根とみなしてアルゴリズムを実行
    int root = 0;
    depth.assign(N, 0);
    subtree_size.assign(N, 0);
    dfs(G, root);

    // 結果
    for (int v = 0; v < N; ++v)
    {
        cout << v << ": depth = " << depth[v]
             << ", subtree_size = " << subtree_size[v] << endl;
    }
}
