/*
 * 2a.cpp
 *
 *  Created on: May 26, 2019
 *      Author: Stanley
 */

#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

int main() {
	int N;
	cin >> N;

	map<string, int> scores;
	map<string, map<int, int> > times;
	string name;
	int score;
	for (int i=0; i<N; i++) {
		cin >> name >> score;
		scores[name] += score;
		times[name][i] = scores[name];
	}

	set<string> winners;
	set<string>::iterator sit = winners.begin();
	int best = 1;
	for (map<string, int>::iterator mit=scores.begin(); mit!=scores.end(); mit++) {
		if (mit->second == best) {
			sit = winners.insert(sit, mit->first);
		}
		else if (mit->second > best) {
			best = mit->second;
			winners.clear();
			sit = winners.insert(winners.begin(), mit->first);
		}
	}

	string winner;
	int first = N;
	for (set<string>::iterator sit=winners.begin(); sit!=winners.end(); sit++) {
		for (map<int, int>::iterator mit=times[*sit].begin(); mit!=times[*sit].end(); mit++) {
			if (mit->second >= best) {
				if (first >= mit->first) {
					first = mit->first;
					winner = *sit;
				}
				break;
			}
		}
	}

	cout << winner << endl;

	return 0;
}
