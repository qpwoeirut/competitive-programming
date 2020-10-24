#include <bits/stdc++.h>
#include "rail.h"

using namespace std;

#define dist first
#define idx second

typedef pair<int,int> pii;

const int MN = 5001;

pii station[MN];

void findLocation(int N, int first, int location[], int stype[]) {
    for (int i=0; i<N; ++i) {
        station[i].dist = getDistance(0, i);
        station[i].idx = i;
        location[i] = -1;
    }

    sort(station+1, station+N);
    int left = 0, right = station[1].idx; 

    location[0] = first;
    stype[0] = 1;
    location[right] = first + station[1].dist;
    stype[right]= 2;

    int dst = station[1].dist;
    for (int i=2; i<N; ++i) {
        cerr << i << endl;
        deque<pii> cur;
        for (int j=0; j<N; ++j) {
            if (location[j] == -1) {
                if (i & 1) {
                    cur.emplace_back(getDistance(left, j), j);
                } else { 
                    cur.emplace_back(getDistance(right, j), j);
                }
            }
        }
        sort(cur.begin(), cur.end());
        dst = location[right] - location[left];
        cerr << left << ' ' << right << ' ' << location[left] << ' ' << location[right] << endl;
        while (cur.size() > 0 && cur.front().dist <= dst) {
            pii st = cur.front(); cur.pop_front();
            if (i & 1) {
                location[st.idx] = location[left] + st.dist;
                stype[st.idx] = 2;
            } else {
                location[st.idx] = location[right] - st.dist;
                stype[st.idx] = 1;
            }
        }

        if (cur.size() > 0) {
            pii st = cur.front(); cur.pop_front();
            if (i & 1) {
                right = st.idx;
                location[right] = location[left] + st.dist;
                stype[right] = 2;
            } else {
                left = st.idx;
                location[left] = location[right] - st.dist;
                stype[left] = 1;
            }
        }
    }
}
