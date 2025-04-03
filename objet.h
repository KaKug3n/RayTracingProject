#ifndef OBJET_H
#define OBJET_H

#include "point.h"
#include "materiel.h"

//classe Objet
class Objet{
    public:
        //variables
        point p;
        materiel m;

        //functions
        Objet(); //default constructor
        Objet(point p, materiel m); //constructor with parameters
        Objet(const Objet& o); //copy constructor
        void set(point p, materiel m); //set the point and material of the object
        void set(const Objet& o); //set the point and material of the object
        void print() const; //print the object
        //void translate(float dx, float dy, float dz); //translate the object
        void rotate(float angle, float x, float y, float z); //rotate the object
        void scale(float sx, float sy, float sz); //scale the object
        virtual float intersect_ray(const ray &r, const Objet &o, float &t); //check if the ray intersects the object

};


#endif