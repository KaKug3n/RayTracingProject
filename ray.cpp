#include "ray.h"

#include <iostream>

ray::ray() : origin(), d(), t(0) {
    // Default constructor
}
ray::ray(point origin, point d) : origin(origin), d(d), t(0) {
    // Constructor with parameters
}
ray::ray(const ray& r) : origin(r.origin), d(r.d), t(r.t) {
    // Copy constructor
}
void ray::set(point origin, point d) {
    this->origin = origin;
    this->d = d;
}
void ray::set(const ray& r) {
    this->origin = r.origin;
    this->d = r.d;
    this->t = 0;
}

void ray::print() const {
    std::cout << "Ray Origin: ";
    origin.print();
    std::cout << "Ray Direction: ";
    d.print();
    std::cout << "Ray t: " << t << std::endl;
}