#include "task1.h"
#include <iostream>
#include <vector>
#include <limits>

void task1() {
	std::cout << "Вариант 1."<< "\n" << " Задача 1. Башня из банок. \n";
	int n;
	std::cout << "Введите кол-во банок: ";
	std::cin >> n;
	if (n <= 0) {
		std::cout << "Ошибка кол-во банок должно быть положительным\n";
		std::cin.ignore(std::numeric_limits<int>::max(), '\n');
		return;
	}
	//Обработка ввода
	std::vector<int> diam(n); //Задаю диаметр каждому элементу массива
	std::cout << "Введите диметр банок: ";
	for (int i = 0; i < n; ++i)	{
		std::cin >> diam[i];
	}
	std::cin.ignore(std::numeric_limits<int>::max(), '\n');
	//Работа алгоритма Big O(n^2) т.к 2 вложенных цикла
	std::vector<int> dp(n, 1);
	int maxLen = 1;
	for (int i = 0; i < n; ++i)	{
		for (int j = 0; j < i; ++j)	{
			if (diam[j] > diam[i] && dp[j] + 1 > dp[i]) {
				dp[i] = dp[j] + 1;
			}
		}
		if (dp[i] > maxLen) maxLen = dp[i];
	}
	std::cout << "Максимальная высота устойчивой башни: " << maxLen << "\n\n";
}