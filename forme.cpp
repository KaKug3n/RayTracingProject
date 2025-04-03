#include "forme.h"

#include <iostream>
#include <cmath>

cercle::cercle() : Objet(), r(0) {
    // Default constructor
}
cercle::cercle(point p, materiel m, float r) : Objet(p, m), r(r) {
    // Constructor with parameters
}
cercle::cercle(const cercle& c) : Objet(c), r(c.r) {
    // Copy constructor
}

void cercle::set(point p, materiel m, float r) {
    this->p = p;
    this->m = m;
    this->r = r;
}
void cercle::set(const cercle& c) {
    this->p = c.p;
    this->m = c.m;
    this->r = c.r;
}

void cercle::print() const {
    std::cout << "Cercle Point: ";
    p.print();
    std::cout << "Cercle Materiel: ";
    m.print();
    std::cout << "Cercle Radius: " << r << std::endl;
}

float cercle::intersect_ray(const ray &r, const cercle &c, float &t) {
    vecteur oc = vecteur(r.origin.x - c.p.x, r.origin.y - c.p.y, r.origin.z - c.p.z);
    float a = r.d.dot(r.d);
    float b = 2.0f * oc.dot(r.d);
    float c_val = oc.dot(oc) - c.r * c.r;
    float delta = b * b - 4 * a * c_val;

    if (delta < 0) return t=-1; // No intersection
    t = (-b - sqrt(delta)) / (2.0f * a);
    return t;
}

plan::plan() : Objet(), n() {
    // Default constructor
}
plan::plan(point p, vecteur n, materiel m) : Objet(p, m), n(n) {
    // Constructor with parameters
}
plan::plan(const plan& pl) : Objet(pl), n(pl.n) {
    // Copy constructor
}
void plan::set(point p, vecteur n, materiel m) {
    this->p = p;
    this->n = n;
    this->m = m;
}
void plan::set(const plan& pl) {
    this->p = pl.p;
    this->n = pl.n;
    this->m = pl.m;
}

void plan::print() const {
    std::cout << "Plan Point: ";
    p.print();
    std::cout << "Plan Normal: ";
    n.print();
    std::cout << "Plan Materiel: ";
    m.print();
}

vecteur plan::normal() const {
    return n;
}
float plan::intersect_ray(const ray &r, const plan &pl, float &t) {
    float denom = pl.n.dot(r.d);
    if (std::abs(denom) < 1e-6) return t=-1; // Ray is parallel to the plane
    vecteur ao = vecteur(pl.p.x - r.origin.x, pl.p.y - r.origin.y, pl.p.z - r.origin.z);
    t = ao.dot(pl.n) / denom;
    return t;
}


triangle::triangle() : plan(), p1(), p2(), p3() {
    // Default constructor
}
triangle::triangle(point p1, point p2, point p3, materiel m) : plan(p1, triangle::normal(p1,p2,p3), m), 
      p1(p1), p2(p2), p3(p3) {
    // Constructor with parameters
}
triangle::triangle(const triangle& t) : plan(t), p1(t.p1), p2(t.p2), p3(t.p3) {
    // Copy constructor
}

void triangle::set(point p1, point p2, point p3, materiel m) {
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->m = m;
}
void triangle::set(const triangle& t) {
    this->p1 = t.p1;
    this->p2 = t.p2;
    this->p3 = t.p3;
    this->m = t.m;
}

void triangle::print() const {
    std::cout << "Triangle Point 1: ";
    p1.print();
    std::cout << "Triangle Point 2: ";
    p2.print();
    std::cout << "Triangle Point 3: ";
    p3.print();
    std::cout << "Triangle Materiel: ";
    m.print();
}

vecteur triangle::normal(point p1, point p2, point p3) const {
    vecteur u = vecteur(p2.x - p1.x, p2.y - p1.y, p2.z - p1.z);
    vecteur v = vecteur(p3.x - p1.x, p3.y - p1.y, p3.z - p1.z);
    return vecteur(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x);
}

vecteur triangle::normal() const {
    vecteur u = vecteur(p2.x - p1.x, p2.y - p1.y, p2.z - p1.z);
    vecteur v = vecteur(p3.x - p1.x, p3.y - p1.y, p3.z - p1.z);
    return vecteur(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x);
}

float triangle::intersect_ray(const ray &r, const triangle &tri, float &t) {
    vecteur n = tri.normal();
    float denom = n.dot(r.d);
    if (std::abs(denom) < 1e-6) return t=-1; // Ray is parallel to the triangle
    vecteur ao = vecteur(tri.p1.x - r.origin.x, tri.p1.y - r.origin.y, tri.p1.z - r.origin.z);
    t = ao.dot(n) / denom;
    return t;
}

carre::carre() : triangle(), p4() {
    // Default constructor
}
carre::carre(point p1, point p2, point p3, point p4, materiel m) : triangle(p1, p2, p3, m), 
      p4(p4) {
    // Constructor with parameters
}
carre::carre(const carre& c) : triangle(c), p4(c.p4) {
    // Copy constructor
}

void carre::set(point p1, point p2, point p3, point p4, materiel m) {
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->p4 = p4;
    this->m = m;
}
void carre::set(const carre& c) {
    this->p1 = c.p1;
    this->p2 = c.p2;
    this->p3 = c.p3;
    this->p4 = c.p4;
    this->m = c.m;
}

void carre::print() const {
    std::cout << "Carre Point 1: ";
    p1.print();
    std::cout << "Carre Point 2: ";
    p2.print();
    std::cout << "Carre Point 3: ";
    p3.print();
    std::cout << "Carre Point 4: ";
    p4.print();
    std::cout << "Carre Materiel: ";
    m.print();
}

vecteur carre::normal(point p1, point p2, point p3, point p4) const {
    vecteur u = vecteur(p2.x - p1.x, p2.y - p1.y, p2.z - p1.z);
    vecteur v = vecteur(p3.x - p1.x, p3.y - p1.y, p3.z - p1.z);
    return vecteur(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x);
}
vecteur carre::normal() const {
    vecteur u = vecteur(p2.x - p1.x, p2.y - p1.y, p2.z - p1.z);
    vecteur v = vecteur(p3.x - p1.x, p3.y - p1.y, p3.z - p1.z);
    return vecteur(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x);
}

float carre::intersect_ray(const ray &r, const carre &c, float &t) {
    vecteur n = c.normal();
    float denom = n.dot(r.d);
    if (std::abs(denom) < 1e-6) return t=-1; // Ray is parallel to the square
    vecteur ao = vecteur(c.p1.x - r.origin.x, c.p1.y - r.origin.y, c.p1.z - r.origin.z);
    t = ao.dot(n) / denom;
    return t;
}
