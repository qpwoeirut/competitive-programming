#include <iostream>
#include <vector>
#include <array>

using namespace std;

using ll=long long;

const int MN = 600005;

ll dp[MN][2];
ll maximizeFun(const vector<array<int, 2>>& itinerary) {
    const int N = itinerary.size();
    for (int i=0; i<=N; ++i) {
        dp[i][0] = dp[i][1] = 0;
    }

    for (int i=0; i<N; ++i) {
        int nxt = min(i + itinerary[i][1] + 1, N);
        if (i) {
            dp[i][0] = max(dp[i][0], dp[i-1][0]);
            dp[i][1] = max(dp[i][1], dp[i-1][1]);
        }
        dp[nxt][0] = max(dp[nxt][0], dp[i][0] + itinerary[i][0]);
        dp[nxt][1] = max(dp[nxt][1], dp[i][1] + itinerary[i][0]);
        dp[nxt][1] = max(dp[nxt][1], dp[i][0] + itinerary[i][0] * 2);
    }

    ll ans = 0;
    for (int i=0; i<=N; ++i) {
        ans = max(ans, dp[i][0]);
        ans = max(ans, dp[i][1]);
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    for (cin >> t; t > 0; t--) {
        cin.get();
        vector<array<int, 2>> itinerary;
        int numEvents;
        for (cin >> numEvents; numEvents > 0; numEvents--) {
            int funValue;
            int energyRequirement;
            cin >> funValue;
            cin >> energyRequirement;
            itinerary.push_back(array<int, 2> {funValue, energyRequirement});     
            if (numEvents > 1) {
                cin.get();
            }
        }
        cout << maximizeFun(itinerary) << '\n';
    }
}

