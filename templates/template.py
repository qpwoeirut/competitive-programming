#!/usr/bin/env python3

import argparse
import datetime
import os


class Feature:
    EMPTY = []
    TIMESTAMP = "timestamp"
    FILE_IO = "file-io"
    TC_FORMAT = "tc-format"
    PROBLEM_HEADER = "train-header"
    USE_CLASS = "class"


FEATURES = [Feature.EMPTY, Feature.TIMESTAMP, Feature.FILE_IO, Feature.TC_FORMAT, Feature.PROBLEM_HEADER]  # , Feature.USE_CLASS]


def main():
    parser = argparse.ArgumentParser(description='Generate my competitive programming template')
    parser.add_argument('filename', type=str, help='name of file to create, should end in ".cpp"')
    parser.add_argument('features', nargs='*', help='list of features to include in template', choices=FEATURES)

    args = parser.parse_args()
    filename = args.filename
    if os.path.isfile(filename):
        if input("Replace existing file? y/n: ").lower() not in ['y', 'yes']:
            return
        else:
            print("Replacing file")

    features = args.features

    comment = f"\n//{args.filename} created at {datetime.datetime.now().strftime('%D %T')}\n"
    basename = args.filename.rsplit('.', maxsplit=1)[0]

    if Feature.TIMESTAMP in features:
        if Feature.PROBLEM_HEADER in features:
            comment = gen_train_header(basename) + '\n' + comment
        with open(filename, 'w') as prog:
            prog.write(comment.strip() + '\n\n')
        return
    header = comment + HEADER
    if Feature.PROBLEM_HEADER in features:
        header = gen_train_header(filename) + '\n' + header

    io = IO
    if Feature.FILE_IO in features:
        io = gen_file_io(basename)

    if Feature.TC_FORMAT in features:
        main_func = """
void solve(int testcase) {


cout << "Case #" << testcase << ": " << ' ' << endl;
}
        
        """ + MAIN
    else:
        main_func = """
void solve(int testcase) {

}
        
        """ + MAIN

    parts = [header, DEFINE, TYPEDEF, FUNC, io, CONST, main_func]
    file = '\n\n'.join([part.strip() for part in parts])

    with open(filename, 'w') as prog:
        prog.write(file)


def gen_train_header(problem_name):
    return f"""
/*
ID: zhongbr1
TASK: {problem_name}
LANG: C++14
*/"""


HEADER = f"""
#include <bits/stdc++.h>

using namespace std;
"""

DEFINE = """
#ifdef LOCAL
#include "qpwoeirut/debug.h"
#else
#define debug
#define debug1
#define debug2
#define debug3
#endif

#define PB push_back
#define INS insert

#define FI first
#define SE second
#define sz(obj) ((int)(obj.size()))
#define all(obj) begin(obj), end(obj)

#define LB lower_bound
#define UB upper_bound
"""

TYPEDEF = """
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

typedef unsigned long long ull;
typedef long double dbl;
typedef pair<int,bool> pib;
typedef pair<ll,bool> plb;
typedef pair<dbl,dbl> pdd;
typedef map<ll,ll> mll;
typedef map<char,int> mci;
typedef map<string,int> msi;
typedef map<string,string> mss;
"""

FUNC = """
ll gcd(ll a, ll b) {return b ? gcd(b, a%b) : a;}

template <class T1,class T2> struct cmpf {
	bool rev;
	inline bool operator()(const pair<T1,T2>& a, const pair<T1,T2>& b) const {return (a.first<b.first)^rev;}
	cmpf(bool b=false) {rev=b;}
};
template <class T1,class T2> struct cmps {
	bool rev;
	inline bool operator()(const pair<T1,T2>& a, const pair<T1,T2>& b) const {return (a.second<b.second)^rev;}
	cmps(bool b=false) {rev=b;}
};

ll binpow(ll x, ll p, const ll& mod) {assert(mod>0);
    ll ret = 1;
    for(; p>0; p>>=1, x = x*x % mod) if(p & 1) ret = ret*x % mod;
    return ret;
}

template <class T> bool chmn(T& a, const T& b) {return ((a>b) ? ((a=b) || true) : false);}
template <class T> bool chmx(T& a, const T& b) {return ((a<b) ? ((a=b) || true) : false);}
"""

IO = """
void setIO(const string& filename = "") {
	cin.tie(0)->sync_with_stdio(0);
    if (filename.size() > 0) {
        freopen((filename + ".in").c_str(), "r", stdin);
        freopen((filename + ".out").c_str(), "w", stdout);
    }
}
"""

def gen_file_io(basename):
    return f"""void setIO(const string& filename = "{basename}") """ + """{
    cin.tie(0)->sync_with_stdio(0);
    if (filename.size() > 0) {
        freopen((filename + ".in").c_str(), "r", stdin);
        freopen((filename + ".out").c_str(), "w", stdout);
    }
}
"""

CONST = """
int chr[8] = {-1, 0, 1, 0, -1, -1, 1, 1};
int chc[8] = {0, 1, 0, -1, -1, 1, -1, 1};

const ll MOD = 1e9+7; //998244353 //1e9+9 //1e9+21 // 1e9+33;
const int INIT = 1001001001;
const int MN = 1001001;

ll N, M, K;
ll A[MN];
//ll G[MN][MN];
//set<ll> adj[MN];
"""

MAIN = """
int main() {
    setIO();
    
    ll T = 1;
    cin >> T;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
"""

if __name__ == "__main__":
    main()
