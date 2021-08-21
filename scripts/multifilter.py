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
    for l, i in enumerate(it):
        win[idx] = i
        idx = 0 if idx == winsize - 1 else (idx + 1)
        if l >= winsize:
            yield median(win)
    if l < winsize:
        yield median(win[:idx])

def edge_times(e):
    for t, rs, re in zip(e['times'], e['refs_start'], e['refs_end']):
        dt = t - rs - re
        if dt <= 0:
            continue
        yield t

def handle_edge(e):
    t = int(round(average(median_filter(edge_times(e)))))
    return {
        'curr': e['curr'],
        'prev': e['prev'],
        'dt': t,
    }

def main(it):
    return (
        handle_edge(edge)
        for edge in it
    )

if __name__ == "__main__":
    import sys
    import json
    json.dump(list(main(json.load(sys.stdin))), sys.stdout)
