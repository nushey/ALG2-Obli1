#include <stdio.h>
#include <iostream>
#include "./adts/list_graph.cpp"
#include "./adts/minHeap.cpp"
#include "./adts/linked_list.cpp"


using namespace std;

enum Check{
    EXPLORED,
    VISITED,
    UNVISITED
};

bool cycleCheck(Graph*& graph, int origin, Check* visited){
    visited[origin] = EXPLORED;
    Iterator<Edge>* edges = graph->getNeighbors(origin);
    while(edges->hasNext()){
        Edge neighbor = edges->next();
        int neighborNode = neighbor.to;
        if(visited[neighborNode] == UNVISITED){
            if(cycleCheck(graph, neighborNode, visited)) return true;
        }
        else if(visited[neighborNode] == EXPLORED){
            return true;
        }
    }
    visited[origin] = VISITED;
    return false;
}



int main(){

    ios::sync_with_stdio(false);
    cout.tie(0);
    cin.tie(0);

    int v,e;
    cin >> v >> e;
    Graph* graph = new ListGraph(v);
    Check* visited = new Check[v+1];
    for(int i = 0; i < v; i++){
        visited[i] = UNVISITED;
    }

    for(int i = 0; i < e; i++){
        int from,to;
        cin >> from >> to;
        graph->addW(from,to,1);
    }
    bool ans = false;
    for(int i = 1; i <= v && !ans; i++){
        if(visited[i] == UNVISITED){
            ans = cycleCheck(graph, i, visited);
        }
    }

    cout << ans << "\n";



    return 0;
}