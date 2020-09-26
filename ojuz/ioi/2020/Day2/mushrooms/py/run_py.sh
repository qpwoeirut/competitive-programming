#!/bin/bash

grader_name=stub

set -e

[ -n "${PYTHON+x}" ] || PYTHON=python3
if ! command -v "${PYTHON}" >/dev/null 2>&1 ; then
	>&2 echo "Python command '${PYTHON}' does not exist."
	exit 1
fi

"${PYTHON}" "${grader_name}.py"
