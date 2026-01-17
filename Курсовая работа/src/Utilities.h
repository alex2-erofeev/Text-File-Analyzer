#ifndef UTILITIES_H
#define UTILITIES_H
#include <filesystem>
#include "common.h"

using namespace std;

// Функция извлечения имени файла из пути
inline string getFileName(const string& path) {
    filesystem::path p(path);
    return p.filename().string();
}

#endif