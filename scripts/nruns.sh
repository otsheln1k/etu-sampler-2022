#!/bin/sh

if [ "$#" != 2 ]
then
    echo "usage: $0 PROGRAM N" >&2
    exit 2
fi

program="$(dirname "$1")/$(basename "$1")"
n="$2"

echo '['
seq "$n" | \
    while read i
    do
        [ "$i" != 1 ] && echo ','
        echo '['
        "$program" -O 3 3>&1 >/dev/null | sed '1!s/^/,/'
        echo ']'
    done
echo ']'
