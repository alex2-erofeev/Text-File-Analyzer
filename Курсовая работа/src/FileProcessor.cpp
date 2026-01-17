#include "FileProcessor.h"
#include <filesystem>

namespace fs = std::filesystem;

FileProcessor::FileProcessor() {
    lastError = "";
}

FileProcessor::~FileProcessor() {}

bool FileProcessor::fileExists(const string& path) const {
    ifstream file(path);
    return file.good();
}

bool FileProcessor::addFile(const string& path) {
    if (!fileExists(path)) {
        lastError = "Файл не найден: " + path;
        return false;
    }
    filePaths.push_back(path);
    return true;
}

bool FileProcessor::addFilesFromDirectory(const string& dirPath) {
    try {
        if (!fs::exists(dirPath) || !fs::is_directory(dirPath)) {
            lastError = "Директория не найдена: " + dirPath;
            return false;
        }

        int count = 0;
        for (const auto& entry : fs::directory_iterator(dirPath)) {
            if (entry.is_regular_file()) {
                string ext = entry.path().extension().string();
                if (ext == ".txt") {
                    filePaths.push_back(entry.path().string());
                    count++;
                }
            }
        }

        if (count == 0) {
            lastError = "В директории не найдено текстовых файлов";
            return false;
        }

        return true;
    }
    catch (const exception& e) {
        lastError = string("Ошибка при чтении директории: ") + e.what();
        return false;
    }
}

vector<string> FileProcessor::getFilePaths() const {
    return filePaths;
}

string FileProcessor::getLastError() const {
    return lastError;
}

string FileProcessor::readFile(const string& path) {
    ifstream file(path);
    if (!file.is_open()) {
        lastError = "Не удалось открыть файл: " + path;
        return "";
    }

    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

vector<string> FileProcessor::readAllFiles() {
    vector<string> contents;
    for (const auto& path : filePaths) {
        string content = readFile(path);
        if (!content.empty()) {
            contents.push_back(content);
        }
    }
    return contents;
}