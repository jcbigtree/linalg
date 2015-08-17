#ifndef AffineTransformParams_HPP
#define AffineTransformParams_HPP

#include <iostream>
#include <stdexcept>
#include "Matrix.hpp"
#include "AffineTransformParams.hpp"

namespace numeric
{

	#define AtpType double

	//
	// Class : Affine transform parameters
	//
	class AffineTransformParams
	{        
		//
		// Note: This is NOT the composition of two transforms
		//
		friend AffineTransformParams operator+(const AffineTransformParams& lh,
											   const AffineTransformParams& rh);
	public:
		static void Add(AffineTransformParams& lh,
			            AffineTransformParams& rh,
			            AffineTransformParams& result);

	public:
		AffineTransformParams();
		AffineTransformParams(const AffineTransformParams&);
		AffineTransformParams(Matrix& linearMap, Matrix& translation);
		AffineTransformParams(AtpType m00,
							  AtpType m01,
							  AtpType m10,
							  AtpType m11,
							  AtpType dx,
							  AtpType dy);
		virtual ~AffineTransformParams();
		AffineTransformParams& operator=(const AffineTransformParams& atp);

		//
		// accessors. More convenient but probably less safer
		//
		inline Matrix& LinearMap() const
		{
			return (*m_pLinearMap);
		}

		inline Matrix& Translation() const
		{
			return (*m_pTranslation);
		}

		//
		// accessors. 
		//
		inline void SetLinearMap(Matrix& alinearmap)
		{
			if (IsThisLinearMap(alinearmap))
			{
				(*m_pLinearMap) = alinearmap;
			}
			else
			{
				throw std::invalid_argument("A linear map must be a 2*2 matrix.");
			}
		}

		inline const Matrix& GetLinearMap() const
		{
			return (*m_pLinearMap);
		}

		inline void SetTranslation(Matrix& atranslation)
		{
			if (IsThisTranslation(atranslation))
			{
				(*m_pTranslation) = atranslation;
			}
			else
			{
				throw std::invalid_argument("A translation must be a 2*1 matrix.");
			}
		}

		inline const Matrix& GetTranslation() const
		{
			return (*m_pTranslation);
		}

	protected:
		virtual void AllocMemory();
		virtual void ReleaseMemory();

		static bool IsThisLinearMap(Matrix& mat);
		static bool IsThisTranslation(Matrix& mat);

	private:
		Matrix* m_pLinearMap;
		Matrix* m_pTranslation;
	};	
}

#endif
