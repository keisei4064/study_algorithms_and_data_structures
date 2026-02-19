#include <iostream>
#include <vector>
using namespace std;

const int N = 8;
const vector<int> a = {3, 5, 8, 10, 14, 17, 21, 39};

// 二部探索：目的の値 key の添え字を返す
int binary_search(int key)
{
    int left = 0, right = (int)a.size() - 1; // 初期化
    while (right >= left)
    {
        int mid = left + (right - left) / 2; // 中心インデックス計算
        if (a[mid] == key)
            return mid;
        else if (a[mid] > key)
            right = mid - 1;
        else if (a[mid] < key)
            left = mid + 1;
    }
    return -1;
}

int main()
{
    cout << binary_search(10) << endl; // 3
    cout << binary_search(3) << endl;  // 0
    cout << binary_search(39) << endl; // 7

    cout << binary_search(-100) << endl; // -1
    cout << binary_search(9) << endl;    // -1
    cout << binary_search(100) << endl;  // -1
}
