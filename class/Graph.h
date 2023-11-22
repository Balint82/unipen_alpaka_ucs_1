#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <list>
#include <set>
#include <map>

#pragma once

using namespace std;


struct Node{
    string name;
    double weight;
    int hotel;

    bool operator==(const Node& other) const {
        return name == other.name;
    }

    bool operator!=(const Node& other) const {
        return name != other.name;
    }

    bool operator<(const Node& other) const {
        return name < other.name;
    }
};


class Graph{
    map<Node, set<Node>> allNodeMap; //fájlból az összes kiindulóvároshoz, rendel célváros halmazt.
    set<Node> nodeCounter;
public:
    Graph(){};
    ~Graph(){};

    map<Node, set<Node>> getAllNodeMap(){
        return allNodeMap;
    }

    set<Node> getNodeCounter(){
        return nodeCounter;
    }

    

    void addNode(string sourceCity, string targetCity, double distance, int incomingHotel){
        Node sourceCityNode;
        Node newCityNode;
    
        sourceCityNode.name = sourceCity;
        sourceCityNode.weight = 0.0;
        newCityNode.name = targetCity;
        newCityNode.weight = distance;
        newCityNode.hotel = incomingHotel;
        
        allNodeMap[sourceCityNode].insert(newCityNode);
    }

    int addNodeForNodeCounterAndCalc(){
        int result = 0;

        for(const auto& pair : allNodeMap){
            nodeCounter.insert(pair.first);
            for(const Node& value : pair.second){
                nodeCounter.insert(value);
            }
        }

        result = nodeCounter.size();

        
        return result;
    }

    

    

    
    friend ostream& operator<<(ostream& s, const Graph& graph){
        for(const auto& pair : graph.allNodeMap){
            s<<pair.first.name<<" -> ";
            for(const Node& node : pair.second){
                s<<"\t  "<<node.name<<"\t"<<node.weight<<" km";
            }
            s<<endl;
        }

        return s;
    }

   


};


#endif // GRAPH_H