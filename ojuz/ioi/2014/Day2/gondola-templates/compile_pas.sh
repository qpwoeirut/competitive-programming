#!/bin/bash

NAME=gondola

/usr/bin/fpc -dEVAL -XS -O2 -o$NAME grader.pas
