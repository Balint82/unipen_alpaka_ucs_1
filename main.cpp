#include "class/Reader.h"
#include "class/Graph.h"
#include "class/Matrix.h"

#include <iostream>
#include <string>

using namespace std;

int main() {
    Graph build;
    Reader reader(build);
   
    cout<<build<<endl;
    cout<<build.addNodeForNodeCounterAndCalc()<<endl;
    Matrix matrix(build);

    //PathList mainPathList(build);
   
    //cout<<"MainPathList: "<<endl;
   // cout<<mainPathList<<endl;
   
   build.printNodeCounter(); 
   matrix.makeMatrix(build);
   cout<<endl;
     


    return 0;
}