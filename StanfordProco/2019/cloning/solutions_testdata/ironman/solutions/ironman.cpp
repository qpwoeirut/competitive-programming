#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef long long ll;
typedef pair<int,int> pii;

const int N=1005;

int G[N][N];
map<int,int> og,now;
int main(){
    ios::sync_with_stdio(0);
    int n; cin>>n;
    for (int i=0;i<n;i++) for (int j=0;j<n;j++) cin>>G[i][j];
    if (n==1){
        cout<<"Y"<<endl; return 0;
    }
    bool ans=1;
    set<int> s; vector<int> v;
    //try to match first row
    for (int j=0;j<n;j++) s.insert(G[0][j]);
    v.assign(s.begin(),s.end());
    for (int i=0;i<n;i++) og[v[i]]=i; //maps from values to relative position from 0 to n-1
    
    for (int i=1;i<n;i++){
        s.clear(); now.clear();
        for (int j=0;j<n;j++) s.insert(G[i][j]);
        v.assign(s.begin(),s.end());
        for (int j=0;j<n;j++) now[v[j]]=j;
        for (int j=0;j<n;j++) if (og[G[0][j]]!=now[G[i][j]]) ans=0;
    }
    //columns
    s.clear(),og.clear();
    for (int i=0;i<n;i++) s.insert(G[i][0]);
    v.assign(s.begin(),s.end());
    for (int i=0;i<n;i++) og[v[i]]=i; //maps from values to relative position from 0 to n-1
    
    for (int i=1;i<n;i++){
        s.clear(); now.clear();
        for (int j=0;j<n;j++) s.insert(G[j][i]);
        v.assign(s.begin(),s.end());
        for (int j=0;j<n;j++) now[v[j]]=j;
        for (int j=0;j<n;j++) if (og[G[j][0]]!=now[G[j][i]]) ans=0;
    }
    if (ans) cout<<"Y"<<endl;
    else cout<<"N"<<endl;
    return 0;
}
