#include "vecteur.h"

#include <iostream>

vecteur::vecteur() : x(0), y(0), z(0) {
    // Default constructor
}
vecteur::vecteur(float x, float y, float z) : x(x), y(y), z(z) {
    // Constructor with parameters
}
vecteur::vecteur(const vecteur& v) : x(v.x), y(v.y), z(v.z) {
    // Copy constructor
}

void vecteur::set(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}
void vecteur::set(const vecteur& v) {
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
}

void vecteur::print() const {
    std::cout << "Vecteur(" << x << ", " << y << ", " << z << ")" << std::endl;
}
vecteur vecteur::operator=(const vecteur& v) {
    if (this != &v) {
        x = v.x;
        y = v.y;
        z = v.z;
    }
    return *this;
}

vecteur vecteur::operator+(const vecteur& v) const {
    return vecteur(x + v.x, y + v.y, z + v.z);
}
vecteur vecteur::operator-(const vecteur& v) const {
    return vecteur(x - v.x, y - v.y, z - v.z);
}
vecteur vecteur::operator*(const vecteur& v) const {
    return vecteur(x * v.x, y * v.y, z * v.z);
}

vecteur vecteur::operator+(float scalar) const {
    return vecteur(x + scalar, y + scalar, z + scalar);
}
vecteur vecteur::operator-(float scalar) const {
    return vecteur(x - scalar, y - scalar, z - scalar);
}
vecteur vecteur::operator*(float scalar) const {
    return vecteur(x * scalar, y * scalar, z * scalar);
}

float vecteur::dot(const vecteur& v) const {
    return x * v.x + y * v.y + z * v.z;
}
