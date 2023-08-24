//
// Created by Willy Seah on 24/8/23.
//

#ifndef TRADINGENGINE_MEMORY_POOL_HPP
#define TRADINGENGINE_MEMORY_POOL_HPP

#include <cstdint>
#include <vector>
#include <string>

#include "../macros.hpp"

namespace Common {
    template<typename T>

    class MemPool {

    public:
        explicit MemPool(int numElems) {
            std::vector<ObjectBlock> store(numElems, {T(), true});
        }

        template<typename... Args>
        T *allocate(Args... args) noexcept {

            auto objBlock = &(store[nextFreeIndex]); //return pointer to that free block, remember block as object and bool

            ASSERT(objBlock->isFree, "Expected free ObjectBlock at index:" + std::to_string(nextFreeIndex)); //assert that it is free
            //remember we assert this is usually true.

            T* obj = &(objBlock->object); //get a pointer to that object

            obj = new(obj) T(args...); //place new object, initialize that new object.
            //TODO need to override new operator dont need to allocate on heap, call this allocate function instead

            objBlock->isFree = false;
            updateNextFreeIndex();

            return obj; //return the address where we store the new object

        }

        auto deallocate(T *elem) { //takes in address of where we initially store obj
            const auto elem_index = (reinterpret_cast<const ObjectBlock *> (elem) - &store[0]); //since all objects are same size, we can get index.
            ASSERT(elem_index >= 0 && static_cast<size_t>(elem_index) < store.size(), "Element being deallocated does not belong to this Memory pool.");
            ASSERT(!store[elem_index].isFree, "Expected used/occupied ObjectBlock at index:" + std::to_string(elem_index));

            store[elem_index].isFree = true;

        }


        // Deleted default, copy & move constructors and assignment-operators.
        //to prevent accidental usage
        MemPool() = delete;

        MemPool(const MemPool &) = delete;

        MemPool(const MemPool &&) = delete;

        MemPool &operator=(const MemPool &) = delete;

        MemPool &operator=(const MemPool &&) = delete;

    private:
        auto updateNextFreeIndex() noexcept {

            int initialFreeIndex = nextFreeIndex;

            while (store[nextFreeIndex].isFree == false) {
                ++nextFreeIndex;

                long expr = UNLIKELY(nextFreeIndex == store.size());
                if (expr) {
                    //using UNLIKELY, telling compiler this is usually false, because we only hit end of vector once every n times.
                    nextFreeIndex = 0;
                }

                expr = UNLIKELY(initialFreeIndex == nextFreeIndex);

                if (expr) {
                    ASSERT(initialFreeIndex != nextFreeIndex, "Memory Pool out of space.");
                }//no space
            }
        }


        struct ObjectBlock {
            T object;
            bool isFree = true;
        };

        std::vector<ObjectBlock> store;
        int nextFreeIndex = 0;

    };
}



#endif //TRADINGENGINE_MEMORY_POOL_HPP
