#ifndef STATISTICS_H
#define STATISTICS_H

#include <vector>

class StatisticsMC {
public:
    StatisticsMC() {}
    virtual void DumpOneResult(double result) = 0;
    virtual std::vector<std::vector<double>> GetResultsSoFar() const = 0;
    virtual StatisticsMC* clone() const = 0;
    virtual ~StatisticsMC() {}
    virtual void reset() = 0;
};

class StatisticsMean : public StatisticsMC {
public:
    StatisticsMean();
    virtual void DumpOneResult(double result);
    virtual std::vector<std::vector<double>> GetResultsSoFar() const;
    virtual StatisticsMC* clone() const;
    virtual void reset();

private:
    double RunningSum;
    unsigned long PathsDone;
};

class StatisticsMeanWithConf : public StatisticsMC {
public:
    StatisticsMeanWithConf(double alpha);
    virtual void DumpOneResult(double result);
    virtual std::vector<std::vector<double>> GetResultsSoFar() const;
    virtual StatisticsMC* clone() const;
    virtual void reset();

private:
    double alpha;
    double RunningSum;
    double RunningSumSquares;
    unsigned long PathsDone;
    double ConfidenceLevel;
};

#endif
