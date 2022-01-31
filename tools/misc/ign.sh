#!/bin/sh
echo ign >&2
printf '0 %s\n' "$0"
printf '> %s\n' "$@" >&2
shift 3
n="$1"
shift
exec "$n" "$@"
