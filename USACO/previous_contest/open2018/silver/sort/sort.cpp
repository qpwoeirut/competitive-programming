/*
 * sort.cpp
 *
 *  Created on: Jul 27, 2018
 *      Author: Stanley
 *
 * First submission at 9:10pm on Jul 27, 2018
 * Timed out on 5/10 cases
 *
 * Same for second at 9:15pm
 *
 * 9/10 at 10:00pm
 */

#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

struct Num {
	int idx, val;
};

bool comp(Num a, Num b) {
	return a.val < b.val;
}

int main() {
	ifstream fin("sort.in");
	ofstream fout("sort.out");

	int size;
	fin >> size;
	Num arr[100000];
	int arr_copy[size];
	for (int i=0; i<size; i++) {
		fin >> arr[i].val;
		arr_copy[i] = arr[i].val;
		arr[i].idx = i;
	}
	fin.close();

	int ans = 0;
//	int temp;
//
//	bool sorted = false;
//	while (sorted == false) {
//	   sorted = true;
//	   ans++;
//	   for (int i=0; i<size; i++) {
//		   cout << arr[i].val << " ";
//	   }
//	   cout << endl;
//	   for (int i = 0; i<size-1; i++) {
//	      if (arr[i].val > arr[i+1].val) {
//	    	  temp = arr[i].val;
//	    	  arr[i].val = arr[i+1].val;
//	    	  arr[i+1].val = temp;
//	          sorted = false;
//	      }
//	   }
//	}
//
//	cout << "brute force ans: " << ans << endl;
//
	stable_sort(arr, arr+size, comp);

	int correct_idx, correct_val, diff;
	for (int i=0; i<size; i++) {
		diff = abs(i - arr[i].idx);
		if (ans < diff) {
			ans = diff;
			correct_idx = arr[i].idx;
			correct_val = arr[i].val;
		}
//		cout << ans << " " << i << " " << arr[i].val << endl;
	}
	ans++;
//	for (int i=correct_idx+1; i<size-1; i++) {
//		if (arr_copy[i] > correct_val && arr_copy[i+1] > correct_val) {
//			ans--;
//			cout << "i: " << i << endl;
//		}
//	}
//	cout << "answer: " << ans << endl;

	fout << ans;
	fout.close();

	return 0;
}
