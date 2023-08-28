//scissors_and_tape.cpp created at 09/20/20 10:14:40

#include <bits/stdc++.h>

using namespace std;

#define x first
#define y second
#define FI first
#define SE second

typedef pair<int,int> pii;
typedef pair<pii,pii> ppii;

vector<ppii> shapes, loc;
vector<bool> in;

void solve(int cur, const ppii& b) { 
    ppii a = shapes[cur];
    int ah = a.SE.y - a.FI.y;
    int aw = a.SE.x - a.FI.x;
    int bh = b.SE.y - b.FI.y;
    int bw = b.SE.x - b.FI.x;
    //cerr << a.FI.x << ' ' << a.FI.y << ", " << a.SE.x << ' ' << a.SE.y << endl;
    //cerr << b.FI.x << ' ' << b.FI.y << ", " << b.SE.x << ' ' << b.SE.y << endl;
    //cerr << ah << 'x' << aw << ' ' << bh << 'x' << bw << endl;
    if (ah == bh && aw == bw) {
        loc[cur] = b;
        return;
    }
    in[cur] = false;

    ppii nxt;
    if (ah > bh) {
        shapes.push_back(ppii(a.FI, pii(a.SE.x, a.FI.y + bh)));
        loc.push_back(ppii(b.FI, pii(b.FI.x + aw, b.SE.y)));
        in.push_back(true);

        shapes.push_back(ppii(pii(a.FI.x, a.FI.y + bh), a.SE));
        loc.push_back(shapes.back());
        in.push_back(true);

        nxt = ppii(pii(b.FI.x + aw, b.FI.y), b.SE);
    } else if (aw > bw) {
        shapes.push_back(ppii(a.FI, pii(a.FI.x + bw, a.SE.y)));
        loc.push_back(ppii(b.FI, pii(b.SE.x, b.FI.y + ah)));
        in.push_back(true);

        shapes.push_back(ppii(pii(a.FI.x + bw, a.FI.y), a.SE));
        loc.push_back(shapes.back());
        in.push_back(true);

        nxt = ppii(pii(b.FI.x, b.FI.y + ah), b.SE);
    } else assert(false);

    assert(shapes.size() >= 3);
    cout << "scissors" << '\n';
    cout << shapes.size() - 3 << ' ' << 2 << '\n';
    ppii o1 = shapes[shapes.size() - 2], o2 = shapes.back();
    cout << "4 " << o1.FI.x << ' ' << o1.FI.y << ' ' << o1.FI.x << ' ' << o1.SE.y << ' ' << o1.SE.x << ' ' << o1.SE.y << ' ' << o1.SE.x << ' ' << o1.FI.y << endl;
    cout << "4 " << o2.FI.x << ' ' << o2.FI.y << ' ' << o2.FI.x << ' ' << o2.SE.y << ' ' << o2.SE.x << ' ' << o2.SE.y << ' ' << o2.SE.x << ' ' << o2.FI.y << endl;

    solve(shapes.size() - 1, nxt);
}

int sx[4], sy[4];
ppii construct() {
    pii lower_left(*min_element(sx, sx+4), *min_element(sy, sy+4));
    pii upper_right(*max_element(sx, sx+4), *max_element(sy, sy+4));
    return ppii(lower_left, upper_right);
}


int main() {
    int a;
    cin >> a;
    assert(a == 4);
    for (int i=0; i<a; ++i) {
        cin >> sx[i] >> sy[i];
    }
    shapes.push_back(construct());
    loc.push_back(shapes[0]);
    in.push_back(true);

    int b;
    cin >> b;

    assert(b == 4);
    for (int i=0; i<b; ++i) {
        cin >> sx[i] >> sy[i];
    }

    solve(0, construct());

    int ct = 0;
    for (int i=0; i<in.size(); ++i) {
        if (in[i]) {
            ++ct;
        }
    }

    cout << "tape" << '\n';
    cout << ct;
    for (int i=0; i<in.size(); ++i) {
        if (in[i]) {
            cout << ' ' << i;
        }
    }
    cout << '\n';
    for (int i=0; i<in.size(); ++i) {
        if (in[i]) {
            ppii out = loc[i];
            cout << "4 " << out.FI.x << ' ' << out.FI.y << ' ' << out.FI.x << ' ' << out.SE.y << ' ' << out.SE.x << ' ' << out.SE.y << ' ' << out.SE.x << ' ' << out.FI.y << '\n';
        }
    }

    cout << "4 " << sx[0] << ' ' << sy[0] << ' ' << sx[1] << ' ' << sy[1] << ' ' << sx[2] << ' ' << sy[2] << ' ' << sx[3] << ' ' << sy[3] << endl;
}
