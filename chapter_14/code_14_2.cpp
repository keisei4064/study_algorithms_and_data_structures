#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

const long long INF = 1LL << 60;

// 重み付きエッジ
struct Edge
{
    int to;      // 隣接頂点
    long long w; // 重み
    Edge(int to, long long w) : to(to), w(w) {}
};

// 重み付きグラフ - 添え字が頂点番号、要素がその頂点から出るエッジのリスト
using Graph = vector<vector<Edge>>;

// 緩和処理
template <class T>
bool chmin(T &a, T b)
{
    if (a > b)
    {
        a = b;
        return true;
    }
    else
        return false;
}

int main()
{
    // true: 負閉路ありのケース, false: 最短路が求まるケース
    // const bool USE_NEGATIVE_CYCLE = true;
    const bool USE_NEGATIVE_CYCLE = false;

    int N = 0;
    int s = 0;
    vector<tuple<int, int, long long>> edges;

    if (USE_NEGATIVE_CYCLE)
    {
        // 頂点 0 から到達可能な負閉路を含む有向グラフ
        N = 4;
        s = 0;
        edges = {
            {0, 1, 1},
            {1, 2, 1},
            {2, 1, -3}, // 1 -> 2 -> 1 が負閉路
            {2, 3, 1},
        };
    }
    else
    {
        // 負閉路を含まない有向グラフ
        N = 6;
        s = 0;
        edges = {
            {0, 1, 5},
            {0, 2, 2},
            {2, 1, 1},
            {1, 3, 3},
            {2, 3, 7},
            {3, 4, 1},
            {4, 5, 2},
        };
    }

    Graph G(N);
    for (auto [a, b, w] : edges)
    {
        G[a].push_back(Edge(b, w));
    }

    // ベルマンフォード法
    bool exist_negative_cycle = false; // 負閉路が存在するか
    vector<long long> dist(N, INF);
    dist[s] = 0;
    for (int iter = 0; iter < N; ++iter)
    {
        bool update = false; // このイテレーションで距離が更新されたか
        for (int v = 0; v < N; ++v)
        {
            // 到達可能か分からない頂点はスキップ
            if (dist[v] == INF)
                continue;

            for (auto e : G[v])
            {
                // 緩和処理実行
                if (chmin(dist[e.to], dist[v] + e.w))
                {
                    update = true;
                }
            }
        }

        // 更新が無かった場合，既に最短路が確定している
        if (!update)
            break;

        // N回目に更新があった場合 == 負の閉路が存在する
        if (iter == N - 1 && update)
            exist_negative_cycle = true;
    }

    // 結果を表示
    cout << "---- Bellman-Ford Result ----" << endl;
    cout << "start vertex: " << s << endl;

    if (exist_negative_cycle)
    {
        // 負閉路が存在
        cout << "reachable negative cycle exists." << endl;
        cout << "shortest path is not defined." << endl;
    }
    else
    {
        cout << "no reachable negative cycle." << endl;
        cout << "shortest distances from vertex " << s << ":" << endl;
        for (int v = 0; v < N; ++v)
        {
            cout << "  to " << v << ": ";
            if (dist[v] < INF)
                // 最短路報告
                cout << dist[v] << endl;
            else
                // 到達不可
                cout << "INF (unreachable)" << endl;
        }
    }
}
