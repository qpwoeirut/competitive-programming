#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef long long ll;
typedef pair<ll,ll> pii;


vector<int> v;
ll lcm(ll a, ll b){
    ll g=__gcd(a,b);
    return b*(a/g);
}
pii solve(vector<int> &v){
    vector<pii> f;
    for (int i=1;i<v.size();i++){
        ll a=v[i]*v[0],b=abs(v[i]-v[0]);
        ll g=__gcd(a,b);
        a/=g,b/=g;
        f.push_back({a,b});
    }
    pii ans=f[0];
    for (int i=1;i<f.size();i++){
        ll d=lcm(ans.second,f[i].second);
        ll n=lcm(ans.first*(d/ans.second),f[i].first*(d/f[i].second));
        ll g=__gcd(n,d);
        n/=g,d/=g;
        ans={n,d};
    }
    return ans;
}
int main(){
    ios::sync_with_stdio(0);
    int n; cin>>n;
    while (n--){
        int x; cin>>x;
        v.push_back(x);
    }
    pii ans=solve(v);
    cout<<ans.first<<" "<<ans.second<<endl;
    return 0;
}
