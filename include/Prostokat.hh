#ifndef PROSTOKAT_HH
#define PROSTOKAT_HH

#include "matrix.hh"
#include "size.hh"
// #include "coordinates.hh"
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

  double pro [NOPOINTS][SIZE];

  public:

  Prostokat(double [NOPOINTS][SIZE]);            // Konstruktor klasy

  Prostokat();                               // Konstruktor klasy

  double  &operator () (unsigned int row, unsigned int column);
    
  const double &operator () (unsigned int row, unsigned int column) const;

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
Prostokat::Prostokat() {
    for (int i = 0; i < NOPOINTS; ++i) {
        for(int j = 0; j < SIZE; ++j) {
        pro[i][j] = 0;
    }
    }
}


// /******************************************************************************
//  |  Konstruktor parametryczny klasy Prostokat.                                   |
//  |  Argumenty:                                                                |
//  |      tmp - dwuwymiarowa tablica z elementami typu double.                  |
//  |  Zwraca:                                                                   |
//  |      Prostokat wypelniona wartosciami podanymi w argumencie.                 |
//  */
Prostokat::Prostokat(double tmp[NOPOINTS][SIZE]) {
    for (int i = 0; i < NOPOINTS; ++i) {
        for(int j = 0; j < SIZE; ++j) {
        pro[i][j] = tmp[i][j];
    }
    }
}

/******************************************************************************
 |  Funktor macierzy                                                          |
 |  Argumenty:                                                                |
 |      row - numer wiersza.                                                  |
 |      column - numer kolumny.                                               |
 |  Zwraca:                                                                   |
 |      Wartosc macierzy w danym miejscu tablicy.                             |
 */
double &Prostokat::operator()(unsigned int row, unsigned int column) {

    if (row >= NOPOINTS) {
        std::cout << "Error: Macierz jest poza zasiegiem"; 
        exit(0); // lepiej byłoby rzucić wyjątkiem stdexcept
    }

    if (column >= SIZE) {
        std::cout << "Error: Macierz jest poza zasiegiem";
        exit(0); // lepiej byłoby rzucić wyjątkiem stdexcept
    }

    return pro[row][column];
}


/******************************************************************************
 |  Funktor macierzy                                                          |
 |  Argumenty:                                                                |
 |      row - numer wiersza.                                                  |
 |      column - numer kolumny.                                               |
 |  Zwraca:                                                                   |
 |      Wartosc macierzy w danym miejscu tablicy jako stala.                  |
 */
const double &Prostokat::operator () (unsigned int row, unsigned int column) const {

    if (row >= NOPOINTS) {
        std::cout << "Error: Prostokat jest poza zasiegiem";
        exit(0); // lepiej byłoby rzucić wyjątkiem stdexcept
    }

    if (column >= SIZE) {
        std::cout << "Error: Prostokat jest poza zasiegiem";
        exit(0); // lepiej byłoby rzucić wyjątkiem stdexcept
    }

    return pro[row][column];
}




Prostokat Prostokat::operator * (Matrix &matrix){
    Prostokat result;
    for (int i = 0; i < NOPOINTS; ++i){
            result(i,0) = matrix(0,0) * this->pro[i][0] + matrix(1,0) *  this->pro[i][1];
            result(i,1) = matrix(0,1) * this->pro[i][0] + matrix(1,1) *  this->pro[i][1];
    }
    return result;
}


Prostokat Prostokat::move(Vector &vec){
    for (int i = 0; i < NOPOINTS; ++i){
        for (int j = 0; j <SIZE; ++j){
        this->pro[i][j] += vec[j];
    }}
    return *this;
}

double Prostokat::lenght(){

   this->slen = sqrt(pow(this->pro[0][0] - this->pro[1][0],2) + pow(this->pro[0][1] - this->pro[1][1],2));
   this->blen = sqrt(pow(this->pro[0][0] - this->pro[3][0],2) + pow(this->pro[0][1] - this->pro[3][1],2));
   return 0;
}


std::ostream& operator << ( std::ostream &stream, const Prostokat &Pr){

for (int i = 0; i < NOPOINTS; ++i){
    
    stream << std::setw(16) << std::fixed << std::setprecision(10) << Pr(i,0) << std::setw(16) << std::fixed << std::setprecision(10) << Pr(i,1) << std::endl;
    }
    stream << std::setw(16) << std::fixed << std::setprecision(10) << Pr(0,0) << std::setw(16) << std::fixed << std::setprecision(10) << Pr(0,1) << std::endl;
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
