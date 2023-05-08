#pragma once

namespace SDIZO {
    struct Vector2 {
        int x;
        int y;
    };

    struct Vector3 {
        int x;
        int y;
        int z;
    };
    
    template <typename T, typename R>
    struct Pair {
        T a;
        R b;
    };
}