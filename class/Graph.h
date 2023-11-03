#include <iostream>
#include <list>
#include <set>
#include <map>

#pragma once

using namespace std;


struct Node{
    string name;
    double weight;

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

    
    void printNodeCounter(){
        for(const Node& item : nodeCounter){
            cout<<item.name<<" - ";
        }
        cout<<endl<<endl;

        for(const Node& item : nodeCounter){
            cout<<item.name<<endl;
        }
        cout<<endl<<endl;   
    }

    void addNode(string sourceCity, string targetCity, double distance){
        Node sourceCityNode;
        Node newCityNode;
        sourceCityNode.name = sourceCity;
        sourceCityNode.weight = 0.0;
        newCityNode.name = targetCity;
        newCityNode.weight = distance;

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