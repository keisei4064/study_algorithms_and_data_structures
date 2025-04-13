#include <iostream>
#include <vector>
#include <optional>

using namespace std;

int main()
{
  int N, v;
  cout << "探索対象の要素数を入力してください" << endl;
  cin >> N;
  cout << "探索対象の値を入力してください" << endl;
  cin >> v;
  vector<int> a(N);

  cout << "探索対象の値を" << N << "個入力してください" << endl;
  for (int i = 0; i < N; ++i)
  {
    cin >> a[i];
  }

  // 線形探索
  optional<int> index = nullopt;
  for (int i = 0; i < N; ++i)
  {
    if (a[i] == v)
    {
      index = i;
      break;
    }
  }

  if (index)
    cout << "Yes - ID: " << *index << endl;
  else
    cout << "No" << endl;
}