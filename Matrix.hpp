#ifndef Numeric_Matrix_HPP
#define Numeric_Matrix_HPP

#include <iostream>
#include <stdexcept>

namespace numeric
{
	//
	// Define the matrix element type. Alternatively, we may use template.
	//
	#define ElemType double

	//
	// Class : A light-weight matrix class. 
	// 
	// Warning : When a set of matrices are needed, std::vector<Matrix> or 
	//           std::vector<Matrix*> is recommended. 
	//
	class Matrix
	{
		//
		// WARNING: Performance might be unacceptable when matrices are very large.
		//
		friend Matrix operator+(const Matrix& lhmat, const Matrix& rhmat);
		friend Matrix operator*(const Matrix& lhmat, const Matrix& rhmat);
		friend Matrix operator*(const ElemType  lhd, const Matrix& rhmat);
		friend Matrix operator*(const Matrix& lhmat, const ElemType  rhd);
	public:
		//
		// Better performance.
		//
		static void DotMul(const Matrix& lhmat, const Matrix& rhmat, Matrix& result);
		static void Mul(const Matrix& lhmat, const Matrix& rhmat, Matrix& result);
		static void Mul(const Matrix& mat, const ElemType  s, Matrix& result);
		static void Add(const Matrix& lhmat, const Matrix& rhmat, Matrix& result);
		static void Sub(const Matrix& lhmat, const Matrix& rhmat, Matrix& result);

		static void Zero(Matrix& mat);
		static void Ones(Matrix& mat);

		static ElemType Max(Matrix& mat);
		static ElemType Min(Matrix& mat);

	public:
		Matrix();
		Matrix(const unsigned int rows, const unsigned int cols);
		Matrix(const Matrix& mat);
		virtual ~Matrix();

		const Matrix& operator=(const Matrix& mat);
		ElemType&     operator()(const unsigned int row, const unsigned int col);

		unsigned int Rows()     const;
		unsigned int Cols()     const;
		unsigned int Capacity() const;
		void         Clear();

		ElemType GetElemAt(const unsigned int row, const unsigned int col) const;
		void   SetElemAt(const unsigned int row, const unsigned int col, const ElemType value);

	public:
		//
		// For debugging
		//
		void PrintOut() const;

	private:
		unsigned int m_rows;
		unsigned int m_cols;
		unsigned int m_capacity;
		ElemType*    m_elements;
	};
}
#endif 


