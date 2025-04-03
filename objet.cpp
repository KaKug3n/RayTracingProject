#include "objet.h"  

#include <iostream>

Objet::Objet() : p(), m() {
    // Default constructor
}
Objet::Objet(point p, materiel m) : p(p), m(m) {
    // Constructor with parameters
}
Objet::Objet(const Objet& o) : p(o.p), m(o.m) {
    // Copy constructor
}

void Objet::set(point p, materiel m) {
    this->p = p;
    this->m = m;
}
void Objet::set(const Objet& o) {
    this->p = o.p;
    this->m = o.m;
}

void Objet::print() const {
    std::cout << "Objet Point: ";
    p.print();
    std::cout << "Objet Materiel: ";
    m.print();
}

/*
void Objet::translate(float dx, float dy, float dz) {
    p.x += dx;
    p.y += dy;
    p.z += dz;
}
*/
void Objet::scale(float sx, float sy, float sz) {
    p.x *= sx;
    p.y *= sy;
    p.z *= sz;
}