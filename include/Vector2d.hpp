#ifndef Vector2d_h
#define Vector2d_h

#include <blaze/Math.h>


struct Vector2d
{
    Vector2d() 
    : vec({0.0f, 0.0f})
    {}

    Vector2d(float x, float y)
    : vec({x, y})
    {}

    Vector2d(blaze::StaticVector<float,2UL> vec)
    : vec(vec)
    {}

    Vector2d(const Vector2d & B)
    : vec(B.vec)
    {}

    Vector2d(const Vector2d * B)
    : vec(B->vec)
    {}
    
    ~Vector2d() {}

    union
    {
        struct
        {
            float x, y;
        };

        struct
        {
            blaze::StaticVector<float,2UL> vec;
        };
    };

    //Setter Vector2 input.
    Vector2d operator = (const Vector2d & B) { return Vector2d(B.vec); };
    //Setter 1 value input.
    Vector2d operator = (const float & b) { return Vector2d(b, b); };
    //Negative operation.
    Vector2d operator - (void) { return Vector2d(-vec); };

    const Vector2d operator + (const Vector2d B) const { return Vector2d(vec + B.vec); };
    const Vector2d operator - (const Vector2d B) const { return Vector2d(vec - B.vec); };
    const Vector2d operator * (const Vector2d B) const { return Vector2d(vec * B.vec); };
    const Vector2d operator / (const Vector2d B) const { return Vector2d(vec / B.vec); };

    Vector2d operator += (const Vector2d & B) { return *this + B; };
    Vector2d operator -= (const Vector2d & B) { return *this - B; };

    const Vector2d operator + (const float b) const { return Vector2d(vec + b); };
    friend Vector2d operator + (const float lhs, const Vector2d &rhs) { return Vector2d(rhs.vec + lhs); };

    const Vector2d operator - (const float b) const { return Vector2d(vec - b); };
    friend Vector2d operator - (const float lhs, const Vector2d &rhs) { return Vector2d(rhs.vec - lhs); };

    const Vector2d operator * (const float b) const { return Vector2d(vec * b); };
    friend Vector2d operator * (const float lhs, const Vector2d &rhs) { return Vector2d(rhs.vec * lhs); };

    const Vector2d operator / (const float b) const { return Vector2d(vec / b); };
    friend Vector2d operator / (const float lhs, const Vector2d &rhs) { return Vector2d(rhs.vec / lhs); };

    Vector2d operator += (float b) { return *this + b; };
    Vector2d operator -= (float b) { return *this - b; };

    bool operator == (const Vector2d & B) const { return vec == B.vec; }
    bool operator != (const Vector2d & B) const { return vec != B.vec; };
};

float Cross(Vector2d A, Vector2d B)
{
    return blaze::cross(A.vec, B.vec)[0];
}

float Dot(Vector2d A, Vector2d B)
{
    return blaze::dot(A.vec, B.vec);
}

float Distance(Vector2d A, Vector2d B)
{
    return blaze::abs(blaze::norm(B.vec - A.vec));
}

Vector2d Normalize(Vector2d A)
{
    return Vector2d( blaze::normalize(A.vec) );
}

Vector2d Zero()
{
    return Vector2d( blaze::zero<float>(2UL) );
}

Vector2d PerpendicularClockwise(Vector2d A)
{
    blaze::StaticVector<float,2UL> newVec;
    newVec[0] = A.vec[1];
    newVec[1] = -A.vec[0];

    return Vector2d(newVec);
}

Vector2d PerpendicularCounterClockwise(Vector2d A)
{
    blaze::StaticVector<float,2UL> newVec;
    newVec[0] = -A.vec[1];
    newVec[1] = A.vec[0];

    return Vector2d(newVec);
}

#endif