#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef long long ll;
typedef pair<int,int> pii;

const int N=10005;
bool isC[N];
vector<ll> primes;

int main(){
    ios::sync_with_stdio(0);
    int t; cin>>t;
    for (int i=2;i*i<N;i++) if (!isC[i]){
        for (int j=i*i;j<N;j+=i) {
            isC[j]=1;
        }
    }
    for (int i=2;i<N;i++) if (!isC[i]) primes.push_back(i);
    while (t--){
        ll x; cin>>x;
        ll n=1,m=1;
        if (x==1) n=4,m=8;
        for (ll p:primes) if (x%p==0){
            ll e=0;
            while (x%p==0){
                e++; x=x/p;
            }
            int a,b;
            if (e<3) a=e,b=e;
            else b=e%3,a=(2*b+e)/3;
            n=n*pow(p,a);
            m=m*pow(p,b);
        }
        if (x!=1) n*=x,m*=x;
	if (n==m) n*=4LL,m*=8LL;
        cout<<n<<" "<<m<<endl;
    }
    
    return 0;
}
