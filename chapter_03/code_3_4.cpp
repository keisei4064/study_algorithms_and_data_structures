#include <iostream>
#include <vector>
#include <optional>
constexpr int INF = 1e9;

using namespace std;

int main()
{
  int N, K;
  cout << "N: ";
  cin >> N;
  cout << "K: ";
  cin >> K;

  vector<int> a(N), b(N);
  cout << "a: ";
  for (int i = 0; i < N; ++i)
  {
    cin >> a[i];
  }
  cout << "b: ";
  for (int i = 0; i < N; ++i)
  {
    cin >> b[i];
  }

  // 線形探索
  int min_value = INF;
  for (int i = 0; i < N; ++i)
  {
    for (int j = 0; j < N; ++j)
    {
      if (a[i] + b[j] < K)
        continue;

      if (a[i] + b[j] < min_value)
      {
        min_value = a[i] + b[j];
      }
    }
  }

  cout << "最小値: " << min_value << endl;
}