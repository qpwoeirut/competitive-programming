#include <cstdio>

int count = 0;
char out, cur = 1;

int main()
{
    out = getchar(); getchar();     // get the letter and consume an extra newline

    while (cur != '\n') {           // stop when we get a newline
        cur = getchar();            // get the next character
        if (cur == out) ++count;    // increment the count if it matches
    }

    printf("%d\n", count);
}

