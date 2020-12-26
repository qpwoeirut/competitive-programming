/*
ID: zhongbr1
TASK: msquare
LANG: C++14
*/

//msquare.cpp created at 12/21/20 20:20:07

#include <bits/stdc++.h>

using namespace std;

int arr[2][4];

void unpack(int state) {
    for (int r=1; r>=0; --r) {
        for (int c=3; c>=0; --c) {
            arr[r][c] = state & 7;
            state >>= 3;
        }
    }

    assert(state == 0);
}

int pack() {
    int state = 0;
    for (int r=0; r<2; ++r) {
        for (int c=0; c<4; ++c) {
            state <<= 3;
            state += arr[r][c];
        }
    }

    return state;
}

map<int,char> path;
map<int,int> par;

int main() {
    freopen("msquare.in", "r", stdin);
    freopen("msquare.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    for (int i=0; i<4; ++i) {
        cin >> arr[0][i];
        --arr[0][i];
    }
    for (int i=3; i>=0; --i) {
        cin >> arr[1][i];
        --arr[1][i];
    }

    const int target = pack();

    arr[0][0] = 0;
    arr[0][1] = 1;
    arr[0][2] = 2;
    arr[0][3] = 3;
    arr[1][3] = 4;
    arr[1][2] = 5;
    arr[1][1] = 6;
    arr[1][0] = 7;

    const int start = pack();

    queue<int> q;
    q.push(start);
    par[start] = -1;
    path[start] = 'S';

    while (q.size() > 0) {
        const int cur = q.front(); q.pop();

        if (cur == target) break;

        unpack(cur);

        swap(arr[0], arr[1]);
        const int op_a = pack();
        if (op_a != start && path.count(op_a) == 0) {
            path[op_a] = 'A';
            par[op_a] = cur;
            q.push(op_a);
        }

        unpack(cur);
        rotate(arr[0], arr[0] + 3, arr[0] + 4);
        rotate(arr[1], arr[1] + 3, arr[1] + 4);
        const int op_b = pack();
        if (op_b != start && path.count(op_b) == 0) {
            path[op_b] = 'B';
            par[op_b] = cur;
            q.push(op_b);
        }

        unpack(cur);
        const int tmp = arr[0][1];
        arr[0][1] = arr[1][1];
        arr[1][1] = arr[1][2];
        arr[1][2] = arr[0][2];
        arr[0][2] = tmp;
        const int op_c = pack();
        if (op_c != start && path.count(op_c) == 0) {
            path[op_c] = 'C';
            par[op_c] = cur;
            q.push(op_c);
        }
    }

    string ans;
    int cur = target;
    while (cur != -1) {
        ans.push_back(path[cur]);
        cur = par[cur];
    }
    assert(ans.back() == 'S');
    ans.pop_back();
    reverse(ans.begin(), ans.end());

    cout << ans.size() << endl;
    for (int i=0; i<ans.size(); ++i) {
        if (i > 0 && i % 60 == 0) cout << '\n';
        cout << ans[i];
    }

    cout << endl;
}

