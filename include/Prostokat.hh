#ifndef PROSTOKAT_HH
#define PROSTOKAT_HH

#include "matrix.hh"
#include "size.hh"
#include "vector.hh"
#include <iostream>


/*
 *  Tutaj trzeba opisac klase. Jakie pojecie modeluje ta klasa
 *  i jakie ma glowne cechy.
 */


class Prostokat {
  /*
   *  Tutaj trzeba wstawic definicje odpowiednich pol i metod prywatnych
   */
  private:

//   Vector pro [2*SIZE];

  public:

//   Prostokat(Vector [2*SIZE]);            // Konstruktor klasy

//   Prostokat();                               // Konstruktor klasy

//   double  &operator () (unsigned int row, unsigned int column);
    
//   const double &operator () (unsigned int row, unsigned int column) const;

  Vector p1,p2,p3,p4;

  double blen;

  double slen;
  
  Prostokat operator + (Vector vec2);

  void turn(int ang);

  double lenght();

  void showres(double temp1, double temp2);

  Prostokat operator * (Matrix &matrix);

  Prostokat move(Vector &vec);
};

std::ostream& operator << ( std::ostream &stream, const Prostokat &Pr);


// /******************************************************************************
//  |  Konstruktor klasy Prostokat.                                                 |
//  |  Argumenty:                                                                |
//  |      Brak argumentow.                                                      |
//  |  Zwraca:                                                                   |
//  |      Prostokat wypelnione wartoscia 0.                                       |
//  */
// Prostokat::Prostokat() {
//     for (int i = 0; i < 2*SIZE; ++i) {
//         pro[i] = 0;
//     }
// }


// /******************************************************************************
//  |  Konstruktor parametryczny klasy Prostokat.                                   |
//  |  Argumenty:                                                                |
//  |      tmp - dwuwymiarowa tablica z elementami typu double.                  |
//  |  Zwraca:                                                                   |
//  |      Prostokat wypelniona wartosciami podanymi w argumencie.                 |
//  */
// Prostokat::Prostokat(Vector tmp[SIZE*2]) {
//     for (int i = 0; i < SIZE*2; ++i) {
//         pro[i] = tmp[i];
//     }
// }




Prostokat Prostokat::operator * (Matrix &matrix){
    Prostokat result;
    result.p1 = matrix * this->p1;
    result.p2 = matrix * this->p2;
    result.p3 = matrix * this->p3;
    result.p4 = matrix * this->p4;

    return result;
}


Prostokat Prostokat::move(Vector &vec){
    Prostokat result;
    result.p1 = this->p1 + vec;
    result.p2 = this->p2 + vec;
    result.p3 = this->p3 + vec;
    result.p4 = this->p4 + vec;

    return result;
}

double Prostokat::lenght(){
   this->slen = this->p1.vlenght(this->p2);
   this->blen = this->p2.vlenght(this->p3);
   return 0;
}


std::ostream& operator << ( std::ostream &stream, const Prostokat &Pr){

    stream << Pr.p1 << std::endl;
    stream << Pr.p2 << std::endl;
    stream << Pr.p3 << std::endl;
    stream << Pr.p4 << std::endl;
    stream << Pr.p1 << std::endl;

    return stream;
}




void Prostokat::showres(double temp1, double temp2){

    this->lenght();

    if(temp2 == this->slen){
       std::cout << ":) Shorter sides are equal." << std::endl;
       std::cout << "Before operation: " << temp2 << std::endl;
       std::cout << "After operation: " << this->slen << std::endl;
   } 
   else{
       std::cout << ":( Shorter sides are not equal." << std::endl;
       std::cout << "Before operation: " << temp2 << std::endl;
       std::cout << "After operation: " << this->slen << std::endl; 
   }
   std::cout << std::endl;
   if(temp1 == this->blen){
       std::cout << ":) Longer sides are equal." << std::endl;
       std::cout << "Before operation: " << temp1 << std::endl;
       std::cout << "After operation: " << this->blen << std::endl;
   } 
   else{
       std::cout << ":( Longer sides are not equal." << std::endl;
       std::cout << "Before operation: " << temp2 << std::endl;
       std::cout << "After operation: " << this->blen << std::endl; 
   }

}


void Prostokat::turn(int ang){
    Matrix matrix;
    matrix.angle = ang;
    matrix.toradians();
    matrix.Init();
    *this = *this * matrix;

}

#endif
