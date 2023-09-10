//comparing_code.cpp created at 09/09/23 20:58:14

#include <bits/stdc++.h>

using namespace std;
using pii=pair<int,int>;
#define fi first
#define se second

const int MN = 1000;
const int MX = 20000;
const int HAL_OFFSET = 10000;

int rbn[MN][3];
int hal[MN][3];
map<string, int> rbn_vars, hal_vars;

pii opts[MX];

bool remove_option(const int a, const int b) {
    if (a == -1 || b == -1) return false;

    if (opts[a].fi == b) {
        if (opts[a].se == -1) return true;
        opts[a] = pii(opts[a].se, -1);
    } else if (opts[a].se == b) {
        opts[a].se = -1;
    } //else assert(0);

    if (opts[b].fi == a) {
        if (opts[b].se == -1) return true;
        opts[b] = pii(opts[b].se, -1);
    } else if (opts[b].se == a) {
        opts[b].se = -1;
    } //else assert(0);

    return false;
}
bool update_single(const int a, const int b) {
    if (opts[a].fi == -1) {
        opts[a].fi = b;
        return false;
    } else if (opts[a].fi == b) {
        return remove_option(a, opts[a].se);
    } else if (opts[a].se == b) {
        return remove_option(a, opts[a].fi);
    } else return true;
}
bool update_double(const int a, const int b1, const int b2) {
    if (opts[a].fi == -1) {
        opts[a] = pii(b1, b2);
        return false;
    } else if (opts[a].fi == b1 && opts[a].se == b2) {
        return false;
    } else if (opts[a].fi == b1 || opts[a].fi == b2) {
        return remove_option(a, opts[a].se);
    } else if (opts[a].se == b1 || opts[a].se == b2) {
        return remove_option(a, opts[a].fi);
    } else return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int R, H;
    cin >> R >> H;

    string a, eq, b, plus, c;
    for (int r = 0; r < R; ++r) {
        cin >> a >> eq >> b >> plus >> c;
        assert(eq == "=" && plus == "+");
        if (rbn_vars.count(a) == 0) rbn_vars.emplace(a, rbn_vars.size());
        if (rbn_vars.count(b) == 0) rbn_vars.emplace(b, rbn_vars.size());
        if (rbn_vars.count(c) == 0) rbn_vars.emplace(c, rbn_vars.size());
        rbn[r][0] = rbn_vars[a];
        rbn[r][1] = min(rbn_vars[b], rbn_vars[c]);
        rbn[r][2] = max(rbn_vars[b], rbn_vars[c]);
    }
    for (int h = 0; h < H; ++h) {
        cin >> a >> eq >> b >> plus >> c;
        assert(eq == "=" && plus == "+");
        if (hal_vars.count(a) == 0) hal_vars.emplace(a, hal_vars.size() + HAL_OFFSET);
        if (hal_vars.count(b) == 0) hal_vars.emplace(b, hal_vars.size() + HAL_OFFSET);
        if (hal_vars.count(c) == 0) hal_vars.emplace(c, hal_vars.size() + HAL_OFFSET);
        hal[h][0] = hal_vars[a];
        hal[h][1] = min(hal_vars[b], hal_vars[c]);
        hal[h][2] = max(hal_vars[b], hal_vars[c]);
    }

    int answer = 0;
    for (int offset = -R + 1; offset < H; ++offset) {
        int max_possible = min(R, H);
        for (int r = R - 1; r >= 0; --r) {
            const int h = r + offset;
            ++max_possible;
            if (h < 0 || h >= H || answer >= max_possible) continue;
            
            for (int i = 0; r + i < R && h + i < H; ++i) {
                opts[rbn[r + i][0]] = opts[rbn[r + i][1]] = opts[rbn[r + i][2]] = 
                opts[hal[h + i][0]] = opts[hal[h + i][1]] = opts[hal[h + i][2]] = pii(-1, -1);
            }

            max_possible = 0;
            for (int i = 0; r + i < R && h + i < H; ++i) {
                if (update_single(rbn[r + i][0], hal[h + i][0])) break;
                if (update_single(hal[h + i][0], rbn[r + i][0])) break;

                if (update_double(rbn[r + i][1], hal[h + i][1], hal[h + i][2])) break;
                if (update_double(hal[h + i][1], rbn[r + i][1], rbn[r + i][2])) break;

                if (update_double(rbn[r + i][2], hal[h + i][1], hal[h + i][2])) break;
                if (update_double(hal[h + i][2], rbn[r + i][1], rbn[r + i][2])) break;

                max_possible = i + 1;
                answer = max(answer, i + 1);
            }
            //cerr << r << ' ' << h << ' ' << max_possible << endl;
        }
    }

    cout << answer << '\n';
}

