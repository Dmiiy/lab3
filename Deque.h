//
// Created by dimak on 04.05.2024.
//

#ifndef LAB3_DEQUE_H
#define LAB3_DEQUE_H
#include <cwchar>
#include <iostream>
#include "Sequence.h"
using namespace std;

template <class T>
class Deque {
    Sequence<T> *data;

public:
    explicit Deque(Sequence<T> *sequence) : data(sequence) {};

    // Деструктор
    ~Deque() {
        delete data;
        data = nullptr;
    }

    // Проверка на пустоту
    bool empty() const {
        return data->getLength() == 0;
    }

    // Получение размера дека
    int getLength() const {
        return data->getLength();
    }

    // Добавление элемента в начало дека
    void pushFront(T item) {
        data->prepend(item);
    }

    // Добавление элемента в конец дека
    void pushBack(T item) {
        data->append(item);
    }

    // Удаление и возврат элемента из начала дека
    T popFront() {
        T value = data->getFirst();
        data->removeAt(0);
        return value;
    }

    // Удаление и возврат элемента из конца дека
    T popBack() {
        T value = data->getLast();
        data->removeAt(data->getLength() - 1);
        return value;
    }

    // Получение элемента по индексу
    T operator[](int i) const {
        return data->get(i);
    }

    // Применение функции к каждому элементу дека
    Deque<T> *map(T (*f)(T)) {
        return new Deque<T>(data->map(f));
    }

    // Фильтрация элементов дека по условию
    Deque<T> *where(bool (*h)(T)) {
        return new Deque<T>(data->where(h));
    }

    // Сворачивание элементов дека с помощью функции
    T reduce(T (*f)(T, T)) {
        return data->reduce(f);
    }

    // Объединение двух деков
    Deque<T> *concat(Deque<T> &deque) {
        return new Deque<T>(data->concat(deque.data));
    }

    // Вывод дека на экран
    void print() {
        wcout << L"Deque size = " << data->getLength() << endl;
        for (int i = 0; i < data->getLength(); i++) {
            wcout << data->get(i) << L" ";
        }
        wcout << endl;
    }

    // Конструктор для ввода элементов дека
    explicit Deque(Sequence<T> *sequence, const wchar_t *string) : data(sequence) {
        wcout << string << endl;
        int N;
        wprintf(L"Введите количество элементов: ");
        wcin >> N;
        // Вводим элементы по одному
        for (int i = 0; i < N; i++) {
            wprintf(L"Введите элемент с индексом %d: ", i);
            T element;
            wcin >> element;
            // Выбор, куда добавить элемент:
            wprintf(L"Добавить в начало (0) или конец (1)? ");
            int choice;
            wcin >> choice;
            if (choice == 0) {
                pushFront(element);
            } else {
                pushBack(element);
            }
            // print(); // Текущее состояние дека
        }
    }

    // Получение подпоследовательности
    Sequence<T> *getSubsequence(int startIndex, int endIndex) const {
        return data->getSubsequence(startIndex, endIndex);
    }

    // Поиск подпоследовательности
    int findSubsequence(Deque<T> &deque) {
        return data->findSubsequence(*deque.data);
    }
};

#endif //LAB3_DEQUE_H
