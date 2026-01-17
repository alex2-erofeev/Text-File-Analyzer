#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include "common.h"

class SettingsManager {
private:
    bool caseSensitive;
    bool ignoreNumbers;
    bool ignoreSpecialChars;
    set<string> stopWords;
    string language;

    void loadDefaultStopWords();

public:
    SettingsManager();

    void setCaseSensitive(bool value);
    void setIgnoreNumbers(bool value);
    void setIgnoreSpecialChars(bool value);
    void setLanguage(const string& lang);
    void addStopWord(const string& word);
    void clearStopWords();

    bool isCaseSensitive() const;
    bool shouldIgnoreNumbers() const;
    bool shouldIgnoreSpecialChars() const;
    string getLanguage() const;
    bool isStopWord(const string& word) const;

    string normalizeWord(string word) const;
};

#endif