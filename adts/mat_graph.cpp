#pragma once
#include "./graph.cpp"
#include "./assert.h"
#include "linked_list.cpp"

class MatGraph : Graph {
    int** mat;
    int vertexs;

    public:
        MatGraph(int vertexs){
            this->vertexs = vertexs;
            this->mat = new int*[vertexs+1];
            for(int i = 1; i <= vertexs; i++){
                this->mat[i] = new int[vertexs+1];
                for(int j = 1; j <= vertexs; j++){
                    mat[i][j] = 0;
                }
            }
        }
        virtual Iterator<Edge>* getAllEdges() override {

        };
        virtual int vertexCount() override {
            return this->vertexs;
        };
        virtual Iterator<Edge>* getNeighbors(int v) override {
            assert(v >= 0);
            assert(v <= this->vertexs);
            List<Edge>* l = new LinkedList<Edge>();
            for(int i = 1; i <= this->vertexs; i++){
                if(this->mat[v][i] != 0){
                    Edge e = Edge();
                    e.from = v;
                    e.to = i;
                    e.weight = this->mat[v][i];
                    l->add(e);
                }
            }
            return l->iterator();

        };
        virtual bool isNeighbor(int v1, int v2) override {

        };
        virtual int getWeight(int v1, int v2) override {

        };
        virtual void add(int v1, int v2) override {
            assert(v1 <= this->vertexs);
            assert(v1 >= 0);
            assert(v2 <= this->vertexs);
            assert(v2 >= 0);
            this->mat[v1][v2] = 1;
        };
        virtual void addW(int v1, int v2, int w) override {
            assert(v1 <= this->vertexs);
            assert(v1 >= 0);
            assert(v2 <= this->vertexs);
            assert(v2 >= 0);
            this->mat[v1][v2] = w;
        };
        virtual void remove(int v1, int v2) override {
            addW(v1,v2, 0);
        };
        virtual int** getAdjMatrix() override {

        };
};