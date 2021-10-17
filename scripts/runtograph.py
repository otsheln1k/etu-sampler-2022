#!/usr/bin/env python3

from collections import OrderedDict

def place_to_tuple(p):
    return (p['file'], p['line'], p['func'])

def make_graph(edges):
    graph = []
    def findplace(p):
        for r, val in graph:
            if r == p:
                return val
        val = {}
        graph.append((p, val))
        return val
    for e in edges:
        src = place_to_tuple(e['prev'])
        dst = place_to_tuple(e['curr'])
        r = tuple(e[k] for k in ('dt', 'var', 'max', 'min'))
        ed = findplace(src)
        findplace(dst)
        rs = ed.setdefault(dst, [])
        rs.append(r)
    return graph

def tuple_to_place(t):
    fl, l, func = t
    return {
        'file': fl,
        'line': l,
        'func': func,
    }

def place_index(graph, p):
    for i, v in enumerate(graph):
        r, l = v
        if r == p:
            return i
    raise ValueError(f'{p!r} not in graph')

def avg(it):
    n = 0
    acc = 0
    for i in it:
        n += 1
        acc = acc + i
    return acc / n

def variance(l, av):
    n = len(l)
    return sum((x - av)**2 for x in l) / n

def mkedge(recs):
    times = [r[0] for r in recs]
    variances = [r[1] for r in recs]
    tmax = max(r[2] for r in recs)
    tmin = min(r[3] for r in recs)
    a = avg(times)
    v = variance(times, a)
    return {
        'total-usec': sum(times),
        'count': len(times),
        'attrs': {
            'avg': a,
            'var': v,
            'var/tot': sum(variances),
            'max': tmax,
            'min': tmin,
        },
    }

def graph_to_dict(graph):
    return [
        {
            **tuple_to_place(k),
            'edges': [
                {
                    'dest': place_index(graph, d),
                    **mkedge(rs),
                }
                for d, rs in v.items()
            ]
        }
        for k, v in graph
    ]

if __name__ == "__main__":
    import sys
    import json
    j = json.load(sys.stdin)
    g = make_graph(j)
    d = graph_to_dict(g)
    json.dump(d, sys.stdout)
