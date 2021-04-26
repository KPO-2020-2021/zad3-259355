#include "vector.hh"

/******************************************************************************
 |  Konstruktor klasy Vector.                                                 |
 |  Argumenty:                                                                |
 |      Brak argumentow.                                                      |
 |  Zwraca:                                                                   |
 |      Tablice wypelniona wartoscia 0.                                       |
 */
Vector::Vector() {
    for (int i = 0; i < SIZE; ++i) {
        size[i] = 0;
    }
}


/******************************************************************************
 |  Konstruktor klasy Vector.                                                 |
 |  Argumenty:                                                                |
 |      tmp - Jednowymiarowa tablica typu double.                             |
 |  Zwraca:                                                                   |
 |      Tablice wypelniona wartosciami podanymi w argumencie.                 |
 */

Vector::Vector(double tmp[SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        size[i] = tmp[i];
    }
}


/******************************************************************************
 |  Realizuje dodawanie dwoch wektorow.                                       |
 |  Argumenty:                                                                |
 |      this - pierwszy skladnik dodawania,                                   |
 |      v - drugi skladnik dodawania.                                         |
 |  Zwraca:                                                                   |
 |      Sume dwoch skladnikow przekazanych jako wskaznik                      |
 |      na parametr.                                                          |
 */
Vector Vector::operator + ( Vector &v) {
    Vector result;
    for (int i = 0; i < SIZE; ++i) {
        result[i] = size[i] += v[i];
    }
    return result;
}

/******************************************************************************
 |  Realizuje odejmowanie dwoch wektorow.                                     |
 |  Argumenty:                                                                |
 |      this - pierwszy skladnik odejmowania,                                 |
 |      v - drugi skladnik odejmowania.                                       |
 |  Zwraca:                                                                   |
 |      Roznice dwoch skladnikow przekazanych jako wskaznik                   |
 |      na parametr.                                                          |
 */
Vector Vector::operator - ( Vector &v) {
    Vector result;
    for (int i = 0; i < SIZE; ++i) {
        result[i] = size[i] -= v[i];
    }
    return result;
}


/******************************************************************************
 |  Realizuje mnozenie wektora przez liczbe zmiennoprzecinkowa.               |
 |  Argumenty:                                                                |
 |      this - pierwszy skladnik mnozenia (wektor),                           |
 |      v - drugi skladnik mnozenia (liczba typu double).                     |
 |  Zwraca:                                                                   |
 |      Iloczyn dwoch skladnikow przekazanych jako wskaznik                   |
 |      na parametr.                                                          |
 */

Vector Vector::operator * (const double &tmp) {
    Vector result;
    for (int i = 0; i < SIZE; ++i) {
        result[i] = size[i] *= tmp;
    }
    return result;
}


/******************************************************************************
 |  Realizuje dzielenie dwoch wektorow.                                       |
 |  Argumenty:                                                                |
 |      this - licznik dzielenia,                                             |
 |      v - mianownik dzielenia.                                              |
 |  Zwraca:                                                                   |
 |      Iloraz dwoch skladnikow przekazanych jako wskaznik                    |
 |      na parametr.                                                          |
 */

Vector Vector::operator / (const double &tmp) {
    Vector result;
    if(tmp != 0){
    for (int i = 0; i < SIZE; ++i) {
        result[i] = size[i] / tmp;
    }}
    else{
        throw std::invalid_argument("Division by 0");
    }


    return result;
}


/******************************************************************************
 |  Funktor wektora.                                                          |
 |  Argumenty:                                                                |
 |      index - index wektora.                                                |
 |  Zwraca:                                                                   |
 |      Wartosc wektora w danym miejscu tablicy jako stala.                   |
 */
const double &Vector::operator [] (int index) const {
    if (index < 0 || index >= SIZE) {
        throw std::out_of_range("Error: Vector jest poza zasiegiem");    
    } 
    return size[index];
}


/******************************************************************************
 |  Funktor wektora.                                                          |
 |  Argumenty:                                                                |
 |      index - index wektora.                                                |
 |  Zwraca:                                                                   |
 |      Wartosc wektora w danym miejscu tablicy.                              |
 */
double &Vector::operator[](int index) {
    return const_cast<double &>(const_cast<const Vector *>(this)->operator[](index));
}


/******************************************************************************
 |  Przeciazenie operatora <<                                                 |
 |  Argumenty:                                                                |
 |      out - strumien wejsciowy,                                             |
 |      tmp - wektor.                                                         |
 */
// std::ostream &operator << (std::ostream &out, Vector const &tmp) {
//     for (int i = 0; i < SIZE; ++i) {
//         out << "[ " << tmp[i] << " ]\n";
//     }
//     return out;
// }

std::ostream& operator << ( std::ostream &stream, Vector const &tmp){

    stream << std::setw(16) << std::fixed << std::setprecision(10) << tmp[0]
           << std::setw(16) << std::fixed << std::setprecision(10) << tmp[1];

    return stream;
}


/******************************************************************************
 |  Przeciazenie operatora >>                                                 |
 |  Argumenty:                                                                |
 |      in - strumien wyjsciowy,                                              |
 |      tmp - wektor.                                                         |
 */
std::istream &operator >> (std::istream &in, Vector &tmp) {
    for (int i = 0; i < SIZE; ++i) {
        in >> tmp[i];
    }
    std::cout << std::endl;
    return in;
}

//Przeciazennie ktore sprawdza czy dane wektory sa rowne
bool Vector::operator == ( const Vector tmp) const {
    if(abs(this->size[0] - tmp[0]) <= MIN_DIFF && abs(this->size[1] - tmp[1]) <= MIN_DIFF){
        return true;
    }
    else{
        return false;
    }
}

// Przeciazenie sprawdzajace czy wektory sa rozne
bool Vector::operator != (const Vector tmp) const{
    if(abs(this->size[0] - tmp[0]) > MIN_DIFF || abs(this->size[1] == tmp[1]) > MIN_DIFF){
        return true;
    }
    else{
        return false;
    }
}
// double Vector::vlenght (Vector vec2){
//     double len;
    
//     len = sqrt(pow(vec2.size[0] - this->size[0],2) + pow(vec2.size[SIZE-1] - this->size[SIZE-1],2));

//     return len;
// }

// Vector Vector::gauss(Matrix mat){
//     Vector tmp;
//     double temp1, temp2;
//     temp1 = mat(0,0);
//     temp2 = mat(0,1);

//     mat(0,0) *= mat(0,1);
//     mat(0,1) *= temp1;
//     this->size[0] *= temp2;
//     mat(1,0) *= temp2;
//     mat(1,1) *= temp1;
//     this->size[1] *= temp1;
//     mat(0,1) -= mat(0,0);
//     mat(1,1) -= mat(1,0);

//     this->size[1] /= mat(1,1);
//     tmp[1] = this->size[1];

//     mat(1,0) *= tmp[1];
//     this->size[0] -= mat(1,0);
//     tmp[0] = this->size[0]/ mat(0,0);

//     return tmp;
// }

