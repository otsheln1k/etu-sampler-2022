#!/usr/bin/env python3

import sys
import json

def ptitle(pt):
    return f"{pt['file']}:{pt['line']} ({pt['func']})"

def etitle(e):
    t = e['total-usec']
    c = e['count']
    a = round(t / c, 3)
    return f"{t}/{c} = {a}"

def esc(s):
    es = s.replace('\\', '\\\\').replace('"', '\\"')
    return f'"{es}"'

def wrgraph(nodelabels, edges,
            file=sys.stdout):
    fprint = lambda *a, **kwa: print(*a, file=file, **kwa)
    fprint('digraph {')
    for i, txt in enumerate(nodelabels):
        fprint(f'  {i} [label={esc(txt)}]')
    for i, j, txt in edges:
        fprint(f'  {i} -> {j} [label={esc(txt)}]')
    fprint('}')

j = json.load(sys.stdin)
ns = []
es = []
for i, pt in enumerate(j):
    ns.append(ptitle(pt))
    for e in pt['edges']:
        es.append((i, e['dest'], etitle(e)))
wrgraph(ns, es)
