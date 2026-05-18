namespace Nullspace {
	template <typename T, int R, int C>
	Matrix<T, R, C>::Matrix()
	{
		m_nrow = 1;
		m_ncol = 1;
		m_nElements = 1;

		m_matrixData = std::vector<T>(m_nElements);
		m_matrixData[0] = T(0);
	}

	template <typename T, int R, int C>
	Matrix<T, R, C>::Matrix(int nrow, int ncol)
	{
		m_nrow = nrow;
		m_ncol = ncol;
		m_nElements = nrow * ncol;

		m_matrixData = std::vector<T>(m_nElements);
		for (int i = 0; i < m_nElements; i++)
			m_matrixData[i] = T(0);
	}

	template <typename T, int R, int C>
	Matrix<T, R, C>::Matrix(int nrow, int ncol, const T *data)
	{
		m_nrow = nrow;
		m_ncol = ncol;
		m_nElements = nrow * ncol;

		m_matrixData = std::vector<T>(m_nElements);
		for (int i = 0; i < m_nElements; i++)
			m_matrixData[i] = data[i];
	}

	template <typename T, int R, int C>
	Matrix<T, R, C>::Matrix(const Matrix<T, R, C>& inputMatrix)
	{
		m_nrow = inputMatrix.m_nrow;
		m_ncol = inputMatrix.m_ncol;
		m_nElements = m_nrow * m_ncol;
		m_matrixData = std::vector<T>(m_nElements);

		for (int i = 0; i < m_nElements; i++)
			m_matrixData[i] = inputMatrix.m_matrixData[i];

	}

	template <typename T, int R, int C>
	Matrix<T, R, C>::Matrix(int nrow, int ncol, std::initializer_list<T> list)
	{
		m_nrow = nrow;
		m_ncol = ncol;
		m_nElements = nrow * ncol;
		m_matrixData = std::vector<T>(m_nElements);

		int i = 0;
		for (auto& val : list) {
			if (i < m_nElements)
				m_matrixData[i++] = val;
			else
				break;
		}
		for (; i < m_nElements; i++) {
			m_matrixData[i] = T(0);
		}
	}

	template <typename T, int R, int C>
	Matrix<T, R, C>::Matrix(T num)
	{
		m_matrixData = std::vector<T>(m_nElements);
		for (int i = 0; i < m_nrow; i++) {
			for (int j = 0; j < m_ncol; j++) {
				int linearIndex = Sub2Ind(i, j);
				// if (i == j)
				m_matrixData[linearIndex] = T(num);
			}
		}
	}

	template <typename T, int R, int C>
	Matrix<T, R, C>::Matrix(std::initializer_list<T> list)
	{
		m_matrixData = std::vector<T>(m_nElements);
		int i = 0;
		for (auto& val : list) {
			if (i < m_nElements)
				m_matrixData[i++] = val;
			else
				break;
		}
		for (; i < m_nElements; i++) {
			m_matrixData[i] = T(0);
		}
	}

	template <typename T, int R, int C>
	Matrix<T, R, C>::~Matrix()
	{
	}

	template <typename T, int R, int C>
	bool Matrix<T, R, C>::Resize(int nrow, int ncol)
	{
		m_nrow = nrow;
		m_ncol = ncol;
		m_nElements = m_nrow * m_ncol;

		m_matrixData.resize(m_nElements);
		return true;
	}

	template <typename T, int R, int C>
	T Matrix<T, R, C>::GetElement(int row, int col) const
	{
		int linearIndex = Sub2Ind(row, col);
		if (linearIndex >= 0)
			return m_matrixData[linearIndex];
		return T{};
	}

	template <typename T, int R, int C>
	bool Matrix<T, R, C>::SetElement(int row, int col, T elementValue)
	{
		int linearIndex = Sub2Ind(row, col);
		if (row >= m_nrow || col >= m_ncol) {
			return false;
		}
		m_matrixData[linearIndex] = elementValue;
		return true;
	}

	template <typename T, int R, int C>
	int Matrix<T, R, C>::GetNumRows() const
	{
		return m_nrow;
	}

	template <typename T, int R, int C>
	int Matrix<T, R, C>::GetNumCols() const
	{
		return m_ncol;
	}

	template <typename T, int R, int C>
	const Matrix<T, R, C> Matrix<T, R, C>::Identity()
	{
		if (R != C)
			throw std::out_of_range("Row and Column are not equal");
		Matrix<T, R, C> result(0);
		for (int i = 0; i < result.m_nrow; i++) {
			for (int j = 0; j < result.m_ncol; j++) {
				int linearIndex = result.Sub2Ind(i, j);
				if (i == j)
					result.m_matrixData[linearIndex] = T(1);
			}
		}
		return result;
	}

	template <typename T, int R, int C>
	const Matrix<T, R, C> Matrix<T, R, C>::Constant(T constant)
	{
		Matrix<T, R, C> result(0);
		for (int i = 0; i < result.m_nElements; i++) {
				result.m_matrixData[i] = constant;
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
		if (lhs.m_nrow == rhs.m_nrow && lhs.m_ncol == rhs.m_ncol) {
			for (int i = 0; i < lhs.m_nElements; i++) {
				if (lhs.m_matrixData[i] == rhs.m_matrixData[i]) {
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
	T& Matrix<T, R, C>::operator()(int nrow, int ncol)
	{
		int linearIndex = Sub2Ind(nrow, ncol);
		if (linearIndex < 0)
			throw std::out_of_range("Matrix index out of bounds");
		return m_matrixData[linearIndex];
	}

	template <typename T, int R, int C>
	const T& Matrix<T, R, C>::operator()(int nrow, int ncol) const
	{
		int linearIndex = Sub2Ind(nrow, ncol);
		if (linearIndex < 0)
			throw std::out_of_range("Matrix index out of bounds");
		return m_matrixData[linearIndex];
	}

	template <typename T, int R, int C>
	std::ostream& operator<<(std::ostream& os, const Matrix<T, R, C>& m)
	{
		os << "[";
		for (int i = 0; i < m.m_nrow; i++) {
			os << "[";
			for (int j = 0; j < m.m_ncol; j++) {
				T element = m.GetElement(i, j);
				if (j == m.m_ncol - 1)
					os << element;
				else
					os << element << ", ";
			}
			os << "]";
			if (i != m.m_nrow - 1)
				os << ", ";
		}
		os << "]";
		return os;
	}

	template <typename T, int R, int C>
	Matrix<T, R, C> operator+(const Matrix<T, R, C>& lhs, const Matrix<T, R, C>& rhs)
	{
		Matrix<T, R, C> result(lhs.m_nrow, lhs.m_ncol);
		if (lhs.m_nrow == rhs.m_nrow && lhs.m_ncol == rhs.m_ncol) {
			for (int i = 0; i < lhs.m_nElements; i++) {
				result.m_matrixData[i] = lhs.m_matrixData[i] + rhs.m_matrixData[i];
			}
		}
		else
			std::cout << "row and column of lhs and rhs is not same" << std::endl;
		return result;
	}

	template <typename T, int R, int C>
	Matrix<T, R, C> operator-(const Matrix<T, R, C>& lhs, const Matrix<T, R, C>& rhs)
	{
		Matrix<T, R, C> result(lhs.m_nrow, lhs.m_ncol);
		if (lhs.m_nrow == rhs.m_nrow && lhs.m_ncol == rhs.m_ncol) {
			for (int i = 0; i < lhs.m_nElements; i++) {
				result.m_matrixData[i] = lhs.m_matrixData[i] - rhs.m_matrixData[i];
			}
		}
		else
			std::cout << "row and column of lhs and rhs is not same" << std::endl;
		return result;
	}

	template <typename T, int R, int C>
	Matrix<T, R, C> operator-(const Matrix<T, R, C>& lhs)
	{
		Matrix<T, R, C> result(lhs.m_nrow, lhs.m_ncol);
		for (int i = 0; i < lhs.m_nElements; i++) {
			result.m_matrixData[i] = T(-1) * lhs.m_matrixData[i];
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
		Matrix<T, R, C> result(rhs.m_nrow, rhs.m_ncol);
		if (lhs == T(0))
			return result;

		for (int i = 0; i < rhs.m_nElements; i++) {
			result.m_matrixData[i] = lhs * rhs.m_matrixData[i];
		}
		return result;
	}

	template <typename T, int R, int C>
	Matrix<T, R, C> operator*(const Matrix<T, R, C>& lhs, const T& rhs) {
		Matrix<T, R, C> result(lhs.m_nrow, lhs.m_ncol);
		if (rhs == T(0))
			return result;

		for (int i = 0; i < lhs.m_nElements; i++) {
			result.m_matrixData[i] = rhs * lhs.m_matrixData[i];
		}
		return result;
	}

	template <typename T, int R, int C>
	void Matrix<T, R, C>::Print()
	{
		std::vector<std::string> formatted;
		formatted.reserve(m_nrow * m_ncol);

		size_t maxWidth = 0;

		for (int i = 0; i < m_nrow; ++i)
		{
			for (int j = 0; j < m_ncol; ++j)
			{
				int linearIndex = Sub2Ind(i, j);
				std::ostringstream oss;
				oss << std::fixed << std::setprecision(2)
					<< m_matrixData[linearIndex];

				std::string s = oss.str();
				maxWidth = std::max(maxWidth, s.size());
				formatted.push_back(s);
			}
		}

		for (int i = 0; i < m_nrow; ++i)
		{
			std::cout << "⎢ ";

			for (int j = 0; j < m_ncol; ++j)
			{
				std::cout << std::setw(maxWidth)
						<< formatted[i * m_ncol + j];

				if (j != m_ncol - 1)
					std::cout << " ";
			}

			std::cout << " ⎢\n";
		}
	}

	template <typename T, int R, int C>
	int Matrix<T, R, C>::Sub2Ind(int row, int col) const
	{
		if ((row < m_nrow) && (row >= 0) && (col < m_ncol) && (col >= 0)) {
			return (row * m_ncol) + col;
		}
		else
			return -1;
	}

}
