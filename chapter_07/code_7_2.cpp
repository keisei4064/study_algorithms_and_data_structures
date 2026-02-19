#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

// 区間型
typedef pair<int, int> Interval;

// 終端でソート用
bool cmp(const Interval &a, const Interval &b)
{
    return a.second < b.second;
}

int main()
{
    // 固定のサンプルで実行
    vector<Interval> inter = {
        {1, 3},
        {2, 5},
        {4, 7},
        {6, 9},
        {8, 10},
    };
    const int N = static_cast<int>(inter.size());

    // 終端でソート
    sort(inter.begin(), inter.end(), cmp);

    // 貪欲法で解く
    int res = 0;
    int current_end_time = 0;
    for (int i = 0; i < N; ++i)
    {
        // 前回選択した区間と重なっているものは選べない
        if (inter[i].first < current_end_time)
            continue;

        ++res;
        current_end_time = inter[i].second;
    }
    cout << res << endl;
}
