#pragma once

#include <iostream>
#include <vector>
#include <initializer_list>

namespace Nullspace {
	template <typename T, int N>
	class Vector {
	public:
		Vector();
		Vector(T num);
		Vector(std::initializer_list<T> list);

		int Dim() const;
		T& operator[](int dim);
		const T& operator[](int dim) const;

		template <typename U, int N1> friend bool operator==(const Vector<U, N1>& lhs, const Vector<U, N1>& rhs);
		template <typename U, int N1> friend bool operator!=(const Vector<U, N1>& lhs, const Vector<U, N1>& rhs);
		template <typename U, int N1> friend std::ostream& operator<<(std::ostream& os, const Vector<U, N1>& v);

		template <typename U, int N1> friend Vector<U, N1> operator+(const Vector<U, N1>& lhs, const Vector<U, N1>& rhs);
		template <typename U, int N1> friend Vector<U, N1> operator-(const Vector<U, N1>& lhs, const Vector<U, N1>& rhs);
		template <typename U, int N1> friend U operator*(const Vector<U, N1>& lhs, const Vector<U, N1>& rhs);
		template <typename U, int N1> friend Vector<U, N1> operator*(const U lhs, const Vector<U, N1>& rhs);
		template <typename U, int N1> friend Vector<U, N1> operator*(const Vector<U, N1>& lhs, const U rhs);
		template <typename U, int N1> friend Vector<U, N1> operator/(const Vector<U, N1>& lhs, const U rhs);

		double Magnitude() const;
		Vector<T, N> Normalize() const;
	private:
		std::vector<T> m_elements;
		int m_dim;
	};
}

#include "Vector.inl"
