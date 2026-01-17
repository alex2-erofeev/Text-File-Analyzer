#include "UserInterface.h"
#include <limits>

UserInterface::UserInterface() {
    analyzer = new TextAnalyzer();
    settings = new SettingsManager();
    resultsManager = new ResultsManager();
    analyzer->setSettings(settings);
}

UserInterface::~UserInterface() {
    delete analyzer;
    delete settings;
    delete resultsManager;
}

void UserInterface::displayMainMenu() {
    cout << "\n";
    cout << "========================================\n";
    cout << "    АНАЛИЗАТОР ТЕКСТОВЫХ ФАЙЛОВ        \n";
    cout << "========================================\n";
    cout << "1. Анализ одного файла\n";
    cout << "2. Анализ папки с файлами\n";
    cout << "3. Сравнительный анализ двух файлов\n";
    cout << "4. Настройки обработки\n";
    cout << "5. Выход\n";
    cout << "========================================\n";
}

void UserInterface::displaySettingsMenu() {
    cout << "\n";
    cout << "========================================\n";
    cout << "         НАСТРОЙКИ ОБРАБОТКИ           \n";
    cout << "========================================\n";
    cout << "Текущие настройки:\n";
    cout << "  Учитывать регистр: " << (settings->isCaseSensitive() ? "Да" : "Нет") << "\n";
    cout << "  Игнорировать числа: " << (settings->shouldIgnoreNumbers() ? "Да" : "Нет") << "\n";
    cout << "  Игнорировать спецсимволы: " << (settings->shouldIgnoreSpecialChars() ? "Да" : "Нет") << "\n";
    cout << "========================================\n";
    cout << "1. Изменить учёт регистра\n";
    cout << "2. Изменить игнорирование чисел\n";
    cout << "3. Изменить игнорирование спецсимволов\n";
    cout << "4. Добавить стоп-слово\n";
    cout << "5. Очистить стоп-слова\n";
    cout << "6. Назад\n";
    cout << "========================================\n";
}

string UserInterface::getInput(const string& prompt) {
    cout << prompt;
    string input;
    getline(cin, input);
    return input;
}

int UserInterface::getIntInput(const string& prompt) {
    while (true) {
        cout << prompt;
        string input;
        getline(cin, input);

        if (input.empty()) {
            cout << "Ошибка: введите число!\n";
            continue;
        }

        // Проверка: все символы должны быть цифрами
        bool isValid = true;
        for (char c : input) {
            if (!isdigit(c)) {
                isValid = false;
                break;
            }
        }

        if (!isValid) {
            cout << "Ошибка: введите только число!\n";
            continue;
        }

        try {
            int value = stoi(input);
            return value;
        }
        catch (const out_of_range&) {
            cout << "Ошибка: число слишком большое!\n";
        }
    }
}

bool UserInterface::getYesNo(const string& prompt) {
    while (true) {
        string input = getInput(prompt + " (y/n): ");
        if(input == "y" || input == "n")
            return (input == "y");
        else {
            cout << "Необходимо ввести y или n. Попробуйте снова." << endl;
            continue;
        }
    }
}

void UserInterface::handleFileAnalysis() {
    analyzer->reset();

    string filePath = "data/input/" + getInput("Введите название файла (название.txt): ");

    if (!analyzer->addFile(filePath)) {
        cout << "Ошибка: " << analyzer->getLastError() << "\n";
        return;
    }

    cout << "Анализирую файл...\n";
    analyzer->analyzeFile(filePath);

    int topN = getIntInput("Сколько топ-слов показать? (по умолчанию 10): ");
    if (topN <= 0) topN = DEFAULT_TOP_N;

    resultsManager->displayResults(analyzer->getWordStatistics(),
        analyzer->getSentenceCounter(), topN);

    if (getYesNo("Сохранить результаты в файл?")) {
        string filename = getInput("Введите имя файла (например, results.txt): ");
        resultsManager->saveResults(filename, analyzer->getWordStatistics(),
            analyzer->getSentenceCounter(), topN);
    }
}

void UserInterface::handleDirectoryAnalysis() {
    analyzer->reset();

    string dirPath = "data/" + getInput("Введите название папки: ");

    if (!analyzer->addFilesFromDirectory(dirPath)) {
        cout << "Ошибка: " << analyzer->getLastError() << "\n";
        return;
    }

    cout << "Найдено файлов: " << analyzer->getFilePaths().size() << "\n";
    cout << "Анализирую файлы...\n";

    analyzer->analyzeAllFiles();

    int topN = getIntInput("Сколько топ-слов показать? (по умолчанию 10): ");
    if (topN <= 0) topN = DEFAULT_TOP_N;

    resultsManager->displayResults(analyzer->getWordStatistics(),
        analyzer->getSentenceCounter(), topN);

    if (getYesNo("Сохранить результаты в файл?")) {
        string filename = getInput("Введите имя файла: ");
        resultsManager->saveResults(filename, analyzer->getWordStatistics(), analyzer->getSentenceCounter(), topN);
    }
}

void UserInterface::handleComparison() {
    string file1 = "data/input/" + getInput("Введите название 1 файла (название.txt): ");
    string file2 = "data/input/" + getInput("Введите название 2 файла (название.txt): ");

    TextAnalyzer analyzer1, analyzer2;
    analyzer1.setSettings(settings);
    analyzer2.setSettings(settings);

    if (!analyzer1.addFile(file1) || !analyzer2.addFile(file2)) {
        cout << "Ошибка при открытии файлов\n";
        return;
    }

    cout << "Анализирую файлы...\n";
    analyzer1.analyzeFile(file1);
    analyzer2.analyzeFile(file2);

    int topN = getIntInput("Сколько топ-слов показать? (по умолчанию 10): ");
    if (topN <= 0) topN = DEFAULT_TOP_N;

    resultsManager->displayComparison(file1, file2, analyzer1.getWordStatistics(), analyzer2.getWordStatistics(), topN);
}

void UserInterface::handleSettings() {
    while (true) {
        displaySettingsMenu();
        int choice = getIntInput("Выберите действие: ");

        switch (choice) {
        case 1:
            settings->setCaseSensitive(!settings->isCaseSensitive());
            cout << "Учёт регистра: " << (settings->isCaseSensitive() ? "Включен" : "Выключен") << "\n";
            break;
        case 2:
            settings->setIgnoreNumbers(!settings->shouldIgnoreNumbers());
            cout << "Игнорирование чисел: " << (settings->shouldIgnoreNumbers() ? "Включено" : "Выключено") << "\n";
            break;
        case 3:
            settings->setIgnoreSpecialChars(!settings->shouldIgnoreSpecialChars());
            cout << "Игнорирование спецсимволов: " << (settings->shouldIgnoreSpecialChars() ? "Включено" : "Выключено") << "\n";
            break;
        case 4: {
            string word = getInput("Введите стоп-слово: ");
            cout << word << endl;
            settings->addStopWord(word);
            cout << "Стоп-слово добавлено\n";
            break;
        }
        case 5:
            settings->clearStopWords();
            cout << "Все стоп-слова очищены\n";
            break;
        case 6:
            return;
        default:
            cout << "Неверный выбор\n";
        }
    }
}

void UserInterface::run() {
    while (true) {
        displayMainMenu();
        int choice = getIntInput("Выберите действие: ");

        switch (choice) {
        case 1:
            handleFileAnalysis();
            break;
        case 2:
            handleDirectoryAnalysis();
            break;
        case 3:
            handleComparison();
            break;
        case 4:
            handleSettings();
            break;
        case 5:
            cout << "До свидания!\n";
            return;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }
}