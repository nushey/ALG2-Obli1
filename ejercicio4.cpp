#include <stdio.h>
#include <iostream>
#include "./adts/list_graph.cpp"
#include "./adts/minHeap.cpp"
#include "./adts/linked_list.cpp"


using namespace std;

void initializeCosts(int*& costs, int n){
    for(int i = 1; i <= n; i++){
        costs[i] = -1;
    }
}

void dijkstra(Graph*& graph, int origin, int edges, int*& costs){

    costs[origin] = 0;

    PriorityQueue<int,int>* pq = new MinHeap<int,int>(edges);
    pq->enqueue(origin, 0);

    while(!pq->isEmpty()){
        int node = pq->top();
        pq->dequeue();
        Iterator<Edge>* edges = graph->getNeighbors(node);
        while(edges->hasNext()){
            Edge neighbor = edges->next();
            int neighborNode = neighbor.to; 
            int edgeWeight = neighbor.weight; 
            int newCost = edgeWeight + costs[node];
            if(newCost < costs[neighborNode] || costs[neighborNode] == -1){
                costs[neighborNode] = newCost;
                pq->enqueue(neighborNode, newCost);
            }
        }
    }
    delete pq;
}


int main(){

    int v,e;
    cin >> v >> e;
    int* costs = new int[v+1];
    Graph* graph = new ListGraph(v);
    for(int i = 0; i < e; i++){
        int from,to,weight;
        cin >> from >> to >> weight;
        graph->addW(from,to,weight);
    }
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++){
        int vertex;
        cin >> vertex;
        initializeCosts(costs, v);
        dijkstra(graph, vertex, v, costs);
        costs[vertex] = -1; // Output 

        for(int j = 1; j <= v; j++){
            cout << costs[j] << endl;
        }
    }

    return 0;
}
