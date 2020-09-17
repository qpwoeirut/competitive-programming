/*
 * threesum.cpp
 *
 *  Created on: Jan 31, 2020
 *      Author: Stanley
 */


#include <fstream>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <utility>
#include <bitset>
#include <deque>
#include <map>
#include <queue>
#include <string>
#include <set>
#include <vector>

using namespace std;

#define PF push_front
#define PB push_back
#define INS insert

#define FI first
#define SE second
#define BE begin
#define EN end

#define LB lower_bound
#define UB upper_bound

#define PRS(A, N) for (int i=0; i<N; i++) cout << A[i] << " ";
#define PRL(A, N) for (int i=0; i<N; i++) cout << A[i] << endl;
#define PSPR(A, N) for (int i=0; i<N; i++) cout << A[i].FI << "," << A[i].SE << " ";
#define PLPR(A, N) for (int i=0; i<N; i++) cout << A[i].FI << "," << A[i].SE << endl;
#define PSISET(A) for (set<int>::iterator it=A.BE(); it!=A.EN(); it++) cout << *it << " ";
#define PSSSET(A) for (set<string>::iterator it=A.BE(); it!=A.EN(); it++) cout << *it << " ";
#define PLISET(A) for (set<int>::iterator it=A.BE(); it!=A.EN(); it++) cout << *it << endl;
#define PLSSET(A) for (set<string>::iterator it=A.BE(); it!=A.EN(); it++) cout << *it << endl;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<set<int> > vsi;

typedef unsigned long long ull;
typedef pair<int,bool> pib;
typedef pair<ll,bool> plb;
typedef map<int,int> mii;
typedef map<ll,ll> mll;
typedef map<char, int> mci;
typedef map<string,int> msi;
typedef map<string,string> mss;

void chmn(int& a, const int& b) {if (a>b) a=b;}
void chmn(ll& a, const ll& b) {if (a>b) a=b;}
void chmx(int& a, const int& b) {if (a<b) a=b;}
void chmx(ll& a, const ll& b) {if (a<b) a=b;}

const int MN = 5001;
const int MV = 2000005;
const int OFF = 1e6;

ll ans[MN][MN];
ll A[MN];
int ct[MV];

int main() {
	ifstream fin("threesum.in");
	ofstream fout("threesum.out");

	int N, Q;
	fin >> N >> Q;

	for (int i=0; i<N; i++) {
		fin >> A[i];
	}

	for (int i=0; i<N; i++) {
		for (int j=i+1; j<N; j++) {
			int idx = OFF - A[i] - A[j];
			if (0 <= idx && idx <= OFF*2) {
				ans[i][j] = ct[idx];
			}
			ct[A[j] + OFF]++;
		}
		for (int j=i+1; j<N; j++) {
			ct[A[j] + OFF]--;
		}
	}


	for (int i=N-1; i>=0; i--) {
		for (int j=i+2; j<N; j++) {
			ans[i][j] += ans[i][j-1] + ans[i+1][j] - ans[i+1][j-1];
		}
	}

	int a, b;
	for (int i=0; i<Q; i++) {
		fin >> a >> b;
		a--; b--;

		fout << ans[a][b] << '\n';
//		cout << ans[a][b] << '\n';
	}

	return 0;
}
