#!/bin/bash

problem=mushrooms
grader_name=stub

set -e
rm -f "${problem}.jar" *.class
javac "${grader_name}.java" "${problem}.java" -Xlint:all
jar cfe "${problem}.jar" "${grader_name}" *.class
