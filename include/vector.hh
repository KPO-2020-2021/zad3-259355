#pragma once

#include "size.hh"
#include <iostream>
#include <math.h>
#include <iomanip>

class Vector {

private:

    double size[SIZE];     //Tablica wektora

public:

    Vector();

    Vector(double [SIZE]);

    Vector operator + ( Vector &v);

    Vector operator - ( Vector &v);

    Vector operator * (const double &tmp);

    Vector operator / (const double &tmp);

    // double vlenght (Vector vec2);

    const double &operator [] (int index) const;

    double &operator [] (int index);

    bool operator == (const Vector tmp) const ;

    bool operator != (const Vector tmp) const ;

};

std::ostream &operator << (std::ostream &stream, Vector const &tmp);

std::istream &operator >> (std::istream &in, Vector &tmp);




