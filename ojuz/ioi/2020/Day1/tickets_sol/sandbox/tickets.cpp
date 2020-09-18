#include "tickets.h"
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

typedef long long int lli;
typedef pair<lli, lli> pii;

long long find_maximum(int k, vector<vector<int>> d) {
    // Number of companies
    int c = d.size();
    // tickets per company
	int s = d[0].size();

    // Sort each company's tickets by their distance
    // o[company][place] => index of ship which is <place>th from left
    vector<vector<int>> o;
    o.resize(c);
    for (int i = 0; i < c; i++) {
        o[i].resize(s);
        for (int j = 0; j < s; j++) {
            o[i][j] = j;
        }
        sort(o[i].begin(), o[i].end(), [&](const int &a, const int &b) {
            return d[i][a] < d[i][b];
        });
    }

    // d_o(company, place) => distance of ship which is <place>th form left
    auto d_o = [&](const int &a, const int &b) {
        return d[a][o[a][b]];
    };

    // gain: (change to cost by turning a - into a +, company index)
    priority_queue<pii> gain;

    // Total cost of the arrangement
    lli cost = 0;

    // plus_count[company] => How many +s the company will send
    vector<int> plus_count;
    plus_count.resize(c, 0);

    for (int i = 0; i < c; i++) {
        for (int j = 0; j < k; j++) {
            // First incur cost of all -s
            cost -= d_o(i, j);
        }
        // Queue a possible - to +
        gain.push(
            pii(
                d_o(i, s - 1 - plus_count[i])
                + d_o(i, k - 1 - plus_count[i]),
                i
            )
        );
    }

    // Take ck/2 +s
    for (int i = 0; i < c * k / 2; i++) {
        pii top = gain.top(); gain.pop();
        cost += top.first;

        // If the company hasnt reached k +s, queue another possible +
        int this_company = top.second;
        plus_count[this_company]++;
        if (plus_count[this_company] < k) {
            gain.push(
                pii(
                    d_o(this_company, s - 1 - plus_count[this_company])
                    + d_o(this_company, k - 1 - plus_count[this_company]),
                    this_company
                )
            );
        }
    }

    // Empty out the priority queue, will use again later
    while (!gain.empty()) gain.pop();

    // gain: (+s remaining, company index)
    for (int i = 0; i < c; i++) {
        gain.push(pii(plus_count[i], i));
    }

    // minus_count[company] => How many -s the company has sent so far
    vector<int> minus_count;
    minus_count.resize(c, 0);

    // Prepare answer vector dimensions and fill with -1s
    vector<vector<int>> answer;
    answer.resize(c);
    for (int i = 0; i < c; i++) {
        answer[i].resize(s, -1);
    }

    // take[company] => Does this company send a + in this days
    vector<int> take;
    take.resize(c, 0);

    // Simulate k days of tickets
    for (int i = 0; i < k; i++) {
        // Pick c/2 companies with the most +s left
        for (int j = 0; j < c / 2; j ++) {
            take[gain.top().second] = 1;
            gain.pop();
        }

        // Check if each company sent a - or +, and change answer accordingly
        for (int j = 0; j < c; j++) {
            if (take[j]) {
                // Company j sent a + this round, send the smallest +
                // Queue the company back
                answer[j][o[j][s - plus_count[j]]] = i;
                plus_count[j]--;
                gain.push(pii(plus_count[j], j));
            } else {
                // Company j sent a - this round, send the smallest -
                answer[j][o[j][minus_count[j]]] = i;
                minus_count[j]++;
            }
            take[j] = 0;
        }
    }

    // Return to grader
    allocate_tickets(answer);
    return cost;
}
