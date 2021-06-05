#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef long long ll;
typedef pair<int,int> pii;

const int N=1e6+5;

int main(){
    ios::sync_with_stdio(0);
    int n; cin>>n;
    string s; cin>>s; 
    s.erase(unique(s.begin(),s.end()),s.end());
    int ans=0;
    for (int i=1;i<s.size();i++) if (s[i]=='0') ans++;
    cout<<ans<<endl;
    return 0;
}
