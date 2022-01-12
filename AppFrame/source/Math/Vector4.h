
/*****************************************************************//**
 * @file   Vector4.h
 * @brief  
 * 
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/
#pragma once

namespace AppFrame {
	
	class Matrix;

	class Vector4{
	public:
		Vector4();
		Vector4(const double x, const double y, const double z) : _x{ x }, _y{ y }, _z{ z }, _w{ 1.0 } {};
		Vector4(const double x, const double y, const double z, double w) : _x{ x }, _y{ y }, _z{ z }, _w{ w } {};
		Vector4(const Vector4&) = default;
		Vector4(Vector4&&) = default;

		virtual ~Vector4() = default;


	private:
		double _x;
		double _y;
		double _z;
		double _w;
	};
}



