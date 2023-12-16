#include <iostream>
#include <fstream>
#include "Windows.h"
using namespace std;
const int sizeArr = 500;

unsigned strLen(char str[sizeArr]){
	unsigned len = 0;
	while (str[len]) {
		++len;
	}
	return len;
}

int bSearch(char str[sizeArr], char x) {
	int left = 0;
	int right = strLen(str) - 1;
	int middle;
	while (left <= right) {
		middle = (left + right) / 2;
		if (x == str[middle]) {
			return middle;
		}
		else if (x > str[middle]) {
			left = middle + 1;
		}
		else {
			right = middle - 1;
		}
	}
	return -1;
}

int isUpper(char x){
	if (x >= 'А' && x <= 'Я') return 1;
	if (x >= 'A' && x <= 'Z') return 1;
	else  return 0;
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
		x += 'z' - 'Z';
		return x;
	}
	if (x >= 'А' && x <= 'Я') {
		x += 'я' - 'Я';
		return x;
	}
}

void toUpper(char x) {

}

void delChar(int pos, char str[sizeArr]) {
	for (int i = pos; i < strLen(str); i++) {
		str[i - 1] = str[i];
	}
	str[strlen(str) - 1] = '\0';
}

//void strcat(char str[sizeArr]){
//
//	unsigned j = my_StrLen(S1);
//
//	for (unsigned i = 0; S2[i]; ++i, ++j)
//
//		S1[j] = S2[i];
//
//	S1[++j] = '\0';
//
//}



void edit(char str[sizeArr]) {
	for (int i = 0; i < strLen(str); i++) {
		while (isSpace(str[i]) && str[i] == str[i + 1]) {
			delChar((i+1), str);
		}
		if (!isLower(str[i])){
			str[i] = toLower(str[i]);
		}
		while (isPunct(str[i]) && str[i] == str[i + 1]) {
			delChar((i + 1), str);
		}
	}
}

void wordSort(char str[]) {
	/*char words[10][50]{};
	int count = 1;
	for (int i = 0; i < strLen(str); i++) {
		if (str[i] == ' ') {
			count++;
		}
	}
	for (int i = 0; i < strLen(str); i++) {
		for (int j = 0; j < )
	}
	int wordCount = 0;
	int startPos = 0;
	int endPos = bSearch(str, ' ');
	while (endPos >= 0) {
		wordCount++;
		startPos = endPos + 1;
		endPos = bSearch(str, ' ');
	}*/
}

int main(){
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char str [sizeArr];
	while (true) {
		cout << "Заполните строку:\n";
		cin.getline(str, sizeArr);
		edit(str);
		cout << "\nОтредактированная строка:\n";
		cout << str << "\n";
		wordSort(str);
	}
	return 0;
}
