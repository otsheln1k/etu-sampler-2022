#!/usr/bin/env python3

import sys
import json
from dataclasses import dataclass, field
from typing import List
from itertools import takewhile

@dataclass
class Checkpoint:
    file: str
    line: int
    func: str

@dataclass
class Edge:
    src: Checkpoint
    dst: Checkpoint
    times: List[int]
    refs_start: List[int]
    refs_end: List[int]

def lines(f):
    for l in f:
        l = l.rstrip('\n')
        if not l:
            yield None
        else:
            yield json.loads(l)

def takerun(ls):
    return takewhile(lambda x: x is not None, ls)

ls = lines(sys.stdin)

edges = [
    Edge(src=Checkpoint(**r['prev']),
         dst=Checkpoint(**r['curr']),
         times=[r['dt']],
         refs_start=[r['ref_start']],
         refs_end=[r['ref_end']])
    for r in takerun(ls)
]

badruns = 0
i = 0
ign = False
for r in ls:
    if r is None:
        i = 0
        ign = False
        continue
    idx, i = i, i+1
    if ign:
        continue

    e = edges[idx]
    csrc = Checkpoint(**r['prev'])
    cdst = Checkpoint(**r['curr'])
    if csrc != e.src or cdst != e.dst:
        badruns += 1
        print(f"Mismatch in run {idx}", file=sys.stderr)
        ign = True
        continue
    e.times.append(r['dt'])
    e.refs_start.append(r['ref_start'])
    e.refs_end.append(r['ref_end'])

if badruns > 0:
    print(f'({badruns} bad runs)', file=sys.stderr)
    exit(1)

json.dump([
    {
        'prev': e.src.__dict__,
        'curr': e.dst.__dict__,
        'times': e.times,
        'refs_start': e.refs_start,
        'refs_end': e.refs_end,
    }
    for e in edges
], sys.stdout)
