#ifndef RAY_H
#define RAY_H

#include "point.h"
#include "vecteur.h"

//classe Ray
class ray
{
public:
    //variables
    point origin; //point of origin
    vecteur d; //direction of the ray
    float t; //distance from the origin to the point on the ray

    //functions
    ray(); //default constructor
    ray(point origin, point d); //constructor with parameters
    ray(const ray& r); //copy constructor
    void set(point origin, point d); //set the origin and direction of the ray
    void set(const ray& r); //set the origin and direction of the ray
    void print() const; //print the ray
    
};




#endif