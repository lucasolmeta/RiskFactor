#include <vector>
#include <string>
#include <iostream>
#include "RiskFactor.hpp"

int main(){
    OddsEngine engine;

    std::vector<std::string> odds = {"-300","+150","-100","+1900"};

    std::vector<double> probs = engine.oddsToProb( odds );

    for(int i = 0; i < probs.size(); i++){
        std::cout << odds[i] << " is equal to " << probs[i] * 100.0 << "%" << std::endl;
    }
}