#include "RiskFactor.hpp"

#include <numeric>

double OddsEngine::oddsToProb(const std::string& odds) {
    OddsType type = inferOddsType( odds );

    if (type == OddsType::American) {
        return americanToProb( odds );
    } else if (type == OddsType::Fractional) {
        return fractionalToProb( odds );
    } else if (type == OddsType::Decimal) {
        return decimalToProb( odds );
    } else {
        return -1.0;
    }
}

double OddsEngine::oddsToProb(const std::string& odds, OddsType type) {
    if (type == OddsType::American) {
        return americanToProb( odds );
    } else if (type == OddsType::Fractional) {
        return fractionalToProb( odds );
    } else if (type == OddsType::Decimal) {
        return decimalToProb( odds );
    } else{
        return -1.0;
    }
}

std::vector<double> OddsEngine::oddsToProb(const std::vector<std::string>& oddsVector) {
    std::vector<double> probsVector;

    for(int i = 0; i < oddsVector.size(); i++){
        OddsType type = inferOddsType ( oddsVector[i] );
        double prob = oddsToProb( oddsVector[i], type );

        probsVector.push_back( prob );
    }

    return probsVector;
}

std::vector<double> OddsEngine::oddsToProb(const std::vector<std::string>& oddsVector, OddsType type) {
    std::vector<double> probsVector;

    for(int i = 0; i < oddsVector.size(); i++){
        double prob = oddsToProb( oddsVector[i], type );

        probsVector.push_back( prob );
    }

    return probsVector;
}

// Compute Vig

double OddsEngine::vig(const std::vector<double>& probs){
    return std::accumulate(probs.begin(), probs.end(), 0.0) - 1.0;
}

// Compute Edge

double OddsEngine::computeEdge(double modelProb, double fairProb){
    return 1.0;
}

// Compute Kelly

double OddsEngine::kelly(double modelProb, double fairProb, double payout){
    return 1.0;
}
    
// Infer Odds Type

OddsType OddsEngine::inferOddsType(const std::string& odds){
    if ( odds.substr(0,1) == "-"  || odds.substr(0,1) == "+"){
        return OddsType::American;
    } else if ( odds.find('/') != std::string::npos ){
        return OddsType::Fractional;
    } else {
        return OddsType::Decimal;
    }
}

// American Odds to Probability

double OddsEngine::americanToProb(const std::string& odds){
    try{
        std::string sign = odds.substr(0,1);
        int num = std::stoi( odds.substr(1) );

        if (sign == "-" ){
            return num / ( num + 100.0 );
        } else if ( sign == "+" ){
            return 100.0 / ( num + 100.0 );
        } else {
            return -1.0;
        }
    } catch (...){
        return -1.0;
    }
}

// Fractional Odds to Probability

double OddsEngine::fractionalToProb(const std::string& odds){
    return 1.0;
}

// Decimal Odds to Probability

double OddsEngine::decimalToProb(const std::string& odds){
    return 1.0;
}