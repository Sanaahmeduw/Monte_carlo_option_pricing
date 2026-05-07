#include "SimpleMC8.h"
#include "Vanilla3.h"
#include "MCStatistics.h"
#include "ParkMiller.h"
#include "Parameters.h"
#include "PayOff3.h"
#include <iostream>

int main() {
    double Expiry;
    double Strike;
    double Spot;
    double Vol;
    double r;
    unsigned long NumberOfPaths;
    double alpha;

    std::cout << "\nEnter expiry in years\n";
    std::cin >> Expiry;

    std::cout << "\nEnter strike\n";
    std::cin >> Strike;

    std::cout << "\nEnter spot\n";
    std::cin >> Spot;

    std::cout << "\nEnter volatility\n";
    std::cin >> Vol;

    std::cout << "\nEnter risk-free rate\n";
    std::cin >> r;

    std::cout << "\nEnter number of paths\n";
    std::cin >> NumberOfPaths;

    std::cout << "\nEnter alpha (confidence level)\n";
    std::cin >> alpha;

    PayOffCall thePayOff(Strike);

    VanillaOption theOption(thePayOff, Expiry);

    ParametersConstant VolParam(Vol);
    ParametersConstant rParam(r);

    StatisticsMeanWithConf gatherer(alpha);

    RandomParkMiller generator(1);

    SimpleMonteCarlo6(theOption, Spot, VolParam, rParam, NumberOfPaths, gatherer, generator);

    std::vector<std::vector<double>> results = gatherer.GetResultsSoFar();

    // Output the results with relevant titles
    std::cout << "\nResults for the call price:\n";
    std::cout << "Averaged discounted payoff: " << results[0][0] << "\n";
    std::cout << "Standard deviation of discounted payoffs: " << results[0][1] << "\n";
    std::cout << "Standard deviation of averaged discounted payoffs: " << results[0][2] << "\n";
    std::cout << alpha * 100 << "% Confidence Limits for mean:\n";
    std::cout << "Lower limit: " << results[0][3] << "\n";
    std::cout << "Upper limit: " << results[0][4] << "\n";

    return 0;
}
