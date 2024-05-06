#ifndef STACK_INCLUDED
#define STACK_INCLUDED
#include "Sequence.h"

template <class T>
class Stack {
    Sequence<T> *data;

public:
    explicit Stack(Sequence<T> *sequence) : data(sequence) {};
    //Деструктор
    ~Stack() {
        delete data;
        data = nullptr;
    }
    // Пустой ли стек?
    bool empty() const {
        return data->getLength() == 0;
    }
    int getLength() const {
        return data->getLength();
    }
    void push(T item) {
        data->append(item);
    }
    T pop() {
        T value = data->getLast();
        data->removeAt(data->getLength() - 1);
        return value;
    }
    T operator[](int i) const {
        return data->get(i);
    }
    Stack<T> *map(T (*f)(T)) {
        return new Stack<T>(data->map(f));
    }
    Stack<T> *where(bool (*h)(T)) {
        return new Stack<T>(data->where(h));
    }
    T reduce(T (*f)(T, T)) {
        return data->reduce(f);
    }
    Stack<T> *concat(Stack<T> &stack) {
        return new Stack<T>(data->concat(stack.data));
    }
    void print() {
        wcout << L"Stack size = " << data->getLength() << endl;
        for (int i = 0; i < data->getLength(); i++) {
            wcout << data->get(i) << L" ";
        }
        wcout << endl;
    }
    // Конструктор для ввода элементов стека
    explicit Stack(Sequence<T> *sequence, const wchar_t *string) : data(sequence) {
        wcout << string << endl;
        int N;
        wprintf(L"Введите количество элементов: ");
        wcin >> N;
        // Вводим элементы по одному
        for (int i = 0; i < N; i++) {
            wprintf(L"Введите элемент с индексом %d: ", i);
            T element;
            wcin >> element;
            push(element);  // Добавляем его на вершину стека
            // print(); // Текущее состояние стека
        }
    }
    Sequence<T> *getSubsequence(int startIndex, int endIndex) const {
        return data->getSubsequence(startIndex, endIndex);
    }
    // Поиск подпоследовательности
    int findSubsequence(Stack<T> &stack) {
        return data->findSubsequence(*stack.data);
    }
};

//namespace stack {
//    template <class T>
//    Stack<T> *map(T (*f)(T), Stack<T> &l) {
//        return l.map(f);
//    }
//    template <class T>
//    Stack<T> *where(bool (*h)(T), Stack<T> &l) {
//        return l.where(h);
//    }
//    template <class T>
//    T reduce(T (*f)(T, T), Stack<T> &l) {
//        return l.reduce(f);
//    }
//}
#endif  // STACK_INCLUDED

