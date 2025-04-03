#ifndef CAMERA_H
#define CAMERA_H

#include "forme.h"

class camera: public carre
{
    public:
    //variables
    int width; //width of the camera
    int height; //height of the camera
    
    //functions
    camera(); //default constructor
    camera(point p1, point p2, point p3, point p4, materiel m, int width, int height); //constructor with parameters
    camera(const camera& c); //copy constructor
    void set(point p1, point p2, point p3, point p4, materiel m, int width, int height); //set the points, material and size of the camera
    void set(const camera& c); //set the points, material and size of the camera
    void print() const; //print the camera
    void translate(float dx, float dy, float dz); //translate the camera
    void rotate(float angle, float x, float y, float z); //rotate the camera
    void set_size(int width, int height); //set the size of the camera

};

#endif