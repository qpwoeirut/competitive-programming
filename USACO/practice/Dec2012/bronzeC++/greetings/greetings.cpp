/*
 * greetings.cpp
 *
 *  Created on: Dec 21, 2018
 *      Author: Stanley
 *
 * Converted from previous Java submission
 * Testing differences between languages
 */

#include <fstream>
#include <queue>

using namespace std;

struct Move {
	short dir;
	int len;
};

int main() {
	ifstream fin("greetings.in");
	ofstream fout("greetings.out");

	int bCount, eCount;
	fin >> bCount >> eCount;
	queue<Move> bMoves, eMoves;
	Move tmp;
	char dir;
	for (int i = 0; i < bCount; i++) {
		fin >> tmp.len >> dir;
		if (dir == 'L') {
			tmp.dir = -1;
		}
		else {
			tmp.dir = 1;
		}
		bMoves.push(tmp);
	}
	for (int i = 0; i < eCount; i++) {
		fin >> tmp.len >> dir;
		if (dir == 'L') {
			tmp.dir = -1;
		}
		else {
			tmp.dir = 1;
		}
		eMoves.push(tmp);
	}

	int meetings = 0;
	int bDistLeft = 0, eDistLeft = 0;
	int bPos = 0, ePos = 0;
	short bDir = 0, eDir = 0;
	short relation = 0;
	Move bMove, eMove;
	while (!bMoves.empty() || !eMoves.empty()) {
		if (bDistLeft == 0 && !bMoves.empty()) {
			bMove = bMoves.front();
			bMoves.pop();
			bDistLeft = bMove.len;
			bDir = bMove.dir;
		}
		if (eDistLeft == 0 && !eMoves.empty()) {
			eMove = eMoves.front();
			eMoves.pop();
			eDistLeft = eMove.len;
			eDir = eMove.dir;
		}

		if (bDistLeft >= eDistLeft) {
			if (eDistLeft > 0) {
				bPos += eDistLeft * bDir;
				ePos += eDistLeft * eDir;
				bDistLeft -= eDistLeft;
				eDistLeft = 0;
			} else {
				bPos += bDistLeft * bDir;
				bDistLeft = 0;
			}
		} else {
			if (bDistLeft > 0) {
				bPos += bDistLeft * bDir;
				ePos += bDistLeft * eDir;
				eDistLeft -= bDistLeft;
				bDistLeft = 0;
			} else {
				ePos += eDistLeft * eDir;
				eDistLeft = 0;
			}
		}

		if (bPos < ePos) {
			if (relation == 1) {
				meetings++;
			}
			relation = -1;
		} else if (bPos == ePos) {
			if (relation != 0) {
				meetings++;
			}
			relation = 0;
		} else {
			if (relation == -1) {
				meetings++;
			}
			relation = 1;
		}
	}

	fout << meetings;

	return 0;
}
