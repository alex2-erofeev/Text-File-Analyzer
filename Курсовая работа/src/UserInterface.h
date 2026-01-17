#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "common.h"
#include "TextAnalyzer.h"
#include "SettingsManager.h"
#include "ResultsManager.h"

class UserInterface {
private:
    TextAnalyzer* analyzer;
    SettingsManager* settings;
    ResultsManager* resultsManager;

    void displayMainMenu();
    void displaySettingsMenu();
    void handleFileAnalysis();
    void handleDirectoryAnalysis();
    void handleComparison();
    void handleSettings();

    string getInput(const string& prompt);
    int getIntInput(const string& prompt);
    bool getYesNo(const string& prompt);

public:
    UserInterface();
    ~UserInterface();

    void run();
};

#endif