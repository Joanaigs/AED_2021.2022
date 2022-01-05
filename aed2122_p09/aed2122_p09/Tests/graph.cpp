// AED 2021/2022 - Aula Pratica 09
// Pedro Ribeiro (DCC/FCUP) [03/01/2022]

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

// Depth-First Search: example implementation
int Graph::dfs(int v) {
    cout << v << " "; // show node order
    int numberOfNodes=1;
    nodes[v].visited = true;
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited)
            numberOfNodes+=dfs(w);
    }
    return numberOfNodes;
}

// Depth-First Search: example implementation
void Graph::bfs(int v) {
    for (int v=1; v<=n; v++) nodes[v].visited = false;
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v]. visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        cout << u << " "; // show node order
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
            }
        }
    }
}

// ----------------------------------------------------------
// Exercicio 1: Introdução a uma classe simplificada de grafos
// ----------------------------------------------------------

// ..............................
// a) Contando diferentes somas de pares
// TODO
int Graph::outDegree(int v) {
    if(v>n ||v<1)
        return -1;
    return nodes[v].adj.size();
}

// ----------------------------------------------------------
// Exercicio 2: Componentes conexos
// ----------------------------------------------------------

// ..............................
// a) Contando componentes conexos
// TODO
int Graph::connectedComponents() {
    int counter=0;
    for(int v=1; v<=n; v++)
        nodes[v].visited=false;
    for(int v=1; v<=n; v++){
        if(!nodes[v].visited) {
            counter++;
            dfs(v);
        }
    }
    return counter;
}

// ..............................
// b) Componente gigante
// TODO
int Graph::giantComponent() {
    int max=0;
    for(int v=1; v<=n; v++)
        nodes[v].visited=false;
    for(int v=1; v<=n; v++){
        if(!nodes[v].visited) {
            int size=dfs(v);
            if(size>max)
                max=size;
        }
    }
    return max;
}


// ----------------------------------------------------------
// Exercicio 3: Ordenacao topologica
// ----------------------------------------------------------
// TODO
list<int> Graph::topologicalSorting() {
    list<int> order;
    for(int v=1; v<=n; v++)
        nodes[v].visited=false;
    for(int v=1; v<=n; v++) {
        if (!nodes[v].visited) {
            dfsTS(v, order);
        }
    }
    return order;
}

void Graph::dfsTS(int v, list<int>& order) {
    nodes[v].visited = true;
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited)
            dfsTS(w, order);
    }
    order.push_front(v);
}

// ----------------------------------------------------------
// Exercicio 4: Distancias em grafos nao pesados
// ----------------------------------------------------------

// ..............................
// a) Distancia entre dois nos
// TODO
int Graph::distance(int a, int b) {
    bfsDis(a);
    return nodes[b].distance;
}

void Graph::bfsDis(int v) {
    for (int v=1; v<=n; v++){
        nodes[v].visited = false;
        nodes[v].distance=-1;
    }
    queue<int> q; // queue of unvisited nodes
    nodes[v].distance=0;
    q.push(v);
    nodes[v]. visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        cout << u << " "; // show node order
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].distance=nodes[u].distance+1;
            }
        }
    }
}

// ..............................
// b) Diametro
// TODO
int Graph::diameter() {
    if(connectedComponents()>1)
        return -1;
    bfsDis(1);
    int maxDis=0;
    for(auto node:nodes){
        if(node.distance>maxDis)
            maxDis=node.distance;
    }
    return maxDis;
}

// ----------------------------------------------------------
// Exercicio 5: To or not be… a DAG!
// ----------------------------------------------------------
// TODO
bool Graph::hasCycle() {
    bool found=false;
    for(int v=1; v<=n; v++)
        nodes[v].color=0;
    for(int v=1; v<=n; v++){
        if(nodes[v].color==0) {
            dfsColor(v, found);
            if(found)
                return true;
        }
    }
    return false;
}

void Graph::dfsColor(int v, bool& found) {
    nodes[v].color=1;
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (nodes[w].color==1)
            found=true;
        else if(nodes[w].color==0)
            dfsColor(w, found);

    }
    nodes[v].color=2;
}
