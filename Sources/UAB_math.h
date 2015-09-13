#ifndef _C_UAB_MATH_H_
#define _C_UAB_MATH_H_

#include <random>
#include <assert.h>

class MathUtils {
public:

    static int randint(int n) {
        if ((n - 1) == RAND_MAX) {
            return rand();
        }
        else {
            long end = RAND_MAX / n;
            assert(end > 0L);
            end *= n;
            int r;
            while ((r = rand()) >= end);
            return r % n;
        }
    }
};

#endif