/*
 * rental.cpp
 *
 *  Created on: Dec 13, 2018
 *      Author: Stanley
 */

/*
 * Checked answer and downloaded test cases
 * I was using a set, which removed duplicates and messed up the answer
 * Using arrays now
 */

#include <fstream>
#include <algorithm>

using namespace std;

struct Store {
	int price, amt_left;
};

const bool comp_store (const Store& a, const Store& b) {
	return a.price > b.price;
}

const bool comp_greater (const int& a, const int& b) {
	return a > b;
}

int main() {
	ifstream fin("rental.in");
	ofstream fout("rental.out");

	int cow_c, store_c, rent_c;
	fin >> cow_c >> store_c >> rent_c;

	int cows[100000];
	for (int c=0; c<cow_c; c++) {
		fin >> cows[c];
	}
	sort(cows, cows+cow_c, comp_greater);

	Store stores[100000];
	for (int s=0; s<store_c; s++) {
		fin >> stores[s].amt_left >> stores[s].price;
	}
	sort(stores, stores+store_c, comp_store);

	int renters[100000];
	for (int r=0; r<rent_c; r++) {
		fin >> renters[r];
	}
	sort(renters, renters+rent_c, comp_greater);

	long long rents[100000];
	rents[0] = 0;
	for (int i = 0; i < rent_c; i++) {
		rents[i+1] = rents[i] + renters[i];
	}
	for (int i=rent_c+1; i<=cow_c; i++) {
		rents[i] = rents[i-1];
	}

	long long cur_milk = 0, cur_profit, price;
	int cur_s = 0;
	long long milk_profit[100000];
	milk_profit[0] = 0;
	for (int i=0; i<cow_c; i++) {
		cur_milk += cows[i];
		cur_profit = 0;
		while (cur_milk > 0) {
			price = stores[cur_s].price;
			if (stores[cur_s].amt_left == 0) {
				cur_s++;
			}
			else {
				if (cur_milk > stores[cur_s].amt_left) {
					cur_profit += price * stores[cur_s].amt_left;
					cur_milk -= stores[cur_s].amt_left;
					stores[cur_s].amt_left = 0;
				}
				else {
					cur_profit += cur_milk * price;
					stores[cur_s].amt_left -= cur_milk;
					cur_milk = 0;
				}
			}
		}

		milk_profit[i+1] = milk_profit[i] + cur_profit;
	}



	long long prev = 0, cur = 0;
	for (int i = 0; i <= cow_c; i++) {
		prev = cur;
		cur = milk_profit[i] + rents[cow_c - i];
		if (prev > cur) {
			break;
		}
	}

	fout << prev;

	return 0;
}
