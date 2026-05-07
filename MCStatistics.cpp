#include "MCStatistics.h"
#include <cmath>
#include <algorithm>

StatisticsMean::StatisticsMean()
    : RunningSum(0.0), PathsDone(0UL) {}

void StatisticsMean::DumpOneResult(double result) {
    PathsDone++;
    RunningSum += result;
}

std::vector<std::vector<double>> StatisticsMean::GetResultsSoFar() const {
    std::vector<std::vector<double>> Results(1);
    Results[0].resize(1);
    Results[0][0] = RunningSum / PathsDone;
    return Results;
}

StatisticsMC* StatisticsMean::clone() const {
    return new StatisticsMean(*this);
}

void StatisticsMean::reset() {
    PathsDone = 0UL;
    RunningSum = 0.0;
}

StatisticsMeanWithConf::StatisticsMeanWithConf(double alpha_)
    : alpha(alpha_), RunningSum(0.0), RunningSumSquares(0.0), PathsDone(0UL) {}

void StatisticsMeanWithConf::DumpOneResult(double result) {
    PathsDone++;
    RunningSum += result;
    RunningSumSquares += result * result;
}

std::vector<std::vector<double>> StatisticsMeanWithConf::GetResultsSoFar() const {
    std::vector<std::vector<double>> Results(1);
    double mean = RunningSum / PathsDone;
    double variance = (RunningSumSquares - (RunningSum * RunningSum) / PathsDone) / (PathsDone - 1);
    double std_dev = std::sqrt(variance);
    double conf_margin = 1.96 * std_dev / std::sqrt(PathsDone);  // Assuming 95% confidence interval

    Results[0].resize(5);
    Results[0][0] = mean;
    Results[0][1] = std_dev;
    Results[0][2] = std_dev / std::sqrt(PathsDone);
    Results[0][3] = mean - conf_margin;
    Results[0][4] = mean + conf_margin;

    return Results;
}

StatisticsMC* StatisticsMeanWithConf::clone() const {
    return new StatisticsMeanWithConf(*this);
}

void StatisticsMeanWithConf::reset() {
    PathsDone = 0UL;
    RunningSum = 0.0;
    RunningSumSquares = 0.0;
}
