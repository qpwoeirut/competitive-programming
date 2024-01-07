#include <bits/stdc++.h>
//#pragma GCC optimize ("Ofast")
#pragma GCC optimize("unroll-loops")
//#pragma GCC target ("avx2")
#pragma GCC optimize ("trapv")
using namespace std;
 
#define MOD 1000000007
#define MOD2 998244353
#define MAXN 100005
#define MAXK 21
#define INF 2e9
#define INF2 2e18
#define ll long long
#define nl '\n'
#define pb push_back
#define pf push_front
#define fi first
#define se second
#define mp make_pair
typedef pair<int,int> pii; 
typedef pair<ll,ll> pll;
#define int long long


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	set<set<int>> s;
	for(int x = 1; x<= 1000000; x++){
        int y = x;
		set<int> u;
		u.insert(1);
		for(int i=2;i*i<=y;i++){
			if(y%i==0){
				u.insert(i);
			}
			while(y%i==0){
				y/=i;
			}
		}
		s.insert(u);
	}
	cout << s.size() << nl;
	for(auto x : s){
		for(auto y: x){
			cout << y << " ";
		}
		cout << nl;
	}
}
