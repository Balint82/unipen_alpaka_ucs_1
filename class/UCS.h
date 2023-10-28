#include <iostream>
#include "Reader.h"
#include "AdjMatrix.h"

class UCS{
    string startCity;
    string destinCity;
    Reader& reader;
    AdjMatrix& adjMatrix;
public:
    UCS(Reader& _reader, AdjMatrix& _adjMatrix) : reader(_reader), adjMatrix(_adjMatrix){};
    ~UCS(){};

    void ucsCalc(){
        set<string> formerUcs = reader.getFormer();



        
    }

};