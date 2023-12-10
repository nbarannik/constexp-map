#pragma once

#include <exception>
#include <stdexcept>

template <class K, class V, int MaxSize = 8>
class ConstexprMap {
public:
    constexpr ConstexprMap() = default;

    constexpr V& operator[](const K& key) {
        if (size_t index = FindIndex(key); index != size_) {
            return key_values_[index].second;
        }
        return AddKeyValue(key);
    }

    constexpr const V& operator[](const K& key) const {
        if (size_t index = FindIndex(key); index != size_) {
            return key_values_[index].second;
        }
        throw std::runtime_error("No such key in map");
    }

    constexpr bool Erase(const K& key) {
        if (size_t index = FindIndex(key); index != size_) {
            for (size_t i = index; i < size_ - 1; ++i) {
                key_values_[i] = key_values_[i + 1];
            }
            --size_;
            return true;
        } else {
            return false;
        }
    }

    constexpr bool Find(const K& key) const {
        return FindIndex(key) != size_;
    }

    constexpr size_t Size() const {
        return size_;
    }

    constexpr const std::pair<K, V>& GetByIndex(size_t pos) const {
        if (pos >= size_) {
            throw std::range_error("Index out of range");
        }
        return key_values_[pos];
    }

    constexpr std::pair<K, V>& GetByIndex(size_t pos) {
        if (pos >= size_) {
            throw std::range_error("Index out of range");
        }
        return key_values_[pos];
    }

private:
    constexpr size_t FindIndex(const K& key) const {
        for (size_t i = 0; i < size_; ++i) {
            if (key_values_[i].first == key) {
                return i;
            }
        }
        return size_;
    }

    constexpr V& AddKeyValue(const K& key) {
        if (size_ == MaxSize) {
            throw std::runtime_error("Cannot add new element, map is full");
        }
        key_values_[size_].first = key;
        return key_values_[size_++].second;
    }

    std::pair<K, V> key_values_[MaxSize] = {};
    size_t size_ = 0;
};
