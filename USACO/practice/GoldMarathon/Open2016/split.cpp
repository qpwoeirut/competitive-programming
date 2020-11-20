#include <bits/stdc++.h>

using namespace std;

#define x first
#define y second

typedef long long ll;
typedef pair<ll,ll> Cow;

void chmn(ll& a, const ll b) {if (a>b) a=b;}
void chmx(ll& a, const ll b) {if (a<b) a=b;}

const int MN = 50005;

int N;
Cow A[MN];

struct cmp_y {
    inline const bool operator()(const Cow& a, const Cow& b) const {
        if (a.y == b.y) return a.x < b.x;
        return a.y < b.y;
    }
};

int main() {
    freopen("split.in", "r", stdin);
    freopen("split.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    ll mnx = 1e9, mny = 1e9, mxx = 1, mxy = 1;
    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i].x >> A[i].y;
        chmn(mnx, A[i].x);
        chmn(mny, A[i].y);
        chmx(mxx, A[i].x);
        chmx(mxy, A[i].y);
    }

    ll ans = (mxx - mnx) * (mxy - mny);

    sort(A, A+N);
    set<Cow, cmp_y> lft, rht;
    lft.insert(A[0]);
    for (int i=1; i<N; ++i) {
        rht.insert(A[i]);
    }
    
    ll best = 1e18;
    for (int i=1; i<N; ++i) {
        if (A[i-1].x < A[i].x) {
            ll l_area = (A[i-1].x - mnx) * (lft.rbegin()->y - lft.begin()->y);
            ll r_area = (mxx - A[i].x) * (rht.rbegin()->y - rht.begin()->y);

            //cerr << i << ' ' << l_area << ' ' << r_area << endl;
            chmn(best, l_area + r_area);
        }

        rht.erase(A[i]);
        lft.insert(A[i]);
    }


    sort(A, A+N, cmp_y());
    set<Cow> bot, top;
    bot.insert(A[0]);
    for (int i=1; i<N; ++i) {
        top.insert(A[i]);
    }

    for (int i=1; i<N; ++i) {
        if (A[i-1].y < A[i].y) {
            ll b_area = (A[i-1].y - mny) * (bot.rbegin()->x - bot.begin()->x);
            ll t_area = (mxy - A[i].y) * (top.rbegin()->x - top.begin()->x);

            //cerr << i << ' ' << b_area << ' ' << t_area << endl;
            chmn(best, b_area + t_area);
        }

        top.erase(A[i]);
        bot.insert(A[i]);
    }

    //cerr << ans << endl;
    //cerr << best << endl;
    cout << ans - best << endl;
}

