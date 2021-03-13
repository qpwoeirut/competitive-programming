#include "bits/stdc++.h"
 
using namespace std;
 
#define              ll              long long
 
#define       forn(i,n)              for(int i=0;i<n;i++)
#define          all(v)              v.begin(), v.end()
#define         rall(v)              v.rbegin(),v.rend()
 
#define            pb                push_back
#define          sz(a)               (int)a.size()
#define         fastio               ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);

#define int long long
int get_max(vector<int> a, vector<int> b,int k)
{
    int n = sz(a);
    priority_queue<int> pA,pC,nA,nC;
    for(int i = 0;i < n;i++){
        int x = a[i];
        if(x > 0){
            pA.push(x);
        }else{
            nA.push(-x);
        }
    }
    for(int i = 0;i < n;i++){
        int x = b[i];
        if(x > 0){
            pC.push(x);
        }else{
            nC.push(-x);
        }
    }
    int ans = 0;
    while(k > 0 && sz(pA) && sz(nA) && sz(pC) && sz(nC)){
        int A = pA.top() * pC.top();
        int B = nA.top() * nC.top();
        if(A >= B){
            ans+=A;
            pA.pop();
            pC.pop();
        }else{
            ans+=B;
            nA.pop();
            nC.pop();
        }
        --k;
    }
    while(k > 0 && sz(pA) && sz(pC))
    {
        int A = pA.top() * pC.top();
        --k;
        ans+=A;
        pA.pop();
        pC.pop();
    }
    while(k > 0 && sz(nA) && sz(nC)){
        int B = nA.top() * nC.top();
        --k;
        ans+=B;
        nA.pop();
        nC.pop();
    }
    if(!k)return ans;
    vector<int> A,C;
    while(!pA.empty()){
        A.pb(pA.top());
        pA.pop();
    }
    while(!nA.empty())
    {
        A.pb(-nA.top());
        nA.pop();
    }
    while(!pC.empty())
    {
        C.pb(pC.top());
        pC.pop();
    }
    while(!nC.empty())
    {

        C.pb(-nC.top());
        nC.pop();
    }
    if(C.back() > 0)swap(A,C);
    int cnt = 0;
    int mx1 = 0,mx2=0,mx3=0,mx4=0,mx5=0,mx6=0,mx7=0,mx8=0;
    sort(all(A));
    sort(rall(C));
    for(int i = 0;i < k;i++){
        mx1+=A[i] * C[k-i-1];
    }
    for(int i = 0;i < k;i++){
        mx2+=C[i]*A[k-i-1];
    }
    sort(rall(A));
    sort(all(C));
    for(int i =0;i <k;i++){
        mx3+=C[i]*A[k-i-1];
    }
    for(int i =0;i < k;i++){
        mx4+=A[i]*C[k-i-1];
    }
    sort(all(A));
    sort(all(C));
    for(int i = 0;i < k;i++){
        mx5+=C[i]*A[k-i-1];
        mx6+=C[k-i-1]*A[i];
    }

    sort(rall(A));
    sort(rall(C));
    for(int i = 0;i < k;i++){
        mx7+=A[i]*C[k-1-i];
        mx8+=C[i]*A[k-i-1];
    }
    ans+=max({mx1,mx2,mx3,mx4,mx5,mx6,mx7,mx8});
    return ans;
}
void solve()
{
    int n,k;
    cin >> n >> k;
    vector<int> a(n),c(n);
    for(int i = 0;i < n;i++){
        int x;
        cin >> x;
        a[i] = x;
    }
    for(int i = 0;i < n;i++){
        int x;
        cin >> x;
        c[i] = x;
    }
    int mx = get_max(a,c,k);
    for(int i = 0;i < n;i++){
        c[i] = -c[i];
    }
    int mn = -get_max(a,c,k);
    cout << mn << " " << mx << '\n';
}
 
int32_t main()
{
    fastio;
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i)
    {
        cout << "Case #" << i << ": ";
        solve(); 
    }
}