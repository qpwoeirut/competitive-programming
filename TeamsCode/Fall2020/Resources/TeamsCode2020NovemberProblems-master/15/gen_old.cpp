#include<bits/stdc++.h>
#define uset unordered_set
#define umap unordered_map
using namespace std;
umap<int,set<int>> f;
int rand(const int min, const int max)
{
    return min + rand() % (max - min + 1);
}
int main()
{
    srand(time(0));
    const int n=rand(99990,100000);
    const int m=rand(4999990,10000000);
    cout<<n<<" "<<m<<endl;
    int s=rand(1,n);
    for (int i = 1; i <= n; i++)
    {
        if(i==s){
            continue;
        }
        int u=rand(1,n);
        while(u==i||f[i].find(u)!=f[i].end()){
            u=rand(1,n);
        }
        f[u].insert(i);
        cout<<u<<" "<<i<<endl;
    }
    
    for (int i = 0; i < m; i++)
    {
        const int a=rand(1,n);
        const int b=rand(1,n);
        cout<<a<<" "<<b<<endl;
    }
    return 0;
}
