#ifndef VECTEUR_H
#define VECTEUR_H

 class vecteur
 {
    public:
        //variables
        float x, y, z;

        //functions
        vecteur(); //default constructor
        vecteur(float x, float y, float z); //constructor with parameters
        vecteur(const vecteur& v); //copy constructor
        void set(float x, float y, float z); //set the components of the vector
        void set(const vecteur& v); //set the components of the vector
        void print() const; //print the vector
        vecteur operator=(const vecteur& v); //assign a vector to another vector
        vecteur operator+(const vecteur& v) const; //add two vectors
        vecteur operator*(const vecteur& v) const; //multiply two vectors
        vecteur operator-(const vecteur& v) const; //subtract two vectors
        
        vecteur operator+(float scalar) const; //add a scalar to a vector
        vecteur operator-(float scalar) const; //subtract a scalar from a vector
        vecteur operator*(float scalar) const; //multiply a vector by a scalar

        float dot(const vecteur& v) const;//dot product of two vectors
    };



#endif