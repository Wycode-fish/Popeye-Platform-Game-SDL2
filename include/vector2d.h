#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <cmath>
#include <assert.h>

using namespace std;
struct Vector2D; /**< Forward reference of Vector2D struct */

/**
 * @brief  Vector2D performs vector operations with 2-dimensions
 *
 * The purpose of this struct is primarily for 2D graphics
 * applications.
 */
struct Vector2D{
    /**
     * @brief  Note: x,y are a convention
     *
     * x,y could be position or any 2-component value.
     */
    float x,y;

    /**
     * @brief Default conostrutcor
     */
    Vector2D();

    /**
     * @brief  The "Real" constructor we want to use.
     *
     * This initializes the values x, y
     */
    Vector2D(float a, float b);

    /**
     * @brief Override index operator
     *
     * Allowing us to access the individual x, y components of our vector
     */
    float& operator[](int i);

    /**
     * @brief Override index operator for const argument
     *
     * Allowing us to access the individual x, y components of our vector
     */
    const float& operator[](int i) const;

    /**
     * @brief Override multiplication operator
     */
    Vector2D& operator *=(float s);

    /**
     * @brief Override division operator
     */
    Vector2D& operator /=(float s);

    /**
     * @brief Override addition operator
     */
    Vector2D& operator +=(const Vector2D& v);

    /**
     * @brief Subtraction operator
     */
    Vector2D& operator -=(const Vector2D& v);

};

/**
 * @brief  Compute the dot product of a Vector2D
 */
inline float Dot(const Vector2D& a, const Vector2D& b){
    return a.x*b.x + a.y*b.y;
}

/**
 * @brief  Multiply a vector by a scalar value
 */
inline Vector2D operator *(const Vector2D& v, float s){
    Vector2D vec = Vector2D (v.x*s, v.y*s);
    return vec;
}

/**
 * @brief Mutiply a scalar value by a vector
 */
inline Vector2D operator *(float s, const Vector2D& v){
    Vector2D vec = Vector2D (v.x*s, v.y*s);
    return vec;
}

/**
 * @brief  Divide a vector by a scalar value
 */
inline Vector2D operator /(const Vector2D& v, float s){
    Vector2D vec = Vector2D (v.x/s, v.y/s);
    return vec;
}

/**
 * @brief Negate the sign of a vector
 */
inline Vector2D operator -(const Vector2D& v){
    Vector2D vec = Vector2D ((-1)*v.x, (-1)*v.y);
    return vec;
}

/**
 * @brief Override equal operator for comparison between vectors
 */
inline bool operator == (const Vector2D& a, const Vector2D& b){
    return (a.x==b.x && a.y==b.y);
}

/**
 * @brief Compute the magnitude of a vector
 */
inline float Magnitude(const Vector2D& v){
    return sqrt(pow(v.x,2)+pow(v.y,2));
}

/**
 * @brief Add one vector to another
 */
inline Vector2D operator +(const Vector2D& a, const Vector2D& b){
    Vector2D vec = Vector2D (a.x + b.x, a.y + b.y);
    return vec;
}

/**
 * @brief Subtract one vector from another
 */
inline Vector2D operator -(const Vector2D& a, const Vector2D& b){
    Vector2D vec = Vector2D (a.x - b.x, a.y - b.y);
    return vec;
}

/**
 * @brief Compute the vector projection of two vectors
 *
 * @return the vector projection of vector a onto vector b
 */
inline Vector2D Project(const Vector2D& a, const Vector2D& b){
    float cos = Dot(a,b) / (Magnitude(a) * Magnitude(b));
    Vector2D vec = (b/Magnitude(b)) * (Magnitude(a) * cos);
    return vec;
}

/**
 * @brief Normalize a vector
 */
inline Vector2D Normalize(const Vector2D& v){
    Vector2D vec = Vector2D (v.x/Magnitude(v), v.y/Magnitude(v));
    return vec;
}

/**
 * @brief The reflection of two vectors
 * @return the reflection of vector a onto b
 */
inline Vector2D reflection(const Vector2D& a, const Vector2D& b){
    Vector2D vec = a - 2.0 * Dot( b, a ) * b;//Project( a , b)  * 2 + a;
     //I - 2.0 * dot(N, I) * N
    return vec;
}

#endif // VECTOR2D_H
