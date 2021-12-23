#include "Functions.h"


float Q_rsqrt(float number) {
    long i;
    float x2, y;
    const float threehalfs  = 1.5F;

    x2                      = number * 0.5F;
    y                       = number;
    i                       = *(long*)&y;                           // evil floating point bit level hacking
    i                       = 0x5f3759df - (i >> 1);                // what the fuck?
    y                       = *(float*)&i;
    y                       = y * (threehalfs - (x2 * y * y));      // 1st iteration

    return                  y;
}

float vecLen(sf::Vector2f vector) {
    return                  vector.x * vector.x + vector.y * vector.y;
}

sf::Vector2f normV(sf::Vector2f vector) {
    sf::Vector2f    vector1 = vector;
    float           InvLen  = Q_rsqrt(vecLen(vector1));
                    vector1 *= InvLen;
    return          vector1;
}




