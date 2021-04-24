#pragma once

#include "size.hh"
#include "vector.hh"
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <stdexcept>

class Matrix {

private:
    double value[SIZE][SIZE];               // Wartosci macierzy

public:
    double angle; 

    Matrix(double [SIZE][SIZE]);            // Konstruktor klasy

    Matrix();                               // Konstruktor klasy

    Vector operator * (Vector tmp);           // Operator mnożenia przez wektor

    Matrix operator + (Matrix tmp);

    Matrix Init();

    double toradians();

    double  &operator () (unsigned int row, unsigned int column);
    
    const double &operator () (unsigned int row, unsigned int column) const;

    bool operator == ( const Matrix tmp) const;

};

std::istream &operator>>(std::istream &in, Matrix &mat);

std::ostream &operator<<(std::ostream &out, Matrix const &mat);

