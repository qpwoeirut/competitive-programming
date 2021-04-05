#include "horses.h"
#include <stdio.h>
#include <stdlib.h>

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


int main() {
	_inputFile = fopen("horses.in", "rb");
	_outputFile = fopen("horses.out", "w");
	
	int N; N = _readInt();

	int *X = (int*)malloc(sizeof(int)*(unsigned int)N);
	int *Y = (int*)malloc(sizeof(int)*(unsigned int)N);

	for (int i = 0; i < N; i++) {
		X[i] = _readInt();
	}

	for (int i = 0; i < N; i++) {
		Y[i] = _readInt();
	}	

	fprintf(_outputFile,"%d\n",init(N,X,Y));

	int M; M = _readInt();

	for (int i = 0; i < M; i++) {
		int type; type = _readInt();
		int pos; pos = _readInt();
		int val; val = _readInt(); 

		if (type == 1) {
			fprintf(_outputFile,"%d\n",updateX(pos,val));
		} else if (type == 2) {
			fprintf(_outputFile,"%d\n",updateY(pos,val));
		}
	}

	return 0;
}
