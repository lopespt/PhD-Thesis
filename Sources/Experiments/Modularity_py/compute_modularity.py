# -*- coding: utf-8 -*-

__author__ = 'wachs'

import sys
from ctypes import *
import networkx as nx
from networkx.algorithms import *
import community
import matplotlib.pyplot as plt


class Header(Structure):
    _fields_ = [('description', c_char * 200),
                ('num_nodes', c_uint),
                ('num_edges', c_uint)]


class Node(Structure):
    _fields_ = [('node_id', c_uint),
                ('type', c_int)]


class LabelNode(Structure):
    _fields_ = [('value', c_char * 50)]


class Linka(Structure):
    _pack_ = 1
    _fields_ = [('time', c_ulonglong),
                ('weight', c_float),
                ('sameLabel', c_bool)]


class Edge(Structure):
    _fields_ = [('node_from', c_uint),
                ('node_to', c_uint),
                ('edge_id', c_uint),
                ('edge', Linka)]


class Bt(Structure):
    _fields_ = [('bt', c_byte*16)]


def print_all_edges(G):
    for node in G.edge:
        for edge in G.edge[node].keys():
            print G.node[node]["text"] + " -> " + G.node[edge]["text"] + " = " + str(G.edge[node][edge]["weight"])


def read_cn_file(path):
    with open(path, 'rb') as f:
        print('entrei')
        G = nx.Graph()
        header = Header()
        f.readinto(header)
        print("Nodes: " + str(header.num_nodes))
        print("Edges: " + str(header.num_edges))
        print( sizeof(Linka))
        for i in range(1, header.num_nodes + 1):
            node = Node()
            f.readinto(node)
            assert node.type in [0]
            if node.type == 0:
                label = LabelNode()
                f.readinto(label)
                node.value = label.value
                G.add_node(node.node_id, {'text': node.value})

        for i in range(1, header.num_edges + 1):
            edge = Edge()
            f.readinto(edge)
            if edge.edge.weight < 1e-30:
                edge.edge.weight = 0
            else:
                G.add_edge(edge.node_from, edge.node_to, weight=edge.edge.weight)

    return G


def partition(G):
    # print("calculando cc")
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
    sub_partition = dict({(i[0], i[1] + x) for i in sub_partition.items()})
    return dict({i if i[1] < x else (i[0], sub_partition[i[0]] + 1) if i[0] in sub_partition else (i[0], i[1] +
                                                                                                   max_cluster + x + 1)
                 for i in partition.items()})


def sub_clusterization_experiment(G1):
    p1 = partition(G1)
    print "Modularity: " + str(community.modularity(p1, G1))

    sizes = clustersSizes(p1)
    ordered = sorted(range(len(sizes)), key=lambda k: sizes[k], reverse=True)
    p1 = splitCluster(G1, p1, ordered[0])
    print "Modularity: " + str(community.modularity(p1, G1))
    sizes = clustersSizes(p1)
    ordered = sorted(range(len(sizes)), key=lambda k: sizes[k], reverse=True)
    p1 = splitCluster(G1, p1, ordered[0])
    print "Modularity: " + str(community.modularity(p1, G1))

    ordered = sorted(range(len(sizes)), key=lambda k: sizes[k])
    while (True):
        word = raw_input("palavra: ")
        s = G1.nbunch_iter([i[0] for i in p1.items() if i[1] == p1[findNode(G1, word)]])
        try:
            for i in s:
                print G1.node[i]["text"] + ", ",
            print
        except:
            pass

    plt.plot(range(1, len(clustersSizes(p1)) + 1), sorted(clustersSizes(p1), reverse=True))
    plt.xlabel("No. do Cluster")
    plt.ylabel("Tamanho do Cluster")
    # plt.title(u"Quantidade de nós para cada cluster (subclusterizando C1)")
    plt.title(u"Quantidade de nós para cada cluster (subclusterizando C1 e C2)")
    plt.show()


def clustering_centrallity_experiment(G):
    partitions = community.best_partition(G)
    sizes = clustersSizes(partitions)
    ordered_sizes = sorted(range(len(sizes)), key=lambda x: sizes[x])
    for i in ordered_sizes:
        print "Centralidade do cluster " + str(i) + u" (Tamanho: %s nós)" % str(sizes[i])
        nodes = [k[0] for k in partitions.items() if k[1] == i]
        # print "nos" + str(nodes)
        Gind = G.subgraph(nodes)
        centr = nx.betweenness_centrality(Gind, weight="weight")
        order = sorted(centr.keys(), key=lambda x: centr[x], reverse=True)
        for j in range(min([len(order), 10])):
            print Gind.node[order[j]]["text"] + ", ",
        print "\n"


def clustering_hubs_experiment(G):
    partitions = community.best_partition(G)
    sizes = clustersSizes(partitions)
    ordered_sizes = sorted(range(len(sizes)), key=lambda x: sizes[x])
    for i in ordered_sizes:
        print "Hubs do cluster " + str(i) + u" (Tamanho: %s nós)" % str(sizes[i])
        nodes = [k[0] for k in partitions.items() if k[1] == i]
        # print "nos" + str(nodes)
        Gind = G.subgraph(nodes)
        hubs = nx.degree(Gind, weight="weight")
        order = sorted(hubs.keys(), key=lambda x: hubs[x], reverse=True)
        for j in range(min([len(order), 10])):
            print "%s (grau: %s), " % (Gind.node[order[j]]["text"], hubs[order[j]]),
        print "\n"


def findNode(G, text):
    for i in G.nbunch_iter():
        if G.node[i]["text"].strip().lower() == text.strip().lower():
            return i
    return None


if __name__ == "__main__":
    G1 = read_cn_file('/tmp/Implementation-Build/bin/labelsNetwork.cn')
    d = G1.degree()
    print d.values()
    d = G1.degree(weight="weight")
    print d.values()

    # sub_clusterization_experiment(G1)
    print "========================Hubs Experiment========================"

    #clustering_hubs_experiment(G1)
    #print "====================Centrallity Experiment====================="
    #clustering_centrallity_experiment(G1)







