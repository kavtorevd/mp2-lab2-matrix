﻿// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <cassert>
#include <cmath>

using namespace std;

const int MAX_VECTOR_SIZE = 10000;
const int MAX_MATRIX_SIZE = 100000000;


template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    if (sz > MAX_VECTOR_SIZE)
        throw length_error("Exceeded vector max size");
    pMem = new T[sz]();
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    if (sz > MAX_VECTOR_SIZE)
        throw length_error("Exceeded vector max size");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
      sz = v.sz;
      pMem = new T[sz];
      copy(v.pMem, v.pMem + v.sz, pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      sz = v.sz;
      pMem = nullptr;
      std :: swap(pMem, v.pMem);
  }
  ~TDynamicVector()
  {
      if (pMem != nullptr)
          delete[] pMem;
      pMem = nullptr;
      sz = 0;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this == &v)
          return *this;
      if (sz != v.sz)
      {
          if (pMem != nullptr)
              delete[] pMem;
          sz = v.sz;
          pMem = new T[sz];
      }
      std::copy(v.pMem, v.pMem + v.sz, pMem);

      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (this == &v)
          return *this;
      if (pMem != nullptr) {
          delete[] pMem;
          pMem = nullptr;
      }

      sz = v.sz;
      std::swap(pMem, v.pMem);

      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind >= sz)
          throw out_of_range("Index shoud be less then size");
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind >= sz)
          throw out_of_range("Index shoud be less then size");
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz)
          return false;

      for (size_t i = 0; i < sz; i++) {
          if (pMem[i] != v.pMem[i])
              return false;
      }

      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector result(*this);

      for (size_t i = 0; i < result.sz; i++)
          result.pMem[i] += val;

      return result;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector result(*this);

      for (size_t i = 0; i < result.sz; i++)
          result.pMem[i] -= val;

      return result;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector result(*this);

      for (size_t i = 0; i < result.sz; i++)
          result.pMem[i] *= val;

      return result;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw logic_error("Sizes are not equal");

      TDynamicVector result(sz);

      for (size_t i = 0; i < sz; i++) {
          result.pMem[i] = pMem[i] + v.pMem[i];
      }

      return result;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw logic_error("Sizes are not equal");

      TDynamicVector result(sz);

      for (size_t i = 0; i < sz; i++) {
          result.pMem[i] = pMem[i] - v.pMem[i];
      }

      return result;
  }
  T operator*(const TDynamicVector& v) //noexcept(noexcept(T()))
  {
      if (sz != v.sz)
          throw logic_error("Sizes are not equal");

      T result = T();

      for (size_t i = 0; i < sz; i++) {
          result += pMem[i] * v.pMem[i];
      }

      return result;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::size;

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (sz != m.sz)
          return false;

      for (size_t i = 0; i < sz; i++) {
          if (pMem[i] != m.pMem[i])
              return false;
      }

      return true;
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix result(*this);

      for (size_t i = 0; i < sz; i++) {
          result.pMem[i] = result.pMem[i] * val;
      }

      return result;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (sz != v.sz)
          throw logic_error("Sizes are not equal");

      TDynamicVector<T> result(sz);

      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < sz; j++) {
              result[i] += pMem[i][j] * v[j];
          }
      }

      return result;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw logic_error("Sizes are not equal");

      TDynamicMatrix result(*this);

      for (size_t i = 0; i < sz; i++)
          result.pMem[i] = result.pMem[i] + m.pMem[i];

      return result;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw logic_error("Sizes are not equal");

      TDynamicMatrix result(*this);

      for (size_t i = 0; i < sz; i++)
          result.pMem[i] = result.pMem[i] - m.pMem[i];

      return result;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw logic_error("Sizes are not equal");

      TDynamicMatrix result(m.sz);

      for (size_t i = 0; i < m.sz; i++) {
          for (size_t j = 0; j < m.sz; j++) {
              for (size_t k = 0; k < m.sz; k++) {
                  result[i][j] += pMem[i][k] * m.pMem[k][j];
              }
          }
      }

      return result;
  }

  T& at(size_t i, size_t j) {
      if (i >= sz || j >= sz)
          throw out_of_range("Index shoud be less then size");
      return pMem[i][j];
  }
  const T& at(size_t i, size_t j) const {
      if (i >= sz || j >= sz)
          throw out_of_range("Index shoud be less then size");
      return pMem[i][j];
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
          istr >> v.pMem[i];
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
          ostr << v.pMem[i] << '\n';
      return ostr;
  }
};

#endif
