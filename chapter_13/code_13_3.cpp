#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using Graph = vector<vector<int>>;

// 始点 s からの最短距離を計算する
vector<int> bfs(const Graph &G, int s)
{
    const int N = static_cast<int>(G.size());
    vector<int> dist(N, -1); // 未訪問は -1
    queue<int> que;

    // 初期条件 (頂点 s がスタート)
    dist[s] = 0;
    que.push(s);

    while (!que.empty())
    {
        int v = que.front();
        que.pop();

        // v から辿れる頂点を探索
        for (int next_v : G[v])
        {
            if (dist[next_v] != -1)
                continue; // 訪問済みならスキップ

            dist[next_v] = dist[v] + 1;
            que.push(next_v);
        }
        cout << "done: v = " << v << endl;
    }

    return dist;
}

int main()
{
    // 頂点数を固定
    const int N = 7;

    // 無向グラフを固定で作る
    const vector<pair<int, int>> edges = {
        {0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5}, {5, 6}};

    // 隣接リストを作成
    Graph G(N);
    for (auto [a, b] : edges)
    {
        G[a].push_back(b);
        G[b].push_back(a);
    }

    // 頂点 0 を始点として BFS
    vector<int> dist = bfs(G, 0);

    // 各頂点の最短距離を表示
    for (int v = 0; v < N; ++v)
    {
        cout << v << ": " << dist[v] << endl;
    }
}
