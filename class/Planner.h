#ifndef PLANNER_H
#define PLANNER_H

#include "UCS.h"

#include <iostream>
#include <list>
#include <map>
#include <vector>

#pragma once
using namespace std;

class Planner{
    UCS& ucsEngine;
    Reader& monocle;
    vector<string> settlementNamesVector;
    vector<double> settlementDistancesVector;
    vector<double> numbersOfAlpacaInhabitantsOfTheSettlementVector;
    vector<double> sumTimeVector;
    vector<int> hotelVector;

public:
    Planner(UCS& _ucsEngine, Reader& _monocle) : ucsEngine(_ucsEngine), monocle(_monocle){}
    ~Planner(){}

    unordered_map<string, list<double>> makePlan(){
        string startSettlementDelivery;
        string stationSettlementDelivery;
        int soulNrOfAlpacas;
        double convertedSoulOfAlpacas;
        list<double> citydatas;
        pair<string, double> incomingUcsPair;
        unordered_map<string, list<double>> wayPlanStorageMap;
        int hotelExist;
      
        
        try{
            cout<<"Kérem adja meg a kiinduló települést: ";
            cin>>startSettlementDelivery;
            
            if(!monocle.isBeginSettlementValid(startSettlementDelivery))
                throw invalid_argument("A megadott kiinduló település nem létezik.");
            
            wayPlanStorageMap[startSettlementDelivery].push_front(0.0);
            hotelExist = monocle.hotelFinder(startSettlementDelivery);
            hotelVector.push_back(hotelExist);

            while(true){     
                cout<<"Kérem adjon meg egy állomástelepülést: ";
                cin>>stationSettlementDelivery;


                if (stationSettlementDelivery != "ok"){   
                    if(!monocle.isEndSettlementValid(stationSettlementDelivery)){
                        throw invalid_argument("A megadott állomástelepülés nem létezik.");
                    } 

                    cout<<"Kérem adja meg az állomástelepülésen található Alpakák számát: ";
                    cin>>soulNrOfAlpacas;

                    while(cin.fail()){
                        throw runtime_error("Beolvasás hiba.");
                        cin.clear();
                    }

                    convertedSoulOfAlpacas = static_cast<double>(soulNrOfAlpacas);
                
                    
                    incomingUcsPair = ucsEngine.UCSmakeWay(startSettlementDelivery,stationSettlementDelivery);
                
                    wayPlanStorageMap[incomingUcsPair.first].push_front(incomingUcsPair.second);

                    auto it = std::next(wayPlanStorageMap[incomingUcsPair.first].begin(), 1);  // Itt az 1 a második helyet jelenti
                    wayPlanStorageMap[incomingUcsPair.first].insert(it, convertedSoulOfAlpacas);

                    
                    hotelExist = monocle.hotelFinder(stationSettlementDelivery);
                    hotelVector.push_back(hotelExist);

                

                    startSettlementDelivery = stationSettlementDelivery;
                } else {
                    while(cin.fail()){
                        throw runtime_error("Beolvasás hiba.");
                        cin.clear();
                    }
                    break;
                 }
            }
        } catch (const exception& e){
            cout<<"Hiba: "<<e.what()<<endl;
        }
        cout<<endl<<endl;
        
        for(const auto& mapItem : wayPlanStorageMap){
            cout<<"Kulcs: "<<mapItem.first<<", értékek: ";
            for(const auto& value : mapItem.second){
                cout<<value<<" ";
            }
            cout<<endl;
        }
        

        return wayPlanStorageMap;
    }

    void setSettlementVectors(unordered_map<string, list<double>> settlMap){
        for(const auto& item : settlMap){
            settlementNamesVector.insert(settlementNamesVector.begin(), item.first);
            settlementDistancesVector.insert(settlementDistancesVector.begin(), item.second.front());
            auto it = prev(item.second.end());
            numbersOfAlpacaInhabitantsOfTheSettlementVector.insert(numbersOfAlpacaInhabitantsOfTheSettlementVector.begin(), *it);       

        }
        
        for(unsigned int i = 0; i < settlementDistancesVector.size(); ++i){
            sumTimeVector.push_back(settlementDistancesVector[i] + numbersOfAlpacaInhabitantsOfTheSettlementVector[i] * 25.0 + 20.0);
        }
    }

    vector<string> getSettleNamesVector(){
        return settlementNamesVector;
    }

    vector<double> getSettleDistancesVector(){
        return settlementDistancesVector;
    }

    vector<double> getNumbersOfAlpacaInhabitantsOfTheSettlementVector(){
        return numbersOfAlpacaInhabitantsOfTheSettlementVector;
    }

    vector<double> getSumTimeVector(){
        return sumTimeVector;
    }

    vector<int> getHotelVector(){
        return hotelVector;
    }

    void printVectors(){
        cout<<endl<<endl;
        cout<<"Választott települések az útvonalon: ";
        for(const auto& item : settlementNamesVector){
            cout<<item<<"-";
        }
        cout<<endl<<endl;

        cout<<"Választott települések távolságai: ";
        for(const auto& item : settlementDistancesVector){
            cout<<item<<"-";
        }
        cout<<endl<<endl;
        cout<<"Választott településeken lakó alpakák száma: ";
        for(const auto& item : numbersOfAlpacaInhabitantsOfTheSettlementVector){
            cout<<item<<"-";
        }  
        cout<<endl<<endl;
        
        cout<<"Választott településeken szállás: ";
        for(const auto& item : hotelVector){
            cout<<item<<"\t";
        } 

        cout<<endl<<endl; 
        for(int i = 0; i < settlementNamesVector.size(); i++){
            cout<<i<<". "<<settlementNamesVector[i]<<", út: "<<settlementDistancesVector[i]<<" km, alpakák száma: "<<numbersOfAlpacaInhabitantsOfTheSettlementVector[i]<<", szállás: ";[](int value){if(value == 1){cout<<"van.";}else if(value == 0){cout<<"nincs.";}else{"nem találtam olvasható értéket.";}}(hotelVector[i]);
            cout<<endl;
        }
        cout<<endl;
    }
};

#endif // PLANNER_H