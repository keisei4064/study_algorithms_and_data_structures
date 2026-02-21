#include <iostream>
#include <vector>
using namespace std;
const int MAX = 100000; // 上限サイズ

int qu[MAX];            // キューとしてふるまう配列
int tail = 0, head = 0; // 先頭と末尾を指す

void init()
{
    head = tail = 0;
}

bool isEmpty()
{
    return (head == tail);
}

bool isFull()
{
    return (head == (tail + 1) % MAX);
}

// enqueue
void enqueue(int x)
{
    if (isFull())
    {
        cout << "error: queue is full." << endl;
        return;
    }
    qu[tail] = x;

    // リングバッファ運用
    ++tail;
    if (tail == MAX)
        tail = 0;
}

// dequeue
int dequeue()
{
    if (isEmpty())
    {
        cout << "error: queue is empty." << endl;
        return -1;
    }
    int res = qu[head];

    // リングバッファ運用
    ++head;
    if (head == MAX)
        head = 0;
    return res;
}

int main()
{
    init();

    enqueue(3);
    enqueue(5);
    enqueue(7);

    cout << dequeue() << endl;
    cout << dequeue() << endl;

    enqueue(9);
}
