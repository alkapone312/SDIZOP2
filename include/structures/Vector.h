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

        Pair() {}
        Pair(T x, R y): a(x), b(y) {}

        bool operator < (Pair x) {
            return b < x.b;
        }
        
        bool operator > (Pair x) {
            return b > x.b;
        }
    };
}