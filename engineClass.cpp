#include <string>
#include <iostream>
#include <vector>
#include <iomanip>

class OddsEngine {
public:
    double americanToProb(std::string odds);
    double removeVig(double p1, double p2);
    double computeEdge(double modelProb, double fairProb);
    double kelly(double modelProb, double fairProb, double payout);

    double americanToProb(std::string odds){
        try{
            std::string sign = odds.substr(0,1);
            int num = std::stoi( odds.substr(1) );

            if ( sign == "-" ){
                return num / ( num + 100.0 ) * 100.0;
            } else if ( sign == "+" ){
                return 100.0 / ( num + 100.0 ) * 100.0;
            } else {
                std::cout << "Invalid Odds Sign Passed";
                return -1;
            }
        } catch (...){
            std::cout << "Error Encountered";
            return -1;
        }
    }
};

double getPercentFromAmericanOdds(std::string odds){
    try{
        std::string sign = odds.substr(0,1);
        int num = std::stoi( odds.substr(1) );

        if ( sign == "-" ){
            return num / ( num + 100.0 ) * 100.0;
        } else if ( sign == "+" ){
            return 100.0 / ( num + 100.0 ) * 100.0;
        } else {
            std::cout << "Invalid Odds Sign Passed";
            return -1;
        }
    } catch (...){
        std::cout << "Error Encountered";
        return -1;
    }
}

int main() {
}