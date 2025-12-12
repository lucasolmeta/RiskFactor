#pragma once

#include <string>
#include <vector>

enum class OddsType { American, Fractional, Decimal };

class OddsEngine{
    public:
        double oddsToImpliedProb(const std::string& odds);
        double oddsToImpliedProb(const std::string& odds, OddsType type);
        std::vector<double> oddsToImpliedProb(const std::vector<std::string>& oddsVector);
        std::vector<double> oddsToImpliedProb(const std::vector<std::string>& oddsVector, OddsType type);

        double computeVig(const std::vector<double>& impliedProbs);
        std::vector<double> removeVig(const std::vector<double>& impliedProbs);

        double computeEdge(double modelProb, double fairProb);
        std::vector<double> computeEdge(const std::vector<double>& modelProbs, const std::vector<double>& fairProbs);

        double kelly(double modelProb, double fairProb, double impliedProb);
        std::vector<double> kelly(std::vector<double> modelProbs, std::vector<double> fairProbs, std::vector<double> impliedProbs);

    private:
        OddsType inferOddsType(const std::string& odds);

        double americanToImpliedProb(const std::string& odds);

        double fractionalToImpliedProb(const std::string& odds);

        double decimalToImpliedProb(const std::string& odds);
};