#include "lab1.h"
#include <windows.h>
#include <iostream>

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int choice;
    do {
        std::cout << "\n==================== МЕНЮ ====================\n";
        std::cout << "1. Задача 1 (Алгоритмы поиска)\n";
        std::cout << "2. Задача 2 (Поиск в двумерном массиве)\n";
        std::cout << "3. Задача 3 (Поиск в отсортированной матрице)\n";
        std::cout << "4. Задача 4 (Морской бой, вариант 1)\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите задание: ";
        std::cin >> choice;

        switch (choice) {
        case 1: task1(); break;
        case 2: task2(); break;
        case 3: task3(); break;
        case 4: task4(); break;
        case 0: std::cout << "Выход.\n"; break;
        default: std::cout << "Неверный выбор. Повторите.\n";
        }
    } while (choice != 0);
    return 0;
}