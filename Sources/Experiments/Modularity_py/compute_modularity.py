# -*- coding: utf-8 -*-
from audioop import reverse

__author__ = 'wachs'

import sys
from ctypes import *
import networkx as nx
from networkx.algorithms import *
import community
import matplotlib.pyplot as plt


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
    #modularity = community.modularity(partition, G)
    #print("Modularity: " + str(modularity))
    return partition


def clustersSizes(partition):
    p = {}
    for i in partition.items():
        if i[1] in p:
            p[i[1]].append(i[0])
        else:
            p[i[1]] = list()
            p[i[1]].append(i[0])
    return [len(p[i]) for i in p.keys()]



def splitCluster(G, partition, x):
    nodes = [i[0] for i in partition.items() if i[1] == x]
    Gind = G.subgraph(nodes)
    sub_partition = community.best_partition(Gind)
    max_cluster = max(sub_partition.values())
    sub_partition = dict({(i[0], i[1]+x) for i in sub_partition.items()})
    return dict({i if i[1] < x else (i[0], sub_partition[i[0]]+1) if i[0] in sub_partition else (i[0], i[1]+
                                                                        max_cluster+x+1) for i in partition.items()})
 #1:0, 2:0, 3:1, 4:1, 5:1, 6:2



if __name__ == "__main__":
    print

    G1 = read_cn_file('/tmp/Implementation-Build/bin/labels_full.cn')

    p1 = partition(G1)
    sizes = clustersSizes(p1)
    ordered = sorted(range(len(sizes)), key=lambda k: sizes[k], reverse=True)
    p1 = splitCluster(G1, p1, ordered[0])
    print "Modularity: " + str(community.modularity(p1, G1))
    sizes = clustersSizes(p1)
    ordered = sorted(range(len(sizes)), key=lambda k: sizes[k], reverse=True)
    p1 = splitCluster(G1, p1, ordered[0])
    print "Modularity: " + str(community.modularity(p1, G1))


    plt.plot(range(1, len(clustersSizes(p1))+1), sorted(clustersSizes(p1), reverse=True))
    plt.xlabel("No. do Cluster")
    plt.ylabel("Tamanho do Cluster")
    #plt.title(u"Quantidade de nós para cada cluster (subclusterizando C1)")
    plt.title(u"Quantidade de nós para cada cluster (subclusterizando C1 e C2)")
    plt.show()

