// Executables must have the following defined if the library contains
// doctest definitions. For builds with this disabled, e.g. code shipped to
// users, this can be left out.
#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "../tests/doctest/doctest.h"
#endif

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <string>

#include "exampleConfig.h"
#include "example.h"
#include "vector.hh"
#include "Prostokat.hh"
#include "matrix.hh"
#include "../include/lacze_do_gnuplota.hh"

using namespace std;

/*!
 * Simple main program that demontrates how access
 * CMake definitions (here the version number) from source code.
 * 
 * EDIT: dodane kreowanie wektorow i macierzy plus obsluga lacza do gnuplota
 */

#define DL_KROTKI_BOK  100
#define DL_DLUGI_BOK   150

/*!
 * Przyklad zapisu wspolrzednych zbioru punktow do strumienia wyjściowego.
 * Dane sa odpowiednio sformatowane, tzn. przyjęto notację stałoprzecinkową
 * z dokładnością do 10 miejsca po przecinku. Szerokość wyświetlanego pola 
 * to 16 miejsc, sposób wyrównywania - do prawej strony.
 * \param[in] StrmWy - strumien wyjsciowy, do ktorego maja zostac zapisane
 *                     kolejne wspolrzedne.
 * \param[in] Przesuniecie - ten parameter jest tylko po to, aby pokazać
 *                          mozliwosc zmiany wspolrzednych i prostokata
 *                          i zmiane jego polorzenia na okienku graficznym
 *                         rysownym przez gnuplota.
 * \retval true - gdy operacja zapisu powiodła się,
 * \retval false - w przypadku przeciwnym.
 */
// void Tostrm( std::ostream& StrmWy, Prostokat pro)
// {
//   StrmWy << pro << endl;
// }

/*!
 * Przyklad zapisu wspolrzednych zbioru punktow do pliku, z ktorego
 * dane odczyta program gnuplot i narysuje je w swoim oknie graficznym.
 * \param[in] sNazwaPliku - nazwa pliku, do którego zostana zapisane
 *                          wspolrzędne punktów.
 * \param[in] Przesuniecie - ten parameter jest tylko po to, aby pokazać
 *                          mozliwosc zmiany wspolrzednych i prostokata
 *                          i zmiane jego polorzenia na okienku graficznym
 *                         rysownym przez gnuplota.
 * \retval true - gdy operacja zapisu powiodła się,
 * \retval false - w przypadku przeciwnym.
 */
// bool Save( const char  *sNazwaPliku, Prostokat pro)
// {
//   std::ofstream  StrmPlikowy;

//   StrmPlikowy.open(sNazwaPliku);
//   if (!StrmPlikowy.is_open())  {
//     std::cerr << ":(  Operacja otwarcia do zapisu \"" << sNazwaPliku << "\"" << std::endl
// 	 << ":(  nie powiodla sie." << std::endl;
//     return false;
//   }

//   Tostrm(StrmPlikowy, pro);

//   StrmPlikowy.close();
//   return !StrmPlikowy.fail();
// }

int main() {
  std::cout << "Project Rotation 2D based on C++ Boiler Plate v"
            << PROJECT_VERSION_MAJOR /*duże zmiany, najczęściej brak kompatybilności wstecz */
            << "."
            << PROJECT_VERSION_MINOR /* istotne zmiany */
            << "."
            << PROJECT_VERSION_PATCH /* naprawianie bugów */
            << "."
            << PROJECT_VERSION_TWEAK /* zmiany estetyczne itd. */
            << std::endl;
  // std::system("cat ../LICENSE");
  // do zadania Rotacja 2D
//   std::cout << "Vector:" << std::endl;
//   Vector tmpV1 = Vector();
//   std::cout << "Vector - konstruktor bezparametryczny:\n" << tmpV1 << std::endl;
//   double argumentsV[] = {1.0, 2.0};
//   Vector tmpV2 = Vector(argumentsV);
//   std::cout << "Vector - konstruktor parametryczny:\n" << tmpV2 << std::endl;

  double arguments1[][SIZE] = {{100, 100}, {100, 400}, {700, 400}, {700, 100}};
  Prostokat pro = Prostokat(arguments1);

  PzG::LaczeDoGNUPlota  Lacze;  // Ta zmienna jest potrzebna do wizualizacji
                                // rysunku prostokata

   //-------------------------------------------------------
   //  Wspolrzedne wierzcholkow beda zapisywane w pliku "prostokat.dat"
   //  Ponizsze metody powoduja, ze dane z pliku beda wizualizowane
   //  na dwa sposoby:
   //   1. Rysowane jako linia ciagl o grubosci 2 piksele
   //
  Lacze.DodajNazwePliku("../datasets/prostokat.dat",PzG::RR_Ciagly,2);
   //
   //   2. Rysowane jako zbior punktow reprezentowanych przez kwadraty,
   //      których połowa długości boku wynosi 2.
   //
  Lacze.DodajNazwePliku("../datasets/prostokat.dat",PzG::RR_Punktowy,2);
   //
   //  Ustawienie trybu rysowania 2D, tzn. rysowany zbiór punktów
   //  znajduje się na wspólnej płaszczyźnie. Z tego powodu powoduj
   //  jako wspolrzedne punktow podajemy tylko x,y.
   //
  Lacze.ZmienTrybRys(PzG::TR_2D);
  pro.Save("../datasets/prostokat.dat");
  Lacze.Rysuj();

  cout << "Beginning" << endl;
  double temp1, temp2;
  char choice;
  pro.lenght();
  temp1 = pro.blen;
  temp2 = pro.slen;
  Vector tmp;

  cout << "m - menu" << endl;
  cout << "o - turn" << endl;
  cout << "w - cords" << endl;
  cout << "p - move" << endl;
  cout << "k - end" << endl;

  while (choice != 'k'){

    cout << "Your choice?  (m-menu) >" << endl;
    cin >> choice;

    switch( choice ){
      case 'o': 
        double ang, howm;

        cout << "Choose an angle: ";
        cin >> ang;
        cout << "Choose how many times to turn rectangle: ";
        cin >> howm;

        pro.turning(pro, "../datasets/prostokat.dat", ang, howm, Lacze);

        cout << pro << endl;
        cout << "After" << endl;
        cout << endl;

        pro.showres(temp1,temp2);
        cout << endl;
      break;

      case 'p': 
        cout << "Vector to move: ";
        cin >> tmp;
        pro.moving(tmp,"../datasets/prostokat.dat", Lacze);

        cout << pro << endl;
        cout << "After" << endl;
        cout << endl;

        pro.showres(temp1,temp2);
        cout << endl;
      break;

      case 'w': 
        cout << "Cooridantes" << endl;
        cout << pro << endl;
        break;
      case 'm': 
        cout << "m - menu" << endl;
        cout << "o - turn" << endl;
        cout << "w - cords" << endl;
        cout << "p - move" << endl;
        cout << "k - end" << endl;
      break;

      case 'k': 
        cout << "The end" << endl;
      break;

      default:
        cout << "Wrong Option" << endl;
      break;
    }
  }

  Dummy d = Dummy();
  return d.doSomething() ? 0 : -1;
}
