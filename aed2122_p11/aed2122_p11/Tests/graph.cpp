// AED 2021/2022 - Aula Pratica 11
// Pedro Ribeiro (DCC/FCUP) [17/01/2022]

#include "graph.h"
#include <climits>

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, int weight) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, weight});
    if (!hasDir) nodes[dest].adj.push_back({src, weight});
}


// ----------------------------------------------------------
// 1) Algoritmo de Dijkstra e caminhos mais curtos
// ----------------------------------------------------------

// ..............................
// a) Distância entre dois nós
// TODO
int Graph::dijkstra_distance(int a, int b) {
    for(int i=1; i<=n; i++ ) {
        nodes[i].dist = INT_MAX;
        nodes[i].visited = false;
    }
    nodes[a].dist=0;
    MinHeap<int, int> minHeap(n, -1);
    for(int i=1; i<=n; i++ ) {
        minHeap.insert(i, nodes[i].dist);
    }
    while (minHeap.getSize()>0){
        int u= minHeap.removeMin();
        nodes[u].visited=true;
        for(auto v:nodes[u].adj){
            if(!nodes[v.dest].visited && nodes[u].dist+v.weight<nodes[v.dest].dist){
                minHeap.decreaseKey(v.dest,v.weight);
                nodes[v.dest].dist=nodes[u].dist+v.weight;
            }
        }
    }
    if(nodes[b].dist==INT_MAX)
        return -1;

    return nodes[b].dist;
}

// ..............................
// b) Caminho mais curto entre dois nós
// TODO
list<int> Graph::dijkstra_path(int a, int b) {
    for(int i=1; i<=n; i++ ) {
        nodes[i].dist = INT_MAX;
        nodes[i].visited = false;
        nodes[i].pred=-1;
    }
    nodes[a].dist=0;
    nodes[a].pred=a;
    MinHeap<int, int> minHeap(n, -1);
    for(int i=1; i<=n; i++ ) {
        minHeap.insert(i, nodes[i].dist);
    }
    while (minHeap.getSize()>0){
        int u= minHeap.removeMin();
        nodes[u].visited=true;
        for(auto v:nodes[u].adj){
            if(!nodes[v.dest].visited && nodes[u].dist+v.weight<nodes[v.dest].dist){
                minHeap.decreaseKey(v.dest,v.weight);
                nodes[v.dest].dist=nodes[u].dist+v.weight;
                nodes[v.dest].pred=u;
            }
        }
    }
    list<int> result;
    if(nodes[b].pred==-1)
        return result;
    result.push_front(b);
    while(b!=a){
        result.push_front(nodes[b].pred);
        b=nodes[b].pred;
    }
    return result;
}
