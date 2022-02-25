// AED 2021/2022 - Aula Pratica 10
// Pedro Ribeiro (DCC/FCUP) [09/01/2022]

#include <algorithm>
#include "graph.h"

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
// Exercicio 3: Algoritmo de Prim
// ----------------------------------------------------------
// TODO
int Graph::prim(int r) {
    int sum=0;
    MinHeap<int, int> q(n, -1);
    for(int i=1; i<=n; i++){
        nodes[i].distance=INT_MAX/2;
        nodes[i].parent=NULL;
        q.insert(i, nodes[i].distance);
    }
    nodes[r].distance=0;
    q.decreaseKey(r, 0);
    while(q.getSize()>0){
        int u=q.removeMin();
        for(auto e:nodes[u].adj){
            int v=e.dest;
            if(q.hasKey(v) && e.weight<nodes[v].distance){
                nodes[v].parent=u;
                nodes[v].distance=e.weight;
                q.decreaseKey(v, e.weight);
            }
        }
    }
    for(auto const & node : nodes)
        sum += node.distance;
    return sum;
}

int Graph::primFun(vector<int> plantas) {
    int sum=0;
    MinHeap<int, int> q(n, -1);
    for(int i=1; i<=n; i++){
        nodes[i].distance=INT_MAX/2;
        nodes[i].parent=NULL;
        q.insert(i, nodes[i].distance);
    }
    for(auto i:plantas){
        nodes[i].distance=0;
        q.decreaseKey(i, 0);
    }
    while(q.getSize()>0){
        int u=q.removeMin();
        for(auto e:nodes[u].adj){
            int v=e.dest;
            if(q.hasKey(v) && e.weight<nodes[v].distance){
                nodes[v].parent=u;
                nodes[v].distance=e.weight;
                q.decreaseKey(v, e.weight);
            }
        }
    }
    for(auto const & node : nodes)
       sum += node.distance;
    return sum;
}
// ----------------------------------------------------------
// Exercicio 5: Algoritmo de Kruskal
// ----------------------------------------------------------
// TODO
int Graph::kruskal() {
    struct E {
        int origin;
        int dest;   // Destination node
        int weight; // An integer weight
    };
    DisjointSets<int> s;
    int t=0;
    vector<E> edges;
    for(int i=1; i<=n; i++) {
        s.makeSet(i);
        for(auto edge:nodes[i].adj){
            edges.push_back({i, edge.dest, edge.weight});
        }
    }
    sort(edges.begin(), edges.end(), [](E e1, E e2){ return e1.weight<e2.weight;});
    for(auto edge:edges){
        if(s.find(edge.origin)!=s.find(edge.dest)){
            t+=edge.weight;
            s.unite(edge.origin, edge.dest);
        }
    }
    return t;
}
