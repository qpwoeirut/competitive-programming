#include "plants.h"
#include <bits/stdc++.h>
using namespace std;
// subtask 1
vector<int> prefix_sum;
int n;
void init(int k, std::vector<int> r) {
	n = r.size();
	prefix_sum.push_back(0);
	for(int i: r) {
        prefix_sum.push_back(prefix_sum.back()+i);
	}
}

int compare_plants(int x, int y) {
    if(x>y) return -compare_plants(y,x);
    if(prefix_sum[x]==prefix_sum[y]) return 1;
    if(prefix_sum[y]==prefix_sum[n] && prefix_sum[0]==prefix_sum[x]) return -1;
    if(prefix_sum[x]-x==prefix_sum[y]-y) return -1;
    if(prefix_sum[y]-y==prefix_sum[n]-n && prefix_sum[0]==prefix_sum[x]-x) return 1;
    return 0;
}
