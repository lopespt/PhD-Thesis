# -*- coding: utf-8 -*-
from audioop import reverse

__author__ = 'wachs'

import sys
from ctypes import *
import networkx as nx
from networkx.algorithms import *
import community
import matplotlib.pyplot as plt
import numpy as np
import math

class Header(Structure):

    _fields_ = [('version', c_int),
                ('num_nodes', c_ulonglong),
                ('num_edges', c_ulonglong)]


class NodeString(Structure):
    _fields_ = [('text', c_char * 50)]


#class Link(Structure):
#    _fields_ = [ () ]

class Node(Structure):
    _fields_ = [('node_id', c_ulonglong),
                ('value', NodeString)]

class Link(Structure):
    _fields_ = [('time', c_ulonglong),
                ('weight', c_float),
                ('max_weight', c_float)]

class Edge(Structure):
    _fields_ = [ ('node_from', c_ulonglong),
                 ('node_to', c_ulonglong),
                 ('edge', Link)]

def print_all_edges(G):

    for node in G.edge:
        for edge in G.edge[node].keys():
            print G.node[node]["text"] +" -> " + G.node[edge]["text"] + " = " + str(G.edge[node][edge]["weight"])


def read_cn_file(path):
    with open(path, 'rb') as f:
        G = nx.Graph()
        header = Header()
        f.readinto(header)
        print("Nodes: "+str(header.num_nodes))
        print("Edges: "+str(header.num_edges))
        for i in range(1, header.num_nodes+1):
            node = Node()
            f.readinto(node)
            G.add_node(node.node_id, {'text': node.value.text})
            #print(node.value.text)

        for i in range(1, header.num_edges):
            edge = Edge()
            f.readinto(edge)
            if edge.edge.weight < 1e-30:
                edge.edge.weight = 0
            else:
                G.add_edge(edge.node_from, edge.node_to, weight=edge.edge.weight)

            #print edge.node_from,
            #print edge.node_to,
            #print edge.edge.weight

    return G


def partition(G):
    #print("calculando cc")
    #print(nx.average_clustering(G, G.nodes(), 'weight'))
    partition = community.best_partition(G)
    #print("Partitions: " + str(partition))
    modularity = community.modularity(partition, G)
    print("Modularity: " + str(modularity))

    p = {}
    for i in partition.items():
        if i[1] in p:
            p[i[1]].append(i[0])
        else:
            p[i[1]] = list()
            p[i[1]].append(i[0])

    #print "Partitions sizes: "+str([len(p[i]) for i in p.keys()])
    #print "Partitions: "+str([p[i] for i in p.keys()])

    return sorted([p[i] for i in p.keys()], key=lambda s: len(s), reverse=True)

    #biggest_cluster = p[1];
    #Gind = G.subgraph(biggest_cluster)
    #partition = community.best_partition(Gind)
    #print(partition)
    #modularity = community.modularity(partition, Gind)
    #print(modularity)
    #p = {}
    #for i in partition.items():
    #    if i[1] in p:
    #        p[i[1]].append(i[0])
    #    else:
    #        p[i[1]] = list()
    #        p[i[1]].append(i[0])

    #for i in p.keys():
    #    print len(p[i])

    #for i in p.keys():
    #    print [Gind.node[k]["text"] for k in p[i]]




G = read_cn_file('/tmp/Implementation-Build/bin/labels_full.cn')
#for e in G.edges_iter(data=True):
#    e[2]["weight"] = ((e[2]["weight"]) ** 2)
G = G.subgraph(partition(G)[0])
#print_all_edges(G)
m = max([i[2]["weight"] for i in G.edges_iter(data=True)])
#for e in G.edges_iter(data=True):
#    e[2]["weight"] = ((e[2]["weight"]) ** 2)

p = partition(G)
print "p[0]"
print [len(i) for i in p]
#print_all_edges(G.subgraph(p[0]))
#print "p[1]"
#print_all_edges(G.subgraph(p[1]))
#print "p[2]"
#print_all_edges(G.subgraph(p[2]))

#print [len(i) for i in partition(G)]