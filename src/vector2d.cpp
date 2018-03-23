#include "../include/vector2d.h"

// Default conostrutcor
Vector2D::Vector2D(): x(0.0f), y(0.0f) {}

// The "Real" constructor we want to use.
// This initializes the values x,y,z
Vector2D::Vector2D(float a, float b): x(a), y(b){}

// Index operator, allowing us to access the individual
// x,y,z components of our vector.
float& Vector2D::operator [](int i){
        // TODO:
    //assert(i > 1 || i < 0);
    switch (i)
    {
        case 0:
        return this->x;
        default:
        return this->y;
    }
}

// Index operator, allowing us to access the individual
// x,y,z components of our vector.
const float& Vector2D::operator [](int i) const{
    // TODO: Understand why this works
    //assert(i > 1 || i < 0);
    switch (i)
    {
        case 0:
        return this->x;
        default:
        return this->y;
    }
}

// Multiplication Operator
Vector2D& Vector2D::operator *=(float s){
    // TODO:
    this->x = this->x * s;
    this->y = this->y * s;
    return *this;
}

// Division Operator
Vector2D& Vector2D::operator /=(float s){
    // TODO:
    this->x = this->x / s;
    this->y = this->y / s;
    return (*this);
}

// Addition operator
Vector2D& Vector2D::operator +=(const Vector2D& v){
    // TODO:
    this->x = this->x + v.x;
    this->y = this->y + v.y;
    return (*this);
}

// Subtraction operator
Vector2D& Vector2D::operator -=(const Vector2D& v){
    // TODO:
    this->x = this->x - v.x;
    this->y = this->y - v.y;
    return (*this);
}



