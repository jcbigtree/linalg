
#include "Matrix.hpp"
#include <iostream>
#include <stdexcept>

using namespace numeric;

///////////////////////////////////////////////////////////////////////////////////////////////////
//Implementation of Matrix
///////////////////////////////////////////////////////////////////////////////////////////////////

Matrix numeric::operator+(const Matrix& lhmat, const Matrix& rhmat)
{
	// Guardian 
	if (lhmat.Rows() != rhmat.Rows() || lhmat.Cols() != rhmat.Cols())
	{
		throw std::invalid_argument(
			"Dimension mismatch"
			);
	}

	int m = lhmat.Rows();
	int n = lhmat.Cols();
	int l = rhmat.Cols();

	Matrix resultMat(m, l);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < l; j++)
		{
			ElemType lval = lhmat.GetElemAt(i, j);
			ElemType rval = rhmat.GetElemAt(i, j);
			resultMat.SetElemAt(i, j, lval + rval);
		}
	}
	return resultMat;
}

Matrix numeric::operator*(const Matrix& lhmat, const Matrix& rhmat)
{
	// Guardian 
	if (lhmat.Cols() != rhmat.Rows())
	{
		throw std::invalid_argument(
			"Dimension mismatch"
			);
	}

	int m = lhmat.Rows();
	int n = lhmat.Cols();
	int l = rhmat.Cols();

	Matrix resultMat(m, l);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < l; j++)
		{
			ElemType sum = 0;
			for (int k = 0; k < n; k++)
			{
				sum += (lhmat.GetElemAt(i, k) * rhmat.GetElemAt(k, j));
			}
			resultMat.SetElemAt(i, j, sum);
		}
	}
	return resultMat;
}

Matrix numeric::operator*(const ElemType lhd, const Matrix& rhmat)
{
	int m = rhmat.Rows();
	int n = rhmat.Cols();
	Matrix resultMat(m, n);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			ElemType value = rhmat.GetElemAt(i, j);
			resultMat.SetElemAt(i, j, lhd * value);
		}
	}
	return resultMat;
}

Matrix numeric::operator*(const Matrix& lhmat, const ElemType rhd)
{
	return (rhd * lhmat);
}


/// \brief       Element-wise multiplication of two matrices.
/// \param[in]   lhmat. Matrix.
/// \param[in]   rhmat. Matrix.
/// \param[out]  resultMat. Matrix.
void Matrix::DotMul(const Matrix& lhmat, const Matrix& rhmat, Matrix& resultMat)
{
	if (lhmat.Rows() != rhmat.Rows() ||
		lhmat.Cols() != rhmat.Cols() ||
		resultMat.Rows() != lhmat.Rows() ||
		resultMat.Cols() != rhmat.Cols())
	{
		throw std::invalid_argument(
			"Dimension mismatch"
			);
	}

	int m = lhmat.Rows();
	int n = lhmat.Cols();

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			ElemType val = lhmat.GetElemAt(i, j) * rhmat.GetElemAt(i, j);
			resultMat.SetElemAt(i, j, val);
		}
	}
}


/// \brief       Matrix multiplication of two matrices.
/// \param[in]   lhmat. Matrix.
/// \param[in]   rhmat. Matrix.
/// \param[out]  resultMat. Matrix.
void Matrix::Mul(const Matrix& lhmat, const Matrix& rhmat, Matrix& resultMat)
{
	if (lhmat.Cols() != rhmat.Rows() ||
		resultMat.Rows() != lhmat.Rows() ||
		resultMat.Cols() != rhmat.Cols())
	{
		throw std::invalid_argument(
			"Dimension mismatch"
			);
	}

	int m = lhmat.Rows();
	int n = lhmat.Cols();
	int l = rhmat.Cols();

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < l; j++)
		{
			ElemType sum = 0;
			for (int k = 0; k < n; k++)
			{
				sum += (lhmat.GetElemAt(i, k) * rhmat.GetElemAt(k, j));
			}
			resultMat.SetElemAt(i, j, sum);
		}
	}
}


/// \brief       Multiply a matrix with a scalar.
/// \param[in]   lhmat. Matrix.
/// \param[in]   s. a scalar.
/// \param[out]  resultMat. Matrix.
void Matrix::Mul(const Matrix& mat, const ElemType s, Matrix& result)
{
	int m = mat.Rows();
	int n = mat.Cols();
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			ElemType value = mat.GetElemAt(i, j);
			result.SetElemAt(i, j, s * value);
		}
	}
}


/// \brief       Add two matrices.
/// \param[in]   lhmat. Matrix.
/// \param[in]   rhmat. Matrix.
/// \param[out]  result. Matrix.
void Matrix::Add(const Matrix& lhmat, const Matrix& rhmat, Matrix& result)
{
	// Guardian 
	if (lhmat.Rows() != rhmat.Rows() ||
		lhmat.Cols() != rhmat.Cols())
	{
		throw std::invalid_argument(
			"Dimension mismatch"
			);
	}

	int m = lhmat.Rows();
	int n = lhmat.Cols();
	int l = rhmat.Cols();

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < l; j++)
		{
			ElemType lval = lhmat.GetElemAt(i, j);
			ElemType rval = rhmat.GetElemAt(i, j);
			result.SetElemAt(i, j, lval + rval);
		}
	}
}


/// \brief       Matrix subtraction.
/// \param[in]   lhmat. Matrix.
/// \param[in]   rhmat. Matrix.
/// \param[out]  result. Matrix.
void Matrix::Sub(const Matrix& lhmat, const Matrix& rhmat, Matrix& result)
{
	// Guardian 
	if (lhmat.Rows() != rhmat.Rows() || lhmat.Cols() != rhmat.Cols())
	{
		throw std::invalid_argument(
			"Dimension mismatch"
			);
	}

	int m = lhmat.Rows();
	int n = lhmat.Cols();
	int l = rhmat.Cols();

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < l; j++)
		{
			ElemType lval = lhmat.GetElemAt(i, j);
			ElemType rval = rhmat.GetElemAt(i, j);
			result.SetElemAt(i, j, lval - rval);
		}
	}
}

/// \brief          Set all the elements of a matrix to zero.
/// \param[in,out]  mat. Matrix.
void Matrix::Zero(Matrix& mat)
{
	int m = mat.Rows();
	int n = mat.Cols();
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			mat.SetElemAt(i, j, 0);
		}
	}
}


/// \brief          Set all the elements of a matrix to one.
/// \param[in,out]  mat. Matrix.
void Matrix::Ones(Matrix& mat)
{
	int m = mat.Rows();
	int n = mat.Cols();
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			mat.SetElemAt(i, j, 1);
		}
	}
}


/// \brief      Find the maximum of the elements of a matrix.
/// \param[in]  mat. Matrix.
/// \return     the maximum element.
ElemType Matrix::Max(Matrix& mat)
{
	ElemType maxVal = -DBL_MAX;
	int rows = mat.Rows();
	int cols = mat.Cols();
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			ElemType val = mat.GetElemAt(i, j);
			maxVal = val > maxVal ? val : maxVal;
		}
	}
	return maxVal;
}


/// \brief Find the minimum of the elements of a matrix.
/// \param[in]  mat. Matrix.
/// \return     the minimum element.
ElemType Matrix::Min(Matrix& mat)
{
	ElemType minVal = DBL_MAX;
	int rows = mat.Rows();
	int cols = mat.Cols();
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			ElemType val = mat.GetElemAt(i, j);
			minVal = val < minVal ? val : minVal;
		}
	}
	return minVal;
}


Matrix::Matrix()
{
	m_rows = 0;
	m_cols = 0;
	m_elements = NULL;
	m_capacity = 1e5;
}


Matrix::~Matrix()
{
	Clear();
}


Matrix::Matrix(const unsigned int rows, const unsigned int cols)
{
	if (rows <= 0 || cols <= 0)
	{
		throw std::invalid_argument(
			"Rows and cols cann't be smaller than one."
			);
	}
	m_rows = rows;
	m_cols = cols;
	m_elements = new ElemType[m_rows * m_cols];
}


Matrix::Matrix(const Matrix& mat)
{
	m_rows = mat.m_rows;
	m_cols = mat.m_cols;
	m_elements = new ElemType[m_rows * m_cols];
	for (unsigned int i = 0; i < m_rows; i++)
	{
		for (unsigned int j = 0; j < m_cols; j++)
		{
			ElemType value = mat.GetElemAt(i, j);
			SetElemAt(i, j, value);
		}
	}
}


const Matrix& Matrix::operator=(const Matrix& mat)
{
	if (this->Cols() != mat.Cols() || this->Rows() != mat.Rows())
	{
		throw std::invalid_argument(
			"Dimension mismatch"
			);
	}

	unsigned int m = mat.Rows();
	unsigned int n = mat.Cols();

	for (unsigned int i = 0; i < m; i++)
	{
		for (unsigned int j = 0; j < n; j++)
		{
			ElemType value = mat.GetElemAt(i, j);
			this->SetElemAt(i, j, value);
		}
	}
	return *this;
}


ElemType& Matrix::operator()(const unsigned int row, const unsigned int col)
{
	if (row >= m_rows || col >= m_cols)
	{
		throw std::out_of_range("Out of Range");
	}
	return m_elements[row * m_cols + col];
}


/// \brief  Return the number of rows
/// \return Number of rows	
unsigned int Matrix::Rows() const
{
	return m_rows;
}


/// \brief  Return the number of columns
/// \return Number of columns 
unsigned int Matrix::Cols() const
{
	return m_cols;
}


/// \brief  Return the size of the storage space currently allocated for the matrix.
/// \return Size of the storage space currently allocated for the matrix. 
unsigned int Matrix::Capacity() const
{
	return m_capacity;
}


/// \brief     Return the (i,j) element.
/// \param[in] row. 
/// \param[in] col.
/// \return    The (i,j) element
ElemType Matrix::GetElemAt(const unsigned int row, const unsigned int col) const
{
	if (row >= m_rows || col >= m_cols)
	{
		throw std::out_of_range("Out of Range");
	}
	return m_elements[row * m_cols + col];
}


/// \brief     Set the (i,j) element.
/// \param[in] row. 
/// \param[in] col.
/// \param[in] value.
void Matrix::SetElemAt(const unsigned int row, const unsigned int col, const ElemType value)
{
	if (row >= m_rows || col >= m_cols)
	{
		throw std::out_of_range("Out of Range");
	}
	m_elements[row * m_cols + col] = value;
}


/// \brief Clear the memory.
void Matrix::Clear()
{
	delete[] m_elements;
	m_elements = NULL;
}

/// \brief Print the elements of the matrix. This is mainly for debugging.
void Matrix::PrintOut() const
{
	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < m_cols; j++)
		{
			std::cout << GetElemAt(i, j) << " ";
		}
		std::cout << std::endl;
	}
}

