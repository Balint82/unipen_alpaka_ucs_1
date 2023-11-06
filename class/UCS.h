#include "Graph.h"
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

    void makeWay(){
        Node inputStartNode, inputDestNode, startNode, destNode, min, mint;
        int row = 0, col;
        list<Node> allNodeList, momentNodeList;
        vector<Node> allVector;
        vector<double> allWeight;
        double** mapMatrix = wayMatrix.getAdjMatrix();
        int mapMatrixSize = wayGraph.addNodeForNodeCounterAndCalc();
        double itemWeight;
        set<Node> nodeSet = wayGraph.getNodeCounter();
        //vector<Node> nodesVector(nodeSet.begin(), nodeSet.end());
        cout<<"Kerem adja meg a kiindulo varost: ";
        cin>>inputStartNode.name;
        inputStartNode.weight = 0.0;
        cout<<"Kerem adja meg a celvarost: ";
        cin>>inputDestNode.name;
        cout<<endl;
        while(cin.fail()){
            cout<<"Beolvasas hiba."<<endl;
            cin.clear();
        }



        int counter = 0;
        while(true){
            //sor keresés megadott kiinduló város alapján
            auto itRow = nodeSet.find(inputStartNode);
            if(itRow != nodeSet.end()){
                row = distance(nodeSet.begin(), itRow);
            } 
            //row oké
            cout<<"inputStartNode1: "<<inputStartNode.name<<inputStartNode.weight<<endl;
            //oszlop választások és tárolások
            for(col = 0; col < mapMatrixSize; col++){
                itemWeight = mapMatrix[row][col]; //a szülő csúcs súlya hozzáadódik a gyerek csúcsok súlyához
                if(itemWeight > 0.0 ){
                    itemWeight = mapMatrix[row][col] + inputStartNode.weight;
                    cout<<mapMatrix[row][col]<<" "<<inputStartNode.weight<<" "<<itemWeight<<"\t";
                    auto itColShowDestNode = nodeSet.begin();
                    advance(itColShowDestNode, col);
                    destNode = *itColShowDestNode;
                    destNode.weight = itemWeight;
                    momentNodeList.push_back(destNode);
                }

            }
        
            cout<<endl;
            cout<<"MNL gyerekcsucsok utan: "<<endl;
             for(const Node& item : momentNodeList){
               cout<<item.name<<item.weight<<"\t";
            }
            cout<<endl;
            //momentNodeList oké
            min = momentNodeList.front();
            for(const Node& item : momentNodeList){
                if(item.weight < min.weight){
                    min = item;
                }
            }

            cout<<"MomentNodelist minimum utan: "<<endl;           
            for(const Node& item : momentNodeList){
               cout<<item.name<<item.weight<<"\t";
            }
            cout<<endl;

            if(inputDestNode.name == min.name){
                cout<<"Elerted a celvarost: "<<min.name<<min.weight<<endl;
                
                cout<<endl;
                for(const Node& item : momentNodeList){
                    cout<<item.name<<item.weight<<"\t";
                }
                cout<<endl;

                break;
            } else{
                inputStartNode = min;
                momentNodeList.remove(min);
                cout<<"inputStartNode2: "<<inputStartNode.name<<inputStartNode.weight<<endl;

                cout<<"MNL else agban: "<<endl;
                for(const Node& item : momentNodeList){
                    cout<<item.name<<item.weight<<"\t";
                }
                cout<<endl;
                cout<<endl;
                cout<<counter<<endl;
                   
            }
            counter++;
        }

    }
    
};












/*
//mátrix sorai közül kiválasztani a kezdővárost és a halmaz alapján megnevezni.
        auto itStart = nodeSet.find(inputStartNode);
        if(itStart != nodeSet.end()){
            row = distance(nodeSet.begin(), itStart);
        }
        startNode = inputStartNode;
        startNode.weight = 0.0;


                //oszlop választások és tárolások
                for(col = 0; col < mapMatrixSize; col++){
                    itemWeight = mapMatrix[row][col]; //a startNode-ik sor col-adik eleme
                    cout<<mapMatrix[row][col]<<"\t";

                    if(itemWeight > 0.0){
                        auto it = nodeSet.begin(); //a col-adik elem keresése a halmazban
                        advance(it, col);
                        destNode.name = it->name; //a célNode a col-adik elemhez tartozó Node
                        destNode.weight = itemWeight;
                        destNode.weight += startNode.weight;
                        momentNodeList.push_back(destNode);
                    }
                }


*/