#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef long long ll;
typedef pair<int,int> pii;

const int N=1e6+5;

int main(){
    ios::sync_with_stdio(0);
    int n; cin>>n;
    multiset<int> s; 
	for (int i=0;i<n;i++){
		int x; cin>>x;
		s.insert(x);
	}
	int ans=0;
	while (s.size()>1){
		int x=*s.begin(); s.erase(s.begin());
		int y=*s.begin(); s.erase(s.begin());
		ans+=x+y;
		s.insert(x+y);
	}
    cout<<ans<<endl;
    return 0;
}
