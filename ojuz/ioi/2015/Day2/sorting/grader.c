#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sorting.h"

static char _buffer[1024];
static int _currentChar = 0;
static int _charsNumber = 0;
static FILE *_inputFile, *_outputFile;

static inline int _read() {
    if (_charsNumber < 0) {
        exit(1);
    }
    if (!_charsNumber || _currentChar == _charsNumber) {
        _charsNumber = (int)fread(_buffer, sizeof(_buffer[0]), sizeof(_buffer), _inputFile);
        _currentChar = 0;
    }
    if (_charsNumber <= 0) {
        return -1;
    }
    return _buffer[_currentChar++];
}

static inline int _readInt() {
    int c, x, s;
    c = _read();
    while (c <= 32) c = _read();
    x = 0;
    s = 1;
    if (c == '-') {
        s = -1;
        c = _read();
    }
    while (c > 32) {
        x *= 10;
        x += c - '0';
        c = _read();
    }
    if (s < 0) x = -x;
    return x;
}


int main()
{
	_inputFile = fopen("sorting.in", "rb");
	_outputFile = fopen("sorting.out", "w");
	int N, M;
	N = _readInt();
	int *S = (int*)malloc(sizeof(int) * (unsigned int)N);
	for (int i = 0; i < N; ++i)
		S[i] = _readInt();
	M = _readInt();
	int *X = (int*)malloc(sizeof(int) * (unsigned int)M), *Y = (int*)malloc(sizeof(int) * (unsigned int)M);
	for (int i = 0; i < M; ++i) {
	    X[i] = _readInt();
	    Y[i] = _readInt();
	}
	int *P = (int*)malloc(sizeof(int) * (unsigned int)M), *Q = (int*)malloc(sizeof(int) * (unsigned int)M);
	int ans = findSwapPairs(N, S, M, X, Y, P, Q);
	fprintf(_outputFile, "%d\n", ans);
	for (int i = 0; i < ans; ++i)
		fprintf(_outputFile, "%d %d\n", P[i], Q[i]);
	return 0;
}

