#include<bits/stdc++.h>
using namespace std;

const int maxn = 1000;
int n;
double lon[maxn], lat[maxn];
bool dir[2][maxn];
double x[maxn], y[maxn], z[maxn]; // assuming height = 0
double pi = 4 * atan(1);

vector<int> adj[maxn];
bool vis[maxn];
int num_vis;

void dfs(int i) {
    num_vis += 1;
    vis[i] = 1;

    for (auto j : adj[i]) {
        if (!vis[j]) {
            dfs(j);
        }
    }
}

bool solve(double height) {
    num_vis = 0;
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < n; i++) {
        adj[i].clear();
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                double dist = (1 + height) * sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]) + (z[i] - z[j]) * (z[i] - z[j]));
                double mid = sqrt((1+height) * (1+height) - dist * dist / 4);

                if (mid > 1) {    
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }
    }

    dfs(0);

    return num_vis == n;
}


int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;

    for (int i = 0; i < n; i++) {
        double lo, la; char dir1, dir2;
        cin >> la >> dir1 >> lo >> dir2;

        lon[i] = lo;
        dir[0][i] = dir2 == 'E';
        lat[i] = la;
        dir[1][i] = dir1 == 'N';
    }
    
    for (int i = 0; i < n; i++) {
        x[i] = (1 - 2 * dir[0][i]) * sin(lon[i] * pi / 180) * cos(lat[i] * pi / 180);
        y[i] = cos(lon[i]) * cos(lat[i] * pi / 180);
        z[i] = (1 - 2 * dir[1][i]) * sin(lat[i] * pi / 180);
        //cout << x[i] << ' ' << y[i] << ' ' << z[i] << '\n';
    }

    double l = 0, r = 1e9;
    while (r - l > 1e-12) {
        double m = (r + l) / 2;
        if (solve(m)) {
            r = m;
        }
        else {
            l = m;
        }
    }

    cout << l;
}
