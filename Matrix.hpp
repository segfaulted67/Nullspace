#pragma once

#include <iostream>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

#include "Constants.hpp"
#include "Vector.hpp"

namespace Nullspace {

	constexpr int Dynamic = -1;

	template <typename T, int Rows, int Cols>
	class Matrix{
	public:
		Matrix();
		Matrix(const Matrix<T, Rows, Cols>& inputMatrix);
		Matrix(T num);
		Matrix(std::initializer_list<T> list);

		~Matrix();

		bool Resize(int row, int col);

		T GetElement(int row, int col) const;
		bool SetElement(int row, int col, T elementValue);
		int GetNumRows() const;
		int GetNumCols() const;

		const static Matrix Identity();
		const static Matrix Constant(T constant);
		const static Matrix Zero();
		Matrix<T, 1, Cols> Row(int r) const;
		Matrix<T, Rows, 1> Column(int c) const;

		T& operator[](int linearindex);
		const T& operator[](int linearindex) const;
		T& operator()(int row, int col);
		const T& operator()(int row, int col) const;

		template <typename U, int R, int C> friend bool operator==(const Matrix<U, R, C>& lhs, const Matrix<U, R, C>& rhs);
		template <typename U, int R, int C> friend bool operator!=(const Matrix<U, R, C>& lhs, const Matrix<U, R, C>& rhs);
		template <typename U, int R, int C> friend std::ostream& operator<<(std::ostream& os, const Matrix<U, R, C>& m);

		template <typename U, int R, int C> friend Matrix<U, R, C> operator-(const Matrix<U, R, C>& lhs);
		template <typename U, int R, int C> friend Matrix<U, R, C> operator+(const Matrix<U, R, C>& lhs, const Matrix<U, R, C>& rhs);
		template <typename U, int R, int C> friend Matrix<U, R, C> operator-(const Matrix<U, R, C>& lhs, const Matrix<U, R, C>& rhs);
		template <typename U, int R, int K, int C> friend Matrix<U, R, C> operator*(const Matrix<U, R, K>& lhs, const Matrix<U, K, C>& rhs);
		template <typename U, int R, int C> friend Matrix<U, R, C> operator*(const U& lhs, const Matrix<U, R, C>& rhs);
		template <typename U, int R, int C> friend Matrix<U, R, C> operator*(const Matrix<U, R, C>& lhs, const U& rhs);

		template <typename U, int N, int C> friend Vector<U, C> operator*(const Matrix<U, C, N>& lhs, const Vector<U, N>& rhs);

		Matrix<T, Cols, Rows> Transpose() const;
		bool IsSymmetric() const;
		bool IsSkewSymmetric() const;

		void Print();

	private:
		int Sub2Ind(int row, int col) const;
	private:
		std::vector<T> m_data;
		int m_row, m_col, m_elements;
	};
}

#include "Matrix.inl"
