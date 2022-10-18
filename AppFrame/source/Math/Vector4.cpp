#include "Vector4.h"
#include "Matrix44.h"
#include <cmath>

namespace AppFrame {

	namespace Math {

		Vector4::Vector4() {
			_x = 0.0f;
			_y = 0.0f;
			_z = 0.0f;
			_w = 1.0f;
		}
		const Vector4 Vector4::operator+(const Vector4& rhs) const { 
			return Vector4(_x + rhs.GetX(), _y + rhs.GetY(), _z + rhs.GetZ());
		}
		const Vector4 Vector4::operator-(const Vector4& rhs) const	{
			return Vector4(_x - rhs.GetX(), _y - rhs.GetY(), _z - rhs.GetZ());
		}
		const Vector4 Vector4::operator*(const float rhs) const	{
			return Vector4(_x * rhs, _y * rhs, _z * rhs);
		}
		const Vector4 Vector4::operator/(const float rhs) const	{
			return Vector4(_x / rhs, _y / rhs, _z / rhs);
		}
		const Vector4 Vector4::operator*(const Matrix44& rhs) const	{
			auto mx = _x * rhs.GetValue(0, 0)
				      + _y * rhs.GetValue(1, 0)
				      + _z * rhs.GetValue(2, 0)
				      +      rhs.GetValue(3, 0);

			auto my = _x * rhs.GetValue(0, 1)
				      + _y * rhs.GetValue(1, 1)
				      + _z * rhs.GetValue(2, 1)
				      +      rhs.GetValue(3, 1);

			auto mz = _x * rhs.GetValue(0, 2)
				      + _y * rhs.GetValue(1, 2)
				      + _z * rhs.GetValue(2, 2)
				      +      rhs.GetValue(3, 2);
			
			auto mw = _x * rhs.GetValue(0, 3)
				      + _y * rhs.GetValue(1, 3)
				      + _z * rhs.GetValue(2, 3)
				      +      rhs.GetValue(3, 3);

			return Vector4(mx, my, mz, mw);
		}
		void Vector4::Set(const Vector4& vec)	{
			_x = vec.GetX();
			_y = vec.GetY();
			_z = vec.GetZ();
			_w = vec.GetW();
		}
		void Vector4::Set(const float x, const float y, const float z) {
			this->_x = x;
			this->_y = y;
			this->_z = z;
		}
		void Vector4::Add(const Vector4& vec) {
			_x += vec.GetX();
			_y += vec.GetY();
			_z += vec.GetZ();
			_w += vec.GetW();
		}
		void Vector4::Add(const float x, const float y, const float z) {
			this->_x += x;
			this->_y += y;
			this->_z += z;
		}
		const float Vector4::Length() const {
			auto length = sqrt(_x * _x + _y * _y + _z * _z);
			return length;
		}
		void Vector4::Normalized()	{
			auto length = Length();

			_x /= length;
			_y /= length;
			_z /= length;
		}
		const Vector4 Vector4::Normalize() const {
			auto length = Length();

			auto nx = _x / length;
			auto ny = _y / length;
			auto nz = _z / length;

			return Vector4(nx, ny, nz);
		}
		const float Vector4::Dot(const Vector4& rhs) const {
			auto dot = _x * rhs.GetX() + _y * rhs.GetY() + _z * rhs.GetZ();
    	return dot;
		}
		const Vector4 Vector4::Cross(const Vector4& rhs) const {
			auto cx = _y * rhs.GetZ() - _z * rhs.GetY();
			auto cy = _z * rhs.GetX() - _x * rhs.GetZ();
			auto cz = _x * rhs.GetY() - _y * rhs.GetX();

			return Vector4(cx, cy, cz);
		}
		//çsóÒÇégÇ¡ÇΩç¿ïWïœä∑
		Vector4 Vector4::Transform(const Vector4& vec, Matrix44& mat) {
			Vector4 result;
			result._x = vec.GetX() * mat.GetRowColmun()[0][0]
				+ vec.GetY() * mat.GetRowColmun()[1][0] 
				+ vec.GetZ() * mat.GetRowColmun()[2][0] 
				+ mat.GetRowColmun()[3][0];
			result._y = vec.GetX() * mat.GetRowColmun()[0][1]
				+ vec.GetY() * mat.GetRowColmun()[1][1]
				+ vec.GetZ() * mat.GetRowColmun()[2][1]
				+ mat.GetRowColmun()[3][1];
			result._z = vec.GetX() * mat.GetRowColmun()[0][2]
				+ vec.GetY() * mat.GetRowColmun()[1][2]
				+ vec.GetZ() * mat.GetRowColmun()[2][2]
				+ mat.GetRowColmun()[3][2];
			return Vector4(result);
		}
	}
}