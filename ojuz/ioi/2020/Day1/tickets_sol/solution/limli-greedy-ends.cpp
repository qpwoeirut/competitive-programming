#include <bits/stdc++.h>

#include "tickets.h"
using namespace std;

typedef pair<int, int> ii;
typedef long long ll;

int n, s, k;

int magic[1510];
int cmp(int a, int b) {
    return magic[a] < magic[b];
}

long long find_maximum(int k1, vector<vector<int>> d) {
    k = k1;
    n = d.size();
    s = d[0].size();
    vector<vector<int>> answer;
    for (int i = 0; i < n; i++) {
        vector<int> row(s);
        for (int j = 0; j < s; j++) {
            row[j] = -1;
        }
        answer.push_back(row);
    }
    vector<deque<ii>> ticketsleft(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < s; j++) {
            ticketsleft[i].push_back(ii(d[i][j], j));
        }
        sort(ticketsleft[i].begin(), ticketsleft[i].end());
        magic[i] = ticketsleft[i][0].first + ticketsleft[i][s-1].first;
    }
    ll pipelength = 0;
    for (int day = 0; day < k; day++) {
        // printf("day %d\n", day);
        vector<int> order(n);
        for (int i = 0; i < n; i++) {
            order[i] = i;
        }
        sort(order.begin(), order.end(), cmp);
        vector<int> stuff(n);
        for (int i = 0; i < n; i++) {
            int ind = order[i];
            ii ship = ii(-1,-1);
            if (i < n / 2) {
                ship = ticketsleft[ind].front();
                ticketsleft[ind].pop_front();
                if (!ticketsleft[ind].empty())
                    magic[ind] += ticketsleft[ind].front().first;
            } else {
                ship = ticketsleft[ind].back();
                ticketsleft[ind].pop_back();
                if (!ticketsleft[ind].empty())
                    magic[ind] += ticketsleft[ind].back().first;
            }
            // printf("company %d: %d %d\n", ind, ship.first, ship.second);
            stuff[ind] = ship.first;
            answer[ind][ship.second] = day;
            magic[ind] -= ship.first;
        }
        sort(stuff.begin(), stuff.end());
        int med = stuff[n / 2];
        for (int i = 0; i < n; i++) {
            pipelength += abs(stuff[i] - med);
        }
    }
    allocate_tickets(answer);
    return pipelength;
}
