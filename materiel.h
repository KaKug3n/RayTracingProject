#ifndef MATERIEL_H
#define MATERIEL_H


class materiel
{
public:
    //variables
    float r; //red
    float g; //green
    float b; //blue
    float a; //alpha (transparency)

    //functions
    materiel(); //default constructor
    materiel(float r, float g, float b, float a); //constructor with parameters
    materiel(float r, float g, float b); //constructor with parameters
    materiel(const materiel& m); //copy constructor
    void set(float r, float g, float b, float a); //set the color of the material
    void set(const materiel& m); //set the color of the material
    void print() const; //print the color of the material
};





#endif