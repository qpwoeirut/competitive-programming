#include <bits/stdc++.h>
#include "holiday.h"

using namespace std;

typedef long long ll;

ll findMaxAttraction(int n, int start, int d, int attraction[]) {
    ll ans = 0;
    for (int i=0; i<=start; ++i) {
        multiset<ll> in;
        ll sum = 0;
        for (int j=i; j<n; ++j) {
            in.insert(attraction[j]);
            sum += attraction[j];

            if (j >= start) {
                ll travel = min((start - i) + (j - i), (j - start) + (j - i));

                ll rem = d - travel;
                if (rem <= 0) {
                    continue;
                }
                while (in.size() > rem) {
                    sum -= *in.begin();
                    in.erase(in.begin());
                }

                //cerr << "i,j,sum,rem: " << i << ' '<< j << ' ' << sum << ' ' << rem << endl;
                //cerr << "in:"; for (auto it=in.begin(); it!=in.end(); ++it) { cerr << ' ' << *it; } cerr << endl;

                ans = max(ans, sum);
            }
        }
    }

    return ans;
}
