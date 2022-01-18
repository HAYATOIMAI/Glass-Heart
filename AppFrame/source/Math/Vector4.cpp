
/*****************************************************************//**
 * @file   Vector4.cpp
 * @brief  
 * 
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/
#include "Vector4.h"
#include "Matrix.h"
#include <cmath>

namespace AppFrame::Math {
    /** コンストラクタ */
    Vector4::Vector4() {
        _x = 0.0;
        _y = 0.0;
        _z = 0.0;
        _w = 1.0;
    }
    const Vector4 Vector4::operator+(const Vector4& rhs) const {
        return Vector4(_x + rhs.Getx(), _y + rhs.GetY(), _z + rhs.GetZ());
    }
    const Vector4 Vector4::operator-(const Vector4& rhs) const {
        return Vector4(_x - rhs.Getx(), _y - rhs.GetY(), _z - rhs.GetZ());
    }
    const Vector4 Vector4::operator*(const double rhs) const {
        return Vector4(_x * rhs, _y * rhs, _z * rhs);
    }
    const Vector4 Vector4::operator/(const double rhs) const {
        return Vector4(_x / rhs, _y / rhs, _z / rhs);
    }
    const Vector4 Vector4::operator*(const Matrix rhs) const {

        auto mx = _x * rhs.GetValue(0, 0)
                + _y * rhs.GetValue(1, 0)
                + _z * rhs.GetValue(2, 0)
                + rhs.GetValue(3, 0);

        auto my = _x * rhs.GetValue(0, 1)
                + _y * rhs.GetValue(1, 1)
                + _z * rhs.GetValue(2, 1)
                + rhs.GetValue(3, 1);

        auto mz = _x * rhs.GetValue(0, 2)
                + _y * rhs.GetValue(1, 2)
                + _z * rhs.GetValue(2, 2)
                + rhs.GetValue(3, 2);

        auto mw = _x * rhs.GetValue(0, 3)
                + _y * rhs.GetValue(1, 3)
                + _z * rhs.GetValue(2, 3)
                + rhs.GetValue(3, 3);

        return Vector4(mx, my, mz, mw);
    }
    void Vector4::Set(const Vector4& vector) {
        _x = vector.Getx();
        _y = vector.GetY();
        _z = vector.GetZ();
        _w = vector.GetW();
    }
    void Vector4::Set(const double x, const double y, const double z) {
        this->_x = x;
        this->_y = y;
        this->_z = z;
    }
    void Vector4::Add(const Vector4& vector) {
        _x += vector.Getx();
        _y += vector.GetY();
        _z += vector.GetZ();
    }
    void Vector4::Add(const double x, const double y, const double z) {
        this->_x += x;
        this->_y += y;
        this->_z += z;
    }
    const double Vector4::Lenght() const {
        return sqrt(_x * _x + _y * _y + _z * _z);
    }
    void Vector4::Normalized() {
        auto len = Lenght();

        _x /= len;
        _y /= len;
        _z /= len;
    }
    const Vector4 Vector4::Normalize() const {

        auto len = Lenght();

        auto nx = _x / len;
        auto ny = _y / len;
        auto nz = _z / len;

        return Vector4(nx, ny, nz);
    }
    const double Vector4::Dot(const Vector4& rhs) const {
        return _x * rhs.Getx() + _y * rhs.GetY() + _z * rhs.GetZ();
    }
    const Vector4 Vector4::Cross(const Vector4& rhs) const {

        auto cx = _y * rhs.GetZ() - _z * rhs.GetY();
        auto cy = _z * rhs.Getx() - _x * rhs.GetZ();
        auto cz = _x * rhs.GetY() - _y * rhs.Getx();

        return Vector4();
    }
}
