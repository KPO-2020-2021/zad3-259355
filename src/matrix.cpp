#include "matrix.hh"

/******************************************************************************
 |  Konstruktor klasy Matrix.                                                 |
 |  Argumenty:                                                                |
 |      Brak argumentow.                                                      |
 |  Zwraca:                                                                   |
 |      Macierz wypelnione wartoscia 0.                                       |
 */
Matrix::Matrix() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            value[i][j] = 0;
        }
    }
}


/******************************************************************************
 |  Konstruktor parametryczny klasy Matrix.                                   |
 |  Argumenty:                                                                |
 |      tmp - dwuwymiarowa tablica z elementami typu double.                  |
 |  Zwraca:                                                                   |
 |      Macierz wypelniona wartosciami podanymi w argumencie.                 |
 */
Matrix::Matrix(double tmp[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            value[i][j] = tmp[i][j];
        }
    }
}


/******************************************************************************
 |  Realizuje mnozenie macierzy przez wektor.                                 |
 |  Argumenty:                                                                |
 |      this - macierz, czyli pierwszy skladnik mnozenia,                     |
 |      v - wektor, czyli drugi skladnik mnozenia.                            |
 |  Zwraca:                                                                   |
 |      Iloczyn dwoch skladnikow przekazanych jako wektor.                    |
 */

Vector Matrix::operator * (Vector tmp) {
    Vector result;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            result[i] += value[i][j] * tmp[j];
        }
    }
    return result;
}


/******************************************************************************
 |  Funktor macierzy                                                          |
 |  Argumenty:                                                                |
 |      row - numer wiersza.                                                  |
 |      column - numer kolumny.                                               |
 |  Zwraca:                                                                   |
 |      Wartosc macierzy w danym miejscu tablicy.                             |
 */
double &Matrix::operator()(unsigned int row, unsigned int column) {

    if (row >= SIZE) {
        throw std::out_of_range("Error: Macierz jest poza zasiegiem");
    }

    if (column >= SIZE) {
        throw std::out_of_range("Error: Macierz jest poza zasiegiem"); 
    }

    return value[row][column];
}


/******************************************************************************
 |  Funktor macierzy                                                          |
 |  Argumenty:                                                                |
 |      row - numer wiersza.                                                  |
 |      column - numer kolumny.                                               |
 |  Zwraca:                                                                   |
 |      Wartosc macierzy w danym miejscu tablicy jako stala.                  |
 */
const double &Matrix::operator () (unsigned int row, unsigned int column) const {

    if (row >= SIZE) {
        std::cout << "Error: Macierz jest poza zasiegiem";
        exit(0); // lepiej byłoby rzucić wyjątkiem stdexcept
    }

    if (column >= SIZE) {
        std::cout << "Error: Macierz jest poza zasiegiem";
        exit(0); // lepiej byłoby rzucić wyjątkiem stdexcept
    }

    return value[row][column];
}

/******************************************************************************
 |  Przeciążenie dodawania macierzy                                                          |
 |  Argumenty:                                                                |
 |      this - macierz, czyli pierwszy skladnik dodawania,                     |
 |      v - wektor, czyli drugi skladnik dodawania.                                               |
 |  Zwraca:                                                                   |
 |      Macierz - iloczyn dwóch podanych macierzy.                  |
 */
Matrix Matrix::operator + (Matrix tmp) {
    Matrix result;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            result(i, j) = this->value[i][j] + tmp(i, j);
        }
    }
    return result;
}

/******************************************************************************
 |  Przeciazenie operatora >>                                                 |
 |  Argumenty:                                                                |
 |      in - strumien wyjsciowy,                                              |
 |      mat - macierz.                                                         |
 */
std::istream &operator>>(std::istream &in, Matrix &mat) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            in >> mat(i, j);
        }
    }
    return in;
}


/******************************************************************************
 |  Przeciazenie operatora <<                                                 |
 |  Argumenty:                                                                |
 |      out - strumien wejsciowy,                                             |
 |      mat - macierz.                                                        |
 */
std::ostream &operator<<(std::ostream &out, const Matrix &mat) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            out << "| " << mat(i, j) << " | "; //warto ustalic szerokosc wyswietlania dokladnosci liczb
        }
        std::cout << std::endl;
    }
    return out;
}

//Metoda inicjujaca macierz obrotu wartosciami trygonometrycznymi danego kata 

Matrix Matrix::Init(){

    this->toradians();
    this->value[0][0] = cos(this->angle);
    this->value[1][0] = -sin(this->angle);
    this->value[0][1] = sin(this->angle);
    this->value[1][1] = cos(this->angle);

    return *this;
}

//Funkcja zmieniajaca kat ze stopni na radiany i zwracajaca nowa wartosc katu

double Matrix::toradians(){

    this->angle = (this->angle * M_PI)/180;
    return this->angle;
}

//Przeciazenie operatora porownania macierzy 
bool Matrix::operator == ( const Matrix tmp) const {
    int k = 0;
    for(int i = 0; i < SIZE; ++i){
        for(int j = 0; j < SIZE; ++j){
            if(this->value[i][j] == tmp(i,j)){
                k++;
            }
        }
    }
    if(k == 4){
        return true;
    }
    else{
        return false;
    }
}

//Funkcja obliczajaca wyznacznik macierzy i zwraca jego wartosc

// double Matrix::determinant(){
//     double deter1, deter2, deter;
//     deter1 = this->value[0][0] * this->value[0][1];
//     deter2 = this->value[0][1] * this->value[1][0];
//     deter = deter1 - deter2;
//     return deter;
// }

//Funkcja obliczajaca dzialanie mnozenia dwoch macierzy 
Matrix Matrix::operator * (Matrix sec){
    Matrix tmp;
    for( int i = 0; i < SIZE; ++i){
        for( int j = 0; j < SIZE; ++j){
            for( int k = 0; k < SIZE; ++k){
                tmp(i,j) += this->value[k][j] * sec(j,k);
            }
        }
    }
    return tmp;
}

double Matrix::determinant(){
    double ratio;
    int i,j,k;
    for( i=0 ; i< SIZE-1 ; i++)
        {
            if(this->value[i][i] == 0.0)
            {
                std::cout<<"Mathematical Error!";
                exit(0);
            }
            for(j=i+1;j<SIZE;j++)
            {
                ratio = this->value[j][i]/this->value[i][i];

                for(k=0;k<SIZE;k++)
                {
                    std::cout << *this << std::endl;
                    this->value[j][k] = this->value[j][k] - ratio*this->value[i][k];
                }
            }
        }
    std::cout << *this << std::endl;
    std::cout << this->value[0][0] << " i " << this->value[0][1] << " i " << this->value[1][1] << std::endl;
    double deter = 1;
    for( i = 0; i < SIZE; ++i){
        deter *= this->value[i][i];
    }
    
    return deter;
}