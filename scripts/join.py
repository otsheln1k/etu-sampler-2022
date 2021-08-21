#!/usr/bin/env python3

import sys
import json
from dataclasses import dataclass, field
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
    times: List[int] = field(default_factory=list)
    refs_start: List[int] = field(default_factory=list)
    refs_end: List[int] = field(default_factory=list)

runs = json.load(sys.stdin)
if not runs:
    print('[]')
    exit()

edges = [
    Edge(src=Checkpoint(**r['prev']),
         dst=Checkpoint(**r['curr']))
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
