#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#define rand(l,h) (rand()%(h-l+1)+l)

using namespace std;

string codes[] = {"LLL", "SSL", "SLL", "SLS"};

int N = 100000;

int main()
{
    srand(time(0));

    for (int i=1; i<=N/3; ++i) cout << codes[rand(0, 3)];
    cout << endl;

    return 0;
}

