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

// template <typename T, typename U>
// void Wymnoz( T Arg1, U (&Arg2_Tab)[4]){
//   for(U &Mnoznik : Arg2_Tab) Mnoznik = Arg1 * Mnoznik;
// }

/*!
 * Simple main program that demontrates how access
 * CMake definitions (here the version number) from source code.
 * 
 * EDIT: dodane kreowanie wektorow i macierzy plus obsluga lacza do gnuplota
 */

int main() {

  // double Arg1 = 2;
  // double Tab[4] = {1,2,3,4};

  // Wymnoz(Arg1, Tab);

  // Matrix mat;
  // Vector vec[4];

  // Wymnoz(mat, vec);


  std::cout << "Project Rotation 2D based on C++ Boiler Plate v"
            << PROJECT_VERSION_MAJOR /*duże zmiany, najczęściej brak kompatybilności wstecz */
            << "."
            << PROJECT_VERSION_MINOR /* istotne zmiany */
            << "."
            << PROJECT_VERSION_PATCH /* naprawianie bugów */
            << "."
            << PROJECT_VERSION_TWEAK /* zmiany estetyczne itd. */
            << std::endl;
  double arg1[] = {10,10};
  double arg2[] = {10,40};
  double arg3[] = {70,40};
  double arg4[] = {70,10};
  Vector vec1 = Vector(arg1);
  Vector vec2 = Vector(arg2);
  Vector vec3 = Vector(arg3);
  Vector vec4 = Vector(arg4);
  Vector arguments1[] = { vec1, vec2, vec3, vec4};
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
  Lacze.UstawZakresY(-155,155);
  Lacze.UstawZakresX(-155,155);
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
