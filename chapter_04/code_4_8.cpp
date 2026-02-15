// メモ化（キャッシュ）で計算量削減

#include <iostream>
#include <vector>
using namespace std;

// 計算済み fibo(N) を保存するメモ
vector<long long> memo;

long long fibo(int N)
{
    // ベースケース
    if (N == 0)
        return 0;
    else if (N == 1)
        return 1;

    // 既に計算済み (メモに値があれば) はそれを返す
    if (memo[N] != -1)
        return memo[N];

    // メモ化しながら再帰計算
    return memo[N] = fibo(N - 1) + fibo(N - 2);
}

int main()
{
    // 未計算は-1として初期化
    memo.assign(50, -1);

    fibo(49);
    for (int N = 2; N < 50; ++N)
    {
        cout << " fibo(" << N << "): " << memo[N] << endl;
    }
}
