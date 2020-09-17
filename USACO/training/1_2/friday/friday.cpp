/*
ID: zhongbr1
TASK: friday
LANG: C++11
*/

#include <fstream>

using namespace std;

inline bool is_leap_year(const int& year) {
	return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

int main() {
	ifstream fin("friday.in");
	ofstream fout("friday.out");
	
	int N;
	fin >> N;

	int day_count[7];
	fill(day_count, day_count+7, 0);

	int day = 2; // 1/1/1900 is a Monday
	int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	for (int year = 1900; year <= 1900+N-1; year++) {
		for (int month = 1; month <= 12; month++) {
			for (int date = 1; date <= days[month-1] || (date == 29 && is_leap_year(year)); date++) {
				if (date == 13) {
					day_count[day]++;
				}
				day++;
				if (day == 7) {
					day = 0;
				}
			}
		}
	}

	for (int i=0; i<7; i++) {
		fout << day_count[i];
		if (i != 6) {
			fout << " ";
		}
	}
	fout << endl;

	return 0;
}
