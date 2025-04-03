#ifndef FORME_H
#define FORME_H

#include "objet.h"
#include "ray.h"


class cercle : public Objet
{
public:
    //variables
    point p; //point of the center of the circle
    float r; //radius
    materiel m; //material of the circle

    //functions
    cercle(); //default constructor
    cercle(point p, materiel m, float r); //constructor with parameters
    cercle(const cercle& c); //copy constructor
    void set(point p, materiel m, float r); //set the point, material and radius of the circle
    void set(const cercle& c); //set the point, material and radius of the circle
    void print() const; //print the circle
    float intersect_ray(const ray &r, const cercle &c, float &t); //check if the ray intersects the circle
};


//TEST//
class plan: public Objet
{
public:
    //variables
    point p; //point of the center of the plane
    vecteur n; //normal vector of the plane
    materiel m; //material of the plane

    //functions
    plan(); //default constructor
    plan(point p, vecteur n, materiel m); //constructor with parameters
    plan(const plan& pl); //copy constructor
    void set(point p, vecteur n, materiel m); //set the point, normal vector and material of the plane
    void set(const plan& pl); //set the point, normal vector and material of the plane
    void print() const; //print the plane
    
    vecteur normal() const; //get the normal vector of the plane
    float intersect_ray(const ray &r, const plan &pl, float &t);//check if the ray intersects the plane
};

class triangle : public plan
{
public:
    //variables
    point p1; //first point
    point p2; //second point
    point p3; //third point

    //functions
    triangle(); //default constructor
    triangle(point p1, point p2, point p3, materiel m); //constructor with parameters
    triangle(const triangle& t); //copy constructor
    void set(point p1, point p2, point p3, materiel m); //set the points and material of the triangle
    void set(const triangle& t); //set the points and material of the triangle
    void print() const; //print the triangle

    vecteur normal(point p1, point p2, point p3) const; //get the normal vector of the triangle
    vecteur normal() const;
    float intersect_ray(const ray &r, const triangle &tri, float &t);
};

class carre : public triangle
{
public:
    //variables
    point p4; //fourth point

    //functions
    carre(); //default constructor
    carre(point p1, point p2, point p3, point p4, materiel m); //constructor with parameters
    carre(const carre& c); //copy constructor
    void set(point p1, point p2, point p3, point p4, materiel m); //set the points and material of the square
    void set(const carre& c); //set the points and material of the square
    void print() const; //print the square

    vecteur normal(point p1, point p2, point p3,point p4) const;
    vecteur normal() const;
    float intersect_ray(const ray &r, const carre &c, float &t); //check if the ray intersects the square
};


#endif