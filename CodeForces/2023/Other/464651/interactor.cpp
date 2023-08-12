#include "testlib.h"
#include <chrono>
#include <random>
 
using namespace std;
typedef long long ll;
const int MAXN = 105, MAXK = 5;
typedef pair<int, int> pii;
const int TOTAL = 100, INF = 1e9 + 7;
int TELEPORT_PROBABILITY = 40, TELEPORT_INCREMENT = 5;

int adj[MAXN][MAXN];
ll dist[MAXN][MAXN];
int deg[MAXN];
ll ct = 101;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll rndv(ll l, ll r) {
    return uniform_int_distribution<ll>(l, r)(rng);
}

ll get_points (ll end_time, ll penalty, ll n)
{
    ct = end_time;
    return (1ll * n * n * n * (TOTAL + 1 - end_time) * (ll)sqrtl(TOTAL + 1 - end_time) - penalty * n * (ll)sqrtl(n))/(1ll * 50 * n * n * n);
}

ll block_penalty (ll v, ll t)
{
    return (100 - t + 1) * v * v * v * v;
}

ll move_penalty (ll t, ll d)
{
    ll fd = max(0ll, d - 1);
    return (100 - t + 1) * (ll)sqrtl(100 - t + 1) * fd * fd * fd * fd * fd * fd * fd;
}


 
int main(int argc, char* argv[])
{
    setName("Interactor");
    registerInteraction(argc, argv);
    for (int i = 0; i < MAXN; i++)
    {
        for (int j = 0; j < MAXN; j++)
        {
            dist[i][j] = INF;
        }
        dist[i][i] = 0;
    }
    
    // reads number of queries from test input file
    int n = inf.readInt();
    inf.readSpace();
    int m = inf.readInt();
    inf.readEoln();
    cout << n << " " << m << endl;
    for (int i = 0; i < m; i++)
    {
        int l = inf.readInt();
        inf.readSpace();
        int r = inf.readInt();
        cout << l << " " << r << endl;
        l--,r--;
        adj[l][r] = adj[r][l] = 1;
        dist[l][r] = dist[r][l] = 1;
        deg[l]++, deg[r]++;
        inf.readEoln();
    }
    
    for (int k = 0; k < n; k++) 
    {
		for (int i = 0; i < n; i++) 
        {
			for (int j = i + 1; j < n; j++) 
            {
				if (dist[i][k] + dist[k][j] < dist[i][j])
                {
					dist[i][j] = dist[j][i] = dist[i][k] + dist[k][j];
				}
			}
		}
	}
 
    int v = n - 1; //Bob's position
    int pl = 0; //Alice's position
    ll totp = 0;
    ll res = -1;
    bool prev = 0;
    for (int TIME = 1; TIME <= TOTAL; TIME++)
    {
        int cur = ouf.readInt();
        if (cur < 0 || cur > n + 1)
        {
            quitf(_wa, "invalid number to block");
        }
        ouf.readEoln();
        set<int> st;
        vector<int> cv;
        if (cur != 0 && cur != n + 1)
        {
            cv = ouf.readInts(cur, 1, n + 1);
            if (cv.size() != cur)
            {
                quitf(_wa, "incorrect number of nodes");
            }
            while (!ouf.seekEoln())
            {
                ouf.readToken();
            }
        }
        for (int i = 0; i < (cur == n + 1 ? 0 : cur); i++)
        {
            int x = cv[i];
            x--;
            st.insert(x);
        }
        
        totp = totp + block_penalty(cur != n + 1 ? cur : deg[pl] + 1, TIME);
        vector<pii> pos;
        bool tel = (prev || rndv(1, 100) <= TELEPORT_PROBABILITY);
        
        if (cur == n + 1)
        {
            TELEPORT_PROBABILITY += TELEPORT_INCREMENT;
        }
        if (tel && cur == n + 1)
        {
            tel = 0;
            prev = 1;
        } else
        {
            prev = 0;
        }
        
        for (int i = 0; i < n; i++)
        {
            if ((tel || adj[v][i]) && !st.count(i))
            {
                pos.push_back({dist[pl][i], i});
            }
        }
        
        sort(pos.rbegin(), pos.rend());
        
        int next = (pos.empty() ? v : pos[rndv(0, min((int)pos.size() - 1,MAXK))].second);
        
        int plv = ouf.readInt();
        plv--;
        if (plv < 0 || plv > n - 1)
        {
            quitf(_wa, "moving to invalid node");
        }
        ouf.readEoln();
        totp = totp + move_penalty(TIME, dist[pl][plv]);
        cout << next + 1 << endl;
        if (next == plv)
        {
            res = max(0ll, get_points(TIME, totp, n));
            break;
        }
        pl = plv;
        v = next;
    }
    
    if (res == -1)
    {
        tout << 0 << " " << ct << " " << totp << " " << 'n' << endl;
    } else
    {
        tout << res << " " << ct << " " << totp << " " << 'a' << endl;
    }

    ouf.readEof();
}
