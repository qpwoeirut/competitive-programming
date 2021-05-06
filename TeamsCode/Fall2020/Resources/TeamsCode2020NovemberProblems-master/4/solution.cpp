#include <cstdio>

int h1, m1, h2, m2;

int main()
{
    scanf("%d:%d%d", &h1, &m1, &m2);
    printf("%02d:%02d\n", (h1+(m1 + m2)/60) % 24, (m1+m2)%60);
}

