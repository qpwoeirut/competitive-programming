/*
 * 1178e.cpp
 *
 *  Created on: Jul 20, 2019
 *      Author: Stanley
 */

#include <iostream>
#include <stack>

using namespace std;

int main() {
	string s;
	cin >> s;

	stack<char> p;

	int rem = s.size() / 2;
	int i=0, j=s.size()-1;
	while (i < j) {
//		cout << i << " " << j << endl;
		if (s[i] == s[j]) {
			cout << s[i];
			p.push(s[j]);
			i++;
			j--;
			rem -= 2;
		}
		else if (s[i+1] == s[j]) {
			cout << s[i+1];
			if (i+1 < j) {
				p.push(s[j]);
				rem--;
			}
			i += 2;
			j--;
			rem--;
		}
		else if (s[i] == s[j-1]) {
			cout << s[i];
			if (i < j-1) {
				p.push(s[j-1]);
				rem--;
			}
			i++;
			j -= 2;
			rem--;
		}
		else if (rem == 1) {
			cout << s[i];
			break;
		}
		else {
			i++;
			j--;
		}
	}

	while (p.size() > 0) {
		cout << p.top();
		p.pop();
	}
	cout << endl;

	return 0;
}
