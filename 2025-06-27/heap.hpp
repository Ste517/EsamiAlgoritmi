#ifndef HEAP_HPP
#define HEAP_HPP
#include <vector>

template <class T>
class Heap {
    // Membri privati
    std::vector<T> data;

    // Funzioni private
    inline bool isValidIndex(size_t i) const noexcept {
        return i < data.size();
    }

    inline static size_t parent(size_t i) noexcept { return (i - 1) / 2; }
    inline static size_t left_child(size_t i) noexcept { return 2 * i + 1; }
    inline static size_t right_child(size_t i) noexcept { return 2 * i + 2; }

    void up(size_t i) {
        while (i > 0 && data[i] > data[parent(i)]) {
            std::swap(data[i], data[parent(i)]);
            i = parent(i);
        }
    }

    void down(size_t i) {
        size_t largest = i;
        size_t left = left_child(i);
        size_t right = right_child(i);

        if (left < data.size() && data[left] > data[largest]) {
            largest = left;
        }
        if (right < data.size() && data[right] > data[largest]) {
            largest = right;
        }

        if (largest != i) {
            std::swap(data[i], data[largest]);
            down(largest);
        }
    }

public:
    Heap() = default;

    explicit Heap(size_t initial_capacity) {
        data.reserve(initial_capacity);
    }

    bool empty() const noexcept {
        return data.empty();
    }

    size_t size() const noexcept {
        return data.size();
    }

    T pop() {
        if (data.empty()) {
            return std::move(T());
        }

        T val = std::move(data.front());
        data[0] = std::move(data.back());
        data.pop_back();

        if (!data.empty()) {
            down(0);
        }

        return val;
    }

    std::vector<T> pop(size_t amount) {
        std::vector<T> temp(amount);
        for (size_t i = 0; i < amount; ++i) {
            temp[i] = pop();
        }
        return std::move(temp);
    }

    void push(const T& val) {
        data.push_back(val);
        up(data.size() - 1);
    }

    void push(T&& val) {
        data.push_back(std::move(val));
        up(data.size() - 1);
    }
};

#endif
