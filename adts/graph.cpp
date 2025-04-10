#pragma once
#include "./iterator.cpp"

struct Edge{
    int from;
    int to;
    int weight;

    bool operator==(const Edge &other){
        return this->from == other.from && this->to == other.to;
    }
};

class Graph{
    public:
        virtual Iterator<Edge>* getAllEdges() = 0;
        virtual int vertexCount() = 0;
        virtual Iterator<Edge>* getNeighbors(int v) = 0;
        virtual bool isNeighbor(int v1, int v2) = 0;
        virtual int getWeight(int v1, int v2) = 0;
        virtual void add(int v1, int v2) = 0;
        virtual void addW(int v1, int v2, int w) = 0;
        virtual void remove(int v1, int v2) = 0;
        virtual int** getAdjMatrix() = 0;


};