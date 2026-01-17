#include <windows.h>
#include "UserInterface.h"
#include <locale>
#include <clocale>

int main() {
    // Установка русской локали для корректного отображения кириллицы
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    UserInterface ui;
    ui.run();

    return 0;
}
