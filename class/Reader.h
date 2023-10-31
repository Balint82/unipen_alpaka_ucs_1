#ifndef READER_H
#define READER_H
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <set>

#include "Graph.h"

#pragma once

using namespace std;


class Reader {
    ifstream fin;
    Graph& graph;
    int edgeCounter;
    set<string> startFormer;
    set<string> destFormer;
    set<string> former;
public:
    Reader(Graph& _graph) : graph(_graph){
        fin.open("./data/cities.txt");
        string starterVertex, destVertex;
        double dist;

        if(fin.is_open()==false){
            cout<<"File opening is unsuccessful"<<endl;
            exit(0);
        }

        while(!fin.eof()){
            fin>>starterVertex>>destVertex>>dist;
            graph.addNode(starterVertex, destVertex, dist);
        }    
        fin.close();
    }
};

#endif // READER_H

