#include <iostream>
using namespace std;

int func(int N)
{
  // 呼び出し順理解用print
  cout << "func(" << N << ") が呼び出されました" << endl;

  // ベースケース
  if (N == 0)
    return 0;

  // 再帰呼び出し
  int result = N + func(N - 1);
  cout << N << " の階乗 = " << result << endl;

  return result;
}

int main()
{
  func(5);
}
