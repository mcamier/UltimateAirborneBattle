#ifndef _C_UAB_MATH_H_
#define _C_UAB_MATH_H_

#include <random>
#include <assert.h>
#include <math.h>

class MathUtils {

public:
    static const float PI;
    static const float TWO_PI;
    static const float HALF_PI;

    static float cosFromDeg(float x) {
        return cos(degToRad(x));
    }

    static float sinFromDeg(float x) {
        return sin(degToRad(x));
    }

    static float degToRad(float x) {
        return x*(MathUtils::PI / 180);
    }

    static float radToDeg(float x) {
        return x * (180 / MathUtils::PI);
    }

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