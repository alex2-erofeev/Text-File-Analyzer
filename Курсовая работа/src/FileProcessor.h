#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include "common.h"

class FileProcessor {
protected:
    vector<string> filePaths;
    string lastError;

    bool fileExists(const string& path) const;

public:
    FileProcessor();
    virtual ~FileProcessor();

    bool addFile(const string& path);
    bool addFilesFromDirectory(const string& dirPath);
    vector<string> getFilePaths() const;
    string getLastError() const;
    virtual void analyzeAllFiles() = 0;

    virtual string readFile(const string& path);
    vector<string> readAllFiles();
};

#endif