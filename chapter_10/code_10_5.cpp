#include <iostream>
#include <vector>
using namespace std;

// 二部ヒープ
struct Heap
{
    vector<int> heap;
    Heap() {}

    // 要素追加
    void push(int x)
    {
        heap.push_back(x);            // 末尾に追加
        int i = (int)heap.size() - 1; // 挿入値の位置インデックス
        while (i > 0)
        {
            int p = (i - 1) / 2; // 親インデックス
            if (heap[p] >= x)
                break; // 親より小さい場合は終了

            // 親より大きい場合は入れ替え
            heap[i] = heap[p];
            i = p;
        }
        heap[i] = x; // x の位置を確定
    }

    int top()
    {
        if (!heap.empty())
            return heap[0];
        else
            return -1;
    }

    // root要素削除
    void pop()
    {
        if (heap.empty())
            return;
        int x = heap.back(); // 末尾の値を取得
        heap.pop_back();
        int i = 0; // rootスタート
        while (i * 2 + 1 < (int)heap.size())
        {
            // 大きい方の子のインデックスを取得
            int child1 = i * 2 + 1, child2 = i * 2 + 2;
            if (child2 < (int)heap.size() && heap[child2] > heap[child1])
            {
                child1 = child2;
            }

            // 子より大きければ終了
            if (heap[child1] <= x)
                break;
            // 子より小さい場合は入れ替え
            heap[i] = heap[child1];
            i = child1;
        }
        heap[i] = x; // 末尾の値を確定
    }
};

int main()
{
    Heap h;
    h.push(5), h.push(3), h.push(7), h.push(1);

    cout << h.top() << endl; // 7
    h.pop();
    cout << h.top() << endl; // 5

    h.push(11);
    cout << h.top() << endl; // 11
}
