#include <iostream>
#include <vector>
using namespace std;

void PrintArray(const vector<int> &a)
{
    for (int i = 0; i < (int)a.size(); ++i)
    {
        if (i)
            cout << " ";
        cout << a[i];
    }
    cout << endl;
}

// クイックソート
void QuickSort(vector<int> &a, int left, int right, int depth = 0)
{
    if (right - left <= 1)
        return; // 要素が1個以下ならソート不要

    int pivot_index = (left + right) / 2; // 中間の要素をピボットに選ぶ
    int pivot = a[pivot_index];

    swap(a[pivot_index], a[right - 1]); // pivot を末尾に移動

    int i = left; // i はピボットより小さい要素の右端を示す
    for (int j = left; j < right - 1; ++j)
    {
        if (a[j] < pivot)
        {
            swap(a[i++], a[j]);
        }
    }
    swap(a[i], a[right - 1]); // ピボットを正しい位置へ

    QuickSort(a, left, i, depth + 1);      // ピボット未満（左区間）をソート
    QuickSort(a, i + 1, right, depth + 1); // ピボット超（右区間）をソート
}

int main()
{
    vector<int> a = {8, 3, 7, 4, 9, 2, 6, 5};
    int N = (int)a.size();

    cout << "before: ";
    PrintArray(a);

    // クイックソートを実行
    QuickSort(a, 0, N);

    cout << "after : ";
    PrintArray(a);
}
