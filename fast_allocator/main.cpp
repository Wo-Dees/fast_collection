#include "stack_allocator.hpp"

#include <vector>
#include <cassert>
#include <iostream>

struct Int {
    Int() = delete;
    explicit Int(int x) : x_(x) {};
    int x_;
};

int main() {
    std::vector<Int*> data;
    Allocator<Int, 4> alloc;
    std::cout << data.size() << std::endl;
    for (int i = 0; i < 128; ++i) {
        std::cout << data.size() << std::endl;
        data.push_back(alloc.AllocateAndConstruct(i));
    }
    // for (int i = 0; i < 128; ++i) {
    //     assert(i == data[i]->x_);
    // }
    for (int i = 0; i < 128; ++i) {
        alloc.DeallocateAndDestroy(data[i]);
    }
    return 0;
}