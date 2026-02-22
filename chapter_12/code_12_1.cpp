#include <iostream>
#include <vector>
using namespace std;

// 挿入ソート
void InsertionSort(vector<int> &a)
{
    int N = (int)a.size();
    for (int i = 1; i < N; ++i)
    {
        // 今回のソート対象
        int v = a[i];

        // 挿入処理
        int j = i;
        for (; j > 0; --j)
        {
            if (a[j - 1] > v)
            {
                a[j] = a[j - 1];
            }
            else
                break;
        }
        a[j] = v;
    }
}

int main()
{
    vector<int> a = {5, 2, 4, 6, 1, 3};
    int N = (int)a.size();

    InsertionSort(a);

    // 結果
    for (int i = 0; i < N; ++i)
    {
        cout << a[i] << (i + 1 == N ? '\n' : ' ');
    }
}
