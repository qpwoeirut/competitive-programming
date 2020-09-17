/*
 * bundling.cpp
 *
 *  Created on: Mar 21, 2020
 *      Author: Stanley
 */


#include <iostream>
#include <algorithm>
#include <cassert>
#include <queue>

using namespace std;

#define PRS(A, N) for (int i=0; i<N; i++) cout << A[i] << " ";

const int MN = 100001;

void setIO() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
}

struct Item {
	int score;
	int start, end;

	Item(int a, int b, int c) {
		score = a;
		start = b;
		end = c;
	}
};

struct cmp_item {
	inline const bool operator() (const Item& a, const Item& b) {
		return a.score < b.score;
	}
};

inline const int calc_score(const string& s1, const string& s2) {
	int i=0;
	for (; i<s1.size() && i<s2.size(); i++) {
		if (s1[i] != s2[i]) {
			return i;
		}
	}
	return i;
}

int N, K;
bool used[MN];
int score[MN];
int R[MN];
priority_queue<Item, vector<Item>, cmp_item> pq;
int solve() {
	cin >> N >> K;

	vector<string> strs(N);
	for (int i=0; i<N; i++) {
		cin >> strs[i];
		strs[i].shrink_to_fit();
		score[i] = 0;
		used[i] = false;
	}
	while (pq.size() > 0) pq.pop();
	sort(strs.begin(), strs.end());

	int min_score = calc_score(strs[0], strs[N-1]);
	int ans = 0;
	for (int i=0; i+K-1<N; i++) {
		score[i] = calc_score(strs[i], strs[i+K-1]);
		if (score[i] > min_score) {
			pq.push(Item(score[i], i, i+K-1));
		}
//		cout << score[i] << " ";
	}
//	cout << endl;

	if (pq.empty()) {
		return min_score;
	}
	Item best = pq.top();
	pq.pop();
	ans += best.score;
//	cout << best.score << " " << ans << endl;

	for (int x=1; x<N/K; x++) {
		for (int i=0, pos=best.end+1; i<K; i++, pos++) {
			if (pos >= N) {
				R[i] = -1;
				continue;
			}
			while (pos<N && used[pos]) {
				pos += K;
			}
			R[i] = pos;
		}
		for (int ct=K-1, L=best.start-1; ct>=0 && L>=0; ct++, L--) {
			while (L>=0 && used[L]) {
				L -= K;
			}
			if (L < 0) break;

			if (R[ct] != -1) {
				score[L] = calc_score(strs[L], strs[R[ct]]);
				if (score[L] >= pq.top().score) {
					pq.push(Item(score[L], L, R[ct]));
				}
			}
		}
		for (int i=best.start; i<best.start+K; i++) {
			used[i] = true;
		}
//		PRS(score, N); cout << endl;
		if (pq.empty()) {
//			cout << 0 << " " << ans << endl;
			ans += min_score;
			continue;
		}
		do {
			best = pq.top();
			pq.pop();
		}
		while (pq.size() > 0 && (used[best.start] || used[best.end]));

		ans += best.score;
//		cout << best.score << " " << ans << endl;
	}

	return ans;
}

int main() {
	setIO();

	int T;
	cin >> T;

	for (int tc=1; tc<=T; tc++) {
		int ans = solve();
		cout << "Case #" << tc << ": " << ans << endl;
	}

	return 0;
}
