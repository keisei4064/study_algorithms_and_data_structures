#include <iostream>
#include <vector>
using namespace std;
const long long INF = 1LL << 60; // クソデカ数値

int main()
{
    // 入力
    int N;
    cin >> N;
    vector<long long> h(N);
    for (int i = 0; i < N; ++i)
        cin >> h[i];

    // メモ化配列
    vector<long long> dp(N, INF);

    // 初期値
    dp[0] = 0;

    // 動的計画法
    for (int i = 1; i < N; ++i)
    {
        if (i == 1)
            dp[i] = abs(h[i] - h[i - 1]);  // 最初は1段目からしかジャンプできない
        else  // 小さいほうを採用
            dp[i] = min(dp[i - 1] + abs(h[i] - h[i - 1]),
                        dp[i - 2] + abs(h[i] - h[i - 2]));
    }

    // 結果
    cout << dp[N - 1] << endl;
}
