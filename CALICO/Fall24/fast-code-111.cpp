// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
#pragma GCC optimize ("trapv")
#define ll long long
#define int ll


using namespace std;

void c(vector<int>&a){for (int i:a){cout<<i<<" ";}cout<<"\n";}

vector<int> findadj(int n){
	set<int> adj;
	while (adj.size() < 3){
		cout << "SCAN " << n << endl;
		int a;
		cin >> a;
		adj.insert(a);
	}
	vector<int> yee;
	for (int i : adj){
		yee.push_back(i);
	}
	return yee;
}

int solve(){
	set<int> found;
	queue<vector<int>> q;
	q.push({1,0});
	while (!found.count(500)){
		int a = q.front()[0];
		int dist = q.front()[1];
		q.pop();
		if (found.count(a)){
			continue;
		}
		if (a == 500){
			cout << "SUBMIT " << dist << endl;
			string s;
			cin >> s;
			if (s == "WRONG_ANSWER"){
				throw(":(");
			}
			else{

			}
			break;

		}
		found.insert(a);
		vector<int> res = findadj(a);
		for (int i = 0; i < 3; i++){
			if (!found.count(res[i])){
				q.push({res[i],dist+1});
			}
		}
	}
    return 0;
}

signed main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--){
        solve();
    }
}
