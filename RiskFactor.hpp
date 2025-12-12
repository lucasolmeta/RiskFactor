#pragma once

#include <string>
#include <vector>

enum class OddsType { American, Fractional, Decimal };

class OddsEngine{
    public:
        double oddsToProb(const std::string& odds);
        double oddsToProb(const std::string& odds, OddsType type);
        std::vector<double> oddsToProb(const std::vector<std::string>& oddsVector);
        std::vector<double> oddsToProb(const std::vector<std::string>& oddsVector, OddsType type);

        double computeVig(const std::vector<double>& probs);
        std::vector<double> removeVig(const std::vector<double>& probs);

        double computeEdge(double modelProb, double fairProb);

        double kelly(double modelProb, double fairProb, double payout);

    private:
        OddsType inferOddsType(const std::string& odds);

        double americanToProb(const std::string& odds);

        double fractionalToProb(const std::string& odds);

        double decimalToProb(const std::string& odds);
};