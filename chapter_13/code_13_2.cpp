#include <vector>
#include <iostream>
using namespace std;
using Graph = vector<vector<int>>;

// 深さ優先探索
vector<bool> seen;
void dfs(const Graph &G, int v)
{
    seen[v] = true; // v を訪問済みにする

    // v から行ける頂点 next_v について探索
    for (auto next_v : G[v])
    {
        if (seen[next_v])
            continue;   // 訪問済みなら探索しない
        dfs(G, next_v); // 再帰的に探索
    }
    cout << "done: dfs(G, " << v << ")" << endl;
}

int main()
{
    // 頂点数を固定
    const int N = 7;

    // 有向グラフを固定で作る
    const vector<pair<int, int>> edges = {
        {0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5}, {5, 6}};

    // 隣接リストを作成
    Graph G(N);
    for (auto [a, b] : edges)
    {
        G[a].push_back(b);
    }

    // 全頂点を探索
    seen.assign(N, false); // 最初はすべて未訪問
    for (int v = 0; v < N; ++v)
    {
        if (seen[v])
            continue; // 訪問済みならスキップ
        dfs(G, v);
    }
}
