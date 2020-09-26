#include "mushrooms.h"
#include <bits/stdc++.h>

using namespace std;

int brute(int n) {
    int ans = 1;
    int i=1;
    for (; i+1<n; i+=2) {
        int resp = use_machine({i, 0, i+1});
        ans += 2 - resp;
    }
    if (i < n) {
        ans += 1 - use_machine({0, i});
    }
    return ans;
}

const int X = 139;

int count_mushrooms(int n) {
    vector<int> a, b;
    a.push_back(0);

    int i=1;
    while (i+1<n && a.size() < X && b.size() < X) {
        int resp = use_machine({i, 0, i+1});
        if (resp == 0) {
            a.push_back(i);
            a.push_back(i+1);
        } else if (resp == 2) {
            b.push_back(i);
            b.push_back(i+1);
        } else if (resp == 1) {
            if (use_machine({0,i}) == 1) {
                a.push_back(i+1);
                b.push_back(i);
            } else {
                a.push_back(i);
                b.push_back(i+1);
            }
        } else assert(false);
        i += 2;
        //cerr << "a: ";for (int j=0; j<a.size(); ++j) cerr << a[j] << ' ';cerr << endl;
        //cerr << "b: ";for (int j=0; j<b.size(); ++j) cerr << b[j] << ' ';cerr << endl;
    }
    if (i+1 == n) {
        if (use_machine({0, i}) == 0) {
            return a.size() + 1;
        } else {
            return a.size();
        }
    }

    int ct[2] = {(int)a.size(), (int)b.size()};
    int sza = a.size(), szb = b.size();
    while (i < n) {
        if (sza >= szb) {
            vector<int> query;
            int pairs = sza >> 1;
            int cur = 0;
            for (int j=0; i<n && j<pairs; ++i, ++j, ++cur) {
                query.push_back(a[j]);
                query.push_back(i);
                query.push_back(a[pairs + j]);
            }
            int resp = use_machine(query);
            assert(resp % 2 == 0);
            resp >>= 1;
            ct[0] += cur - resp;
            ct[1] += resp;
        } else {
            vector<int> query;
            int pairs = szb >> 1;
            int cur = 0;
            for (int j=0; i<n && j<pairs; ++i, ++j, ++cur) {
                query.push_back(b[j]);
                query.push_back(i);
                query.push_back(b[pairs + j]);
            }
            int resp = use_machine(query);
            assert(resp % 2 == 0);
            resp >>= 1;
            ct[0] += resp;
            ct[1] += cur - resp;
        }
    }

    return ct[0];
}
