#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
using namespace std;

const long long INF = 1LL << 60;

struct Edge
{
    int to;
    long long w;
    Edge(int to, long long w) : to(to), w(w) {}
};

using Graph = vector<vector<Edge>>;

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
    // 頂点数と始点を固定
    const int N = 6;
    const int s = 0;

    // 有向グラフを固定で作る
    const vector<tuple<int, int, long long>> edges = {
        {0, 1, 5},
        {0, 2, 2},
        {2, 1, 1},
        {1, 3, 3},
        {2, 3, 7},
        {3, 4, 1},
        {4, 5, 2},
    };

    // 隣接リストを作成
    Graph G(N);
    for (auto [a, b, w] : edges)
    {
        G[a].push_back(Edge(b, w));
    }

    // ダイクストラ法　（ヒープ使用ver）

    // 始点からの距離推定値
    vector<long long> dist(N, INF);
    dist[s] = 0;

    // (d[v], v) を保持するヒープ
    priority_queue<pair<long long, int>,
                   vector<pair<long long, int>>,
                   greater<pair<long long, int>>>
        que;
    que.push(make_pair(dist[s], s));

    // ヒープが空になるまでループ
    while (!que.empty())
    {
        // topはdが最小の頂点v
        int v = que.top().second;
        long long d = que.top().first;
        que.pop();

        // d > dist[v] の場合はゴミとして無視
        if (d > dist[v])
            continue;

        // 緩和処理
        for (auto e : G[v])
        {
            if (chmin(dist[e.to], dist[v] + e.w))
            {
                // 距離が更新された場合はヒープに追加
                que.push(make_pair(dist[e.to], e.to));
            }
        }
    }

    // 結果
    for (int v = 0; v < N; ++v)
    {
        if (dist[v] < INF)
            cout << dist[v] << endl;
        else
            cout << "INF" << endl;
    }
}
