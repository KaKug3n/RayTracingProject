#ifndef _POINT_H
#define _POINT_H

class point{
    public:
        //variables
        float x, y, z;

        //functions
        point();
        point(float x, float y, float z);
        point(const point& p);
        void set(float x, float y, float z);
        void set(const point& p);
        
        void print() const;
};


#endif