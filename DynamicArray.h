#ifndef DYNAMICARRAY_INCLUDED
#define DYNAMICARRAY_INCLUDED

#include <cstring>
#include <iostream>

#include "Common.h"

template <class T>
class DynamicArray {
    int size;       // Количество элементов массива
    T *data;        // Данные массива
    bool *defined;  // Задан ли элемент массива?

    void checkIndex(int index) const {
        if (index < 0 || index >= size) {
            throw IndexOutOfRange(string("Index ") + to_string(index) + " out of range 0.." + to_string(size - 1));
        }
    }

public:
    //Создание объекта
    DynamicArray(T *items, int count) : size(count) {
        if (size < 0) throw IndexOutOfRange("Size < 0");
        data = new T[size];
        defined = new bool[size];
        memcpy(data, items, sizeof(T) * size);
        for (int i = 0; i < size; i++) {
            defined[i] = true;
        }
    };
    explicit DynamicArray(int count = 0) : size(count) {
        if (size < 0) throw IndexOutOfRange("Count < 0");
        data = new T[size];
        defined = new bool[size];
        for (int i = 0; i < size; i++) {
            defined[i] = false;
        }
    }
    DynamicArray(const DynamicArray<T> &dynamicArray) {
        size = dynamicArray.size;
        // Копируем элементы
        data = new T[dynamicArray.size];
        memcpy(data, dynamicArray.data, dynamicArray.size * sizeof(T));
        // Копируем какие элементы определены
        defined = new bool[dynamicArray.size];
        memcpy(defined, dynamicArray.defined, dynamicArray.size * sizeof(bool));
    }
    //Деструктор
    ~DynamicArray() {
        delete[] data;
        data = nullptr;
        delete[] defined;
        defined = nullptr;
    }
    //Декомпозиция
    T &get(int index) const {
        checkIndex(index);
        if (!defined[index]) {
            throw IndexOutOfRange(string("Element with index ") + to_string(index) + " not defined");
        }
        return data[index];
    }
    int getSize() const {
        return size;
    }
    //Операции
    void set(int index, T value) {
        checkIndex(index);
        data[index] = value;
        defined[index] = true;
    }
    T operator[](size_t index) const {  // Получение значения
        return get(index);
    }
    T &operator[](size_t index) {  // Чтобы делать присваивание так: dynamicArray[1] = 1233;
        checkIndex(index);
        defined[index] = true;
        return data[index];
    }
    // Изменить размер массива
    void resize(int newSize) {
        if (newSize < 0) {
            throw bad_array_new_length();
        }
        T *newData = new T[newSize];
        bool *newDefined = new bool[newSize];
        // Если размер увеличивается, все элементы копируются в начало новой памяти
        // Если уменьшается – элементы, которые не помещаются, отбрасываются
        for (int i = 0; i < min(size, newSize); i++) {
            newData[i] = data[i];
            newDefined[i] = defined[i];
        }
        memcpy(newData, data, sizeof(T) * min(size, newSize));
        // Копируем какие элементы определены
        memcpy(newDefined, defined, sizeof(bool) * min(size, newSize));
        // Оставшиеся заполняем false - будет работать только если newSize > size
        for (int i = size; i < newSize; i++) {
            newDefined[i] = false;
        }
        // Обновляем количество элементов, сами элементы и какие определены
        size = newSize;
        delete[] data;  // Очищаем память
        data = newData;
        delete[] defined;  // Очищаем память
        defined = newDefined;
    }
    // Меняем элементы i и j местами
    // Может быть использовано для сортировки и других алгоритмов

    void append(T item) {
        resize(size + 1);  // Увеличиваем массив на 1
        set(size - 1, item);
    }
    // Добавляем элемент в начало массива
    void prepend(T item) {
        resize(size + 1);  // Увеличиваем массив на 1
        // Сдвигаем все элементы вправо (в сторону увеличения индексов)
        for (int i = size - 1; i >= 1; i--) {
            data[i] = data[i - 1];
            defined[i] = defined[i - 1];
        }
        // Вставляем новый элемент как первый
        data[0] = item;
        defined[0] = true;
    }
    // Вставляет элемент в заданную позицию
    // Может выбрасывать исключения:
    // − IndexOutOfRange (если индекс отрицательный или больше/равен числу элементов)
    void insertAt(T item, int index) {
        resize(size + 1);  // Увеличиваем размер на 1
        checkIndex(index);  // Проверяем индекс и генерируем исключение если он неверный
        // Сдвигаем все элементы вправо
        for (int i = size - 1; i > index; i--) {
            data[i] = data[i - 1];
            defined[i] = defined[i - 1];
        }
        set(index, item);
    };
    // Удаление элемента по индексу
    void removeAt(const int index) {
        checkIndex(index);  // Проверяем индекс и генерируем исключение если он неверный
        for (int i = index + 1; i < size; i++) {  // Сдвигаем все элементы начиная с index+1 влево на один
            data[i - 1] = data[i];  // Сдвигаем значение
            defined[i - 1] = defined[i];
        }
        resize(size - 1);  // Уменьшаем размер массива
    }
    // Печать динамического массива
    void print() const {
        wcout << L"DynamicArray size = " << size << L":";
        for (int i = 0; i < size; i++) {
            if (defined[i])
                wcout << L" " << data[i];
            else
                wcout << L" *";  // Если элемент "не задан" => печатается звёздочка *
        }
        wcout << endl;
    }
};

#endif
