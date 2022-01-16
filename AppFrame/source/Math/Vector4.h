
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

        Vector4& operator =(const Vector4&) = default; // コピー
        Vector4& operator =(Vector4&&) = default; // ムーブ

        const Vector4 operator +(const Vector4& rhs) const;
        const Vector4 operator -(const Vector4& rhs) const;
              
        const Vector4 operator *(const double rhs) const;
        const Vector4 operator /(const double rhs) const;
              
        const Vector4 operator *(const Matrix rhs) const;

        void Set(const Vector4& vector);
        void Set(const double x, const double y, const double z);

        void Add(const Vector4& vector);
        void Add(const double x, const double y, const double z);

        const double Getx() const { return _x; }
        const double GetY() const { return _y; }
        const double GetZ() const { return _z; }
        const double GetW() const { return _w; }

        const double Lenght() const;

        void Normalized();
        const Vector4 Normalize() const;

        const double Dot(const Vector4& rhs) const;
        const Vector4 Cross(const Vector4& rhs) const;

    private:
        double _x;
        double _y;
        double _z;
        double _w;
    };
}



