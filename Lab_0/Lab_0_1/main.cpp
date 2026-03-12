#include <iostream>
#include <windows.h>
#include "task1.h"
#include "task2.h"
#include "task3.h"
#include "task4.h"
#include "task5.h"

int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	bool ch = true; int choice;

	l1: while (ch != false) {
		system("cls");
		std::cout << "Введите какую задачу нужно посмотреть от 1 до 5: \n";
		std::cin >> choice;
		switch (choice) {
		case 1:
			system("cls");
			task1();
			system("pause");
			system("cls");
			std::cout << "Вернуться или завершить програму?\n"<<"1/0\n";
			std::cin >> choice;
			if (choice == 1) {
				goto l1;
			}else {
				ch = false;
			}
		case 2:
			system("cls");
			task2();
			system("pause");
			system("cls");
			std::cout << "Вернуться или завершить програму?\n" << "1/0\n";
			std::cin >> choice;
			if (choice == 1) {
				goto l1;
			}
			else {
				ch = false;
			}
		//case 3:
		//	task3();
		//	std::cout << "Вернуться или завершить програму?\n" << "1/0\n";
		//	std::cin >> choice;
		//	if (choice == 1) {
		//		goto l1;
		//	}
		//	else {
		//		ch = false;
		//	}
		//case 4:
		//	task4();
		//	std::cout << "Вернуться или завершить програму?\n" << "1/0\n";
		//	std::cin >> choice;
		//	if (choice == 1) {
		//		goto l1;
		//	}
		//	else {
		//		ch = false;
		//	}
		//case 5:
		//	task5();
		//	std::cout << "Вернуться или завершить програму?\n" << "1/0\n";
		//	std::cin >> choice;
		//	if (choice == 1) {
		//		goto l1;
		//	}
		//	else {
		//		ch = false;
		//	}
		}
	}
	return 0;
}