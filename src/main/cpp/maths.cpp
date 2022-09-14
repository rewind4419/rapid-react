#include "maths.h"

#include <math.h>

v2 Rotate(v2 vector, float angle)
{
    return v2
    {
        cos(-angle) * vector.x - sin(-angle) * vector.y,
        sin(-angle) * vector.x + cos(-angle) * vector.y
    };
}

float Dot(v2 a, v2 b)
{
    return a.x * b.x + a.y * b.y;
}

v2 LeftPerpendicular(v2 vector)
{
    return v2 { -vector.y, vector.x };
}

v2 RightPerpendicular(v2 vector)
{
    return v2 { vector.y, -vector.x };
}

float Sign(float x)
{
    if (x < 0) return -1;
    if (x > 0) return 1;
    return 0;
}

float Length(v2 v) {
    return sqrtf(v.x * v.x + v.y * v.y);
}