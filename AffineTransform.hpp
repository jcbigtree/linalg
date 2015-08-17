#ifndef AffineTransform_Hpp
#define AffineTransform_Hpp

#include "Matrix.hpp"
#include "AffineTransformParams.hpp"

namespace numeric
{
	//
	// Function : Apply affine transform
	//
	void AffineTransform(AffineTransformParams& atp, Matrix& p, Matrix& trans_p);

	//
	// Function : Inverse an affine transform
	//
	bool InverseAffineTransform(AffineTransformParams& atp, AffineTransformParams& inv_atp);

	//
	// Function : Compose two affine transforms
	//      trans_point = atp1( atp0( point ) )
	//      trans_point = atp01( point )
	//
	void CombineAffineTransform(AffineTransformParams& atp0,
		                    AffineTransformParams& atp1,
		                    AffineTransformParams& atp01);
}

#endif 

