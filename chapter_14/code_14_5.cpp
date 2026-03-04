#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

const long long INF = 1LL << 60;

int main() {
    // 頂点数を固定
    const int N = 6;

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

    // dp [i][j]: 頂点 i から頂点 j への最短距離の推定値
    vector<vector<long long>> dp(N, vector<long long>(N, INF));

    // == フロイド・ワーシャル法 ==

    // 初期化
    for (auto [a, b, w] : edges) {
        dp[a][b] = w;
    }
    for (int v = 0; v < N; ++v) dp[v][v] = 0;

    // コア計算
    for (int k = 0; k < N; ++k)
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);

    // 結果
    bool exist_negative_cycle = false;
    for (int v = 0; v < N; ++v) {
        if (dp[v][v] < 0) exist_negative_cycle = true;
    }
    if (exist_negative_cycle) {
        cout << "NEGATIVE CYCLE" << endl;
    }
    else {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (j) cout << " ";
                if (dp[i][j] < INF/2) cout << dp[i][j];
                else cout << "INF";
            }
            cout << endl;
        }
    }                              
}
