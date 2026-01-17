#ifndef WORDSTATISTICS_H
#define WORDSTATISTICS_H

#include "common.h"

class WordStatistics {
private:
    map<string, int> wordFrequency;
    map<string, int> wordLength;
    int totalWords;

public:
    WordStatistics();

    void addWord(const string& word);
    void clear();

    int getTotalWords() const;
    int getUniqueWords() const;
    int getWordFrequency(const string& word) const;

    vector<pair<string, int>> getTopFrequentWords(int n) const;
    vector<pair<string, int>> getTopLongestWords(int n) const;
    map<string, int> getAllWordFrequencies() const;
};

#endif