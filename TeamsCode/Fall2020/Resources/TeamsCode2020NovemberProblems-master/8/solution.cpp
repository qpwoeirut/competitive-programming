#include <iostream>
#include <string>
#include <cstdio>
using namespace std;
string s;
int main()
{
    cin >> s;
    string c;
    for (int i = 0; i < s.size(); i++)
    {
        c += s[i];
        if (c.size() == 3)
        {
            if (c == "LLL")
            {
                printf("A");
            }
            else if (c == "SSL")
            {
                printf("T");
            }
            else if (c == "SLL")
            {
                printf("G");
            }
            else if (c == "SLS")
            {
                printf("C");
            }
            c.clear();
        }
    }
    cout << endl;
    return 0;
}
