#!/usr/bin/env python3

def average(it):
    c = 0
    acc = 0
    for i in it:
        acc += i
        c += 1
    if c == 0:
        return 0
    return acc / c

def median(it):
    sl = sorted(it)
    return sl[len(sl)//2]

def median_filter(it, winsize=3):
    win = [None]*winsize
    idx = 0
    for i, x in enumerate(it):
        win[idx] = x
        idx = 0 if idx == winsize - 1 else (idx + 1)
        if i >= winsize:
            yield median(win)
    if idx > 0 and i < winsize:
        yield median(win[:idx])

def edge_times(e):
    for t, rs, re in zip(e['times'], e['refs_start'], e['refs_end']):
        dt = t - (rs + re) * 0.5
        yield dt

def handle_edge(e, winsize=3, separate=False):
    if winsize <= 0:
        times = edge_times(e)
    elif not separate:
        times = edge_times(e)
        times = median_filter(times, winsize=winsize)
    else:
        times = edge_times({
            k: median_filter(e[k], winsize=winsize)
            for k in ('times', 'refs_start', 'refs_end')
        })
    t = round(average(times))
    return {
        'curr': e['curr'],
        'prev': e['prev'],
        'dt': t,
    }

def parse_args(args):
    import argparse
    import sys

    parser = argparse.ArgumentParser()

    parser.add_argument(
        '-w', '--winsize', metavar='N', type=int,
        action='store', default=3,
        help='window size for median filter (disable if nonpositive)'
    )

    parser.add_argument(
        '-s', '--separate',
        action='store_true', default=False,
        help='use separate median filter'
    )

    parser.add_argument(
        'input_file', metavar='INPUT', type=argparse.FileType('r'),
        action='store', default=sys.stdin, nargs='?',
        help='input file (stdin if omitted or "-")'
    )

    parser.add_argument(
        'output_file', metavar='OUTPUT', type=argparse.FileType('w'),
        action='store', default=sys.stdout, nargs='?',
        help='output file (stdout if omitted or "-")'
    )

    return parser.parse_args(args)

if __name__ == "__main__":
    import sys
    import json

    args = parse_args(sys.argv[1:])

    j = json.load(args.input_file)
    edges = [
        handle_edge(
            edge,
            winsize=args.winsize,
            separate=args.separate
        )
        for edge in j
    ]
    json.dump(edges, args.output_file)
