#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef long long ll;
typedef pair<int,int> pii;

const int N=1005;
const ld PI = acos(-1.0);
struct point{
  ld x,y,z;  
};
ld minH(point a, point b){
    ld ang=acos(a.x*b.x+a.y*b.y+a.z*b.z);
    return 1.0/cos(ang/2.0)-1.0;
}

int par[N];
int find(int a){
    if (par[a]==0) return a;
    return par[a]=find(par[a]);
}
bool unite(int a, int b){
    int aR=find(a),bR=find(b);
    if (aR==bR) return 0;
    par[aR]=bR; return 1;
}
int main(){
    ios::sync_with_stdio(0);
    int n; cin>>n;
    vector<point> v;
    for (int i=0;i<n;i++){
        ld theta,phi; char c,d;
        cin>>theta>>c>>phi>>d;
        if (c=='S') theta*=-1;
        if (d=='W') phi*=-1; 
        theta = theta * (PI/180.0);
        phi=phi*(PI/180.0); 
        
        point p; 
        p.x=sin(phi)*cos(theta),p.y=cos(phi)*cos(theta),p.z=sin(theta);
        v.push_back(p);
    }
    vector<pair<ld,pii>> edges;
    for (int i=0;i<n;i++) for (int j=i+1;j<n;j++) edges.push_back({minH(v[i],v[j]),{i,j}});
    sort(edges.begin(),edges.end());
    int cmp=n; ld ans=0;
    for (int i=0;i<edges.size();i++){
        if (unite(edges[i].second.first,edges[i].second.second)){
            cmp--;
            ans=edges[i].first;
        }
    }
    cout<<fixed<<setprecision(10)<<ans<<endl;
    return 0;
}
