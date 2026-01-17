#ifndef RESULTSMANAGER_H
#define RESULTSMANAGER_H

#include "common.h"
#include "WordStatistics.h"
#include "SentenceCounter.h"

class ResultsManager {
private:
    string formatTopWords(const vector<pair<string, int>>& words, const string& title) const;

public:
    ResultsManager();

    void displayResults(WordStatistics* stats, SentenceCounter* counter, int topN = DEFAULT_TOP_N);
    bool saveResults(const string& filename, WordStatistics* stats, SentenceCounter* counter, int topN = DEFAULT_TOP_N);

    void displayComparison(const string& file1, const string& file2,
        WordStatistics* stats1, WordStatistics* stats2, int topN = DEFAULT_TOP_N);
};

#endif