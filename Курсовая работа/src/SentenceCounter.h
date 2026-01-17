#ifndef SENTENCECOUNTER_H
#define SENTENCECOUNTER_H

#include "common.h"

class SentenceCounter {
private:
    int sentenceCount;

    bool isSentenceEnd(char c) const;

public:
    SentenceCounter();

    void countSentences(const string& text);
    int getSentenceCount() const;
    void reset();
};

#endif