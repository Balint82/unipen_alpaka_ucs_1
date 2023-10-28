#include "class/Graph.h"
#include "class/Reader.h"
#include "class/AdjMatrix.h"

#include <iostream>

using namespace std;

int main(){
    Graph graphFirst;
    Reader reader(graphFirst);
    AdjMatrix matrix(reader);
    matrix.makeMatrix(graphFirst);
    //graphFirst.addEdge("Budapest", "Debrecen", 230);

    cout<<graphFirst<<endl;
    cout<<"Reader.getEdgeCounter: "<<reader.getEdgeCounter()<<endl;
    cout<<endl;
    cout<<"Adj matrix: "<<endl;
    cout<<matrix<<endl;
   
    return 0;
}


