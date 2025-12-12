#include "RiskFactor.hpp"

#include <numeric>

double OddsEngine::oddsToImpliedProb(const std::string& odds) {
    OddsType type = inferOddsType( odds );

    if (type == OddsType::American) {
        return americanToImpliedProb( odds );
    } else if (type == OddsType::Fractional) {
        return fractionalToImpliedProb( odds );
    } else if (type == OddsType::Decimal) {
        return decimalToImpliedProb( odds );
    } else {
        return -1.0;
    }
}

double OddsEngine::oddsToImpliedProb(const std::string& odds, OddsType type) {
    if (type == OddsType::American) {
        return americanToImpliedProb( odds );
    } else if (type == OddsType::Fractional) {
        return fractionalToImpliedProb( odds );
    } else if (type == OddsType::Decimal) {
        return decimalToImpliedProb( odds );
    } else{
        return -1.0;
    }
}

std::vector<double> OddsEngine::oddsToImpliedProb(const std::vector<std::string>& oddsVector) {
    std::vector<double> probsVector;

    for(int i = 0; i < oddsVector.size(); i++){
        OddsType type = inferOddsType( oddsVector[i] );
        double prob = oddsToImpliedProb( oddsVector[i], type );

        probsVector.push_back( prob );
    }

    return probsVector;
}

std::vector<double> OddsEngine::oddsToImpliedProb(const std::vector<std::string>& oddsVector, OddsType type) {
    std::vector<double> probsVector;

    for(int i = 0; i < oddsVector.size(); i++){
        double prob = oddsToImpliedProb( oddsVector[i], type );

        probsVector.push_back( prob );
    }

    return probsVector;
}

// Compute Vig

double OddsEngine::computeVig(const std::vector<double>& impliedProbs){
    return std::accumulate(impliedProbs.begin(), impliedProbs.end(), 0.0) - 1.0;
}

// Remove Vig

std::vector<double> OddsEngine::removeVig(const std::vector<double>& impliedProbs){
    double vig = computeVig(impliedProbs);
    std::vector<double> probsWithoutVig;

    for(int i = 0; i < impliedProbs.size(); i++){
        probsWithoutVig.push_back( impliedProbs[i] / ( 1 + vig ) );
    }

    return probsWithoutVig;
}

// Compute Edge

double OddsEngine::computeEdge(double modelProb, double fairProb){
    return modelProb - fairProb;
}

std::vector<double> OddsEngine::computeEdge(const std::vector<double>& modelProbs, const std::vector<double>& fairProbs){
    std::vector<double> edges;

    for(int i = 0; i < modelProbs.size(); i++){
        edges.push_back(modelProbs[i] - fairProbs[i]);
    }

    return edges;
}

// Compute Kelly

double OddsEngine::kelly(double modelProb, double fairProb, double impliedProb){
    if (modelProb <= fairProb){ 
        return 0.0;
    }

    double payoutRatio = (1.0 / impliedProb) - 1.0;
    
    return (modelProb / impliedProb - 1) / payoutRatio;
}

std::vector<double> OddsEngine::kelly(std::vector<double> modelProbs, std::vector<double> fairProbs, std::vector<double> impliedProbs){
    std::vector<double> kellyVals;

    for(int i = 0; i < modelProbs.size(); i++){
        double val = kelly( modelProbs[i], fairProbs[i], impliedProbs[i] );

        kellyVals.push_back( val );
    }

    return kellyVals;
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

double OddsEngine::americanToImpliedProb(const std::string& odds){
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

double OddsEngine::fractionalToImpliedProb(const std::string& odds){
    return 1.0;
}

// Decimal Odds to Probability

double OddsEngine::decimalToImpliedProb(const std::string& odds){
    return 1.0;
}