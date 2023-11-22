#ifndef MATRIX_H
#define MATRIX_H

#include "Graph.h"
#include "Reader.h"

#include <iostream>
#include <algorithm>

#pragma once
using namespace std;


class Matrix {
    Graph incomingNodes;
    string startVertex;
    string destiniVertex;
    double weight;
   

    double** adjacencyMatrix;
    int n;
public:
    class AdjMatrixRow{
        Matrix& adjMatrix;
        int rowCol;
       
        AdjMatrixRow(Matrix& _adjMatrix, int _rowCol):adjMatrix(_adjMatrix),rowCol(_rowCol){}
        friend class Matrix;
        public:
       
        double& operator[](int t){
            return adjMatrix.adjacencyMatrix[rowCol][t];
        }
    };

    AdjMatrixRow operator[](int rowCol){
        return AdjMatrixRow(*this, rowCol);
    }
    
    Matrix(const Graph& _graph) : incomingNodes(_graph){
            n = incomingNodes.addNodeForNodeCounterAndCalc();
            adjacencyMatrix = new double*[n];
        
            for(int i = 0; i < n; i++){
                adjacencyMatrix[i] = new double[n];
                for(int j = 0; j < n; j++){ 
                    adjacencyMatrix[i][j] = 0;
                    
            }
        }
    }

    ~Matrix(){} 
    
    void dozerMatrix(){
        for (int k = 0; k < n; k++){
            delete[] adjacencyMatrix[k];
        }
        delete[] adjacencyMatrix;
    }
                    

    void makeMatrix(Graph& incomingNodes) { 
        int i , j;
        i = j = 0;
        set<Node> matrixClassNodeCounter;
        map<Node, set<Node>> matrixClassNodeMap;
        
        matrixClassNodeCounter = incomingNodes.getNodeCounter(); 
        matrixClassNodeMap = incomingNodes.getAllNodeMap();
       

        //végigmegy a halmazon
        for(const Node& setItem : matrixClassNodeCounter){
            //map párokon iterálás
            for(const auto& pair : matrixClassNodeMap){
                //ha talál olyat ami a halmazban van és a map kulcsai között megtalálható
                if(setItem.name == pair.first.name){
                    //akkor induljon el map értékein iterálva
                    for(const Node& mapValue : pair.second){
                         auto it = find(matrixClassNodeCounter.begin(), matrixClassNodeCounter.end(), mapValue);
                         if (it != matrixClassNodeCounter.end()) {
                            j= distance(matrixClassNodeCounter.begin(), it);
                             adjacencyMatrix[i][j] = mapValue.weight;
                         }
                    }
                }
            
            }
            i++;
        }
    }

    double** getAdjMatrix(){
        return adjacencyMatrix;
    }



    friend ostream& operator<<(ostream& s, const Matrix& matrix){
        for(int i = 0; i < matrix.n; i++){
            for(int j = 0; j < matrix.n; j++){
                 s<<matrix.adjacencyMatrix[i][j]<<"\t";
            }
            s<<endl;
            s<<endl;
        }
        return s;
    }
};


#endif // MATRIX_H