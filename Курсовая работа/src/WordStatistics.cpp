#include "WordStatistics.h"

WordStatistics::WordStatistics() {
    totalWords = 0;
}

void WordStatistics::addWord(const string& word) {
    if (word.empty()) return;

    wordFrequency[word]++;
    wordLength[word] = word.length();
    totalWords++;
}

void WordStatistics::clear() {
    wordFrequency.clear();
    wordLength.clear();
    totalWords = 0;
}

int WordStatistics::getTotalWords() const {
    return totalWords;
}

int WordStatistics::getUniqueWords() const {
    return wordFrequency.size();
}

int WordStatistics::getWordFrequency(const string& word) const {
    auto it = wordFrequency.find(word);
    return (it != wordFrequency.end()) ? it->second : 0;
}

vector<pair<string, int>> WordStatistics::getTopFrequentWords(int n) const {
    vector<pair<string, int>> pairs(wordFrequency.begin(), wordFrequency.end());

    sort(pairs.begin(), pairs.end(),
        [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second > b.second;
        });

    if (n > pairs.size()) n = pairs.size();
    return vector<pair<string, int>>(pairs.begin(), pairs.begin() + n);
}

vector<pair<string, int>> WordStatistics::getTopLongestWords(int n) const {
    vector<pair<string, int>> pairs(wordLength.begin(), wordLength.end());

    sort(pairs.begin(), pairs.end(),
        [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second > b.second;
        });

    if (n > pairs.size()) n = pairs.size();
    return vector<pair<string, int>>(pairs.begin(), pairs.begin() + n);
}

map<string, int> WordStatistics::getAllWordFrequencies() const {
    return wordFrequency;
}