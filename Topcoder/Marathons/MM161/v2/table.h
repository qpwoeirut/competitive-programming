#ifndef TABLE_H
#define TABLE_H

#include <algorithm>
//#include <cassert>
#include <tuple>
#include <utility>

template <typename T, size_t N>
struct SmallTable {
    T items[N];
    int indexes[N];
    int size;

    SmallTable() : size(0) {
        std::fill(indexes, indexes + N, -1);
    }
    
    bool empty() const {
        return size == 0;
    }

    void insert(const T& item) {
        const int idx = item.hash();
        if (idx == -1) return;
        //assert(0 <= idx && idx < (int)N);
        if (indexes[idx] == -1) {
            indexes[idx] = size++;
            //assert(size <= (int)N);
        }
        items[indexes[idx]] = item;
    }

    template <typename... Args>
    void emplace(Args&&... args) {
        insert(T(std::forward<Args>(args)...));  // not super efficient but whatever
    }

    void erase(const int idx) {
        if (idx == -1) return;
        if (indexes[idx] != -1) {
            indexes[items[--size].hash()] = indexes[idx];
            std::swap(items[indexes[idx]], items[size]);
            indexes[idx] = -1;
            //assert(size >= 0);
        }
    }

    void erase(const T& item) {
        erase(item.hash());
    }
};

const int LARGE_SIZE = 1 << 23;
const int MASK = LARGE_SIZE - 1;  // Unsure if this will mess w/ zobrist hashing
template <typename T, typename U>
struct LargeTable {
    std::tuple<T, U, int> items[LARGE_SIZE];
    int indexes[LARGE_SIZE];
    int size;

    LargeTable() : size(0) {
        std::fill(indexes, indexes + LARGE_SIZE, -1);
    }

    bool get(const T& hash, U& out) const {
        int idx = indexes[hash & MASK];
        while (idx != -1) {
            if (std::get<0>(items[idx]) == hash) {
                out = std::get<1>(items[idx]);
                return true;
            }
            idx = std::get<2>(items[idx]);
        }
        return false;
    }

    U set(const T& hash, const U& item) {
        items[size] = std::make_tuple(hash, item, indexes[hash & MASK]);
        indexes[hash & MASK] = size++;
        //assert(size < LARGE_SIZE);

        return item;
    }
};

#endif  // TABLE_H
