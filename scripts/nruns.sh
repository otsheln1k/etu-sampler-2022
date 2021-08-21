#!/bin/sh

if [ "$#" -lt 3 ]
then
    cat >&2 <<EOF
usage: $0 N S PROGRAM [ARGS...]
  N is the total number of runs.
  S is the number of initial runs to skip.
  PROGRAM is the program to run. It's always interpreted as a relative
    path, and never searched in \$PATH.
EOF
    exit 2
fi

n="$1"
s="$2"
program="$(dirname "$3")/$(basename "$3")"
shift 3

first="$(expr "$s" + 1)"

echo '['
seq "$n" | \
    while read i
    do
        if [ "$i" -le "$s" ]
        then
            "$program" -o /dev/null -- "$@" >/dev/null 2>&1
        else
            [ "$i" -ne "$first" ] && echo ','
            echo '['
            "$program" -O 3 -- "$@" 3>&1 >/dev/null | sed '1!s/^/,/'
            echo ']'
        fi
    done
echo ']'
