/*
ID: zhongbr1
TASK: combo
LANG: C++11
*/

#include <fstream>

using namespace std;

int main() {
	ifstream fin("combo.in");
	ofstream fout("combo.out");

	int dials;
	fin >> dials;

	int fj[3];
	fin >> fj[0] >> fj[1] >> fj[2];

	int master[3];
	fin >> master[0] >> master[1] >> master[2];

	bool fj_valid[3][101], master_valid[3][101], intersection[3][101];
	int fj_total[3], master_total[3], intersection_total[3];
	for (int i=0; i<3; i++) {
		fj_total[i] = 0;
		master_total[i] = 0;
		intersection_total[i] = 0;
		for (int j=0; j<=dials; j++) {
			fj_valid[i][j] = false;
			master_valid[i][j] = false;
			intersection[i][j] = false;
		}
	}

	int fj_num, master_num;
	for (int i=0; i<3; i++) {
		for (int n=-2; n<=2; n++) {
			fj_num = (dials + fj[i] + n) % dials;
			if (fj_num == 0) {
				fj_num = dials;
			}

			fj_valid[i][fj_num] = true;
			if (master_valid[i][fj_num] == true) {
				intersection[i][fj_num] = true;
			}

			master_num = (dials + master[i] + n) % dials;
			if (master_num == 0) {
				master_num = dials;
			}

			master_valid[i][master_num] = true;
			if (fj_valid[i][master_num] == true) {
				intersection[i][master_num] = true;
			}
		}


		for (int j=1; j<=dials; j++) {
			if (fj_valid[i][j] == true) {
				fj_total[i]++;
			}
			if (master_valid[i][j] == true) {
				master_total[i]++;
			}
			if (intersection[i][j] == true) {
				intersection_total[i]++;
			}
		}
	}

	int ans = 0;
	ans += (fj_total[0] * fj_total[1] * fj_total[2]) + (master_total[0] * master_total[1] * master_total[2]);
	ans -= intersection_total[0] * intersection_total[1] * intersection_total[2];

	fout << ans << endl;

	return 0;
}
