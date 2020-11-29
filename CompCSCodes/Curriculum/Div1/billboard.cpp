//billboard.cpp created at 11/12/20 15:17:17

#include <bits/stdc++.h>

using namespace std;

#define x first
#define y second

typedef pair<int,int> point;

point bl1, tr1, bl, tr;
bool inside(point pt) {
    return bl1.x <= pt.x && pt.x <= tr1.x && bl1.y <= pt.y && pt.y <= tr1.y;
}

int main() {
    freopen("billboard.in", "r", stdin);
    freopen("billboard.out", "w", stdout);
    cin >> bl.x >> bl.y >> tr.x >> tr.y;
    cin >> bl1.x >> bl1.y >> tr1.x >> tr1.y;

    point br(tr.x, bl.y), tl(bl.x, tr.y);
    int width = tr.x - bl.x;
    int height = tr.y - bl.y;
    if (inside(bl) && inside(tr)) {
        width = height = 0;
    } else if (inside(bl) && inside(br)) {
        height = tr.y - tr1.y;
    } else if (inside(tl) && inside(tr)) {
        height = bl1.y - bl.y;
    } else if (inside(bl) && inside(tl)) {
        width = tr.x - tr1.x;
    } else if (inside(br) && inside(tr)) {
        width = bl1.x - bl.x;
    }

    cout << width * height << endl;
}

