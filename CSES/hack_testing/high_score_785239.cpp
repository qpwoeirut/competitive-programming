// https://cses.fi/problemset/hack/1673/entry/785239/

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
 
int main(){
	//freopen("input.txt", "r", stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m;
	cin>>n>>m;
	
	vector<tuple<int, int, ll> >edge(m);
	vector<ll>dist(n);
	
	for(int i=0; i<m; i++){
		int a,b;
		ll w;
		cin>>a>>b>>w;
		a--;
		b--;
		edge.push_back(make_tuple(a,b,w));
	}
	
	for(int i=0; i<n; i++)
		dist[i] = -1e18;
	
	bool changed;
	dist[0] = 0;
	for(int i=0; i<n; i++){
		changed = 0;
		for(auto e:edge){
			int a,b;
			ll w;
			tie(a,b,w) = e;
			if(dist[b] < w+dist[a]){
				dist[b] = w+dist[a];
				changed = 1;
			}
		}
	}
    cerr << dist[n-1] << endl;
	
	if(changed && dist[n-1] != 1)
		cout<<-1;
	else
		cout<<dist[n-1];
}

/*
GOTEM
4 4
1 2 -3
2 4 0
3 2 1
2 3 1

Also it seems somebody copied this submission so I hacked that too :kekw:
https://cses.fi/problemset/hack/1673/entry/877119/
*/
