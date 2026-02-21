#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 双方向リンクノード
struct Node
{
    Node *prev, *next;
    string name; // データ内容

    Node(string name_ = "") : prev(NULL), next(NULL), name(name_) {}
};

// 番兵（センチネル）
Node *nil;

// 初期化
void init()
{
    nil = new Node();
    nil->prev = nil;
    nil->next = nil;
}

// 連結リストを出力する
void printList()
{
    Node *cur = nil->next; // 先頭から出発
    for (; cur != nil; cur = cur->next)
    {
        cout << cur->name << " -> ";
    }
    cout << endl;
}

// 挿入
void insert(Node *v, Node *p = nil)
{
    v->next = p->next;
    p->next->prev = v;
    p->next = v;
    v->prev = p;
}

// 削除
void erase(Node *v)
{
    if (v == nil)
        return; // 番兵に対しては何もしない
    v->prev->next = v->next;
    v->next->prev = v->prev;
    delete v; // メモリ解法
}

int main()
{
    init();

    vector<string> names = {"yamamoto",
                            "watanabe",
                            "ito",
                            "takahashi",
                            "suzuki",
                            "sato"};

    // 順に先頭に挿入
    Node *watanabe;
    for (int i = 0; i < (int)names.size(); ++i)
    {
        Node *node = new Node(names[i]);

        insert(node);

        if (names[i] == "watanabe")
            watanabe = node; // あとで削除するようにポインタを保存
    }

    cout << "before: ";
    printList();
    erase(watanabe); // 削除
    cout << "after: ";
    printList();
}
