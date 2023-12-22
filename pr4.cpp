#include <iostream>
#include <fstream>
#include "Windows.h"
#include <cstring>
#include "string.h"
#undef max
using namespace std;
const int sizeArr = 750;

void clearStream() {
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

//int countWords(char str[sizeArr]) {
//	int count = 0;
//	bool endWord = false;
//	for (int i = 0; i < strlen(str); i++) {
//		if (str[i] == ' ' && !endWord) {
//			count++;
//			endWord = true;
//		}
//		else if (ispunct(str[i])) {
//			endWord = false;
//		}
//	}
//	return count;
//}

void delChar(int pos, char str[sizeArr]) {
	for (int i = pos; i < strlen(str); i++) {
		str[i - 1] = str[i];
	}
	str[strlen(str) - 1] = '\0';
}

void edit(char str[sizeArr]) {
	for (int i = 0; i < strlen(str); i++) {
		while (isspace(str[i]) && str[i] == str[i + 1]) {
			delChar((i + 1), str);
		}
		if (!islower(str[i])) {
			str[i] = tolower(str[i]);
		}
		while (ispunct(str[i]) && str[i] == str[i + 1]) {
			delChar((i + 1), str);
		}
	}
}

void mergeWords(char words[75][10], int count, char* str) {
	str[0] = '\0';

	for (int i = 0; i < count; i++) {
		strcat_s(str, 750, words[i]);

		if (i != count - 1) {
			strcat_s(str, 750, " ");
		}
	}
}

void sortWords(char str[sizeArr]){
	char words[75][10];
	int count = 0;
	char* context = nullptr;
	char* token = nullptr;
	token = strtok_s(str, " ", &context);
	while (token != nullptr && count < 75) {
		strcpy_s(words[count++], token);
		token = strtok_s(nullptr, " ", &context);
	}
	for (int i = 0; i < count - 1; i++) {
		for (int j = i + 1; j < count; j++) {
			if (strcmp(words[i], words[j]) > 0) {
				char temp[10];
				strcpy_s(temp, words[i]);
				strcpy_s(words[i], words[j]);
				strcpy_s(words[j], temp);
			}
		}
	}
	mergeWords(words, count, str);
}


void toLat(char str[sizeArr]) {
	for (int i = 0; i < strlen(str); i++) {
		if (isdigit(str[i])) {
			str[i] += '1';
			cout << "\n" <<str[i];
		}
	}
}

int linearSearch(char* str) {
	char pattern [10];
	cout << "\nВведите подстроку\n-->> ";
	clearStream();
	cin.getline(pattern, 10);
	int n = strlen(str);
	int m = strlen(pattern); // длина подстроки

	for (int i = 0; i <= n - m; i++) {
		int j;
		for (j = 0; j < m; j++) {
			if (str[i + j] != pattern[j])
				break;
		}
		if (j == m) // если все символы совпали
			return i; // вернуть индекс начала подстроки
	}

	return -1;
}

int main() {
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
				"5) Бойера-Мура\n" <<
				"6) Выход в главное меню\n-->> ";
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
				toLat(str);
				cout << "\nНовая строка:\n" << str << "\n";
			}
			else if (choise == 4) {
				int result = linearSearch(str);
				if (result == -1)
					cout << "Подстрока не найдена" << endl;
				else
					cout << "Подстрока найдена в позиции: " << result << endl;
			}
			else if (choise == 5) {

			}
			else if (choise == 6) {
				exit(0);
			}
			else {
				cout << "\nНеправильный ввод\n";
			}
		}
		
	}
	else if (choise == 2) {
		char c;
		while (true) {
			cout << "\nМеню:\n" <<
				"1) Отредактировать строку\n" <<
				"2) Отсортировать строку\n" <<
				"3) Заменить цифры буквами\n" <<
				"4) Линейный поиск\n" <<
				"5) Бойера-Мура\n" <<
				"6) Выход в главное меню\n-->> ";
			cin >> choise;
			if (choise == 1) {
				int n = 0;
				fin.open("File.txt");
				while (fin.get(c)){
					str[n] = c;
					++n;
				}
				str[n] = '\0';
				fout.open("File.txt");
				edit(str);
				fout << str;
				fin.close();
				fout.close();
				cout << "\nОтредактированная строка:\n" << str << "\n";
			}
			else if (choise == 2){
				int n = 0;
				fin.open("File.txt");
				while (fin.get(c)) {
					str[n] = c;
					++n;
				}
				str[n] = '\0';
				fout.open("File.txt");
				sortWords(str);
				fout << str;
				fin.close();
				fout.close();
				cout << "\nОтсортированная строка:\n" << str << "\n";
			}
			else if (choise == 3) {
				int n = 0;
				fin.open("File.txt");
				while (fin.get(c)) {
					str[n] = c;
					++n;
				}
				str[n] = '\0';
				fout.open("File.txt");
				toLat(str);
				fout << str;
				fin.close();
				fout.close();
				cout << "\nНовая строка:\n" << str << "\n";
			}
			else if (choise == 4) {
				int n = 0;
				fin.open("File.txt");
				while (fin.get(c)) {
					str[n] = c;
					++n;
				}
				str[n] = '\0';
				int result = linearSearch(str);
				if (result == -1)
					cout << "Подстрока не найдена" << endl;
				else
					cout << "Подстрока найдена в позиции: " << result << endl;
			}
			else if (choise == 5) {

			}
			else if (choise == 6) {
				exit(0);
			}
			else {
				cout << "\nНеправильный ввод\n";
			}
		}
	}
	return 0;
}
