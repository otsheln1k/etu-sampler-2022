#!/bin/sh
a="$1"
b="$2"
c="$3"
n="$4"
shift 4
printf '%d  %s %s %s\n' $$ "$n" "$a" "$b"
exec "$n" "$a" "$b" "$c" "$@"
