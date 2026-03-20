#ifndef LONGEST_WORD_H
#define LONGEST_WORD_H

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

inline void run() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    std::cout << "Введите предложение: ";
    std::string line;
    std::getline(std::cin, line);

    std::vector<std::string> longest_words;
    size_t max_len = 0;
    std::string word;

    for (char ch : line) {
        if (ch == ' ' || ch == '.' || ch == ',') {
            if (!word.empty()) {
                if (word.length() > max_len) {
                    max_len = word.length();
                    longest_words.clear();
                    longest_words.push_back(word);
                }
                else if (word.length() == max_len) {
                    longest_words.push_back(word);
                }
                word.clear();
            }
        }
        else {
            word += ch;
        }
    }

    if (!word.empty()) {
        if (word.length() > max_len) {
            longest_words.clear();
            longest_words.push_back(word);
        }
        else if (word.length() == max_len) {
            longest_words.push_back(word);
        }
    }

    if (longest_words.empty()) {
        std::cout << "Слов не найдено." << std::endl;
    }
    else {
        std::cout << "Самое длинное слово (все варианты):" << std::endl;
        for (const auto& w : longest_words) {
            std::cout << w << std::endl;
        }
    }
}

#endif