#include "SentenceCounter.h"

SentenceCounter::SentenceCounter() {
    sentenceCount = 0;
}

bool SentenceCounter::isSentenceEnd(char c) const {
    return (c == '.' || c == '!' || c == '?');
}

void SentenceCounter::countSentences(const string& text) {
    sentenceCount = 0;
    bool inSentence = false;

    for (size_t i = 0; i < text.length(); i++) {
        char c = text[i];

        if (!isspace(c) && c != '\n' && c != '\r') {
            inSentence = true;
        }

        if (isSentenceEnd(c) && inSentence) {
            if (c == '.') {
                while (i + 1 < text.length() && text[i + 1] == '.') {
                    i++;  // пропускаем дополнительные точки
                }
            }

            sentenceCount++;
            inSentence = false;
        }
    }
}

int SentenceCounter::getSentenceCount() const {
    return sentenceCount;
}

void SentenceCounter::reset() {
    sentenceCount = 0;
}