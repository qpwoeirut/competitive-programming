// Helping debug teammate's code
// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
#pragma GCC optimize ("trapv")
#define ll long long
#define int ll

using namespace std;

void c(vector<int>&a){for(int i:a){cout<<i<<" ";}cout<<"\n";}
void cn(vector<int>&a){for(int i:a){cout<<i<<"\n";}}
void d(vector<int>&a){for(int i=0;i<a.size();i++){cin>>a[i];}}

int MOD = 998244353;
int gcdExtended(int a, int b, int* x, int* y)
{
    if (a == 0) {
        *x = 0, *y = 1;
        return b;
    }
    int x1, y1;
    int gcd = gcdExtended(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    return gcd;
}
int inv(int a) {
    int A = a;
    int M = MOD;
    int x, y;
    int g = gcdExtended(A, M, &x, &y);
    if (g != 1)
        assert(false);
    else {
        int res = (x % M + M) % M;
        return res;
    }
}
int add(int a, int b){
    return ((a%MOD)+(b%MOD))%MOD;
}
int sub(int a, int b){
    return ((a%MOD)-(b%MOD)+MOD)%MOD;
}
int mul(int a, int b){
    return ((a%MOD)*(b%MOD))%MOD;
}
int fra(int a, int b){
    return ((a%MOD)*inv(b))%MOD;
}
int binpow(int a, int b) {
    a %= MOD;
    int res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}


int solve(){
    return 0;
}

vector<int> dfs(map<int, vector<int>> &adj, vector<int> &arr, vector<int> &barr, int depth, int at, int par){
    vector<int> curbest = {0,0};
    for (int i = 0; i < adj[at].size(); i++){
        int newval = adj[at][i];
        if (newval == par){
            continue;
        }
        vector<int> res = dfs(adj, arr, barr, depth + 1, newval, at);
        if (depth%2 == 0){
            if (res[0] > curbest[0]){
                curbest = res;
            }
            else if (res[0] == curbest[0]){
                curbest[1] = max(curbest[1], res[1]);
            }
        }
        else{
            if (res[1] > curbest[1]){
                curbest = res;
            }
            else if (res[1] == curbest[1]){
                curbest[0] = max(curbest[0], res[0]);
            }
        }
    }
    if (arr[at] == 1){
        curbest[0] ++;
    }
    if (barr[at] == 1){
        curbest[1] ++;
    }
    return curbest;
}

signed main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n,m;
    cin >> n >> m;
    vector<string> arr(n);
    for (int i = 0; i < n; i++){
        cin >> arr[i];
    }
    vector<vector<int>> yee(m);
    for (int i = 0; i < m; i++){
        int start = -1;
        int end = -1;
        for (int j = 0; j < n; j++){
            if (start == -1 && arr[j][i] == 'X'){
                start = j;
            }
            if (start != -1 && end == -1 && arr[j][i] == '.'){
                end = j;
            }
        }
        if (end == -1){
            end = n;
        }
        yee[i] = {start, end};
    }
    int best = LLONG_MAX;
    for (int i = 0; i <= m; i++){
        multiset<int> startr;
        multiset<int> endr;
        multiset<int> startl;
        multiset<int> endl;
        for (int j = i; j < m; j++){
            if (yee[j][0] != -1){
                startr.insert(yee[j][0]);
                endr.insert(yee[j][1]);
            }
        }
        for (int j = 0; j <= i; j++){
            int vertstroke = i-j;
            int msr,mer, msl, mel;
            if (startr.size() == 0){
                msr = -1;
            }
            else{
                msr = *startr.begin();
            }
            if (endr.size() == 0){
                mer = -1;
            }
            else{
                mer = *prev(endr.end());
            }
            if (startl.size() == 0){
                msl = -1;
            }
            else{
                msl = *startl.begin();
            }
            if (endl.size() == 0){
                mel = -1;
            }
            else{
                mel = *prev(endl.end());
            }
            int minstart = LLONG_MAX;
            int maxend = -1;
            if (msr != -1){
                minstart = min(minstart, msr);
            }
            if (msl != -1){
                minstart = min(minstart, msl);
            }
            if (mel != -1){
                maxend = max(maxend, mel);
            }
            if (mer != -1){
                maxend = max(maxend, mer);
            }
            int totstroke = vertstroke + maxend - minstart;
            if (maxend == -1){
                totstroke = vertstroke;
            }
            best = min(best, totstroke);
            // cout << totstroke << " " << maxend << " " << minstart << " " << i << " " << j << "\n";
            if (j < m && yee[j][0] != -1){
                startl.insert(yee[j][0]);
                endl.insert(yee[j][1]);
            }
        }
    }
    cout << best << "\n";
}
/*
1 1
.
1 1
X
4 1
.
X
X
.
1 4
.XXX
6 3
X..
X..
XXX
XXX
..X
..X

6 5
XX...
.X...
.XXX.
.XXX.
...X.
...XX

6 7
XXX....
..X....
..XXX..
..XXX..
....X..
....XXX

8 8
..X.....
..XXX...
..XXXX..
XXXXXXXX
..XXXXX.
...XXX..
....X...
....X...

6 10
..X.......
..X.......
XXXXXXXXXX
XXXXXXXXXX
.......X..
.......X..

10 6
..XX..
..XX..
..XXXX
..XX..
..XX..
..XX..
..XX..
XXXX..
..XX..
..XX..
*/
