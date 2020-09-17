/*
ID: zhongbr1
TASK: milk
LANG: C++11
*/

#include <iostream>

#include <fstream>
#include <queue>

using namespace std;

struct Farmer {
	int rate;
	int amount;
};

struct comp_farmer {
	const bool operator() (const Farmer& a, const Farmer& b) const {
		return a.rate > b.rate;
	}
};

int main() {
	ifstream fin("milk.in");
	ofstream fout("milk.out");

	int quota, farmer_c;
	fin >> quota >> farmer_c;

	priority_queue<Farmer, vector<Farmer>, comp_farmer> q;
	Farmer tmp;
	for (int f=0; f<farmer_c; f++) {
		fin >> tmp.rate >> tmp.amount;
		q.push(tmp);
	}
	fin.close();

	int price = 0;
	Farmer cur;
	while (quota > 0 && q.size() > 0) {
		cur = q.top();
		cout << "cur rate, amt: " << cur.rate << " " << cur.amount << endl;
		q.pop();

		if (quota >= cur.amount) {
			price += (cur.rate * cur.amount);
			quota -= cur.amount;
		}
		else {
			price += (cur.rate * quota);
			quota = 0;
		}
	}

	fout << price << endl;
	fout.close();

	return 0;
}
