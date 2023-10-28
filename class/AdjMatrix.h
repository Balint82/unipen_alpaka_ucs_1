#include "Graph.h"
#include "Reader.h"

#include <iostream>

using namespace std;


class AdjMatrix {
    Graph incomingEdges;
    string startVertex;
    string destiniVertex;
    double weight;
    Reader& reader;

    double** adjacencyMatrix;
    int n;
public:
    class AdjMatrixRow{
        AdjMatrix& adjMatrix;
        int rowCol;
       
        AdjMatrixRow(AdjMatrix& _adjMatrix, int _rowCol):adjMatrix(_adjMatrix),rowCol(_rowCol){}
        friend class AdjMatrix;
        public:
       
        double& operator[](int t){
            return adjMatrix.adjacencyMatrix[rowCol][t];
        }
    };

    AdjMatrixRow operator[](int rowCol){
        return AdjMatrixRow(*this, rowCol);
    }
    
    AdjMatrix(Reader& _reader) : reader(_reader){
            n = reader.getEdgeCounter();
            adjacencyMatrix = new double*[n];
        
            for(int i = 0; i < n; i++){
                adjacencyMatrix[i] = new double[n];
                for(int j = 0; j < n; j++){ 
                    adjacencyMatrix[i][j] = 0;
                    
            }
        }
    }

    ~AdjMatrix() {
        for (int k = 0; k < n; k++)
                delete[] adjacencyMatrix[k];
        delete[] adjacencyMatrix;
    }
                    

    void makeMatrix(Graph& incomingEdges) { 
        int i , j;
        i = j = 0;                               
        for (const auto& pair : incomingEdges.getMapping()) { 
            for (const Edge& edge : pair.second) {
                if(i < n && j < n){
                adjacencyMatrix[i][j] = edge.distance;
                }
                ++j;
            }
            ++i;
        }
    }

    double** getAdjMatrix(){
        return adjacencyMatrix;
    }



    friend ostream& operator<<(ostream& s, const AdjMatrix& matrix){
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