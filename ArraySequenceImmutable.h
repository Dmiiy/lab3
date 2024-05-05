#ifndef LAB2_ARRAYSEQUENCEIMMUTABLE_H
#define LAB2_ARRAYSEQUENCEIMMUTABLE_H

#include <cwchar>

#include "DynamicArray.h"
#include "Sequence.h"

template<class T>
class ArraySequenceImmutable : public Sequence<T> {
private:
    DynamicArray<T> data;
public:
    //Создание объекта
    ArraySequenceImmutable(T *data, int count) : data(data, count) {}

    ArraySequenceImmutable() : data() {};

    explicit ArraySequenceImmutable(const DynamicArray<T> &array) : data(array) {};

    //Декомпозиция
    T getFirst() const override {
        return data.get(0);
    };

    T getLast() const override {
        return data.get(data.getSize() - 1);
    };

    T get(int index) const override {
        return data.get(index);
    };

    //Перегруженные операторы
    T operator[](int i) const override {
        return data[i];
    }

    T &operator[](int i) override {
        return data[i];
    }

    Sequence<T> *getSubsequence(int startIndex, int endIndex) const override {
        if (startIndex > endIndex) {
            throw IndexOutOfRange(string("Index startIndex <= endIndex"));
        }
        int size = endIndex - startIndex + 1;
        DynamicArray<T> da(size);
        for (int i = 0; i < size; i++) {
            da[i] = get(startIndex + i);
        }
        return new ArraySequenceImmutable<T>(da);
    }

    int getLength() const override {
        return data.getSize();
    }

    //Операции
    Sequence<T> *append(T item) override {
        int size = data.getSize();
        DynamicArray<T> da(size);
        for (int i = 0; i < size; i++) {
            da[i] = get(i);
        }
        data.resize(size + 1);
        size = data.getSize();
        data.set(size - 1, item);
        return new ArraySequenceImmutable<T>(da);
    };

    Sequence<T> *prepend(T item) override {
        int size = data.getSize();
        DynamicArray<T> da(size);
        for (int i = 0; i < size; i++) {
            da[i] = get(i);
        }
        da.prepend(item);
        return new ArraySequenceImmutable<T>(da);

    };

    Sequence<T> *insertAt(T item, int index) override {
        int size = data.getSize();
        DynamicArray<T> da(size);
        for (int i = 0; i < size; i++) {
            da[i] = get(i);
        }
        da.insertAt(item, index);
        return new ArraySequenceImmutable<T>(da);
    };

    Sequence<T> *concat(Sequence<T> *list) override {
        auto *result = new ArraySequence<T>(this->data);
        result->data.resize(getLength() + list->getLength());
        for (int i = 0; i < list->getLength(); i++) {
            result->data.set(getLength() + i, list->get(i));
        }
        return result;
    };

    Sequence<T> *removeAt(int index) override {
        int size = data.getSize();
        DynamicArray<T> da(size);
        for (int i = 0; i < size; i++) {
            da[i] = get(i);
        }
        da.removeAt(index);
        return new ArraySequenceImmutable<T>(da);
    }



    //Виртуальный деструктор
    virtual ~ArraySequenceImmutable<T>() = default;

    Sequence<T> *map(T (*f)(T)) const override {
        Sequence<T> *res = new ArraySequenceImmutable<T>();
        for (int i = 0; i < getLength(); i++) {
            res->append(f(data.get(i)));
        }
        return res;
    }

    Sequence<T> *where(bool (*h)(T)) const override {
        auto *res = new ArraySequenceImmutable<T>;
        for (int i = 0; i < getLength(); i++) {
            T item = data.get(i);
            if (h(item)) {
                res->append(item);
            }
        }
        return res;
    }

    T reduce(T (*f)(T, T)) const override {
        T result = data.get(0);
        for (int i = 1; i < data.getSize(); i++) {
            result = f(result, data.get(i));
        }
        return result;
    }
};

#endif //LAB2_ARRAYSEQUENCEIMMUTABLE_H
