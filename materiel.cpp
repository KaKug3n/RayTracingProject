#include "materiel.h"

#include <iostream>

materiel::materiel() : r(0), g(0), b(0), a(1) {
    // Default constructor
}
materiel::materiel(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {
    // Constructor with parameters
}
materiel::materiel(float r, float g, float b) : r(r), g(g), b(b), a(1) {
    // Constructor with parameters
}
materiel::materiel(const materiel& m) : r(m.r), g(m.g), b(m.b), a(m.a) {
    // Copy constructor
}

void materiel::set(float r, float g, float b, float a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}
void materiel::set(const materiel& m) {
    this->r = m.r;
    this->g = m.g;
    this->b = m.b;
    this->a = m.a;
}

void materiel::print() const {
    std::cout << "Materiel Color: (" << r << ", " << g << ", " << b << ", " << a << ")" << std::endl;
}
