// ����, ���, ���� "��⮤� �ணࠬ��஢����-2", �++, ���
//
// sample_matrix.cpp - Copyright (c) ��ࣥ�� �.�. 07.05.2001
//   ���ࠡ�⠭� ��� Microsoft Visual Studio 2008 ��ᮥ�� �.�. (20.04.2015)
//
// ����஢���� ���孥��㣮�쭮� ������

#include <iostream>
#include "utmatrix.h"
//---------------------------------------------------------------------------

int main()
{
  TMatrix<int> a(5), b(5), c(5);
  int i, j;

  setlocale(LC_ALL, "Russian");
  cout << "����஢���� �ணࠬ� �����প� �।�⠢����� ��㣮���� �����"
    << endl;
  for (i = 0; i < 5; i++)
    for (j = i; j < 5; j++ )
    {
      a[i][j] =  i * 10 + j;
      b[i][j] = (i * 10 + j) * 100;
    }
  c = a + b;
  cout << "Matrix a = " << endl << a << endl;
  cout << "Matrix b = " << endl << b << endl;
  cout << "Matrix c = a + b" << endl << c << endl;
  return 0;
}
//---------------------------------------------------------------------------
