//
// Created by dimak on 04.05.2024.
//

#ifndef LAB3_DEQUE_H
#define LAB3_DEQUE_H
#include <iostream>
#include "Sequence.h"

#include <vector>
#include "Sequence.h"

template <typename T>
class Deque : public Sequence<T> {
private:
    std::vector<std::vector<T>> segments;
    int headSegment, headIndex;
    int tailSegment, tailIndex;

    void expandIfNeeded() {
        if (tailIndex == segments[tailSegment].size()) {
            segments.push_back(std::vector<T>());
            tailSegment++;
            tailIndex = 0;
        }
    }

public:
    Deque() : headSegment(0), headIndex(0), tailSegment(0), tailIndex(0) {
        segments.push_back(std::vector<T>());
    }

    bool isEmpty() const override {
        return headSegment == tailSegment && headIndex == tailIndex;
    }

    int size() const override {
        int size = 0;
        for (int i = 0; i < segments.size(); ++i) {
            size += segments[i].size();
        }
        return size - headIndex + tailIndex;
    }

    void pushFront(const T& value) override {
        if (headIndex == 0) {
            if (headSegment == 0) {
                segments.insert(segments.begin(), std::vector<T>());
                headSegment++;
            } else {
                headSegment--;
            }
            headIndex = segments[headSegment].size();
        }
        segments[headSegment][--headIndex] = value;
    }

    void pushBack(const T& value) override {
        expandIfNeeded();
        segments[tailSegment][tailIndex++] = value;
    }

    T popFront() override {
        if (isEmpty()) {
            throw std::runtime_error("Deque is empty");
        }
        T value = segments[headSegment][headIndex++];
        if (headIndex == segments[headSegment].size()) {
            headSegment++;
            headIndex = 0;
        }
        return value;
    }

    T popBack() override {
        if (isEmpty()) {
            throw std::runtime_error("Deque is empty");
        }
        if (tailIndex == 0) {
            tailSegment--;
            tailIndex = segments[tailSegment].size();
        }
        return segments[tailSegment][--tailIndex];
    }

    T& front() override {
        if (isEmpty()) {
            throw std::runtime_error("Deque is empty");
        }
        return segments[headSegment][headIndex];
    }

    T& back() override {
        if (isEmpty()) {
            throw std::runtime_error("Deque is empty");
        }
        return segments[tailSegment][tailIndex - 1];
    }

    void clear() override {
        segments.clear();
        segments.push_back(std::vector<T>());
        headSegment = tailSegment = headIndex = tailIndex = 0;
    }
};

#endif //LAB3_DEQUE_H
