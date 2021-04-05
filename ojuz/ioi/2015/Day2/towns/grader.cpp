#include "towns.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "graderlib.c"

int main() {
    FILE *f;
    f = freopen("towns.in","r",stdin);
    assert(f != NULL);
    f = freopen("towns.out","w",stdout);
    assert(f != NULL);
    int ncase, R, N;
    int subtask;
    int ret;
    ret = scanf("%d%d",&subtask,&ncase);
    assert(ret == 2);
    for (int i = 0; i < ncase; i++) {
        ret = scanf("%d",&N);
	assert(ret == 1);
        _ini_query(N,subtask);
        R=hubDistance(N,subtask);
        printf("%d\n",R);
    }
    return 0;
}
