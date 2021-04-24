#ifndef PROSTOKAT_HH
#define PROSTOKAT_HH

#include "matrix.hh"
#include "size.hh"
// #include "coordinates.hh"
#include "vector.hh"
#include <iostream>
#include <iomanip>
#include "../include/lacze_do_gnuplota.hh"
#include <unistd.h>
#include <fstream>


/*
 *  Tutaj trzeba opisac klase. Jakie pojecie modeluje ta klasa
 *  i jakie ma glowne cechy.
 */


class Prostokat {
  /*
   *  Tutaj trzeba wstawic definicje odpowiednich pol i metod prywatnych
   */
  private:

  Vector pro [NOPOINTS];

  public:

  Prostokat(Vector [NOPOINTS]);             //Konstruktor klasy 

  Prostokat();                               // Konstruktor klasy

  Prostokat operator * (const Matrix &matrix);

  Prostokat move (const Vector &vec);

  void moving(Vector &vec, const char *sNazwaPliku, PzG::LaczeDoGNUPlota Lacze);

  Prostokat operator + (const Vector vec2);

  double  &operator () (unsigned int row, unsigned int column);

  const double  &operator () (unsigned int row, unsigned int column) const;
    
  const Vector &operator () (unsigned int row) const;

  double blen;

  double slen;

  void turn(int const ang);

  void turning(Prostokat &pro, const char *sNazwaPliku, double const ang, double const howm, PzG::LaczeDoGNUPlota Lacze);

  Prostokat lenght();

  bool Save(const char *sNazwaPliku);
  
  void showres(double const temp1, double const temp2);

//   friend bool operator == (const double temp1, const double temp2);

};

std::ostream& operator << ( std::ostream &stream, const Prostokat &Pr);

// bool operator == (const double temp1, const double temp2);

#endif
