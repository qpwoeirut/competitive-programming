/*
ID: zhongbr1
TASK: crypt1
LANG: C++11
*/

#include <fstream>
#include <cmath>

using namespace std;

bool valid_digits[10];
bool is_valid(int i, int digit_count) {
	if (i >= pow(10, digit_count) || i < pow(10, digit_count - 1)) {
		return false;
	}
	int mod;
	while (i != 0) {
		mod = i % 10;
		if (mod == 0 || valid_digits[mod] == false) {
			return false;
		}
		i /= 10;
	}

	return true;
}

int main() {
	ifstream fin("crypt1.in");
	ofstream fout("crypt1.out");

	int digit_c;
	fin >> digit_c;

	int digits[10];
	for (int i=0; i<10; i++) {
		valid_digits[i] = false;
	}
	for (int d=0; d<digit_c; d++) {
		fin >> digits[d];
		valid_digits[digits[d]] = true;
	}

	int combos = 0;
	int a, b, c, d, e;
	int product_d, product_e;
	for (int i=0; i<digit_c; i++) {
		a = digits[i];
		for (int j=0; j<digit_c; j++) {
			b = digits[j];
			for (int k=0; k<digit_c; k++) {
				c = digits[k];
				for (int l=0; l<digit_c; l++) {
					d = digits[l];

					product_d = d * ((a * 100) + (b * 10) + c);

					if (is_valid(product_d, 3)) {
						for (int m=0; m<digit_c; m++) {
							e = digits[m];

							product_e = e * ((a * 100) + (b * 10) + c);

							if (is_valid(product_e, 3) && is_valid(10 * product_d + product_e, 4)) {
								combos++;
							}
						}
					}
				}
			}
		}
	}

	fout << combos << endl;

	return 0;
}
