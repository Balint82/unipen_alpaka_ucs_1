#ifndef UCS_H
#define UCS_H

#include "Matrix.h"
#include <string.h>
#include <iostream>

#pragma once
using namespace std;



class UCS{
    Graph wayGraph;
    Matrix wayMatrix;

public:
    UCS(Graph& _wayGraph, Matrix& _wayMatrix) : wayGraph(_wayGraph), wayMatrix(_wayMatrix){}
    ~UCS(){
        wayMatrix.dozerMatrix();
    }

    pair<string, double> UCSmakeWay(string incomingStarStr, string incomingDestStr){
        Node inputStartNode, inputDestNode, startNode, destNode, min, mint;
        int row = 0, col;
        list<Node> allNodeList, momentNodeList;
        double** mapMatrix = wayMatrix.getAdjMatrix();
        int mapMatrixSize = wayGraph.addNodeForNodeCounterAndCalc();
        double itemWeight;
        set<Node> nodeSet = wayGraph.getNodeCounter();
        pair<string, int> UCSresult;
       
        inputStartNode.name = incomingStarStr;
        inputStartNode.weight = 0.0;

        inputDestNode.name = incomingDestStr;
        

        int counter = 0;
        while(true){
            //sor keresés megadott kiinduló város alapján
            auto itRow = nodeSet.find(inputStartNode);
            if(itRow != nodeSet.end()){
                row = distance(nodeSet.begin(), itRow);
            } 
            
            //oszlop választások és tárolások
            for(col = 0; col < mapMatrixSize; col++){
                itemWeight = mapMatrix[row][col]; //a szülő csúcs súlya hozzáadódik a gyerek csúcsok súlyához
                if(itemWeight > 0.0 ){
                    itemWeight = mapMatrix[row][col] + inputStartNode.weight;
                    auto itColShowDestNode = nodeSet.begin();
                    advance(itColShowDestNode, col);
                    destNode = *itColShowDestNode;
                    destNode.weight = itemWeight;
                    momentNodeList.push_back(destNode);
                }

            }
        
            min = momentNodeList.front();
            for(const Node& item : momentNodeList){
                if(item.weight < min.weight){
                    min = item;
                }
            }

            if(inputDestNode.name == min.name){
                UCSresult.first = min.name;
                UCSresult.second = min.weight;
                break;
            } else{
                inputStartNode = min;
                momentNodeList.remove(min);     
            }
            counter++;
        }

        return UCSresult;
    }
};

#endif // UCS_H











