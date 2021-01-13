/*
ID: zhongbr1
TASK: frameup
LANG: C++14
*/

//frameup.cpp created at 01/02/21 22:12:19

#include <bits/stdc++.h>

using namespace std;

const int MN = 31;
const int MC = 31;
const int INIT = 50;

void chmn(int& a, const int b) {if (a>b) a=b;}
void chmx(int& a, const int b) {if (a<b) a=b;}

int N, M, K;
int G[MN][MN];

bool in[MC];
set<int> adj[MC];

int mnr[MC], mxr[MC], mnc[MC], mxc[MC];

vector<string> ans;
bool visited[MC];
int deg[MC];

void recurse(const string& cur) {
    if (cur.size() == K) {
        ans.push_back(cur + '\n');
        return;
    }
    for (int i=0; i<26; ++i) {
        if (in[i] && !visited[i] && deg[i] == 0) {
            visited[i] = true;
            for (const int v: adj[i]) --deg[v];
            recurse(cur + char('A' + i));
            for (const int v: adj[i]) ++deg[v];
            visited[i] = false;
        }
    }
}

int main() {
    freopen("frameup.in", "r", stdin);
    freopen("frameup.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;

    fill(mnr, mnr + MC, INIT);
    fill(mnc, mnc + MC, INIT);
    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            char c;
            cin >> c;
            G[i][j] = c == '.' ? 30 : c - 'A';

            chmn(mnr[G[i][j]], i);
            chmx(mxr[G[i][j]], i);
            chmn(mnc[G[i][j]], j);
            chmx(mxc[G[i][j]], j);
        }
    }

    for (int i=0; i<26; ++i) {
        if (mnr[i] < INIT) {
            in[i] = true;
            ++K;
        }

        for (int r=mnr[i]; r<=mxr[i]; ++r) {
            adj[i].insert(G[r][mnc[i]]);
            adj[i].insert(G[r][mxc[i]]);
        }
        for (int c=mnc[i]; c<=mxc[i]; ++c) {
            adj[i].insert(G[mnr[i]][c]);
            adj[i].insert(G[mxr[i]][c]);
        }
        adj[i].erase(i);

        for (const int u: adj[i]) ++deg[u];
    }
    //for (int i=0; i<26; ++i) { cerr << "====== " << i << " ======\n"; for (const int u: adj[i]) { cerr << u << ' '; } cerr << endl; }

    recurse("");

    for (const string& s: ans) cout << s;
}
