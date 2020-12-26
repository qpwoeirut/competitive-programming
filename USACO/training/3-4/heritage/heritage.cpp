/*
ID: zhongbr1
TASK: heritage
LANG: C++14
*/

//heritage.cpp created at 12/23/20 19:12:47
 
#include <bits/stdc++.h>

using namespace std;

int N;
string inorder, preorder;
int in_pos[26], pre_pos[26];

void recurse(const int L, const int R) {
    char root = -1;
    for (int i=0; i<N; ++i) {
        if (L <= in_pos[preorder[i] - 'A'] && in_pos[preorder[i] - 'A'] < R) {
            root = preorder[i];
            break;
        }
    }
    if (root == -1) return;

    recurse(L, in_pos[root - 'A']);
    recurse(in_pos[root - 'A'] + 1, R);
    cout << root;
}

int main() {
    freopen("heritage.in", "r", stdin);
    freopen("heritage.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> inorder >> preorder;
    N = inorder.size();

    for (int i=0; i<N; ++i) {
        in_pos[inorder[i] - 'A'] = i;
        pre_pos[preorder[i] - 'A'] = i;
    }
    recurse(0, N);
    cout << endl;
}

