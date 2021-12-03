// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// sample_matrix.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (20.04.2015)
//
// Тестирование верхнетреугольной матрицы

#include <iostream>
#include "utmatrix.h"
//---------------------------------------------------------------------------

int main()
{
  cout << "Testing programs supporting the representation of triangular matrices" << endl;
  int count_way;
  int count;
  int inf = 2;
  int size;

  while (inf != 1){
      cout << "Enter the size of the matrix" << endl;
      cin >> size;
      TMatrix<int> a(size), b(size);
      cout << "Choose a filling method" << endl;
      cout << "1. Manually" << endl << "2. Random" << endl;
      cin >> count_way;

      switch (count_way) {
          case 1:
          {
              cout << "Enter the matrix A" << endl;
              cin >> a;
              cout << "Enter the matrix B" << endl;
              cin >> b;
              cout << "A:" << endl << a << endl;
              cout << "B:" << endl << b << endl;
              break;
          }
          case 2:
          {
              for (int i = 0; i < size; ++i) {
                  for (int k = i; k < size; ++k) {
                      a[i][k] = rand()%1000;
                      b[i][k] = rand()%1000;
                  }
              }
              cout << "A:" << endl << a << endl;
              cout << "B:" << endl << b << endl;
              break;
          }
          default:
          {
              cout << "Unknown command" << endl;
              cout << "1. Manually" << endl << "2. Random" << endl;
              cin >> count_way;
          }
      }

      cout << "Choose a math action" << endl;
      cout << "1. Addition A + B" << endl << "2. Subtraction A - B" << endl;
      cin >> count;

      switch (count){
          case 1:
          {
              cout << a + b << endl;
              break;
          }
          case 2:
          {
              cout << a - b << endl;
              break;
          }
          default:
          {
              cout << "Unknown command" << endl;
              cout << "1. Addition A + B" << endl << "2. Subtraction A - B" << endl;
              cin >> count;
          }
      }

      cout << "1. Exit" << endl << "2. Resume" << endl;
      cin >> inf;
      switch (inf) {
          case 1:
          {
              inf = 1;
              break;
          }
          case 2:
          {
              inf = 2;
              break;
          }
          default:
          {
              cout << "Unknown command" << endl;
              cout << "1. Exit" << endl << "2. Resume" << endl;
              cin >> inf;
          }
      }
  }

  return 0;
}
//---------------------------------------------------------------------------
