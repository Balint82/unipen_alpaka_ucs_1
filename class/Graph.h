#ifndef SOURCE_GRAPH_H_
#define SOURCE_GRAPH_H_

#include <iostream>
#include <string>
#include <map>
#include <list>

using namespace std;

struct Edge {
    string targetCity;
    double distance;

    /*bool operator<(const Edge& other) const {
            return targetCity < other.targetCity;
        }*/
};

class Graph {
protected:
    map<string, list<Edge>> mapping;
public:
    Graph(){}
    ~Graph(){}


    void addEdge(string sourceCity, string targetCity, double distance){
        Edge edge;
        edge.targetCity = targetCity;
        edge.distance = distance;
        mapping[sourceCity].push_back(edge);
    }

     map<string, list<Edge>> getMapping(){
       return mapping;
    }

    friend ostream& operator<<(ostream& s, const Graph& graph) {
        for (const auto& pair : graph.mapping) {
            s << pair.first << "-";
            for (const Edge& edge : pair.second) {
                s << edge.targetCity << " "<< edge.distance <<"km"<<endl;
            }
        }
        return s;
    }

   
};

#endif /* SOURCE_GRAPH_H_ */
