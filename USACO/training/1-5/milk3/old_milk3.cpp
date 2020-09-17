/*
ID: zhongbr1
TASK: milk3
LANG: C++11
*/

#include <iostream>

#include <fstream>
#include <set>

//using namespace std;
//
//struct Amounts {
//	int a, b, c;
//};
//
//struct comp_amts {
//	bool operator() (const Amounts& a, const Amounts& b) {
//		return a.a < b.a;
//	}
//};
//
//pair<int, int> add(int a, int b, int capacity) {
//	if (b < capacity) {
//		if (a+b > capacity) {
//			a = a - (capacity - b);
//			b = capacity;
//		}
//		else {
//			b = a + b;
//			a = 0;
//		}
//	}
//
//	return make_pair(a, b);
//}
//
//int buckets[3];
//set<Amounts, comp_amts> used;
//set<int> vals;
//void recurse(int a, int b, int c) {
//	cout << a << " " << b << " " << c << endl;
//	if (a == 0) {
//		vals.insert(c);
//	}
//
//	if (a > 0) {
//		Amounts amts;
//		pair<int, int> tmp = add(a, b, buckets[1]);
//		amts.a = tmp.first;
//		amts.b = tmp.second;
//		amts.c = c;
//		cout << "search a, b, c: " << amts.a << " " << amts.b << " " << amts.c << endl;
//		if (used.find(amts) == used.end()) {
//			used.insert(amts);
//			recurse(amts.a, amts.b, amts.c);
//		}
//
//		tmp = add(a, c, buckets[2]);
//		amts.a = tmp.first;
//		amts.b = tmp.second;
//		amts.c = c;
//		cout << "search a, b, c: " << amts.a << " " << amts.b << " " << amts.c << endl;
//		if (used.find(amts) == used.end()) {
//			used.insert(amts);
//			recurse(amts.a, amts.b, amts.c);
//		}
//	}
//	if (b > 0) {
//		Amounts amts;
//		pair<int, int> tmp = add(b, a, buckets[0]);
//		amts.a = tmp.second;
//		amts.b = tmp.first;
//		amts.c = c;
//		cout << "search a, b, c: " << amts.a << " " << amts.b << " " << amts.c << endl;
//		if (used.find(amts) == used.end()) {
//			used.insert(amts);
//			recurse(amts.a, amts.b, amts.c);
//		}
//
//		tmp = add(b, c, buckets[2]);
//		amts.a = a;
//		amts.b = tmp.first;
//		amts.c = tmp.second;
//		cout << "search a, b, c: " << amts.a << " " << amts.b << " " << amts.c << endl;
//		if (used.find(amts) == used.end()) {
//			used.insert(amts);
//			recurse(amts.a, amts.b, amts.c);
//		}
//	}
//	if (c > 0) {
//		Amounts amts;
//		pair<int, int> tmp = add(c, a, buckets[0]);
//		amts.a = tmp.second;
//		amts.b = b;
//		amts.c = tmp.first;
//		if (used.find(amts) == used.end()) {
//			used.insert(amts);
//			recurse(amts.a, amts.b, amts.c);
//		}
//
//		tmp = add(c, b, buckets[1]);
//		amts.a = a;
//		amts.b = tmp.second;
//		amts.c = tmp.first;
//		if (used.find(amts) == used.end()) {
//			used.insert(amts);
//			recurse(amts.a, amts.b, amts.c);
//		}
//	}
//}
//
//int amain() {
//	ifstream fin("milk3.in");
//	ofstream fout("milk3.out");
//
//	fin >> buckets[0] >> buckets[1] >> buckets[2];
//
//	recurse(0, 0, buckets[2]);
//
//	for (set<int>::iterator it = vals.begin(); it != vals.end(); it++) {
//		fout << *it << " ";
//	}
//	fout << endl;
//
//	return 0;
//}
