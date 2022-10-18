#pragma once
#include <DxLib.h>

struct tagVECTOR;
struct tagMATRIX;

namespace AppFrame::Math {
	class Vector4;
	class Matrix44;
}

namespace AppFrame {

	namespace Utility {

		VECTOR ToDx(AppFrame::Math::Vector4& vec);

		AppFrame::Math::Vector4 ToMath(VECTOR& vec);

		MATRIX ToDx(AppFrame::Math::Matrix44& matrix);

		AppFrame::Math::Matrix44 ToMath(MATRIX& matrix);
	}
}