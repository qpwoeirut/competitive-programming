/*
ID: zhongbr1
TASK: lamps
LANG: C++11
*/

#include <fstream>
#include <algorithm>
#include <set>
#include <string>

using namespace std;

string flip(string s, int i, int step) {
	for (; i<s.size(); i+=step) {
		s[i] = (s[i] == '0' ? '1' : '0');
	}
	return s;
}

set<string> lamps;
void change(int rem, string cur) {
	if (rem == 0) {
    lamps.insert(cur);
		return;
	}

	if ((rem == 1 && lamps.find(cur) == lamps.end()) || (rem > 1 && lamps.emplace(cur).second == true)) {
    change(rem - 1, flip(cur, 0, 1));
    change(rem - 1, flip(cur, 0, 2));
    change(rem - 1, flip(cur, 1, 2));
    change(rem - 1, flip(cur, 0, 3));
	}
}

int main() {
	ifstream fin("lamps.in");
	ofstream fout("lamps.out");

	int N, C;
	fin >> N >> C;

	set<int> on, off;
  int tmp;
  for (int i=0; i<N; i++) {
    fin >> tmp;
    if (tmp == -1) break;
    on.insert(tmp-1);
  }
  for (int i=0; i<N; i++) {
    fin >> tmp;
    if (tmp == -1) break;
    off.insert(tmp-1);
  }

  change(min(16, C), string(N, '1'));

  bool has_any = false;
  bool valid;
  for (set<string>::iterator it=lamps.begin(); it!=lamps.end(); it++) {
    valid = true;
    for (set<int>::iterator it1=on.begin(); valid && it1!=on.end(); it1++) {
      if ((*it)[*it1] != '1') {
        valid = false;
      }
    }
    for (set<int>::iterator it1=off.begin(); valid && it1!=off.end(); it1++) {
      if ((*it)[*it1] != '0') {
        valid = false;
      }
    }

    if (valid) {
      fout << *it << endl;
      has_any = true;
    }
  }

  if (has_any == false) {
	  fout << "IMPOSSIBLE" << endl;
  }

	return 0;
}
