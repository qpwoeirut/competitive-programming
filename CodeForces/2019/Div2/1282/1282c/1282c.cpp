/*
 * 1282c.cpp
 *
 *  Created on: Dec 23, 2019
 *      Author: Stanley
 */


#include <iostream>
#include <algorithm>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <utility>
#include <bitset>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

#define MP make_pair

#define PF push_front
#define PB push_back
#define I insert

#define LB lower_bound
#define UB upper_bound

#define PRS(A, N) for (int i=0; i<N; i++) cout << A[i] << " ";
#define PRL(A, N) for (int i=0; i<N; i++) cout << A[i] << endl;
#define PISET(A) for (set<int>::iterator it=A.B(); it!=A.E(); it++) cout << *it << " ";
#define PSSET(A) for (set<string>::iterator it=A.B(); it!=A.E(); it++) cout << *it << " ";

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,bool> pib;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

typedef map<int,int> mii;
typedef map<ll,ll> mll;
typedef map<char, int> mci;
typedef map<string,int> msi;

ll gcd(ll a, ll b) {return b ? gcd(b, a%b) : a;}

const ll MOD = 1e9+7; // 998244353;
const ll INF = 1e18;
const int MAXN = 200001;

bool comp_first(const pib& a, const pib& b) {
	if (a.first == b.first) return a.second;
	return a.first < b.first;
}

ll N, T, A, B;
ll easy, hard;
ll extra(ll diff) {
	if (diff >= easy * A) {
		diff -= easy * A;
		if (diff >= hard * B) {
			return easy + hard;
		}
		else {
			return easy + (diff/B);
		}
	}
	return diff/A;
}

pair<ll, bool> prob[MAXN];
void solve() {
	cin >> N >> T >> A >> B;

	easy = hard = 0;
	for (int i=0; i<N; i++) {
		cin >> prob[i].second;
		if (prob[i].second == false) easy++;
		else hard++;
	}
	for (int i=0; i<N; i++) {
		cin >> prob[i].first;
	}
	sort(prob, prob+N, comp_first);

	ll ans = max(0LL, extra(prob[0].first-1));
	ll sum = 0;
	for (int i=0; i<N; i++) {
		if (prob[i].second == false) {
			sum += A;
			easy--;
		}
		else {
			sum += B;
			hard--;
		}
//		cout << prob[i].first << " " << prob[i].second << " " << sum << endl;
		if (sum > T) break;
		if (i+1 == N || sum < prob[i+1].first) {
			int diff = (i+1 == N ? T : prob[i+1].first-1) - sum;
			ans = max(ans, i+1+extra(diff));
		}
	}
	cout << ans << endl;
//cout << "\n";
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int M;
	cin >> M;

	while (M > 0) {
		M--;
		solve();
	}
	return 0;
}
