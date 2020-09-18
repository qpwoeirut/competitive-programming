#include "tickets.h"
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
vector<set<pair<ll,ll> > > se;
int cur[1505];
long long find_maximum(int k, vector<vector<int>> d) {
    ll c = d.size();
    ll s = d[0].size();
    ll sum =0 ,a,b,x,maxn,minx,y,z;
    vector<vector<int>> answer;
    for (int i = 0; i < c; i++) {
        vector<int> row;
        for(int j=0;j<s;j++)row.push_back(-1);
        answer.push_back(row);
    }
    ll i,j;
    for(i=0;i<c;i++){
        set<pair<ll,ll> > temp;
        for(j=0;j<s;j++){
            temp.insert(make_pair(d[i][j],j));
        }
        se.push_back(temp);
    }
    for(i=0;i<k;i++){
        vector<tuple<ll,int,int> > v;
        y = se[0].size();
        for(j=0;j<c;j++){
            auto it = *se[j].begin();
            auto it2 = *(--se[j].end());
            cur[j] = it2.second;
            sum+=it2.first;
            v.push_back(make_tuple(it.first+it2.first,j,it.second));
        }
        sort(v.begin(),v.end());
        for(j=0;j<c/2;j++){
            tie(a,b,x) = v[j];
            sum-=a;
            se[b].erase(se[b].begin());
            cur[b] = x;
        }
        for(j=0;j<c;j++)answer[j][cur[j]] = i;
        for(j=0;j<c;j++){
            if(se[j].size()==y){
                se[j].erase(--se[j].end());
            }
        }
    }

    allocate_tickets(answer);
    return sum;
}
