#include <iostream>
#include <tuple>
#include <vector>
using namespace std;


const long long INF = 1LL << 60;

struct Edge {
    int to;
    long long w;
    Edge(int to, long long w) : to(to), w(w) {}
};

using Graph = vector<vector<Edge>>;

template<class T> bool chmin(T& a, T b) {
    if (a > b) {
        a = b;
        return true;
    }
    else return false;
}

int main() {
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
    for (auto [a, b, w] : edges) {
        G[a].push_back(Edge(b, w));
    }

    // ダイクストラ法　（線形探索ver）
    vector<bool> used(N, false); // 使用済みの頂点
    vector<long long> dist(N, INF); // 始点からの距離推定値
    dist[s] = 0;
    for (int iter = 0; iter < N; ++iter) {
        // dist[v] が最小の v を探す（線形探索）
        long long min_dist = INF;
        int min_v = -1;
        for (int v = 0; v < N; ++v) {
            // 使用済みでない　かつ　始点からの距離推定値が最小の頂点
            if (!used[v] && dist[v] < min_dist) {
                min_dist = dist[v];
                min_v = v;
            }
        }

        // 使用済みでない頂点がない場合は終了
        if (min_v == -1) break;

        // 緩和処理
        for (auto e : G[min_v]) {
            chmin(dist[e.to], dist[min_v] + e.w);
        }
        used[min_v] = true; // min_v を使用済みにする
    }

    // 結果を表示
    for (int v = 0; v < N; ++v) {
        if (dist[v] < INF) cout << dist[v] << endl;
        else cout << "INF" << endl;
    }
}
