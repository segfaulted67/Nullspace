#pragma once

#include <iostream>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>



namespace Nullspace {

	constexpr int Dynamic = -1;
	constexpr double PI = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;
	constexpr double e = 2.71828182845904523536028747135266249775724709369995;

	template <typename T, int Rows = Dynamic, int Cols = Dynamic>
	class Matrix{
	public:
		Matrix();
		Matrix(int nrow, int ncol);
		Matrix(int nrow, int ncol, const T *data);
		Matrix(const Matrix<T, Rows, Cols>& inputMatrix);
		Matrix(int nrow, int ncol, std::initializer_list<T> list);
		Matrix(T num);
		Matrix(std::initializer_list<T> list);

		~Matrix();

		bool Resize(int nrow, int ncol);

		T GetElement(int row, int col) const;
		bool SetElement(int row, int col, T elementValue);
		int GetNumRows() const;
		int GetNumCols() const;

		const static Matrix Identity();
		const static Matrix Constant(T constant);
		const static Matrix Zero();
		Matrix<T, 1, Cols> Row(int r) const;
		Matrix<T, Rows, 1> Column(int c) const;

		T& operator()(int nrow, int ncol);
		const T& operator()(int nrow, int ncol) const;
		template <typename U, int R, int C> friend bool operator==(const Matrix<U, R, C>& lhs, const Matrix<U, R, C>& rhs);
		template <typename U, int R, int C> friend std::ostream& operator<<(std::ostream& os, const Matrix<U, R, C>& m);

		template <typename U, int R, int C> friend Matrix<U, R, C> operator-(const Matrix<U, R, C>& lhs);
		template <typename U, int R, int C> friend Matrix<U, R, C> operator+(const Matrix<U, R, C>& lhs, const Matrix<U, R, C>& rhs);
		template <typename U, int R, int C> friend Matrix<U, R, C> operator-(const Matrix<U, R, C>& lhs, const Matrix<U, R, C>& rhs);
		template <typename U, int R, int K, int C> friend Matrix<U, R, C> operator*(const Matrix<U, R, K>& lhs, const Matrix<U, K, C>& rhs);
		template <typename U, int R, int C> friend Matrix<U, R, C> operator*(const U& lhs, const Matrix<U, R, C>& rhs);
		template <typename U, int R, int C> friend Matrix<U, R, C> operator*(const Matrix<U, R, C>& lhs, const U& rhs);

		void Print();

	private:
		int Sub2Ind(int row, int col) const;
	private:
		std::vector<T> m_matrixData;
		int m_nrow = (Rows == Dynamic ? 0 : Rows), m_ncol = (Cols == Dynamic ? 0 : Cols), m_nElements = m_nrow * m_ncol;
	};
}

#include "Matrix.inl"
