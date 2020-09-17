/*
ID: zhongbr1
TASK: zerosum
LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <set>
#include <string>

using namespace std;

bool eval(const string& s) {
	string str;
	for (int i=0; i<s.size(); i++) {
		if (s[i] != ' ') str.push_back(s[i]);
	}

	int ret = 0, cur = 0;
	int op = 1;
	for (int i=0; i<str.size(); i++) {
		if (str[i] == '+') {
			ret += cur * op;
			cur = 0;
			op = 1;
		}
		else if (str[i] == '-') {
			ret += cur * op;
			cur = 0;
			op = -1;
		}
		else {
			cur *= 10;
			cur += (str[i] - '0');
		}
	}

	ret += cur * op;


//	cout << s << " = " << ret << endl;
	return ret == 0;
}

int N;
set<string> ans;
void gen(const string& s) {
	char cur = s.back();
	if (cur-'0' == N) {
		if (eval(s)) {
			ans.insert(s);
		}
		return;
	}

	char nxt = cur+1;
	gen(s + '+' + nxt);
	gen(s + '-' + nxt);
	gen(s + ' ' + nxt);
}

int main() {
	ifstream fin("zerosum.in");
	ofstream fout("zerosum.out");

	fin >> N;
	gen("1");

	for (set<string>::iterator it=ans.begin(); it!=ans.end(); it++) {
		fout << *it << endl;
		cout << *it << endl;
	}

	return 0;
}
