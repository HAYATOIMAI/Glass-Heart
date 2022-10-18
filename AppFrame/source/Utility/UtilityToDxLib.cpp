#include "UtilityToDxLib.h"
#include "../Math/Matrix44.h"
#include "../Math/Vector4.h"
#include <utility>

namespace AppFrame {

	namespace Utility {

		VECTOR ToDx(AppFrame::Math::Vector4& vec) {
			return VGet(vec.GetX(), vec.GetY(), vec.GetZ());
		}
		AppFrame::Math::Vector4 ToMath(VECTOR& vec) {
			return AppFrame::Math::Vector4(vec.x, vec.y, vec.z);
		}
		MATRIX ToDx(AppFrame::Math::Matrix44& matrix) {
			MATRIX ret;

			for (auto i = 0; i < AppFrame::Math::RowMax; ++i) {
				for (auto j = 0; j < AppFrame::Math::ColumnMax; ++j)	{
					ret.m[i][j] = matrix.GetValue(i, j);
				}
			}
			return  ret;
		}
		AppFrame::Math::Matrix44 ToMath(MATRIX& matrix) {
			AppFrame::Math::Matrix44 ret;

			for (auto i = 0; i < AppFrame::Math::RowMax; ++i) {
				for (auto j = 0; j < AppFrame::Math::ColumnMax; ++j) {
					ret.SetValue(i,j, matrix.m[i][j]);
				}
			}
			return  ret;
		}
	}
}