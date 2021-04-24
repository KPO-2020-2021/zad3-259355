#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../tests/doctest/doctest.h"

// This is all that is needed to compile a test-runner executable.
// More tests can be added here, or in a new tests/*.cpp file.

#include "../tests/doctest/doctest.h"
#include "Prostokat.hh"
#include "size.hh"
#include "example.h"
#include <fstream>

// Tests which check if functions related with rectangle

TEST_CASE("Rectangle - Proper save of coordinates")
{
  double arg1[] = {100,100};
  double arg2[] = {100,400};
  double arg3[] = {700,400};
  double arg4[] = {700,100};
  Vector vec1 = Vector(arg1);
  Vector vec2 = Vector(arg2);
  Vector vec3 = Vector(arg3);
  Vector vec4 = Vector(arg4);
  Vector arguments1[] = { vec1, vec2, vec3, vec4};
  Prostokat pro = Prostokat(arguments1);
  SUBCASE("First coordinate"){
      double temp1[] = {100,100};
      Vector vect1 = Vector(temp1);
    CHECK( vect1 == pro(0));
  }
  SUBCASE("Second coordinate"){
      double temp2[] = {100,400};
      Vector vect2 = Vector(temp2);
    CHECK( vect2 == pro(1));
  }
  SUBCASE("Third coordinate"){
      double temp3[] = {700,400};
      Vector vect3 = Vector(temp3);
    CHECK( vect3 == pro(2));
  }
  SUBCASE("Fourth coordinate"){
      double temp4[] = {700,100};
      Vector vect4 = Vector(temp4);
    CHECK( vect4 == pro(3));
  }
}

TEST_CASE("Rectangle - rotate (angle - 180, 1 time)"){
    double arg1[] = {100,100};
    double arg2[] = {100,400};
    double arg3[] = {700,400};
    double arg4[] = {700,100};
    Vector vec1 = Vector(arg1);
    Vector vec2 = Vector(arg2);
    Vector vec3 = Vector(arg3);
    Vector vec4 = Vector(arg4);
    Vector arguments1[] = { vec1, vec2, vec3, vec4};
    Prostokat pro = Prostokat(arguments1);
    double ang = 180;
    pro.turn(ang);
    SUBCASE("First coordinate"){
      double temp1[] = {-100,-100};
      Vector vect1 = Vector(temp1);
    CHECK( vect1 == pro(0));
  }
  SUBCASE("Second coordinate"){
      double temp2[] = {-100,-400};
      Vector vect2 = Vector(temp2);
    CHECK( vect2 == pro(1));
  }
  SUBCASE("Third coordinate"){
      double temp3[] = {-700,-400};
      Vector vect3 = Vector(temp3);
    CHECK( vect3 == pro(2));
  }
  SUBCASE("Fourth coordinate"){
      double temp4[] = {-700,-100};
      Vector vect4 = Vector(temp4);
    CHECK( vect4 == pro(3));
  }
}

TEST_CASE("Rectangle - move (vector [100,100])"){
  
    double arg1[] = {100,100};
    double arg2[] = {100,400};
    double arg3[] = {700,400};
    double arg4[] = {700,100};
    Vector vec1 = Vector(arg1);
    Vector vec2 = Vector(arg2);
    Vector vec3 = Vector(arg3);
    Vector vec4 = Vector(arg4);

    Vector arguments1[] = { vec1, vec2, vec3, vec4};
    Prostokat pro = Prostokat(arguments1);;
    double args[SIZE] = {100,100};
    Vector vec = Vector(args);
    pro.move(vec);

    SUBCASE("First coordinate"){
      double temp1[] = {200,200};
      Vector vect1 = Vector(temp1);
    CHECK( vect1 == pro(0));
    }
    SUBCASE("Second coordinate"){
        double temp2[] = {200,500};
        Vector vect2 = Vector(temp2);
      CHECK( vect2 == pro(1));
    }
    SUBCASE("Third coordinate"){
        double temp3[] = {800,500};
        Vector vect3 = Vector(temp3);
      CHECK( vect3 == pro(2));
    }
    SUBCASE("Fourth coordinate"){
        double temp4[] = {800,200};
        Vector vect4 = Vector(temp4);
      CHECK( vect4 == pro(3));
    }
}

// Tests Vector

TEST_CASE("Vector - sum"){
    double arg1[] = {100,100};
    double arg2[] = {300,300};
    Vector vec1 = Vector(arg1);
    Vector vec2 = Vector(arg2);
    double argt[] = {400,400};
    Vector temp = Vector(argt);
    CHECK( (vec1 + vec2) == temp);
}

TEST_CASE("Vector - difference"){
    double arg1[SIZE] = {100,100};
    double arg2[SIZE] = {300,300};
    Vector vec1 = Vector(arg1);
    Vector vec2 = Vector(arg2);
    double argt[SIZE] = {-200,-200};
    Vector temp = Vector(argt);
    CHECK( temp == vec1 - vec2);
}

TEST_CASE("Vector - multiplication"){
    double arg1[SIZE] = {100,100};
    double arg = 2;
    Vector vec1 = Vector(arg1);
    double argt[SIZE] = {200,200};
    Vector temp = Vector(argt);
    CHECK( temp == vec1 * arg);
}

TEST_CASE("Vector - division (arg = 2)"){
    double arg1[SIZE] = {100,100};
    double arg = 2;
    Vector vec1 = Vector(arg1);
    double argt[SIZE] = {50,50};
    Vector temp = Vector(argt);
    CHECK( temp == vec1 / arg);
}

TEST_CASE("Vector - division (arg = 0)"){
    double arg1[SIZE] = {100,100};
    double arg = 0;
    Vector vec1 = Vector(arg1);
    WARN_THROWS(vec1 / arg);
}

TEST_CASE("Index operator"){
  double value[] = {3,4};
  double a, b;
  Vector Vec(value);
  a = Vec[0];
  b = Vec[1];
  CHECK( (a == 3 && b == 4));
}

TEST_CASE("Index operator values to vector"){
  double a = 3;
  double b = 4;
  Vector Vec;
  Vec[0] = a;
  Vec[1] = b;
  CHECK( (Vec[0] == 3 && Vec[1] == 4));
}

TEST_CASE("Constructor values in"){
  double value[] = {3,4};
  Vector Vec(value);
  CHECK( (Vec[0] == 3 && Vec[1] == 4));
}

TEST_CASE("Out of range"){
  double value[] = {3,4};
  Vector Vec(value);
  WARN_THROWS( Vec[2]);
}

TEST_CASE("Start Constructor"){
  Vector Vec;
  CHECK( (Vec[0] == 0 && Vec[1] == 0));
}

TEST_CASE(">> operator"){
  Vector vec;
  std::istringstream in("0 1");
  in >> vec;
  CHECK( (vec[0] == 0 && vec[1] == 1) );
}

TEST_CASE("Vector - display"){
    double arg[] = {0,1};
    Vector vec1(arg);
    std::ostringstream stream;
    stream << vec1;
    CHECK( "    0.0000000000    1.0000000000" == stream.str());
}

// Tests Matrix 

TEST_CASE("Matrix - Init"){

    Matrix matr;
    matr.angle = 180;
    matr.Init();
    double arg[][SIZE] = {{-1, 0.0}, {-0.0, -1}};
    Matrix matrtemp = Matrix(arg);
    for(int i = 0; i < SIZE; ++i){
      for(int j = 0; j < SIZE; ++j){
        CHECK( abs(matr(i,j) - matrtemp(i,j)) <= MIN_DIFF );
    }
  }
}

TEST_CASE("Matrix - toradians"){
    Matrix matr;
    matr.angle = 30;
    matr.toradians();
    double radangle = 0.5235987756;
    CHECK( abs(matr.angle - radangle) <= MIN_DIFF );
}

TEST_CASE("Matrix - sum of matrixs"){

    double arg1[][SIZE] = {{20,20}, {20,20}};
    Matrix matr = Matrix(arg1);

    double arg2[][SIZE] = {{20,20}, {30,30}};
    Matrix matr2 = Matrix(arg2);

    double argtemp[][SIZE] = {{40,40}, {50,50}};
    Matrix matrtemp = Matrix(argtemp);

    for(int i = 0; i < SIZE; ++i){
    CHECK( abs(matrtemp(i,i) - (matr(i,i) + matr2(i,i))) <= MIN_DIFF );
    }
}

TEST_CASE("Matrix - multiplication (vector)"){

    double arg1[SIZE] = {20,20};
    Vector vec = Vector(arg1);

    double arg2[][SIZE] = {{20,30}, {20,30}};
    Matrix matr = Matrix(arg2);

    double argtemp[SIZE] = {1000,1000};
    Vector vectemp = Vector(argtemp);

    CHECK( vectemp == matr * vec );
}

TEST_CASE("Index operator"){
  double value[][SIZE] = { {3,4}, {3,4}};
  double a, b;
  Matrix mat(value);
  a = mat(0,0);
  b = mat(0,1);
  CHECK( (a == 3 && b == 4) );
}

TEST_CASE("Index operator values to vector"){
  double a = 3;
  double b = 4;
  double c = 0;
  double d = 5;
  Matrix mat;
  mat(0,0) = a;
  mat(0,1) = b;
  mat(1,0) = c;
  mat(1,1) = d;

  CHECK( (mat(0,0) == 3 && mat(0,1) == 4 && mat(1,0) == 0 && mat(1,1) == 5) );
}

TEST_CASE("Constructor values in"){
  double value[][SIZE] = {{3,4}, {4,5}};
  Matrix mat(value);
  CHECK( (mat(0,0) == 3 && mat(0,1) == 4 && mat(1,0) == 4 && mat(1,1) == 5) );
}

TEST_CASE("Out of range"){
  double value[][SIZE] = {{3,4}, {4,5}};
  Matrix mat(value);
  WARN_THROWS( mat(2,2));
}

TEST_CASE("Start Constructor"){
  Matrix mat;
  CHECK( (mat(0,0) == 0 && mat(0,1) == 0 && mat(1,0) == 0 && mat(1,1) == 0) );
}

TEST_CASE(">> operator"){
  Matrix mat;
  std::istringstream in("0 0 1 1");
  in >> mat;
  CHECK( (mat(0,0) == 0 && mat(0,1) == 0 && mat(1,0) == 1 && mat(1,1) == 1) );
}

TEST_CASE("Matrix - display"){
    double value[][SIZE] = {{3,4}, {4,5}};
    Matrix mat(value);
    std::ostringstream stream;
    stream << mat;
    CHECK( "| 3 | | 4 | | 4 | | 5 | " == stream.str());
}
