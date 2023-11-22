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
    
public:
    Reader(Graph& _graph) : graph(_graph){
        fin.open("./data/cities.txt");
        string starterVertex, destVertex;
        double dist;
        int hotel;

        if(fin.is_open()==false){
            cout<<"File opening is unsuccessful"<<endl;
            exit(0);
        }

        while(!fin.eof()){
            fin>>starterVertex>>destVertex>>dist>>hotel;
            graph.addNode(starterVertex, destVertex, dist, hotel);
        }    
        fin.close();
    }

    int hotelFinder(string station){
        string starterVertex, destVertex;
        double dist;
        int hotelReader;
        ifstream finput;
        finput.open("./data/cities.txt");
        string line;
        int lineCounter = 0;
        int hotelResult;

        if(finput.is_open()==false){
            cout<<"File opening is unsuccessful"<<endl;
            exit(0);
        }
        
        while(!finput.eof()){
        if(finput>>starterVertex>>destVertex>>dist>>hotelReader){
       
            if(station == destVertex){
                hotelResult = hotelReader;
            }
             
            }else {
                cout<<"Sikertelen szálloda érték beolvasás."<<endl;
            }
        }
        finput.close();
        return hotelResult;
    }



    bool isBeginSettlementValid(string rawBeginSettlement){
        map<Node, set<Node>> mapBook = graph.getAllNodeMap();
        bool result = false;

        for(const auto& item : mapBook){
            if(rawBeginSettlement == item.first.name){
                result = true;
            }
        }


        return result;
    }



    bool isEndSettlementValid(string rawStationSettlement){
        map<Node, set<Node>> mapBook = graph.getAllNodeMap();
        bool result = false;

        for(const auto& pair : mapBook){
            for(const Node& item : pair.second){
                if(rawStationSettlement == item.name){
                    result = true;
                }
            }
        }
    
    
        return result;
    }
};

#endif // READER_H

