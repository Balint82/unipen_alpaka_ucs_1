#include "class/TimeCalc.h"

#include <iostream>
#include <string>


using namespace std;



int main() {
    Graph build;
    Reader reader(build);
    Matrix matrix(build); 

    build.addNodeForNodeCounterAndCalc(); 
    matrix.makeMatrix(build);

    UCS ucsSpecimen(build, matrix);
    Planner wayMap(ucsSpecimen, reader);
    unordered_map<string, list<double>> mainMap = wayMap.makePlan();
    wayMap.setSettlementVectors(mainMap);
    wayMap.printVectors();

    TimeCalc timeCalculator(wayMap);
    timeCalculator.measureTime();


    return 0;
}