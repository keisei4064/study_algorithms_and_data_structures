#include <iostream>
#include <vector>
using namespace std;
const int MAX = 100000; // 上限サイズ

int st[MAX]; // スタックとしてふるまう配列
int top = 0; // 一番上を指す

void init()
{
    top = 0;
}

bool isEmpty()
{
    return (top == 0);
}

bool isFull()
{
    return (top == MAX);
}

// push
void push(int x)
{
    if (isFull())
    {
        cout << "error: stack is full." << endl;
        return;
    }
    st[top] = x; // 一番上に代入
    ++top;       // インクリメント
}

// pop
int pop()
{
    if (isEmpty())
    {
        cout << "error: stack is empty." << endl;
        return -1;
    }
    --top;          // デクリメント
    return st[top]; // 一番上にあった値を返す
}

int main()
{
    init();

    push(3);
    push(5);
    push(7);

    cout << pop() << endl;
    cout << pop() << endl;

    push(9);
}
