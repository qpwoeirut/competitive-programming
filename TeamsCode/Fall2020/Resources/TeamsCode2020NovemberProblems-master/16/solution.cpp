#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <string.h>
#include <utility>
#include <map>
#include <list>
#include <queue>
using namespace std;
typedef pair <int, int> pii;
typedef long long ll;
#define f first
#define s second

const int maxn = 1e6 + 10;

int n, med;
priority_queue <int, vector <int>, less <int> > lo;
priority_queue <int, vector <int>, greater <int> > hi;
int cnt, mode;
map <int, int> mp;

void med_ins(int x) {
    if (med < x) {
        if (hi.size() > lo.size()) {
            lo.push(hi.top());
            hi.pop();
            hi.push(x);
            med = (lo.top() + hi.top()) / 2;
        }
        else {
            hi.push(x);
            if (hi.size() > lo.size()) med = hi.top();
            else med = (lo.top() + hi.top()) / 2;
        }
    }
    else {
        if (lo.size() > hi.size()) {
            hi.push(lo.top());
            lo.pop();
            lo.push(x);
            med = (lo.top() + hi.top()) / 2;
        }
        else {
            lo.push(x);
            if (lo.size() > hi.size()) med = lo.top();
            else med = (lo.top() + hi.top()) / 2;
        }
    }
}

int main() {
    scanf("%d", &n);
    int mn=0, mx=0;
    ll sum=0;
    for (int i = 0; i < n; ++i) {
        int x; scanf("%d", &x);
        x ^= med; // decryption
        med_ins(x);
        mp[x]++;
        if (mp[x] >= cnt) {
            mode = x;
            cnt = mp[x];
        }
        if (!i) mn = mx = x;
        mn = min(mn, x);
        mx = max(mx, x);
        sum += x;
        printf("%d %d %lld %d %d\n", mn, mx, sum, med, mode);
    }
}

