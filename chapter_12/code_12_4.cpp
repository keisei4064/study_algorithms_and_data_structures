#include <iostream>
#include <vector>
using namespace std;

void PrintArray(const vector<int> &a) {
    for (int i = 0; i < (int)a.size(); ++i) {
        if (i) cout << " ";
        cout << a[i];
    }
    cout << endl;
}

// a[i]を根として，部分木 a[i:N) をヒープ化する
void Heapify(vector<int> &a, int i, int N) {
    int child1 = i * 2 + 1; // 左の子
    if (child1 >= N) return; // 子が存在しない場合は終了

    // 右の子が存在し，左の子より大きい場合は右の子を child1 とする
    if (child1 + 1 < N && a[child1 + 1] > a[child1]) ++child1;
    
    if (a[child1] <= a[i]) return; // 逆転がない場合は終了

    // swap
    swap(a[i], a[child1]);

    // 子の位置で再帰的にヒープ化
    Heapify(a, child1, N);
}

// ヒープソート
void HeapSort(vector<int> &a) {
    int N = (int)a.size();

    // 入力列をヒープ化．理解してない．
    for (int i = N / 2 - 1; i >= 0; --i) {
        Heapify(a, i, N);
    }

    // 最大値を末尾に移動し，残りをヒープ化する操作を繰り返す
    for (int i = N - 1; i > 0; --i) {
        swap(a[0], a[i]); // 最大値を評価済みの末尾へ
        Heapify(a, 0, i); // 未評価範囲を再びヒープ化
    }
}

int main() {
    vector<int> a = {7, 1, 9, 3, 8, 2, 5, 4, 6};

    cout << "before: ";
    PrintArray(a);

    HeapSort(a);

    cout << "after : ";
    PrintArray(a);
}
