#include "camera.h"

#include <iostream>

camera::camera() : carre(), width(0), height(0) {
    // Default constructor
}
camera::camera(point p1, point p2, point p3, point p4, materiel m, int width, int height) : carre(p1, p2, p3, p4, m), width(width), height(height) {
    // Constructor with parameters
}
camera::camera(const camera& c) : carre(c), width(c.width), height(c.height) {
    // Copy constructor
}
void camera::set(point p1, point p2, point p3, point p4, materiel m, int width, int height) {
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->p4 = p4;
    this->m = m;
    this->width = width;
    this->height = height;
}
void camera::set(const camera& c) {
    this->p1 = c.p1;
    this->p2 = c.p2;
    this->p3 = c.p3;
    this->p4 = c.p4;
    this->m = c.m;
    this->width = c.width;
    this->height = c.height;
}

void camera::print() const {
    std::cout << "Camera Point 1: ";
    p1.print();
    std::cout << "Camera Point 2: ";
    p2.print();
    std::cout << "Camera Point 3: ";
    p3.print();
    std::cout << "Camera Point 4: ";
    p4.print();
    std::cout << "Camera Materiel: ";
    m.print();
    std::cout << "Camera Width: " << width << std::endl;
    std::cout << "Camera Height: " << height << std::endl;
}

void camera::translate(float dx, float dy, float dz) {
    p1.x += dx;
    p1.y += dy;
    p1.z += dz;
    p2.x += dx;
    p2.y += dy;
    p2.z += dz;
    p3.x += dx;
    p3.y += dy;
    p3.z += dz;
    p4.x += dx;
    p4.y += dy;
    p4.z += dz;
}

void camera::rotate(float angle, float x, float y, float z) {
    // Implement rotation logic here
}

void camera::set_size(int width, int height) {
    this->width = width;
    this->height = height;
}