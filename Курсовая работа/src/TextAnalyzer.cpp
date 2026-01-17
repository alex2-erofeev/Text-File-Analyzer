#include "TextAnalyzer.h"

TextAnalyzer::TextAnalyzer() : FileProcessor() {
    //settings = new SettingsManager();
    settings = nullptr;
    wordStats = new WordStatistics();
    sentenceCounter = new SentenceCounter();
}

TextAnalyzer::~TextAnalyzer() {
    //delete settings;
    delete wordStats;
    delete sentenceCounter;
}

void TextAnalyzer::setSettings(SettingsManager* settingsManager) {
    if (settingsManager != nullptr) {
        //delete settings;
        settings = settingsManager;
    }
}

vector<string> TextAnalyzer::tokenizeText(const string& text) {
    vector<string> tokens;
    string currentWord = "";

    for (char c : text) {
        if (isalpha((unsigned char)c) || (isdigit((unsigned char)c) && !settings->shouldIgnoreNumbers())) {
            currentWord += c;
        }
        else {
            if (!currentWord.empty()) {
                tokens.push_back(currentWord);
                currentWord = "";
            }
        }
    }

    if (!currentWord.empty()) {
        tokens.push_back(currentWord);
    }

    return tokens;
}

bool TextAnalyzer::isValidWord(const string& word) const {
    if (word.empty()) return false;

    // Проверка на числа
    if (settings->shouldIgnoreNumbers()) {
        bool hasLetter = false;
        for (char c : word) {
            if (isalpha((unsigned char)c)) {
                hasLetter = true;
                break;
            }
        }
        if (!hasLetter) return false;
    }

    // Проверка на стоп-слова
    string normalized = settings->normalizeWord(word);
    if (settings->isStopWord(normalized)) {
        return false;
    }

    return true;
}

string TextAnalyzer::cleanWord(string word) const {
    // Удаление спецсимволов
    if (settings->shouldIgnoreSpecialChars()) {
        string cleaned = "";
        for (char c : word) {
            if (isalnum((unsigned char)c)) {
                cleaned += c;
            }
        }
        word = cleaned;
    }

    // Нормализация (регистр)
    word = settings->normalizeWord(word);

    return word;
}

void TextAnalyzer::analyzeText(const string& text) {
    // Подсчёт предложений
    sentenceCounter->countSentences(text);

    // Токенизация
    vector<string> tokens = tokenizeText(text);
    
    // Анализ слов
    for (const string& token : tokens) {
        string word = cleanWord(token);
        if (isValidWord(word)) {
            wordStats->addWord(word);
        }
    }
}

void TextAnalyzer::analyzeFile(const string& filePath) {
    string content = readFile(filePath);
    if (!content.empty()) {
        analyzeText(content);
    }
}

void TextAnalyzer::analyzeAllFiles() {
    vector<string> contents = readAllFiles();
    for (const string& content : contents) {
        analyzeText(content);
    }
}

WordStatistics* TextAnalyzer::getWordStatistics() const {
    return wordStats;
}

SentenceCounter* TextAnalyzer::getSentenceCounter() const {
    return sentenceCounter;
}

void TextAnalyzer::reset() {
    wordStats->clear();
    sentenceCounter->reset();
}