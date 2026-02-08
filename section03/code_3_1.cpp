// 線形探索法

#include <iostream>
#include <vector>
using namespace std;

int main()
{
  // 探索対象の作成
  int N, v;
  cin >> N >> v;
  vector<int> a(N);
  for (int i = 0; i < N; ++i)
    cin >> a[i];

  // 探索ループ
  bool exist = false; // 初期フラグ
  for (int i = 0; i < N; ++i)
  {
    if (a[i] == v)
    {
      exist = true; // 発見
    }
  }

  // 結果
  if (exist)
    cout << "Yes" << endl;
  else
    cout << "No" << endl;
}
