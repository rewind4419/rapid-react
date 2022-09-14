#pragma once

// Note(sean):
// *** DONT RENAME THIS FILE TO MATH.H!! ***
// math.h is taken so renaming by the C standard library,
// which will make this one will cause conflicts


float Sign(float x);


struct v2
{
    float x;
    float y;    
};


// @Todo inline all of these

// Preforms a clockwise rotation in radians on the 2d vector
v2 Rotate(v2 vector, float angle);

v2 LeftPerpendicular(v2 vector);
v2 RightPerpendicular(v2 vector);

float Dot(v2 a, v2 b);
float Length(v2 v);

inline v2 operator+(v2 a, v2 b) { return v2 { a.x + b.x, a.y + b.y }; }
inline v2 operator-(v2 a, v2 b) { return v2 { a.x - b.x, a.y - b.y }; }
inline v2 operator*(v2 a, v2 b) { return v2 { a.x * b.x, a.y * b.y }; }
inline v2 operator/(v2 a, v2 b) { return v2 { a.x / b.x, a.y / b.y }; }

inline v2 Normalize(v2 v) { float l = Length(v); return v / v2 { l, l }; }
