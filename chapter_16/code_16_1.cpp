#include <iostream>
#include <vector>
using namespace std;

// グラフを表すクラス
struct Graph
{
    // rev: 逆向きのエッジのインデックス,
    // from: エッジの始点, to: エッジの終点, cap: エッジの容量
    struct Edge
    {
        int rev, from, to, cap;
        Edge(int r, int f, int t, int c) : rev(r), from(f), to(t), cap(c) {}
    };

    // 隣接リスト
    vector<vector<Edge>> list;

    // N: 頂点数
    Graph(int N = 0) : list(N) {}

    // 頂点数
    size_t size()
    {
        return list.size();
    }

    // iを始点とするエッジのリストを取得
    vector<Edge> &operator[](int i)
    {
        return list[i];
    }

    // 逆向きのエッジ取得
    Edge &redge(const Edge &e)
    {
        return list[e.to][e.rev];
    }

    // 流量f をエッジeに流す
    void run_flow(Edge &e, int f)
    {
        e.cap -= f;
        redge(e).cap += f;
    }

    // エッジを両方向用意
    void addedge(int from, int to, int cap)
    {
        int fromrev = (int)list[from].size();
        int torev = (int)list[to].size();
        list[from].push_back(Edge(torev, from, to, cap));
        list[to].push_back(Edge(fromrev, to, from, 0));
    }
};

// フォード・ファルカーソン法のアルゴリズム実装
struct FordFulkerson
{
    static const int INF = 1 << 30; // 初期化用
    vector<bool> seen;              // DFS用の訪問済み配列

    FordFulkerson() {}

    // s-tパスを探し，最小容量を記録し，その容量だけ流す
    int fodfs(Graph &G, int v, int t, int f)
    {
        // 終点に到達．
        if (v == t)
            // それまでの最小容量を返す
            return f;

        // 訪問済みフラグを立てる
        seen[v] = true;
        for (auto &e : G[v])
        {
            // すでに訪問済みの頂点はスキップ
            if (seen[e.to])
                continue;

            // 容量0のエッジはスキップ（存在しない）
            if (e.cap == 0)
                continue;

            // s-t パスを再帰的に探す
            //  最小容量値も更新
            int flow = fodfs(G, e.to, t, min(f, e.cap));

            // s-t パスが見つからなかった場合はこの辺eをスキップ
            if (flow == 0)
                continue;

            // 見つかったパスにおける最小容量文だけの流量を流す
            G.run_flow(e, flow);

            // 最小容量を返す
            return flow;
        }

        // 0: s-t パスが見つからなかったことを表す
        return 0;
    }

    // フォード・ファルカーソン法の実行
    int solve(Graph &G, int s, int t)
    {
        int res = 0;

        // s-t パスが見つからなくなるまで繰り返す
        while (true)
        {
            // s-t パスを探し，見つかったらその最小容量を流す
            seen.assign((int)G.size(), 0);
            int flow = fodfs(G, s, t, INF);

            // 新たな s-t パスが見つからなかった場合は終了
            if (flow == 0)
                return res;

            // 合計流量を更新
            res += flow;
        }

        // no reach
        return 0;
    }
};

int main()
{
    // 入力は固定データで用意する（頂点は 0..N-1, 0 が始点, N-1 が終点）
    struct InputEdge
    {
        int u, v, cap;
    };

    const int N = 6;
    vector<InputEdge> input_edges = {
        {0, 1, 10},
        {0, 2, 10},
        {1, 2, 2},
        {1, 3, 4},
        {1, 4, 8},
        {2, 4, 9},
        {4, 3, 6},
        {3, 5, 10},
        {4, 5, 10},
    };
    int M = static_cast<int>(input_edges.size());

    Graph G(N);
    vector<int> forward_edge_index(M, -1);
    for (int i = 0; i < M; ++i)
    {
        int u = input_edges[i].u;
        int v = input_edges[i].v;
        int c = input_edges[i].cap;

        // forward edge の位置を覚えておく（後で流量を表示するため）
        forward_edge_index[i] = static_cast<int>(G[u].size());
        G.addedge(u, v, c);
    }

    // 実行
    FordFulkerson ff;
    int s = 0, t = N - 1;
    int max_flow = ff.solve(G, s, t);
    cout << "最大流: " << max_flow << endl;

    // 結果詳細
    cout << "--- 辺ごとの結果 (u -> v) ---" << endl;
    for (int i = 0; i < M; ++i)
    {
        int u = input_edges[i].u;
        int v = input_edges[i].v;
        int cap = input_edges[i].cap;
        const Graph::Edge &e = G[u][forward_edge_index[i]];
        int flow = cap - e.cap; // 初期容量 - 残余容量 = 流れた流量

        cout << u << " -> " << v
             << " | capacity = " << cap
             << ", flow = " << flow
             << ", residual = " << e.cap << endl;
    }

    vector<int> out_flow(N, 0), in_flow(N, 0);
    for (int i = 0; i < M; ++i)
    {
        int u = input_edges[i].u;
        int v = input_edges[i].v;
        int cap = input_edges[i].cap;
        const Graph::Edge &e = G[u][forward_edge_index[i]];
        int flow = cap - e.cap;
        out_flow[u] += flow;
        in_flow[v] += flow;
    }

    cout << "--- 頂点ごとの出入流量 ---" << endl;
    for (int v = 0; v < N; ++v)
    {
        cout << "v = " << v
             << " | in = " << in_flow[v]
             << ", out = " << out_flow[v] << endl;
    }
}
