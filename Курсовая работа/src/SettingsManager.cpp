#include "SettingsManager.h"

SettingsManager::SettingsManager() {
    caseSensitive = false;
    ignoreNumbers = true;
    ignoreSpecialChars = true;
    language = "russian";
    loadDefaultStopWords();
}

void SettingsManager::loadDefaultStopWords() {
    // Русские стоп-слова
    string russianStopWords[] = {
        "и", "в", "не", "на", "с", "а", "как", "по", "но", "к", "у",
        "из", "за", "так", "же", "от", "для", "ли"
    };

    string englishStopWords[] = {
        "a", "an", "and", "the", "in", "on", "at", "to", "of", "for",
        "is", "was", "are", "were", "be", "been", "have", "has", "had",
        "do", "does", "did", "will", "would", "can", "could", "should",
        "may", "might", "must", "i", "you", "he", "she", "it", "we", "they",
        "this", "that", "these", "those", "with", "from", "by", "as", "but"
    };

    for (const auto& word : russianStopWords) {
        stopWords.insert(word);
    }

    for (const auto& word : englishStopWords) {
        stopWords.insert(word);
    }
}

void SettingsManager::setCaseSensitive(bool value) {
    caseSensitive = value;
}

void SettingsManager::setIgnoreNumbers(bool value) {
    ignoreNumbers = value;
}

void SettingsManager::setIgnoreSpecialChars(bool value) {
    ignoreSpecialChars = value;
}

void SettingsManager::setLanguage(const string& lang) {
    language = lang;
}

void SettingsManager::addStopWord(const string& word) {
    stopWords.insert(normalizeWord(word));
    //cout << word << endl;
}

void SettingsManager::clearStopWords() {
    stopWords.clear();
}

bool SettingsManager::isCaseSensitive() const {
    return caseSensitive;
}

bool SettingsManager::shouldIgnoreNumbers() const {
    return ignoreNumbers;
}

bool SettingsManager::shouldIgnoreSpecialChars() const {
    return ignoreSpecialChars;
}

string SettingsManager::getLanguage() const {
    return language;
}

bool SettingsManager::isStopWord(const string& word) const {
    return stopWords.find(normalizeWord(word)) != stopWords.end();
}

string SettingsManager::normalizeWord(string word) const {
    if (!caseSensitive) {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
    }
    return word;
}