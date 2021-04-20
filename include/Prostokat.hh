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

  double lenght();

  bool Save(const char *sNazwaPliku);
  
  void showres(double const temp1, double const temp2);

//   friend bool operator == (const double temp1, const double temp2);

};

std::ostream& operator << ( std::ostream &stream, const Prostokat &Pr);

// bool operator == (const double temp1, const double temp2);


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
Prostokat::Prostokat(Vector tmp[NOPOINTS]) {
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
const Vector &Prostokat::operator () (unsigned int row) const {

    if (row >= NOPOINTS) {
        std::cout << "Error: Prostokat jest poza zasiegiem";
        exit(0); // lepiej byłoby rzucić wyjątkiem stdexcept
    }

    // if (column >= SIZE) {
    //     std::cout << "Error: Prostokat jest poza zasiegiem";
    //     exit(0); // lepiej byłoby rzucić wyjątkiem stdexcept
    // }

    return pro[row];
}

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

//Przeciazenie operatora przyjmująca jako argument macierz i zmieniajaca wartosci wspolrzednych prostokata

Prostokat Prostokat::operator * (const Matrix &matrix){
    Prostokat result;
    for (int i = 0; i < NOPOINTS; ++i){
            result(i,0) = matrix(0,0) * this->pro[i][0] + matrix(1,0) *  this->pro[i][1];
            result(i,1) = matrix(0,1) * this->pro[i][0] + matrix(1,1) *  this->pro[i][1];
    }
    return result;
}

//Funkcja przyjmujaca jako argument wektor i zmieniajaca wartosci wspolrzednych prostokata (przesuniecie o wektor)

Prostokat Prostokat::move(const Vector &vec){
    for (int i = 0; i < NOPOINTS; ++i){
        for (int j = 0; j < SIZE; ++j){
        this->pro[i][j] += vec[j];
    }}
    
    // this->Save(sNazwaPliku);
    // Lacze.Rysuj();
    return *this;
}

void Prostokat::moving(Vector &vec, const char *sNazwaPliku, PzG::LaczeDoGNUPlota Lacze){

    Vector temp;
    temp = vec / 100.00 ;
    for(int i = 0; i < 100; ++i){
        this->move(temp);
        this->Save(sNazwaPliku);
        usleep(4000);
        Lacze.Rysuj(); 
        usleep(4000); 
    }
}

//Metoda ktora oblicza wartosci dluzszego (blen) i krotszego (slen) boku prostokata

double Prostokat::lenght(){

   this->slen = sqrt(pow(this->pro[0][0] - this->pro[1][0],2) + pow(this->pro[0][1] - this->pro[1][1],2));
   this->blen = sqrt(pow(this->pro[0][0] - this->pro[3][0],2) + pow(this->pro[0][1] - this->pro[3][1],2));
   return 0;
}

//Przeciazenie operatora przesuniecia bitowego w lewo
//Pozwala w odpowiedni sposob wyswietlic wspolrzedne prostokata 

std::ostream& operator << ( std::ostream &stream, const Prostokat &Pr){

for (int i = 0; i < NOPOINTS; ++i){
    
    stream << std::setw(16) << std::fixed << std::setprecision(10) << Pr(i) << std::endl;
    }
    stream << std::setw(16) << std::fixed << std::setprecision(10) << Pr(0) << std::endl;
    return stream;
}

//Funkcja przyjmujaca odpowiednio temp1 - dlugosc dluzszego boku oraz temp2 - dlugosc krotszego boku trojkata (na poczatku)
//Porownuje ona dlugosci bokow po operacji przesuniecia i obrotu

void Prostokat::showres(double const temp1, double const temp2){

    this->lenght();

    if((temp2 - this->slen) < MIN_DIFF){
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
   if((temp1 - this->blen) < MIN_DIFF){
       std::cout << ":) Longer sides are equal." << std::endl;
       std::cout << "Before operation: " << temp1 << std::endl;
       std::cout << "After operation: " << this->blen << std::endl;
   } 
   else{
       std::cout << ":( Longer sides are not equal." << std::endl;
       std::cout << "Before operation: " << temp1 << std::endl;
       std::cout << "After operation: " << this->blen << std::endl; 
   }
}

//Funkcja przyjmujaca kat o ktory obracamy prostokat wokol punktu (0,0)
//Zmienia wartosci wspolrzednych prostokata o dany kata

void Prostokat::turn(int const ang){
    Matrix matrix;
    matrix.angle = ang;
    // matrix.toradians();
    matrix.Init();
    *this = *this * matrix;
}

bool Prostokat::Save(const char *sNazwaPliku)
{
  std::ofstream  StrmPlikowy;

  StrmPlikowy.open(sNazwaPliku);
  if (!StrmPlikowy.is_open())  {
    std::cerr << ":(  Operacja otwarcia do zapisu \"" << sNazwaPliku << "\"" << std::endl
	 << ":(  nie powiodla sie." << std::endl;
    return false;
  }

  StrmPlikowy << *this << std::endl;

  StrmPlikowy.close();
  return !StrmPlikowy.fail();
}

void Prostokat::turning(Prostokat &pro, const char *sNazwaPliku, double const ang, double const howm, PzG::LaczeDoGNUPlota Lacze)
{
  
    for(int i = 0; i < howm; ++i){
        for(int k = 0; k < ang; ++k){
            pro.turn(1);
            pro.Save(sNazwaPliku);
            usleep(4000);
            Lacze.Rysuj(); 
            usleep(4000);
        }
    }
}

// bool operator == (const double temp1,const double temp2){
//     if(abs(temp1 - temp2) < MIN_DIFF){
//         return true;
//     }
//     else{
//         return false;
//     }
// }

#endif
