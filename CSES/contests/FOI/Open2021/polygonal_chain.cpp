//polygonal_chain.cpp created at 01/29/21 22:20:43

#include <bits/stdc++.h>

using namespace std;

const int MN = 100005;

int N;
int A[MN];
string dir;

bool intersect(const int x1, int y1, int y2, int x3, int x4, const int y3) {
    if (x3 > x4) swap(x3, x4);
    if (y1 > y2) swap(y1, y2);
    //cerr << x1 << ' ' << y1 << ' ' << y2 << ' ' << x3 << ' ' << x4 << ' ' << y3 << endl;
    return (x3 <= x1 && x1 <= x4) && (y1 <= y3 && y3 <= y2);
}

int ord[MN], pos[MN];
int vert_seg[MN][3], hor_seg[MN][3];
int ans[MN];
bool check() {
    //for (int i=0; i<N; ++i) { cerr << ord[i] << ' '; } cerr << endl;
    int x = 0;
    
    int vidx = 0, hidx = 0;
    for (int i=0; i<N; ++i) {
        hor_seg[hidx][0] = x;
        x += A[i] * ((i & 1) ? -1 : +1);
        hor_seg[hidx][1] = x;
        hor_seg[hidx][2] = pos[i];
        ++hidx;

        if (i+1 < N) {
            const int p = pos[i];
            const int tar = pos[i+1];

            vert_seg[vidx][0] = x;
            vert_seg[vidx][1] = p;
            vert_seg[vidx][2] = tar;
            if ((dir[i] == 'D') ^ (p < tar)) return false;
            ++vidx;
            ans[i] = abs(p - tar);
        }
    }

    for (int i=0; i<hidx; ++i) {
        for (int j=0; j<vidx; ++j) {
            if (i == j || i == j + 1) continue;
            //cerr << i << ' ' << j << endl;
            if (intersect(vert_seg[j][0], vert_seg[j][1], vert_seg[j][2], hor_seg[i][0], hor_seg[i][1], hor_seg[i][2])) return false;
        }
    }

    cout << "YES\n";
    for (int i=0; i<N-1; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << endl;
    return true;
}

bool gen(const int idx, const int prev, const int inc) {
    if (idx == N) {
        return check();
    }
    for (int i=prev+inc; 0 <= i && i < N; i+=inc) {
        if (ord[i] == -1) {
            ord[i] = idx;
            pos[idx] = i;
            if (gen(idx+1, i, dir[idx] == 'D' ? +1 : -1)) return true;
            ord[i] = -1;
        }
    }

    return false;
}

void brute() {
    fill(ord, ord+N, -1);
    dir.push_back('D'); // dummy
    if (!gen(0, -1, 1)) {
        cout << "NO\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    cin >> dir;

    if (N <= 15) {
        brute();
        return 0;
    } else {
        assert(false);
    }
}

