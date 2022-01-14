
/*****************************************************************//**
 * @file   Utility.h
 * @brief  
 * 
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/
#pragma once
#include <tuple>
#include <DxLib.h>

namespace AppFrame {

	class Vector4;

	using plane = std::tuple<Vector4/*point*/, Vector4/*normal*/>;
	using collision = std::tuple<bool, Vector4>;

	class Utility {
	public:
		static constexpr double Degrees180 = 180.0;

		static double DegreeToRadian(double degree) {
			return degree * DX_PI / Degrees180;
		}

		static double RadianToDegree(double radion) {
			return radion * Degrees180 / DX_PI;
		}

		static int GetRandom(const int min, const int max);
		static bool GetRandom() {
			return GetRandom(1, 2) == 1 ? true : false;
		}
	private:
		Utility() = default;
	};
}


