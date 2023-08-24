//
// Created by Willy Seah on 24/8/23.
//
#include "memory_pool.hpp"

struct MyStruct {
    int d_[3];
};

int main(int, char **) {
    using namespace Common;

    MemPool<double> doublePool(5);
    MemPool<MyStruct> structPool(5);

    for(auto i = 0; i < 5; ++i) {
        auto p_ret = doublePool.allocate(i);
        auto s_ret = structPool.allocate(MyStruct{i, i+1, i+2});

        std::cout << "prim elem:" << *p_ret << " allocated at:" << p_ret << std::endl;
        std::cout << "struct elem:" << s_ret->d_[0] << "," << s_ret->d_[1] << "," << s_ret->d_[2] << " allocated at:" << s_ret << std::endl;

        if(i % 5 == 0) {
            std::cout << "deallocating prim elem:" << *p_ret << " from:" << p_ret << std::endl;
            std::cout << "deallocating struct elem:" << s_ret->d_[0] << "," << s_ret->d_[1] << "," << s_ret->d_[2] << " from:" << s_ret << std::endl;

            doublePool.deallocate(p_ret);
            structPool.deallocate(s_ret);
        }
    }

    return 0;
}
