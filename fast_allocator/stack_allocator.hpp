#pragma once

#include <cstdlib>
#include <type_traits>
#include <utility>

template <class T, std::size_t N>
class Allocator {
    static constexpr std::size_t stub = -1;
public:
    Allocator() {
        head_ = N - 1;
        meta_[0] = stub;
        for (std::size_t i = 1; i < N; ++i) {
            meta_[i] = i - 1;
        }
    }

    template <typename... Args>
    T* AllocateAndConstruct(Args&&... args) {
        if (head_ == stub) {
            return nullptr;
        }
        auto new_obj = new(operator*() + sizeof(T) * head_) T(std::forward<Args>(args)...);
        head_ = meta_[head_];
        return new_obj;
    }

    void DeallocateAndDestroy(T* ptr) {
        std::size_t offset = (ptr - operator*()) / sizeof(T);
        meta_[offset] = head_;
        head_ = offset;
        ptr->~T();
    }

private:
    T* operator*() {
        return static_cast<T*>(static_cast<void*>(&data_));
    }

    std::size_t head_;
    std::size_t meta_[N];
    std::aligned_storage_t<sizeof(T), alignof(T)> data_[N];
};
