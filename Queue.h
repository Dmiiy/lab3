#ifndef LAB3_QUEUE_H
#define LAB3_QUEUE_H

#include <cwchar>
#include <iostream>
#include "Sequence.h"
using namespace std;

template <class T>
class Queue {
    Sequence<T> *data;

public:
    explicit Queue(Sequence<T> *sequence) : data(sequence) {};
    //Деструктор
    ~Queue() {
        delete data;
        data = nullptr;
    }
    // Пустая ли очередь?
    bool empty() const {
        return data->getLength() == 0;
    }
    int getLength() const {
        return data->getLength();
    }
    // Добавление элемента в конец очереди
    void enqueue(T item) {
        data->append(item);
    }
    // Извлечение элемента из начала очереди
    T dequeue() {
        T value = data->getFirst();
        data->removeAt(0);
        return value;
    }
    T operator[](int i) const {
        return data->get(i);
    }
    Queue<T> *map(T (*f)(T)) {
        return new Queue<T>(data->map(f));
    }
    Queue<T> *where(bool (*h)(T)) {
        return new Queue<T>(data->where(h));
    }
    T reduce(T (*f)(T, T)) {
        return data->reduce(f);
    }
    Queue<T> *concat(Queue<T> &queue) {
        return new Queue<T>(data->concat(queue.data));
    }
    void print() {
        wcout << L"Queue size = " << data->getLength() << endl;
        for (int i = 0; i < data->getLength(); i++) {
            wcout << data->get(i) << L" ";
        }
        wcout << endl;
    }
    // Конструктор для ввода элементов очереди
    explicit Queue(Sequence<T> *sequence, const wchar_t *string) : data(sequence) {
        wcout << string << endl;
        int N;
        wprintf(L"Введите количество элементов: ");
        wcin >> N;
        // Вводим элементы по одному
        for (int i = 0; i < N; i++) {
            wprintf(L"Введите элемент с индексом %d: ", i);
            T element;
            wcin >> element;
            enqueue(element);  // Добавляем его в конец очереди
            // print(); // Текущее состояние очереди
        }
    }
    Sequence<T> *getSubsequence(int startIndex, int endIndex) const {
        return data->getSubsequence(startIndex, endIndex);
    }
    // Поиск подпоследовательности
    int findSubsequence(Queue<T> &queue) {
        return data->findSubsequence(*queue.data);
    }
};

namespace queue {
    template <class T>
    Queue<T> *map(T (*f)(T), Queue<T> &l) {
        return l.map(f);
    }
    template <class T>
    Queue<T> *where(bool (*h)(T), Queue<T> &l) {
        return l.where(h);
    }
    template <class T>
    T reduce(T (*f)(T, T), Queue<T> &l) {
        return l.reduce(f);
    }
}
#endif

