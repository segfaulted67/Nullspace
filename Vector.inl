namespace Nullspace {

	template <typename T, int N>
	Vector<T, N>::Vector()
		: m_elements(N, T(0)), m_dim(N)
	{
	}

	template <typename T, int N>
	Vector<T, N>::Vector(T num)
		: m_elements(N, num), m_dim(N)
	{
	}

	template <typename T, int N>
	Vector<T, N>::Vector(std::initializer_list<T> list)
		: m_elements(N, T(0)), m_dim(N)
	{
		int i = 0;

		for (const auto& val : list) {
			if (i >= m_dim)
				break;

			m_elements[i++] = val;
		}
	}

	template <typename T, int N>
	bool operator==(const Vector<T, N>& lhs, const Vector<T, N>& rhs)
	{
		int result = 1;
		for (int i = 0; i < lhs.m_dim; i++) {
			if (lhs[i] == rhs[i]) {
				result = result && 1;
			}
		}
		return result;
	}

	template <typename T, int N>
	bool operator!=(const Vector<T, N>& lhs, const Vector<T, N>& rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T, int N>
	std::ostream& operator<<(std::ostream& os, const Vector<T, N>& v)
	{
		os << "<";

		for (int i = 0; i < N; i++) {
			os << v.m_elements[i];

			if (i != N - 1)
				os << ", ";
		}

		os << ">";

		return os;
	}

	template <typename T, int N>
	T& Vector<T, N>::operator[](int dim)
	{
		if (dim < 0 || dim > m_dim - 1) {
			throw;
		}
		return m_elements[dim];
	}

	template <typename T, int N>
	const T& Vector<T, N>::operator[](int dim) const
	{
		if (dim < 0 || dim > m_dim - 1) {
			throw;
		}
		return m_elements[dim];
	}

	template <typename T, int N>
	Vector<T, N> operator+(const Vector<T, N>& lhs, const Vector<T, N>& rhs)
	{
		Vector<T, N> result;
		for (int i = 0; i < lhs.m_dim; i++) {
			result[i] = lhs[i] + rhs[i];
		}

		return result;
	}

	template <typename T, int N>
	Vector<T, N> operator-(const Vector<T, N>& lhs, const Vector<T, N>& rhs)
	{
		Vector<T, N> result;
		for (int i = 0; i < lhs.m_dim; i++) {
			result[i] = lhs[i] - rhs[i];
		}

		return result;
	}

	template <typename T, int N>
	T operator*(const Vector<T, N>& lhs, const Vector<T, N>& rhs)
	{
		T result = 0;
		for (int i = 0; i < lhs.m_dim; i++) {
			result += lhs[i] * rhs[i];
		}

		return result;
	}

	template <typename T, int N>
	Vector<T, N> operator*(const T lhs, const Vector<T, N>& rhs)
	{
		Vector<T, N> result;
		for (int i = 0; i < rhs.m_dim; i++) {
			result[i] = lhs * rhs[i];
		}

		return result;
	}

	template <typename T, int N>
	Vector<T, N> operator*(const Vector<T, N>& lhs, const T rhs)
	{
		Vector<T, N> result;
		for (int i = 0; i < lhs.m_dim; i++) {
			result[i] = lhs[i] * rhs;
		}

		return result;
	}

	template <typename T, int N>
	Vector<T, N> operator/(const Vector<T, N>& lhs, const T rhs)
	{
		if (rhs == 0) {
			throw;
		}
		Vector<T, N> result;

		for (int i = 0; i < lhs.m_dim; i++) {
			result[i] = lhs[i] / rhs;
		}

		return result;
	}

	template <typename T, int N>
	double Vector<T, N>::Magnitude() const
	{
		double result = 0;
		for (int i = 0; i < m_dim; i++) {
			result += (* this)[i] * (* this)[i];
		}
		return std::sqrt(result);
	}

	template <typename T, int N>
	Vector<T, N> Vector<T, N>::Normalize() const
	{
		Vector<T, N> result;
		double mag = (* this).Magnitude();
		if (mag == 0.0) { throw; }
		for (int i = 0; i < m_dim; i++) {
			result[i] = (* this)[i] / T(mag);
		}
		return result;
	}
}