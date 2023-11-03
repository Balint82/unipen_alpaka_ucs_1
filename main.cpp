#include "class/Reader.h"
#include "class/UCS.h"

#include <iostream>
#include <string>

using namespace std;

int main() {
    Graph build;
    Reader reader(build);
    Matrix matrix(build);
    //cout<<build<<endl;
    cout<<build.addNodeForNodeCounterAndCalc()<<endl;
   

    //PathList mainPathList(build);
   
    //cout<<"MainPathList: "<<endl;
   // cout<<mainPathList<<endl;
   
   build.printNodeCounter(); 
   matrix.makeMatrix(build);
   //cout<<endl;
   
   UCS ucsSpecimen(build, matrix);
   ucsSpecimen.makeWay();


    return 0;
}