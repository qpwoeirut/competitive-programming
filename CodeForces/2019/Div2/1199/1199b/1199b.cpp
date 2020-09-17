/*
 * 1199b.cpp
 *
 *  Created on: Jul 30, 2019
 *      Author: Stanley
 */

#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

typedef long long LL;

int main() {
	double H, L;
	cin >> H >> L;

	double radius = ((H*H) + (L*L));
	radius /= (2*H);
	radius -= H;

	cout << setprecision(12) << radius << endl;

	return 0;
}
