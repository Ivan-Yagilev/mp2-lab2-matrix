﻿// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
	ValType* pVector;
	int Size;       // размер вектора
	int StartIndex; // индекс первого элемента вектора
public:
	TVector(int s = 10, int si = 0);
	TVector(const TVector& v);                // конструктор копирования
	~TVector();
	int GetSize() const { return Size; } // размер вектора
	int GetStartIndex() const { return StartIndex; } // индекс первого элемента
	ValType& operator[](int pos);             // доступ
	bool operator==(const TVector& v) const;  // сравнение
	bool operator!=(const TVector& v) const;  // сравнение
	TVector& operator=(const TVector& v);     // присваивание

	TVector operator-();

	// скалярные операции
	TVector  operator+(const ValType& val);   // прибавить скаляр
	TVector  operator-(const ValType& val);   // вычесть скаляр
	TVector  operator*(const ValType& val);   // умножить на скаляр

	// векторные операции
	TVector  operator+(const TVector& v);     // сложение
	TVector  operator-(const TVector& v);     // вычитание
	ValType  operator*(const TVector& v);     // скалярное произведение

	// ввод-вывод
	friend istream& operator>>(istream& in, TVector& v)
	{
		for (int i = 0; i < v.Size - v.StartIndex; i++)
			in >> v.pVector[i];
		return in;
	}
	friend ostream& operator<<(ostream& out, const TVector& v)
	{
		for (int i = 0; i < v.Size - v.StartIndex; i++)
			out << v.pVector[i] << ' ';
		return out;
	}
};

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
	if ((s > MAX_VECTOR_SIZE) || (si < 0) || (s < 0) || (s <= si))
		throw 1;

	pVector = new ValType[s - si];
	Size = s;
	StartIndex = si;
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType>& v)
{
	Size = v.Size;
	StartIndex = v.StartIndex;
	pVector = new ValType[Size - StartIndex];

	for (int i = 0; i < Size - StartIndex; i++)
		pVector[i] = v.pVector[i];

} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
	delete[] pVector;
} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
	if ((pos - StartIndex < 0) || (pos > Size))
		throw 1;

	return pVector[pos - StartIndex];
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector& v) const
{
	if (Size != v.Size)
		return false;

	for (int i = 0; i < Size - StartIndex; i++)
		if (pVector[i] != v.pVector[i])
			return false;

	return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector& v) const
{
	if (*this == v)
		return false;
	return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector& v)
{
	if (this != &v) {
		delete[] pVector;

		Size = v.Size;
		StartIndex = v.StartIndex;
		pVector = new ValType[Size - StartIndex];

		for (int i = 0; i < Size - StartIndex; i++)
			pVector[i] = v.pVector[i];
	}
	return *this;
} /*-------------------------------------------------------------------------*/


template <class ValType>
TVector<ValType> TVector<ValType>::operator-()
{
	TVector<ValType> a(*this);

	for (int i = 0; i < Size - StartIndex; i++) {
		ValType val = a.pVector[i];
		a.pVector[i] = -val;
	}
	return a;
}

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType& val)
{
	TVector a(Size);

	for (int i = 0; i < Size; i++) 
		a.pVector[i] = val;

	for (int i = StartIndex; i < Size; i++)
		a.pVector[i] = a.pVector[i] + pVector[i - StartIndex];

	return a;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType& val)
{
	TVector<ValType> a(*this);
	return a + (-val);
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType& val)
{
	TVector a(*this);
	for (int i = 0; i < Size - StartIndex; i++)
		a.pVector[i] = a.pVector[i] * val;

	return a;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType>& v)
{
	if (Size + StartIndex != v.Size + v.StartIndex)
		throw 1;

	if (StartIndex < v.StartIndex) {
		TVector<ValType> a(*this);

		for (int i = v.Size - v.StartIndex - 1; i >= 0; i--)
			a.pVector[v.StartIndex - StartIndex + i] = a.pVector[v.StartIndex - StartIndex + i] + v.pVector[i];

		return a;
	}
	else {
		TVector<ValType> a(v);

		for (int i = Size - StartIndex - 1; i >= 0; i--)
			a.pVector[StartIndex - v.StartIndex + i] = a.pVector[StartIndex - v.StartIndex + i] + pVector[i];

		return a;
	}
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType>& v)
{
	if (Size + StartIndex != v.Size + v.StartIndex)
		throw 1;
	if (StartIndex < v.StartIndex) {
		TVector<ValType> a(*this);
		for (int i = v.Size - v.StartIndex - 1; i >= 0; i--)
			a.pVector[v.StartIndex - StartIndex + i] = pVector[v.StartIndex - StartIndex + i] - v.pVector[i];

		return a;
	}
	else {
		TVector<ValType> a(v);
		for (int i = 0; i < StartIndex - v.StartIndex; i++)
		{
			a.pVector[i] = -a.pVector[i];
		}
		for (int i = Size - StartIndex - 1; i >= 0; i--) {
			a.pVector[StartIndex - v.StartIndex + i] = pVector[i] - a.pVector[StartIndex - v.StartIndex + i];
		}
		return a;
	}
} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType>& v)
{
	if (Size + StartIndex != v.Size + v.StartIndex)
		throw 1;
	ValType res = 0;
	if (StartIndex > v.StartIndex) {
		for (int i = Size - StartIndex - 1; i >= 0; i--)
			res = res + pVector[i] * v.pVector[StartIndex - v.StartIndex + i];
	}
	else {
		for (int i = v.Size - v.StartIndex - 1; i >= 0; i--)
			res = res + pVector[v.StartIndex - StartIndex + i] * v.pVector[i];
	}
	return res;
} /*-------------------------------------------------------------------------*/


// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
	TMatrix(int s = 10);
    TMatrix(const TMatrix& mt);                    // копирование
    TMatrix(const TVector<TVector<ValType> >& mt); // преобразование типа
	bool operator==(const TMatrix& mt) const;      // сравнение
	bool operator!=(const TMatrix& mt) const;      // сравнение
	TMatrix& operator= (const TMatrix& mt);        // присваивание
	TMatrix  operator+ (const TMatrix& mt);        // сложение
	TMatrix  operator- (const TMatrix& mt);        // вычитание

	// ввод / вывод
	friend istream& operator>>(istream& in, TMatrix& mt)
	{
		for (int i = 0; i < mt.Size - mt.StartIndex; i++)
			in >> mt.pVector[i];
		return in;
	}
	friend ostream& operator<<(ostream& out, const TMatrix& mt)
	{
		for (int i = 0; i < mt.Size - mt.StartIndex; i++)
			out << mt.pVector[i] << endl;
		return out;
	}
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType> >(s)
{
	if (s > MAX_MATRIX_SIZE) {
		throw 2;
	}
	Size = s;
	for (int i = 0; i < s; i++) {
		TVector<ValType> tmp(s, i);
		pVector[i] = tmp;
	}
} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType>& mt) : TVector<TVector<ValType> >(mt)
{
	Size = mt.GetSize();
	StartIndex = 0;
}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> >& mt) : TVector<TVector<ValType> >(mt)
{
	Size = mt.GetSize();
	StartIndex = 0;
}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType>& mt) const
{
	return TVector<TVector<ValType>>::operator==(mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType>& mt) const
{
	return TVector<TVector<ValType>>::operator!=(mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType>& mt)
{
	TVector<TVector<ValType>>::operator=(mt);
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType>& mt)
{
	return TVector<TVector<ValType>>::operator+(mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType>& mt)
{
	return TVector<TVector<ValType>>::operator-(mt);
} /*-------------------------------------------------------------------------*/

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif