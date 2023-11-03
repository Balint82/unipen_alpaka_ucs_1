#include "Graph.h"
#include "Matrix.h"

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
        Node startNode;
        Node destNode;
        int row = 0;
        int col;
        size_t colContainer;
        list<Node> momentNodeList;
        double** mapMatrix = wayMatrix.getAdjMatrix();
        int mapMatrixSize = wayGraph.addNodeForNodeCounterAndCalc();
        double itemWeight;
        Node minWeightNode;
        Node nodeAtIndex;

        set<Node> nodeSet = wayGraph.getNodeCounter();
        vector<Node> nodesVector(nodeSet.begin(), nodeSet.end());
        
        
        cout<<"Kerem adja meg a kiindulo varost: ";
        cin>>startNode.name;
        startNode.weight = 0.0;

        cout<<"Kerem adja meg a celvarost: ";
        cin>>destNode.name;
        cout<<endl;

        while(cin.fail()){
            cout<<"Beolvasas hiba."<<endl;
            cin.clear();
        }

        if(startNode.name != destNode.name){
            momentNodeList.push_back(startNode);
        }
       
        
        //mátrix sorai közül kiválasztani a kezdővárost
        auto itStart = nodeSet.find(startNode);
        if(itStart != nodeSet.end()){
            row = distance(nodeSet.begin(), itStart);
        }

        cout<<row<<endl;
        cout<<"MomentNodelist:"<<endl;
        for(const Node& listItem : momentNodeList){
            cout<<listItem.name<<listItem.weight;
        }
        cout<<endl;
        //a.) ha megvan a kezdő város ki kell választani a minimum súlyút, ami nem nulla
        cout<<"mapMatrixSize: "<<mapMatrixSize<<endl;
        
        
        for(col = 0; col < mapMatrixSize; col++){
            itemWeight = mapMatrix[row][col]; //a startNode-ik sor col-adik eleme
            cout<<mapMatrix[row][col]<<"\t";
            
            auto it = nodeSet.begin(); //a coladik elem keresése a halmazban
            advance(it, col);
            destNode = *it; //a célNode a coladik elemhez tartozó Node

            destNode.weight = itemWeight; //a coladik elem súlya a mátrix érték
            if(destNode.weight > 0.0)
                momentNodeList.push_back(destNode); //kerüljön be a listába ha nem nulla a súlya
        }
        cout<<endl;
        cout<<endl;
        cout<<"MomentNodelist2: {";
        for(const Node& listItem : momentNodeList){
            cout<<listItem.name<<listItem.weight<<", ";
        }
        cout<<"}"<<endl;
        cout<<endl;

        //a.) momentNodeListből kiválasztjuk a legkisebb költségű csúcsot
        
        //keressen a minWeight-nak az első olyan elemet, ami nem a kiinduló város 
        cout<<"StartNode : "<<startNode.name<<endl;
        for(const Node& item : momentNodeList){
            if(item != startNode){
                cout<<item.name<<endl;
                destNode = item;
                break;
               
            }
        }

         //minimumkeresés
        for(const Node& listItem : momentNodeList){
            if(listItem != startNode){
                if(listItem.weight < destNode.weight){
                    destNode = listItem;
                }
            }
        }

        cout<<"MinWeightNode: ";
        cout<<destNode.name<<destNode.weight<<endl;




        
        









    }



};