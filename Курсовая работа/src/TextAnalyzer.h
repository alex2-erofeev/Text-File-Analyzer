#ifndef TEXTANALYZER_H
#define TEXTANALYZER_H

#include "common.h"
#include "FileProcessor.h"
#include "SettingsManager.h"
#include "WordStatistics.h"
#include "SentenceCounter.h"

class TextAnalyzer : public FileProcessor {
private:
    SettingsManager* settings;
    WordStatistics* wordStats;
    SentenceCounter* sentenceCounter;

    vector<string> tokenizeText(const string& text);
    bool isValidWord(const string& word) const;
    string cleanWord(string word) const;

public:
    TextAnalyzer();
    virtual ~TextAnalyzer();

    void setSettings(SettingsManager* settingsManager);

    void analyzeText(const string& text);
    void analyzeFile(const string& filePath);
    void analyzeAllFiles() override;

    WordStatistics* getWordStatistics() const;
    SentenceCounter* getSentenceCounter() const;

    void reset();
};

#endif