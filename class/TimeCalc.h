#ifndef TIMECALC_H
#define TIMECALC_H

#include "Planner.h"
#include <chrono>
#include <iomanip>

class TimeCalc{
    Planner& plannedWay;
    double travelTimePerDay;
    const double packingTime;
    double allpackingTime;

public:
    TimeCalc(Planner& _plannedWay, double _travelTimePerDay = 0.0, double _packingTime = 20.0, double _allpackingTime = 20.0) : plannedWay(_plannedWay), travelTimePerDay(_travelTimePerDay), packingTime(_packingTime), allpackingTime(_allpackingTime){}
    ~TimeCalc(){}

    void measureTime(){
        vector<string> settleNames = plannedWay.getSettleNamesVector();
        vector<double> distances = plannedWay.getSettleDistancesVector();
        vector<double> alpacas = plannedWay.getNumbersOfAlpacaInhabitantsOfTheSettlementVector();
        vector<double> sumTime = plannedWay.getSumTimeVector(); //distance + alpacas*25 + packing time;
        vector<int> hotels = plannedWay.getHotelVector();

        auto currentTime = chrono::system_clock::now();
        double sumDistance = 0.0;
        double alpacaCounter = 0;
        double alpacaPerDay;

        auto todayTime = chrono::system_clock::to_time_t(currentTime);
        tm* todayTimeInfo = localtime(&todayTime);
        cout<<"Aktuális dátum: "<<put_time(todayTimeInfo, "%Y-%m-%d")<<endl;
        
        
        int i = 0;
        while(i < sumTime.size()){
            if(i > 0){
                travelTimePerDay += sumTime[i];
                alpacaPerDay = alpacas[i];
                alpacaCounter += alpacas[i];
                sumDistance += distances[i];
                if(alpacaPerDay < 16 && travelTimePerDay < 730){
                    cout<<settleNames[i]<<": "<<distances[i]<<" km, alpakák: "<<alpacas[i]<<endl;   
                }else{                  
                    while(alpacaPerDay >= 0){
                        cout<<settleNames[i]<<": "<<distances[i]<<" km, alpakák: "<<alpacaPerDay<<endl;
                        alpacaPerDay -= 15;
                        travelTimePerDay = 0.0;
                        cout<<endl;
                        
                        if(alpacaPerDay <= 0){break;} 
                        auto tomorrow = currentTime + chrono::hours(24);
                        auto tomorrowTime = chrono::system_clock::to_time_t(tomorrow);
                        tm* tomorrowTimeInfo = localtime(&tomorrowTime);
                        cout<<put_time(tomorrowTimeInfo, "%Y-%m-%d")<<":"<<endl;
                        currentTime = tomorrow;                        
                    };               
                }
            }
            i++;
        }
        cout<<endl<<endl;
        cout<<"Össz alpaka szám: "<<alpacaCounter<<endl;
        cout<<"Össz távolság: "<<sumDistance<<endl;
          
        
    }
};

#endif // TIMECALC_H

//szállást
//beleszámolni, ha haza is kell jönni, akkor is ha egy nap, akkor is ha több napos, jövő: ha nincs szállás megkeresni a legközelebbi várost ahol van.