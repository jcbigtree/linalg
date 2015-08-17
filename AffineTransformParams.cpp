#include "AffineTransformParams.hpp"

using namespace numeric;

///////////////////////////////////////////////////////////////////////////////////////////////////
//Implementation of AffineTransformParams
///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Friend function. Note that this implementation is practical only when AffineTransformParams is 
// small so that the copy constructor won't cost too much time. 
//
AffineTransformParams numeric::operator + (const AffineTransformParams& lh,
	                                       const AffineTransformParams& rh)
{
	//
	// Sanity check
	//	
	Matrix linearmap = lh.LinearMap() + rh.LinearMap();
	Matrix translation = lh.Translation() + rh.Translation();
	AffineTransformParams sumAtp(linearmap, translation);
	return sumAtp;
}


//
// Member functions 
//
void AffineTransformParams::Add(AffineTransformParams& lh,
	                            AffineTransformParams& rh,
                                AffineTransformParams& result)
{
	result.SetLinearMap(lh.LinearMap() + rh.LinearMap());
	result.SetTranslation(lh.Translation() + rh.Translation());
}


AffineTransformParams::AffineTransformParams()
{
	m_pLinearMap = 0;
	m_pTranslation = 0;
	this->AllocMemory();
}

AffineTransformParams::AffineTransformParams(Matrix& linearMap, Matrix& translation)
{
	//
	// Sanity check
	//
	if (!IsThisLinearMap(linearMap) || !IsThisTranslation(translation))
	{
		throw std::invalid_argument("Not proper linear maps or translation");
	}

	//
	// Copy values instead of passing inferences.
	//
	this->AllocMemory();
	(*m_pLinearMap) = linearMap;
	(*m_pTranslation) = translation;
}

AffineTransformParams::AffineTransformParams(AtpType m00,
											 AtpType m01,
											 AtpType m10,
											 AtpType m11,
											 AtpType dx,
											 AtpType dy)
{
	this->AllocMemory();
	(*m_pLinearMap)(0, 0) = m00;
	(*m_pLinearMap)(0, 1) = m01;
	(*m_pLinearMap)(1, 0) = m10;
	(*m_pLinearMap)(1, 1) = m11;
	(*m_pTranslation)(0, 0) = dx;
	(*m_pTranslation)(1, 0) = dy;
}


AffineTransformParams::AffineTransformParams(const AffineTransformParams& atp)
{
	this->AllocMemory();
	(*m_pLinearMap) = atp.LinearMap();
	(*m_pTranslation) = atp.Translation();
}


AffineTransformParams::~AffineTransformParams()
{
	this->ReleaseMemory();
}


void AffineTransformParams::AllocMemory()
{
	try
	{
		m_pLinearMap = new Matrix(2, 2);
		m_pTranslation = new Matrix(2, 1);
	}
	catch (std::bad_alloc& exc)
	{
		this->ReleaseMemory();
		//throw std::bad_alloc("AffineTransformParams::AllocMemory Failed");
		throw exc;
	}
}

void AffineTransformParams::ReleaseMemory()
{
	delete m_pLinearMap;
	delete m_pTranslation;
}


bool AffineTransformParams::IsThisLinearMap(Matrix& mat)
{
	if (mat.Rows() == 2 && mat.Cols() == 2)
	{
		return true;
	}
	return false;
}

bool AffineTransformParams::IsThisTranslation(Matrix& mat)
{
	if (mat.Rows() == 2 && mat.Cols() == 1)
	{
		return true;
	}
	return false;
}


AffineTransformParams& AffineTransformParams::operator = (const AffineTransformParams& atp)
{
	(*m_pLinearMap) = atp.LinearMap();
	(*m_pTranslation) = atp.Translation();
	return (*this);
}
