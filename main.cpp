#include <vector>
#include <string>
#include <iostream>
#include "RiskFactor.hpp"

int main(){
    OddsEngine engine;

    std::vector<std::string> odds = {"-250","+380","+950","+1000"};

    std::vector<double> probs = engine.oddsToProb( odds );

    for(int i = 0; i < probs.size(); i++){
        std::cout << odds[i] << " is equal to " << probs[i] * 100.0 << "%" << std::endl;
    }

    double vig = engine.computeVig( probs );

    std::cout << "Vig is " << vig << std::endl;

    std::vector<double> fairProbs = engine.removeVig( probs );

    for(int i = 0; i < probs.size(); i++){
        std::cout << probs[i] * 100.0 << "%'s fair prob counterpart is " << fairProbs[i] * 100.0 << "%" << std::endl;
    }

    std::vector<double> edges = engine.computeEdge( probs, fairProbs );
    
    for(int i = 0; i < probs.size(); i++){
        std::cout << "Edge for " << odds[i] << " is equal to " << edges[i] << std::endl;
    }
}