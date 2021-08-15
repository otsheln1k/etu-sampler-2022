#!/usr/bin/env python3

import sys
import json
from dataclasses import dataclass
from typing import List

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

runs = json.load(sys.stdin)
if not runs:
    print('[]')
    exit()

edges = [
    Edge(src=Checkpoint(**r['prev']),
         dst=Checkpoint(**r['curr']),
         times=[])
    for r in runs[0]
]

badruns = 0
for i, run in enumerate(runs):
    for e, r in zip(edges, run):
        csrc = Checkpoint(**r['prev'])
        cdst = Checkpoint(**r['curr'])
        if csrc != e.src or cdst != e.dst:
            badruns += 1
            print(f"Mismatch in run {i}", file=sys.stderr)
            break
        e.times.append(r['dt'])

if badruns > 0:
    print(f'({badruns} bad runs)', file=sys.stderr)
    exit(1)

json.dump([
    {
        'prev': e.src.__dict__,
        'curr': e.dst.__dict__,
        'times': e.times,
    }
    for e in edges
], sys.stdout)
