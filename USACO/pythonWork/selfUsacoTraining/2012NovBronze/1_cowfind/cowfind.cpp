/*
 * cowfind.cpp
 * Author: Stanley
 *
 * Created on April 5, 2018, 5:59 PM
 * Submitted on June 18, 2018, 2:46 PM for second time
 * Got 8/10 (2 timeouts) and then 10/10
 *
 */

#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;


int main() {
    ifstream fin("cowfind.in");
    ofstream fout("cowfind.out");
    
//    fin.seekg(0, ios::end);
//    int length = fin.tellg();
//    fin.seekg(0, ios::beg);
    
    char grass[50000];
    
    unsigned int i;
    for (i=0; i<50000; i++) {
        if (fin.peek() == EOF) {
            fin.close();
            break;
        }
        
        fin >> grass[i];
    }
    
    int ans = 0;
    int left_leg_pairs[i];
    int right_leg_pairs[i];
    int left_leg_idx, right_leg_idx = 0;
    
    for (int g=1; g<i-1; g++) {
        if (grass[g] == '(' && grass[g-1] == '(') {
            left_leg_pairs[left_leg_idx] = g;
            left_leg_idx++;
        }
        else if (grass[g] == ')' && grass[g-1] == ')') {
            right_leg_pairs[right_leg_idx] = g;
            right_leg_idx++;
        }
    }

    for (int l=0; l<left_leg_idx; l++) {
        for (int r=0; r<right_leg_idx; r++) {
            if (left_leg_pairs[l] < right_leg_pairs[r]) {
                ans += right_leg_idx - r;
                break;
            }
        }
    }

    fout << ans << '\n';
    fout.close();
    cout << ans << endl << endl;
    return 0;
}

