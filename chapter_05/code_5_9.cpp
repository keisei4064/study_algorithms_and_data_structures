#include <iostream>
#include <vector>
using namespace std;

template <class T>
void chmin(T &a, T b)
{
  if (a > b)
    a = b;
}

const long long INF = 1LL << 60;

int main()
{
  const int N = 5;

  // c[j][i] = 区間 [j, i) を1区間としたときのコスト
  vector<vector<int64_t>> c = {
      {0, 4, 7, 10, 15, 18},
      {INF, 0, 3, 6, 8, 13},
      {INF, INF, 0, 2, 5, 9},
      {INF, INF, INF, 0, 3, 4},
      {INF, INF, INF, INF, 0, 2},
      {INF, INF, INF, INF, INF, 0},
  };

  // 区間 [0, i) をいくつかに分割したときの最小コスト
  vector<int64_t> dp(N + 1, INF);

  // 初期条件
  dp[0] = 0;

  for (int i = 0; i <= N; ++i)
  {
    for (int j = 0; j < i; ++j)
    {
      // [0, j) の最適分割 + [j, i) のコスト
      chmin(dp[i], dp[j] + c[j][i]);
    }
  }

  cout << dp[N] << endl;
}