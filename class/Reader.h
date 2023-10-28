#ifndef READER_H
#define READER_H
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <set>


#include "Graph.h"

using namespace std;


class Reader {
    ifstream fin;
    Graph& graph;
    int edgeCounter;
    set<string> startFormer;
    set<string> destFormer;
    set<string> former;
public:
    Reader(Graph& _graph, int _edgeCounter = 0) : graph(_graph){
        fin.open("./data/cities.txt");
        string starterVertex, destVertex;
        double dist;
        edgeCounter = _edgeCounter;

        if(fin.is_open()==false){
            cout<<"File opening is unsuccessful"<<endl;
            exit(0);
        }

        while(!fin.eof()){
            fin>>starterVertex>>destVertex>>dist;
            graph.addEdge(starterVertex, destVertex, dist);

            this->startFormer.insert(starterVertex);
            this->destFormer.insert(destVertex);
            this->former.insert(starterVertex);
            this->former.insert(destVertex);
        }    
        fin.close();

        for(auto it = former.begin(); it != former.end(); it++){
            edgeCounter++;
        }
    }


    int getEdgeCounter(){
        return edgeCounter;
    }

    set<string> getStartFormer(){
        return startFormer;
    }

    set<string> getDestFormer(){
        return destFormer;
    }

    set<string> getFormer(){
        return former;
    }
};

#endif // READER_H

