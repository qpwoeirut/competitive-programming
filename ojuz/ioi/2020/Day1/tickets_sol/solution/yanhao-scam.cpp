#include "tickets.h"
#include <bits/stdc++.h>
using namespace std;
int c, s, k;
vector<vector<int>> d;
vector<int> tanks; // the location of the tanks

vector<vector<int>> ret;
int ord[1505];
set<tuple<int,int,int>> lt[1505]; // (position, company, ship)
set<tuple<int,int,int>> rg[1505]; // (position, company, ship)
void optimize_tickets(int h) {
    // optimize separately for each company
    for(int i=0; i<k; i++) {
        ord[i] = i;
    }
    sort(ord, ord+k, [](int x, int y)->bool {return tanks[x]>tanks[y];}); // now ord[i] gives the index of the i-th smallest position
    for(int j=0; j<s; j++) {
        ret[h][j] = -1; // first reset everything
    }
    // for each j=0 to k-1, pick either the j-th ship or the (s-k+j)-th ship
    assert(tanks[ord[0]] >= tanks[ord[1]]);
    // we pick them in reverse order
    for(int j=0; j<k; j++) {
        if(abs(tanks[ord[j]] - d[h][j]) < abs(tanks[ord[j]] - d[h][s-k+j])) {
            ret[h][s-k+j] = ord[j];
            if(get<0>(*rg[ord[j]].begin())>d[h][s-k+j]) {
                lt[ord[j]].insert(make_tuple(d[h][s-k+j], h, s-k+j));
            } else {
                rg[ord[j]].insert(make_tuple(d[h][s-k+j], h, s-k+j));
            }
        } else {
            ret[h][j] = ord[j];
            if(get<0>(*rg[ord[j]].begin())>d[h][j]) {
                lt[ord[j]].insert(make_tuple(d[h][j], h, j));
            } else {
                rg[ord[j]].insert(make_tuple(d[h][j], h, j));
            }
        }
    }
}
long long ans;
void optimize_tanks(int h) { // get all the medians, excluding company h
    for(int i=0; i<s; i++) {
        if(ret[h][i]!=-1) {
            lt[ret[h][i]].erase(make_tuple(d[h][i], h, i));
            rg[ret[h][i]].erase(make_tuple(d[h][i], h, i));
        }
    }
    // rebalance such that there are c/2-1 items on left, c/2 items on right
    for(int i=0; i<k; i++) {
        //assert(lt[i].size() + rg[i].size() == c-1);
        while((int) lt[i].size()>c/2-1) {
            rg[i].insert(*(--lt[i].end()));
            lt[i].erase(--lt[i].end());
        }
        while((int)rg[i].size()>c/2) {
            lt[i].insert(*rg[i].begin());
            rg[i].erase(rg[i].begin());
        }
    }
    for(int i=0; i<k; i++) {
        tanks[i] = get<0>(*rg[i].begin());
    }
    /*vector<int> v[k];
    for(int i=0; i<c; i++) {
        if(i==h) continue;
        for(int j=0; j<s; j++) {
            if(ret[i][j]!=-1) {
                v[ret[i][j]].push_back(d[i][j]);
            }
        }
    }
    for(int i=0; i<k; i++) {
        tanks[i] = get<0>(*rg[i].begin());
        nth_element(v[i].begin(), v[i].begin() + c/2 - 1, v[i].end());
        assert(tanks[i] == v[i][c/2-1]);
    }*/
}

void init() {
    ans = 0;
    vector<int> v[k];

    for(int i=0; i<c; i++) {
        for(int j=0; j<s; j++) {
            if(ret[i][j]!=-1) {
                v[ret[i][j]].push_back(d[i][j]);
            }
        }
    }
    for(int i=0; i<k; i++) {
        while((int)rg[i].size()>c/2) {
            lt[i].insert(*rg[i].begin());
            rg[i].erase(rg[i].begin());
        }
        nth_element(v[i].begin(), v[i].begin() + c/2 - 1, v[i].end());
        for(int j: v[i]) {
            ans += abs(v[i][c/2-1] - j);
        }
        assert(v[i][c/2-1]== get<0>(*(--lt[i].end())));
    }
}
void calc_ans() { // get all the medians, excluding company h
    ans = 0;
    vector<int> v[k];

    for(int i=0; i<c; i++) {
        for(int j=0; j<s; j++) {
            if(ret[i][j]!=-1) {
                v[ret[i][j]].push_back(d[i][j]);
            }
        }
    }
    for(int i=0; i<k; i++) {
        nth_element(v[i].begin(), v[i].begin() + c/2 - 1, v[i].end());
        for(int j: v[i]) {
            ans += abs(v[i][c/2-1] - j);
        }
    }
}

long long find_maximum(int _k, std::vector<std::vector<int>> _d) {
    d = _d;
    k = _k;
	c = d.size();
	s = d[0].size();
	tanks.resize(k); // the location of the tanks for each day
	for (int i = 0; i < c; i++) {
		std::vector<int> row(s);
		for (int j = 0; j < s; j++) {
			if (j < k) {
				row[j] = j;
			} else {
				row[j] = -1;
			}
		}
		ret.push_back(row);
	}
	calc_ans();
	long long prev_ans = 0;
	int ctr = 0;
	do {
        ctr++;
        prev_ans = ans;
        for(int h=0; h<c; h++) {
            optimize_tanks(h);
            optimize_tickets(h);
        }
        calc_ans();
	} while (ans!=prev_ans);
	assert(ctr<=5);
	allocate_tickets(ret);
	calc_ans();
	return ans;
}
