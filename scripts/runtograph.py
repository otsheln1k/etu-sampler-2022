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
        dt = e['dt']
        ed = findplace(src)
        findplace(dst)
        el = ed.setdefault(dst, [])
        el.append(dt)
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

def graph_to_dict(graph):
    return [
        {
            **tuple_to_place(k),
            'edges': [
                {
                    'dest': place_index(graph, d),
                    'total-usec': sum(times),
                    'count': len(times),
                }
                for d, times in v.items()
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
