#include "ResultsManager.h"
#include "Utilities.h"
#include <iomanip>
#include <filesystem>

ResultsManager::ResultsManager() {}

string ResultsManager::formatTopWords(const vector<pair<string, int>>& words, const string& title) const {
    stringstream ss;
    ss << "\n" << title << ":\n";
    ss << string(50, '-') << "\n";

    int position = 1;
    for (const auto& pair : words) {
        ss << position << ". " << pair.first << " - " << pair.second << "\n";
        position++;
    }

    return ss.str();
}

void ResultsManager::displayResults(WordStatistics* stats, SentenceCounter* counter, int topN) {
    cout << "\n";
    cout << "========================================\n";
    cout << "         РЕЗУЛЬТАТЫ АНАЛИЗА ТЕКСТА     \n";
    cout << "========================================\n\n";

    cout << "Общая статистика:\n";
    cout << "  Всего слов: " << stats->getTotalWords() << "\n";
    cout << "  Уникальных слов: " << stats->getUniqueWords() << "\n";
    cout << "  Количество предложений: " << counter->getSentenceCount() << "\n";

    vector<pair<string, int>> topFrequent = stats->getTopFrequentWords(topN);
    cout << formatTopWords(topFrequent, "Топ-" + to_string(topN) + " самых частых слов");

    vector<pair<string, int>> topLongest = stats->getTopLongestWords(topN);
    cout << formatTopWords(topLongest, "Топ-" + to_string(topN) + " самых длинных слов");

    cout << "\n========================================\n\n";
}

bool ResultsManager::saveResults(const string& filename, WordStatistics* stats,
    SentenceCounter* counter, int topN) {
    ofstream file(OUTPUT_DIR + filename);
    if (!file.is_open()) {
        cerr << "Ошибка: не удалось создать файл " << filename << "\n";
        return false;
    }

    file << "РЕЗУЛЬТАТЫ АНАЛИЗА ТЕКСТА\n";
    file << "========================================\n\n";

    file << "Общая статистика:\n";
    file << "  Всего слов: " << stats->getTotalWords() << "\n";
    file << "  Уникальных слов: " << stats->getUniqueWords() << "\n";
    file << "  Количество предложений: " << counter->getSentenceCount() << "\n";

    vector<pair<string, int>> topFrequent = stats->getTopFrequentWords(topN);
    file << formatTopWords(topFrequent, "Топ-" + to_string(topN) + " самых частых слов");

    vector<pair<string, int>> topLongest = stats->getTopLongestWords(topN);
    file << formatTopWords(topLongest, "Топ-" + to_string(topN) + " самых длинных слов");

    file.close();
    cout << "Результаты сохранены в файл: " << OUTPUT_DIR + filename << "\n";
    return true;
}

void ResultsManager::displayComparison(const string& file1, const string& file2, WordStatistics* stats1, WordStatistics* stats2, int topN) {
    string name1 = getFileName(file1);
    string name2 = getFileName(file2);

    cout << "\n";
    cout << "========================================\n";
    cout << "      СРАВНИТЕЛЬНЫЙ АНАЛИЗ ТЕКСТОВ     \n";
    cout << "========================================\n\n";

    cout << left << setw(30) << "Параметр" << setw(15) << name1 << setw(15) << name2 << "\n";
    cout << string(60, '-') << "\n";
    cout << left << setw(30) << "Всего слов:" << setw(15) << stats1->getTotalWords() << setw(15) << stats2->getTotalWords() << "\n";
    cout << left << setw(30) << "Уникальных слов:" << setw(15) << stats1->getUniqueWords() << setw(15) << stats2->getUniqueWords() << "\n";

    cout << "\n" << name1 << " - Топ-" << topN << " слов:\n";
    vector<pair<string, int>> top1 = stats1->getTopFrequentWords(topN);
    for (size_t i = 0; i < top1.size(); i++) {
        cout << (i + 1) << ". " << top1[i].first << " (" << top1[i].second << ")\n";
    }

    cout << "\n" << name2 << " - Топ-" << topN << " слов:\n";
    vector<pair<string, int>> top2 = stats2->getTopFrequentWords(topN);
    for (size_t i = 0; i < top2.size(); i++) {
        cout << (i + 1) << ". " << top2[i].first << " (" << top2[i].second << ")\n";
    }

    cout << "\n========================================\n\n";
}