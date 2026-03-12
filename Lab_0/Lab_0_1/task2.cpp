#include "task2.h"
#include <iostream>
#include <string>
#include <sstream>

void task2() {
	std::cout << "Вариант 1" << "\n" << "Задача 2. Самое длинное слово" << "\n Введите предложение из слов (слова в свою очередь могут быть разделены пробелами,"<<" так же могут быть использованы \".\" и \",\"): ";
	std::string line;
	std::getline(std::cin,line);

	std::istringstream ss(line);
	std::string token;
	std::string longestWord;
	size_t maxLen = 0;

	while (ss >> token)	{
		size_t start = 0;
		while (start < token.size() && (token[start] == '.' || token[start] == ','))	{
			++start;
		}
		size_t end= 0;
		while (end > start && (token[end - 1] == '.' || token[end - 1] == ',')) {
			--end;
		}

		if (maxLen > 0) {
			std::cout << "Самое длинное слово: \" " << longestWord << "\"" << maxLen << ")\n\n";
		}else {
			std::cout << "В предложении нет слов. \n\n";
		}
	}
}


//str.erase()