#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using Graph = vector<vector<int>>;

vector<bool> seen;
vector<int> order;

void rec(const Graph &G, int v)
{
  // v を訪問済みにする
  seen[v] = true;

  for (int next_v : G[v])
  {
    if (seen[next_v])
      continue;

    // 未訪問の隣接頂点を先に探索する
    rec(G, next_v);
  }

  // v から先を全部探索し終わった「帰りがけ」に記録
  order.push_back(v);
}

int main()
{
  // 例：
  //
  // 0 → 1 → 3
  // ↓   ↓
  // 2 → 4
  //
  // 0→1, 0→2, 1→3, 1→4, 2→4
  const Graph G = {
      {1, 2},
      {3, 4},
      {4},
      {},
      {},
  };

  const int N = static_cast<int>(G.size());

  seen.assign(N, false);
  order.clear();

  // 非連結な DAG にも対応
  for (int v = 0; v < N; ++v)
  {
    if (seen[v])
      continue;

    rec(G, v);
  }

  // 帰りがけ順を逆転するとトポロジカル順になる
  reverse(order.begin(), order.end());

  for (int v : order)
  {
    cout << v << ' ';
  }
  cout << '\n';
}