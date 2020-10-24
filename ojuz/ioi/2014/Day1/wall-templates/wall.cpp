#include "wall.h"
#include <bits/stdc++.h>

using namespace std;

const int MN = 100005;

void chmn(int& a, const int b) {if (a>b) a=b;}
void chmx(int& a, const int b) {if (a<b) a=b;}

void solve_sub1(int N, int K, int op[], int left[], int right[], int height[], int finalHeight[]) {
    fill(finalHeight, finalHeight+N, 0);

    for (int i=0; i<K; ++i) {
        for (int j=left[i]; j<=right[i]; ++j) {
            if (op[i] == 1) {
                chmx(finalHeight[j], height[i]);
            } else {
                chmn(finalHeight[j], height[i]);
            }
        }
    }
}

multiset<int> add[MN][2], rem[MN][2];
void buildWall(int N, int K, int op[], int left[], int right[], int height[], int finalHeight[]){
    if (N <= 10000 && K <= 5000) {
        solve_sub1(N, K, op, left, right, height, finalHeight);
        return;
    }
    for (int i=0; i<K; ++i) {
        if (op[i] == 1) {
            add[left[i]][0].insert(height[i]);
            add[right[i]][1].insert(height[i]);
        } else {
            rem[left[i]][0].insert(height[i]);
            rem[right[i]][1].insert(height[i]);
        }
    }

    multiset<int> cur;
    cur.insert(0);
    for (int i=0; i<N; ++i) {
        cur.insert(add[i][0].begin(), add[i][0].end());

        finalHeight[i] = *cur.rbegin();

        for (multiset<int>::iterator it=add[i][1].begin(); it!=add[i][1].end(); ++it) {
            cur.erase(cur.find(*it));
        }
    }
    //for (int i=0; i<N; ++i) cerr << finalHeight[i] << ' '; cerr << endl;

    assert(cur.size() == 1 && *cur.begin() == 0);
    cur.clear();
    cur.insert(1001001001);
    for (int i=0; i<N; ++i) {
        cur.insert(rem[i][0].begin(), rem[i][0].end());

        chmn(finalHeight[i], *cur.begin());

        for (multiset<int>::iterator it=rem[i][1].begin(); it!=rem[i][1].end(); ++it) {
            cur.erase(cur.find(*it));
        }
    }
}

