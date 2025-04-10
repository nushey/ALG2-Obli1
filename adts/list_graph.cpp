#pragma once
#include "./graph.cpp"
#include "./linked_list.cpp"
#include <assert.h>

class ListGraph : public Graph {

    List<Edge> **graph;
    int vertexs;

    public:

        ListGraph(int vertexs){
            this->vertexs = vertexs;
            this->graph = new List<Edge> *[vertexs+1];
            for(int i = 1; i <= vertexs; i++){
                this->graph[i] = new LinkedList<Edge>();
            }

        }

        virtual Iterator<Edge>* getAllEdges() override{
            List<Edge> *edges = new LinkedList<Edge>();
            for(int i = 1; i <= this->vertexs; i++){
                Iterator<Edge> *it = this->graph[i]->iterator();
                while(it->hasNext()){
                    Edge e = it->next();
                    edges->add(e);
                }
            }
            return edges->iterator();
        }
        virtual int vertexCount() override {
            return this->vertexs;
        };
        virtual Iterator<Edge>* getNeighbors(int v) override {
            assert(v >= 0 && v <= this->vertexs);
            return this->graph[v]->iterator();
        };
        virtual bool isNeighbor(int v1, int v2) override {
            assert(v1 >= 0 && v1 <= this->vertexs);
            assert(v2 >= 0 && v2 <= this->vertexs);
            Iterator<Edge>* it = this->graph[v1]->iterator();
            while(it->hasNext()){
                Edge e = it->next();
                if(e.to == v2) return true;
            }
            return false;
        };
        virtual int getWeight(int v1, int v2) override {
            assert(v1 >= 0 && v1 <= this->vertexs);
            assert(v2 >= 0 && v2 <= this->vertexs);
            Iterator<Edge>* it = this->graph[v1]->iterator();
            while(it->hasNext()){
                Edge e = it->next();
                if(e.to == v2) return e.weight;
            }
            return -1;
        };
        virtual void add(int v1, int v2) override {
            addW(v1,v2, 1);

        };
        virtual void addW(int v1, int v2, int w) override {
            assert(v1 >= 0 && v1 <= this->vertexs);
            assert(v2 >= 0 && v2 <= this->vertexs);
            remove(v1,v2);
            Edge e;
            e.from = v1;
            e.to = v2;
            e.weight = w;
            this->graph[v1]->add(e);
        };
        virtual void remove(int v1, int v2) override {
            assert((v1 >= 0 && v1 <= this->vertexs));
            assert((v2 >= 0 && v2 <= this->vertexs));
            Edge e = Edge();
            e.from = v1;
            e.to = v2;
            this->graph[v1]->remove(e);
        };

        virtual int** getAdjMatrix() override {
            int** adjM = new int*[this->vertexs+1];
            for(int i = 1; i <= this->vertexs; i++){
                Iterator<Edge> *it = this->graph[i]->iterator();
                while(it->hasNext()){
                    Edge e = it->next();
                    adjM[i][e.to] = e.weight;
                }
            }
            return adjM;
        };

};