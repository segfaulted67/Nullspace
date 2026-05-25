namespace Nullspace {
	template <typename T, int R, int C>
	Matrix<T, R, C>::Matrix()
		: m_row(R), m_col(C), m_elements(m_row * m_col),
		m_data(R * C, T{}) { }

	template <typename T, int R, int C>
	Matrix<T, R, C>::Matrix(const Matrix<T, R, C>& inputMatrix)
	{
		m_row = inputMatrix.m_row;
		m_col = inputMatrix.m_col;
		m_elements = m_row * m_col;
		m_data = std::vector<T>(m_elements);

		for (int i = 0; i < m_elements; i++)
			m_data[i] = inputMatrix.m_data[i];
	}

	template <typename T, int R, int C>
	Matrix<T, R, C>::Matrix(T num)
		: m_row(R), m_col(C), m_elements(m_row * m_col),
		m_data(R * C, T{})
	{
		for (int i = 0; i < m_row; i++) {
			for (int j = 0; j < m_col; j++) {
				int linearIndex = Sub2Ind(i, j);
				if (i == j)
					m_data[linearIndex] = T(num);
			}
		}
	}

	template <typename T, int R, int C>
	Matrix<T, R, C>::Matrix(std::initializer_list<T> list)
		: m_row(R), m_col(C), m_elements(m_row * m_col),
		m_data(R * C, T{})
	{
		int i = 0;
		for (auto& val : list) {
			if (i < m_elements)
				m_data[i++] = val;
			else
				break;
		}
		for (; i < m_elements; i++) {
			m_data[i] = T(0);
		}
	}

	template <typename T, int R, int C>
	Matrix<T, R, C>::~Matrix()
	{
	}

	template <typename T, int R, int C>
	bool Matrix<T, R, C>::Resize(int row, int col)
	{
		if constexpr (R != Dynamic || C != Dynamic)
			throw std::out_of_range("Static Matrix cannot be resized");
		m_row = row;
		m_col = col;
		m_elements = m_row * m_col;

		m_data.resize(m_elements);
		return true;
	}

	template <typename T, int R, int C>
	T Matrix<T, R, C>::GetElement(int row, int col) const
	{
		int linearIndex = Sub2Ind(row, col);
		if (linearIndex >= 0)
			return m_data[linearIndex];
		return T{};
	}

	template <typename T, int R, int C>
	bool Matrix<T, R, C>::SetElement(int row, int col, T elementValue)
	{
		int linearIndex = Sub2Ind(row, col);
		if (row >= m_row || col >= m_col) {
			return false;
		}
		m_data[linearIndex] = elementValue;
		return true;
	}

	template <typename T, int R, int C>
	int Matrix<T, R, C>::GetNumRows() const
	{
		return m_row;
	}

	template <typename T, int R, int C>
	int Matrix<T, R, C>::GetNumCols() const
	{
		return m_col;
	}

	template <typename T, int R, int C>
	const Matrix<T, R, C> Matrix<T, R, C>::Identity()
	{
		if (R != C)
			throw std::out_of_range("Row and Column are not equal");
		Matrix<T, R, C> result(0);
		for (int i = 0; i < result.m_row; i++) {
			for (int j = 0; j < result.m_col; j++) {
				int linearIndex = result.Sub2Ind(i, j);
				if (i == j)
					result.m_data[linearIndex] = T(1);
			}
		}
		return result;
	}

	template <typename T, int R, int C>
	const Matrix<T, R, C> Matrix<T, R, C>::Constant(T constant)
	{
		Matrix<T, R, C> result(0);
		for (int i = 0; i < result.m_elements; i++) {
				result.m_data[i] = constant;
		}
		return result;
	}

	template <typename T, int R, int C>
	const Matrix<T, R, C> Matrix<T, R, C>::Zero()
	{
		Matrix<T, R, C> result(0);
		return result;
	}

	template <typename T, int R, int C>
	Matrix<T, 1, C> Matrix<T, R, C>::Row(int r) const
	{
		Matrix<T, 1, C> result(0);
		for (int i = 0; i < C; i++) {
			result(0, i) = (*this)(r, i);
		}
		return result;
	}

	template <typename T, int R, int C>
	Matrix<T, R, 1> Matrix<T, R, C>::Column(int c) const
	{
		Matrix<T, R, 1> result(0);
		for (int i = 0; i < R; i++) {
			result(i, 0) = (*this)(i, c);
		}
		return result;
	}

	template <typename T, int R, int C>
	bool operator==(const Matrix<T, R, C>& lhs, const Matrix<T, R, C>& rhs)
	{
		int result = 1;
		if (lhs.m_row == rhs.m_row && lhs.m_col == rhs.m_col) {
			for (int i = 0; i < lhs.m_elements; i++) {
				if (lhs.m_data[i] == rhs.m_data[i]) {
					result = result && 1;
				}
				else
					result = result && 0;
			}
		}
		else {
			std::cout << "row and column of lhs and rhs is not same" << std::endl;
			result = 0;
		}
		return result;
	}

	template <typename T, int R, int C>
	T& Matrix<T, R, C>::operator[](int linearindex)
	{
		if (linearindex < 0)
			throw std::out_of_range("Matrix index out of bounds");
		return m_data[linearindex];
	}

	template <typename T, int R, int C>
	const T& Matrix<T, R, C>::operator[](int linearindex) const
	{
		if (linearindex < 0)
			throw std::out_of_range("Matrix index out of bounds");
		return m_data[linearindex];
	}

	template <typename T, int R, int C>
	T& Matrix<T, R, C>::operator()(int row, int col)
	{
		int linearIndex = Sub2Ind(row, col);
		if (linearIndex < 0)
			throw std::out_of_range("Matrix index out of bounds");
		return m_data[linearIndex];
	}

	template <typename T, int R, int C>
	const T& Matrix<T, R, C>::operator()(int row, int col) const
	{
		int linearIndex = Sub2Ind(row, col);
		if (linearIndex < 0)
			throw std::out_of_range("Matrix index out of bounds");
		return m_data[linearIndex];
	}

	template <typename T, int R, int C>
	std::ostream& operator<<(std::ostream& os, const Matrix<T, R, C>& m)
	{
		os << "[";
		for (int i = 0; i < m.m_row; i++) {
			os << "[";
			for (int j = 0; j < m.m_col; j++) {
				T element = m(i, j);
				if (j == m.m_col - 1)
					os << element;
				else
					os << element << ", ";
			}
			os << "]";
			if (i != m.m_row - 1)
				os << ", ";
		}
		os << "]";
		return os;
	}

	template <typename T, int R, int C>
	Matrix<T, R, C> operator+(const Matrix<T, R, C>& lhs, const Matrix<T, R, C>& rhs)
	{
		Matrix<T, R, C> result;
		if (lhs.m_row == rhs.m_row && lhs.m_col == rhs.m_col) {
			for (int i = 0; i < lhs.m_elements; i++) {
				result[i] = lhs[i] + rhs[i];
			}
		}
		else
			std::cout << "row and column of lhs and rhs is not same" << std::endl;
		return result;
	}

	template <typename T, int R, int C>
	Matrix<T, R, C> operator-(const Matrix<T, R, C>& lhs, const Matrix<T, R, C>& rhs)
	{
		Matrix<T, R, C> result;
		if (lhs.m_row == rhs.m_row && lhs.m_col == rhs.m_col) {
			for (int i = 0; i < lhs.m_elements; i++) {
				result[i] = lhs[i] - rhs[i];
			}
		}
		else
			std::cout << "row and column of lhs and rhs is not same" << std::endl;
		return result;
	}

	template <typename T, int R, int C>
	Matrix<T, R, C> operator-(const Matrix<T, R, C>& lhs)
	{
		Matrix<T, R, C> result;
		for (int i = 0; i < lhs.m_elements; i++) {
			result[i] = T(-1) * lhs[i];
		}
		return result;
	}

	template <typename T, int R, int K, int C>
	Matrix<T, R, C> operator*(const Matrix<T, R, K>& lhs, const Matrix<T, K, C>& rhs)
	{
		Matrix<T, R, C> result(T(0));
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				for (int k = 0; k < K; k++) {
					result(i, j) += lhs(i, k) * rhs(k, j);
				}
			}
		}
		return result;
	}

	template <typename T, int R, int C>
	Matrix<T, R, C> operator*(const T& lhs, const Matrix<T, R, C>& rhs) {
		Matrix<T, R, C> result;
		if (lhs == T(0))
			return result;

		for (int i = 0; i < rhs.m_elements; i++) {
			result[i] = lhs * rhs[i];
		}
		return result;
	}

	template <typename T, int R, int C>
	Matrix<T, R, C> operator*(const Matrix<T, R, C>& lhs, const T& rhs) {
		Matrix<T, R, C> result;
		if (rhs == T(0))
			return result;

		for (int i = 0; i < lhs.m_elements; i++) {
			result[i] = rhs * lhs[i];
		}
		return result;
	}

	template <typename T, int N, int C>
	Vector<T, C> operator*(const Matrix<T, C, N>& lhs, const Vector<T, N>& rhs)
	{
		Vector<T, C> result;
		for (int i = 0; i < C; i++) {
			for (int j = 0; j < N; j++) {
				result[i] += lhs(i, j) * rhs[j];
			}
		}
		return result;
	}

	template <typename T, int R, int C>
	Matrix<T, C, R> Matrix<T, R, C>::Transpose() const
	{
		Matrix<T, C, R> result(T(0));
		for (int i = 0; i < m_row; i++) {
			for (int j = 0; j < m_col; j++) {
				result(j, i) = (* this)(i, j);
			}
		}
		return result;
	}

	template <typename T, int R, int C>
	bool Matrix<T, R, C>::IsSymmetric() const
	{
		return ((* this) == (* this).Transpose());
	}

	template <typename T, int R, int C>
	bool Matrix<T, R, C>::IsSkewSymmetric() const
	{
		return ((* this) == -(* this).Transpose());
	}

	template <typename T, int R, int C>
	void Matrix<T, R, C>::Print()
	{
		std::vector<std::string> formatted;
		formatted.reserve(m_row * m_col);

		size_t maxWidth = 0;

		for (int i = 0; i < m_row; ++i)
		{
			for (int j = 0; j < m_col; ++j)
			{
				int linearIndex = Sub2Ind(i, j);
				std::ostringstream oss;
				oss << std::fixed << std::setprecision(2)
					<< m_data[linearIndex];

				std::string s = oss.str();
				maxWidth = std::max(maxWidth, s.size());
				formatted.push_back(s);
			}
		}

		for (int i = 0; i < m_row; ++i)
		{
			std::cout << "⎢ ";

			for (int j = 0; j < m_col; ++j)
			{
				std::cout << std::setw(maxWidth)
						<< formatted[i * m_col + j];

				if (j != m_col - 1)
					std::cout << " ";
			}

			std::cout << " ⎢\n";
		}
	}

	template <typename T, int R, int C>
	int Matrix<T, R, C>::Sub2Ind(int row, int col) const
	{
		if ((row < m_row) && (row >= 0) && (col < m_col) && (col >= 0)) {
			return (row * m_col) + col;
		}
		else
			return -1;
	}

}
