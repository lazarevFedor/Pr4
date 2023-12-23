#include <iostream>
#include <fstream>
#include "Windows.h"
#include "string.h"
#undef max
using namespace std;
const int sizeArr = 500;
const int strLenght = 50;
const int wordLenght = 10;
char numbers[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

void clearStream() {
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
//Пунктуационные функции
int isNumber(char x) {
	for (int i = 0; i < strlen(numbers); i++) {
		if (x == numbers[i]) {
			return 1;
		}
	}
	return 0;
}

int isLower(char x) {
	if (x >= 'а' && x <= 'я') return 1;
	if (x >= 'a' && x <= 'z') return 1;
	else  return 0;
}

int isSpace(char x) {
	if (x == ' ')    return 1;
	else  return 0;
}

int isPunct(char x) {
	if (x >= '!' && x <= '/' || x >= ':' && x <= '@' || x >= '[' && x <= '`' || x >= '{' && x <= '~') return 1;
	else  return 0;
}

char toLower(char x) {
	if (x >= 'A' && x <= 'Z') {
		x += 26;
		return x;
	}
	if (x >= 'А' && x <= 'Я') {
		x += 32;
		return x;
	}
}


void delChar(int pos, char str[sizeArr]) {
	for (int i = pos; i < strlen(str); i++) {
		str[i - 1] = str[i];
	}
	str[strlen(str) - 1] = '\0';
}

void edit(char str[sizeArr]) {
	for (int i = 0; i < strlen(str); i++) {
		while (isSpace(str[i]) && str[i] == str[i + 1]) {
			delChar((i + 1), str);
		}
		if (!isLower(str[i]) && i != 0){
			str[i] = toLower(str[i]);
		}
		while (isPunct(str[i]) && str[i] == str[i + 1]) {
			delChar((i + 1), str);
		}
	}
}

void mergeWords(char words[strLenght][wordLenght], int count, char* str) {
	str[0] = '\0';

	for (int i = 0; i < count; i++) {
		strcat_s(str, sizeArr, words[i]);

		if (i != count - 1) {
			strcat_s(str, sizeArr, " ");
		}
	}
}

int split(char str[sizeArr], char words[50][10]) {
	int wordsCount = 0;
	int wordIndex = 0;
	int wordLength = 0;
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] == ' ') {
			words[wordIndex][wordLength] = '\0';
			wordIndex++;
			wordsCount++;
			wordLength = 0;
		}
		else {
			words[wordIndex][wordLength] = str[i];
			wordLength++;
		}
	}
	words[wordIndex][wordLength] = '\0';
	wordsCount++;
	return wordsCount;
}

int strСmp(const char* a, const char* b) {
	while (*a && *b && *a == *b)
		++a, ++b;
	return *a - *b;
}

void sortWords(char str[sizeArr]) {
	char words[strLenght][wordLenght];
	int count = split(str, words);
	for (int i = 0; i < count - 1; i++) {
		for (int j = i + 1; j < count; j++) {
			if (strСmp(words[i], words[j]) > 0) {
				char temp[wordLenght];
				strcpy_s(temp, words[i]);
				strcpy_s(words[i], words[j]);
				strcpy_s(words[j], temp);
			}
		}
	}
	mergeWords(words, count, str);
}


void toLatin(char str[sizeArr]) {
	for (int i = 0; i < strlen(str); i++) {
		if (isNumber(str[i])) {
			str[i] += '1';
		}
	}
}


void linearS(char* str) {
	char pattern[wordLenght];
	int count = 0;
	cout << "\nВведите подстроку\n-->> ";
	clearStream();
	cin.getline(pattern, wordLenght);
	int strL = strlen(str);
	int patL = strlen(pattern);
	for (int i = 0; i <= strL - patL; i++) {
		int j;
		for (j = 0; j < patL; j++) {
			if (str[i + j] != pattern[j])
				break;
		}
		if (j == patL) {
			count++;
			cout << "Подстрока найдена под индексом " << i << "\n";
		}
	}
	if (count == 0) {
		cout << "Подстрока не найдена\n";
	}
}

int main4() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	ofstream fout;
	ifstream fin;

	char str[sizeArr];
	int choise;
	cout << "Выберите способ заполнения:\n" <<
		"1) С клавиатуры\n2) Из файла\n-->> ";
	cin >> choise;
	if (choise == 1) {
		cout << "Заполните строку:\n";
		clearStream();
		cin.getline(str, sizeArr);
		while (true) {
			cout << "\nМеню:\n" <<
				"1) Отредактировать строку\n" <<
				"2) Отсортировать строку\n" <<
				"3) Заменить цифры буквами\n" <<
				"4) Линейный поиск\n" <<
				"5) Выход в главное меню\n-->> ";
			cin >> choise;
			if (choise == 1) {
				edit(str);
				cout << "\nОтредактированная строка:\n" << str << "\n";
			}
			else if (choise == 2) {
				sortWords(str);
				cout << "\nОтсортированная строка:\n" << str << "\n";
			}
			else if (choise == 3) {
				toLatin(str);
				cout << "\nНовая строка:\n" << str << "\n";
			}
			else if (choise == 4) {
				linearS(str);
			}
			else if (choise == 5) {
				return 0;
			}
			else {
				cout << "\nНеправильный ввод\n";
			}
		}

	}
	else if (choise == 2) {
		char c;
		int n = 0;
		fin.open("First.txt");
		while (fin.get(c)) {
			str[n] = c;
			++n;
		}
		str[n] = '\0';
		fin.close();
		while (true) {
			cout << "\nМеню:\n" <<
				"1) Отредактировать строку\n" <<
				"2) Отсортировать строку\n" <<
				"3) Заменить цифры буквами\n" <<
				"4) Линейный поиск\n" <<
				"5) Выход в главное меню\n-->> ";
			cin >> choise;
			if (choise == 1) {
				edit(str);
				cout << "\nОтредактированная строка:\n" << str << "\n";
			}
			else if (choise == 2) {
				sortWords(str);
				cout << "\nОтсортированная строка:\n" << str << "\n";
				fout.open("First.txt");
				fout << str;
				fout.close();
			}
			else if (choise == 3) {
				int n = 0;
				fin.open("Second.txt");
				while (fin.get(c)) {
					str[n] = c;
					++n;
				}
				str[n] = '\0';
				fin.close();
				toLatin(str);
				fout.open("Second.txt");
				fout << str;
				fout.close();
				cout << "\nНовая строка:\n" << str << "\n";
			}
			else if (choise == 4) {
				int n = 0;
				fin.open("First.txt");
				while (fin.get(c)) {
					str[n] = c;
					++n;
				}
				str[n] = '\0';
				fin.close();
				linearS(str);
			}
			else if (choise == 5) {
				fout.open("First.txt");
				fout << str;
				fout.close();
				return 0;
			}
			else {
				cout << "\nНеправильный ввод\n";
			}
		}
	}
	return 0;
}
