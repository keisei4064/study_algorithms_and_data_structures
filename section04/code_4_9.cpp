#include <iostream>
#include <vector>
using namespace std;

bool func(int i, int w, const vector<int> &a) {
    // ベースケース
    if (i == 0) { // 0個の整数を使って
        if (w == 0) return true; // 和0を作る -> true
        else return false;
    }

    // a[i - 1] a[i]を使用しない場合
    if (func(i - 1, w, a)) return true;

    // a[i - 1] a[i]を使用する場合
    if (func(i - 1, w - a[i - 1], a)) return true;

    // どちらでも和wを作れなかった
    return false;
}

int main() {
    int N, W;
    cout << "N W? ";
    cin >> N >> W;
    vector<int> a(N);
    cout << "a[]? ";
    for (int i = 0; i < N; ++i) cin >> a[i];

    if (func(N, W, a)) cout << "Yes" << endl;
    else cout << "No" << endl;
}
