#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <string>
#include <fcntl.h>

#include "ArraySequence.h"
#include "LinkedListSequence.h"
#include "Common.h"
#include "Sequence.h"
#include "menu.h"


int map_function(int x) {
    return x * x;
}

bool where_function(int x) {
    bool result = (x % 2) == 0;
    wcout << L"  where: число " << x << L" чётное: " << result << endl;
    return result;
}


int reduce_function(int a, int b) {
    int result = a + b;
    wcout << L"  reduce: " << a << L" + " << b << " = " << result << endl;
    return result;
}


void apply_map_where_reduce_linked_list() {
    wprintf(L"Применение функций map, where, reduce\n");
    wprintf(L"Введите из скольки символов будет состоять последовательность: ");
    int length;
    wcin >> length;
    int data[length];
    for (int i = 0; i < length; i++) {
        wcout << L"Введите элемент последовательности под индексом " << i << L": ";
        wcin >> data[i];
    }
    LinkedListSequence<int> linkedListSequence(data, length);

    wprintf(L"Применяем операцию map\n");
    Sequence<int> *mapRes = linkedListSequence.map(map_function);
    mapRes->print();
    delete mapRes;    // Очищаем память

    wprintf(L"Применяем операцию where\n");
    Sequence<int> *whereRes = linkedListSequence.where(where_function);
    whereRes->print();
    delete whereRes;  // Очищаем память

    wprintf(L"Применяем операцию reduce\n");
    int reduceRes = linkedListSequence.reduce(reduce_function);
    wcout << L"Результат reduce: " << reduceRes << endl << endl;

    wprintf(L"\n");
}


void linked_list_concat() {
    wprintf(L"Конкатенация двух списков\n");
    wprintf(L"Введите из скольки символов будет состоять 1 последовательность: ");
    int length;
    wcin >> length;
    int data[length];
    for (int i = 0; i < length; i++) {
        wcout << L"Введите элемент последовательности под индексом " << i << L": ";
        wcin >> data[i];
    }
    wprintf(L"Введите из скольки символов будет состоять 2 последовательность: ");
    int length2;
    wcin >> length2;
    int data2[length];
    for (int i = 0; i < length2; i++) {
        wcout << L"Введите элемент последовательности под индексом " << i << L": ";
        wcin >> data2[i];
    }
    try {
        LinkedListSequence<int> linkedListSequence1(data, length);
        LinkedListSequence<int> linkedListSequence2(data2, length2);
        Sequence<int> *result = linkedListSequence1.concat(&linkedListSequence2);
        result->print();
        delete result;

        wprintf(L"\n");
    } catch (IndexOutOfRange &ex) {
        wcout << L"Exception: " << ex.what() << endl << endl;
    }
}

void linked_list_getSubSequence() {
    wprintf(L"Извлечение подпоследовательности (по заданным индексам)\n");
    wprintf(L"Введите из скольки символов будет состоять последовательность: ");
    int length;
    wcin >> length;
    int data[length];
    for (int i = 0; i < length; i++) {
        wcout << L"Введите элемент последовательности под индексом " << i << L": ";
        wcin >> data[i];
    }
    try {

        wcout << L"Введите начальный индекс: ";
        int startIndex;
        wcin >> startIndex;
        wcout << L"Введите конечный индекс: ";
        int endIndex;
        wcin >> endIndex;
        LinkedListSequence<int> linkedListSequence(data, length);
        Sequence<int> *result = linkedListSequence.getSubsequence(startIndex, endIndex);
        result->print();
        delete result;

        wcout << endl;
    } catch (IndexOutOfRange &ex) {
        wcout << L"Exception: " << ex.what() << endl << endl;
    }
}


void linked_list_findSubSequence() {
    wprintf(L"Поиск на вхождение подпоследовательности\n");
    wprintf(L"Введите из скольки символов будет состоять последовательность: ");
    int length;
    wcin >> length;
    int data[length];
    for (int i = 0; i < length; i++) {
        wcout << L"Введите элемент последовательности под индексом " << i << L": ";
        wcin >> data[i];
    }
    wprintf(L"Ведите из скольки символов будет состоять подпоследовательность: ");
    int subLength;
    wcin >> subLength;
    int subData[subLength];
    for (int i = 0; i < subLength; i++) {
        wcout << L"Введите элемент подпоследовательности под индексом " << i << L": ";
        wcin >> subData[i];
    }
    try {
        LinkedListSequence<int> linkedListSequence(data, length);
        LinkedListSequence<int> subSequence(subData, subLength);
        int index = linkedListSequence.findSubsequence(subSequence);
        wcout << L"Позиция подпоследовательности = " << index << endl << endl;
    } catch (IndexOutOfRange &ex) {
        wcout << L"Exception: " << ex.what() << endl << endl;
    }
}

void dynamic_array_concat() {
    wprintf(L"Конкатенация двух массивов\n");
    wprintf(L"Введите из скольки символов будет состоять 1 последовательность: ");
    int length;
    wcin >> length;
    int data[length];
    for (int i = 0; i < length; i++) {
        wcout << L"Введите элемент последовательности под индексом " << i << L": ";
        wcin >> data[i];
    }
    wprintf(L"Введите из скольки символов будет состоять 2 последовательность: ");
    int length2;
    wcin >> length2;
    int data2[length];
    for (int i = 0; i < length2; i++) {
        wcout << L"Введите элемент последовательности под индексом " << i << L": ";
        wcin >> data2[i];
    }
    try {
        ArraySequence<int> arraySequence1(data, length);
        ArraySequence<int> arraySequence2(data2, length2);
        Sequence<int> *result = arraySequence1.concat(&arraySequence2);
        result->print();
        delete result;

        wprintf(L"\n");
    } catch (IndexOutOfRange &ex) {
        wcout << L"Exception: " << ex.what() << endl << endl;
    }
}

void dynamic_array_getSubSequence() {
    wprintf(L"Извлечение подпоследовательности (по заданным индексам)\n");
    wprintf(L"Введите из скольки символов будет состоять последовательность: ");
    int length;
    wcin >> length;
    int data[length];
    for (int i = 0; i < length; i++) {
        wcout << L"Введите элемент последовательности под индексом " << i << L": ";
        wcin >> data[i];
    }
    try {

        wcout << L"Введите начальный индекс: ";
        int startIndex;
        wcin >> startIndex;
        wcout << L"Введите конечный индекс: ";
        int endIndex;
        wcin >> endIndex;
        ArraySequence<int> arraySequence(data, length);
        Sequence<int> *result = arraySequence.getSubsequence(startIndex, endIndex);
        result->print();
        delete result;

        wcout << endl;
    } catch (IndexOutOfRange &ex) {
        wcout << L"Exception: " << ex.what() << endl << endl;
    }
}


void dynamic_array_findSubSequence() {
    wprintf(L"Поиск на вхождение подпоследовательности\n");
    wprintf(L"Введите из скольки символов будет состоять последовательность: ");
    int length;
    wcin >> length;
    int data[length];
    for (int i = 0; i < length; i++) {
        wcout << L"Введите элемент последовательности под индексом " << i << L": ";
        wcin >> data[i];
    }
    wprintf(L"Ведите из скольки символов будет состоять подпоследовательность: ");
    int subLength;
    wcin >> subLength;
    int subData[subLength];
    for (int i = 0; i < subLength; i++) {
        wcout << L"Введите элемент подпоследовательности под индексом " << i << L": ";
        wcin >> subData[i];
    }
    try {
        ArraySequence<int> arraySequence(data, length);
        ArraySequence<int> subSequence(subData, subLength);
        int index = arraySequence.findSubsequence(subSequence);
        wcout << L"Позиция подпоследовательности = " << index << endl << endl;
    } catch (IndexOutOfRange &ex) {
        wcout << L"Exception: " << ex.what() << endl << endl;
    }
}

// Основные операции
void main_menu_for_linked_list() {
    MenuItem menu_list[] = {
            {L"Применение функции map, where, reduce", apply_map_where_reduce_linked_list},
            {L"Конкатенация двух списков", linked_list_concat},
            {L"Извлечение подпоследовательности (по заданным индексам)", linked_list_getSubSequence},
            {L"Поиск на вхождение подпоследовательности", linked_list_findSubSequence}};
    menuLoop(L"Возможные операции", _countof(menu_list), menu_list);
}


void main_menu_for_dynamic_array() {
    MenuItem menu_array[] = {
            {L"Конкатенация двух массивов", dynamic_array_concat},
            {L"Извлечение подпоследовательности (по заданным индексам)", dynamic_array_getSubSequence},
            {L"Поиск на вхождение подпоследовательности", dynamic_array_findSubSequence}};
    menuLoop(L"Возможные операции", _countof(menu_array), menu_array);
}

// Основная программа
int main() {
    // Задаём кодировку UTF-16 для всего вывода в программе
    // Все символы и строки будут wchar_t
#if WIN32 || WIN64
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);
#endif

    wprintf(L"== Тестирование операций ==\n");

    MenuItem menu[] = {{L"Связанные списки", main_menu_for_linked_list},
                       {L"Динамические массивы", main_menu_for_dynamic_array}};

    try {
        menuLoop(L"Выберите тип элементов", _countof(menu), menu);
    } catch (IndexOutOfRange &ex) {
        wcout << L"Exception: " << ex.what() << endl << endl;
    }

}