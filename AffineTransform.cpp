#include "AffineTransform.hpp"
#include <stdexcept>


using namespace std;
using namespace numeric;

///////////////////////////////////////////////////////////////////////////////////////////////////
//Implementation of Functions
///////////////////////////////////////////////////////////////////////////////////////////////////
void numeric::AffineTransform(AffineTransformParams& atp, Matrix& p, Matrix& trans_p)
{
	//
	// Sanity check. Assume that the atp is OK
	//
	if (!(p.Rows() == 2 && p.Cols() == 1 && trans_p.Rows() == 2 && trans_p.Cols() == 1))
	{
		throw std::invalid_argument("Points must be 2*1 matrices.");
	}

	trans_p = atp.LinearMap()*p + atp.Translation();
}


//
// Note: If the class Matrix contains a matrix inverse method, the implementation of the following
// function would be straightforward. 
//
bool numeric::InverseAffineTransform(AffineTransformParams& atp, AffineTransformParams& inv_atp)
{
	//
	// Sanity check. Assume that both atps are OK.
	//

	double val = atp.LinearMap()(0, 0)*atp.LinearMap()(1, 1) -
		atp.LinearMap()(0, 1)*atp.LinearMap()(1, 0);

	if (std::abs(val) < 1e-20)
	{
		return false;
	}

	inv_atp.LinearMap()(0, 0) = atp.LinearMap()(1, 1) / val;
	inv_atp.LinearMap()(0, 1) = -atp.LinearMap()(0, 1) / val;
	inv_atp.LinearMap()(1, 0) = -atp.LinearMap()(1, 0) / val;
	inv_atp.LinearMap()(1, 1) = atp.LinearMap()(0, 0) / val;

	inv_atp.Translation()(0, 0) = -atp.Translation()(0, 0)*inv_atp.LinearMap()(0, 0)
		- atp.Translation()(1, 0)*inv_atp.LinearMap()(0, 1);
	inv_atp.Translation()(1, 0) = -atp.Translation()(0, 0)*inv_atp.LinearMap()(1, 0)
		- atp.Translation()(1, 0)*inv_atp.LinearMap()(1, 1);
	return true;
}

void numeric::CombineAffineTransform(AffineTransformParams& atp0,
	                             AffineTransformParams& atp1,
	                             AffineTransformParams& atp01)
{
	//
	// Sanity check.
	//
	atp01.LinearMap() = atp1.LinearMap() * atp0.LinearMap();
	atp01.Translation() = atp1.Translation() + atp1.LinearMap()*atp0.Translation();
}



