/*
 * homework.cpp
 *
 *  Created on: Dec 15, 2018
 *      Author: Stanley
 */

#include <fstream>
#include <algorithm>
#include <set>

using namespace std;

struct Grade {
	int total;
	int question_c;
	pair<int, int> fr;
};

bool comp_grade (const Grade& a, const Grade& b) {
	float tmp_a = a.fr.second, tmp_b = b.fr.second;
	return (a.fr.first / tmp_a) > (b.fr.first / tmp_b);
}

int main() {
	ifstream fin("homework.in");
	ofstream fout("homework.out");

	int q_c;
	fin >> q_c;

	int scores[100000];
	for (int s=0; s<q_c; s++) {
		fin >> scores[s];
	}

	int cur_grade = scores[q_c - 1] + scores[q_c - 2];
	int worst = min(scores[q_c - 1], scores[q_c - 2]);
	Grade grades[q_c];
	grades[q_c - 2].total = grades[q_c - 2].fr.first = cur_grade - worst;
	grades[q_c - 2].question_c = grades[q_c - 2].fr.second = 1;

	for (int i=q_c-3; i >= 1; i--) {
		worst = min(worst, scores[i]);
		cur_grade += scores[i];

		grades[i].total = grades[i].fr.first = cur_grade - worst;
		grades[i].question_c = grades[i].fr.second = q_c - i - 1;

		for (int n=2; n<=min(grades[i].total, grades[i].question_c); n+=2) {
			while ((grades[i].fr.first % n) == 0 && (grades[i].fr.second % n) == 0) {
				grades[i].fr.first /= n;
				grades[i].fr.second /= n;
			}
			if (n == 2) {
				n--;
			}
		}
	}

	sort(grades + 1, grades + q_c - 1, comp_grade);
	set<int> best;
	best.insert(q_c - (grades[1].question_c + 1));
	for (int i=2; i<q_c - 1; i++) {
		if (grades[1].fr.first == grades[i].fr.first &&
			grades[1].fr.second == grades[i].fr.second) {
				best.insert(q_c - (grades[i].question_c + 1));
		}
		else {
			break;
		}
	}

	for (set<int>::iterator it = best.begin(); it != best.end(); it++) {
		fout << *it << endl;
	}

	return 0;
}
