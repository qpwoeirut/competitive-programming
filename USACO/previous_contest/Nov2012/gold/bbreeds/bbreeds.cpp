/*
 * bbreeds.cpp
 *
 *  Created on: Oct 5, 2018
 *      Author: Stanley
 */

// 4/16 test cases
// 2012 November Gold Problem 1

#include <fstream>

using namespace std;

string str;
int len;

int ans = 0;

void dfs(int idx, int g_open, int g_close, int h_open, int h_close) {
	if (idx >= len) {
		if (g_open == g_close && h_open == h_close) {
			ans++;
		}
		return;
	}

	if (((g_open - g_close) > (len - idx)) || ((h_open - h_close) > (len - idx))) {
		return;
	}

	if (str[idx] == '('){
		dfs(idx+1, g_open+1, g_close, h_open, h_close);
		dfs(idx+1, g_open, g_close, h_open+1, h_close);
	}
	else {
		if (g_open > g_close) {
			dfs(idx+1, g_open, g_close+1, h_open, h_close);
		}
		if (h_open > h_close) {
			dfs(idx+1, g_open, g_close, h_open, h_close+1);
		}
	}
}

int main() {
	ifstream fin("bbreeds.in");
	ofstream fout("bbreeds.out");
	fin >> str;
	len = str.size();

	dfs(0, 0, 0, 0, 0);

	fout << (ans % 2012);

	return 0;
}
