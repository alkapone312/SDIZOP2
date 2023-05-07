#pragma once
#include "structures/DoubleSidedList.h"
#include "structures/DynamicArray.h"
#include "structures/Vector.h"

namespace SDIZO {
    class ListsOfNeighbors {
    private:
        DynamicArray<DoubleSidedList<Vector2>>* listsOfNeighbors = new DynamicArray<DoubleSidedList<Vector2>>();
    public:
        ListsOfNeighbors() {}

        ~ListsOfNeighbors() {
            delete listsOfNeighbors;
        }
    };
};