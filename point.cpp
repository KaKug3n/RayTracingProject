#include "point.h"

#include <iostream>



point::point() : x(0), y(0), z(0) {
    // Default constructor
}
point::point(float x, float y, float z) : x(x), y(y), z(z) {
    // Constructor with parameters
}
point::point(const point& p) : x(p.x), y(p.y), z(p.z) {
    // Copy constructor
}

void point::set(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}
void point::set(const point& p) {
    this->x = p.x;
    this->y = p.y;
    this->z = p.z;
}

void point::print() const {
    std::cout << "Point(" << x << ", " << y << ", " << z << ")" << std::endl;
}
