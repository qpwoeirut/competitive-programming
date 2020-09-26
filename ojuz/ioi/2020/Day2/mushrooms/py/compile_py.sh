#!/bin/bash

problem=mushrooms
grader_name=stub

set -e

[ -n "${PYTHON+x}" ] || PYTHON=python3
if ! command -v "${PYTHON}" >/dev/null 2>&1 ; then
	>&2 echo "Python command '${PYTHON}' does not exist."
	exit 1
fi

if [ ! -f "${problem}.py" ]; then
	>&2 echo "Error: Solution file '${problem}.py' not found."
	exit 4
fi

"${PYTHON}" -m py_compile "${grader_name}.py"
