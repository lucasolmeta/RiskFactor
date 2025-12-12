#include <vector>
#include <string>
#include <iostream>
#include "RiskFactor.hpp"

int main(){
    OddsEngine engine;

    std::vector<std::string> odds = {"-250","+380","+950","+1000"};

    std::vector<double> impliedProbs = engine.oddsToImpliedProb( odds );

    for(int i = 0; i < impliedProbs.size(); i++){
        std::cout << odds[i] << " is equal to " << impliedProbs[i] * 100.0 << "%" << std::endl;
    }

    double vig = engine.computeVig( impliedProbs );

    std::cout << "Vig is " << vig << std::endl;

    std::vector<double> fairProbs = engine.removeVig( impliedProbs );

    for(int i = 0; i < impliedProbs.size(); i++){
        std::cout << impliedProbs[i] * 100.0 << "%'s fair prob counterpart is " << fairProbs[i] * 100.0 << "%" << std::endl;
    }
}