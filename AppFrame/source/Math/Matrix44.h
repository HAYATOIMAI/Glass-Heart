/*****************************************************************//**
 * @file   Matrix4Å~4.h
 * @brief  
 * 
 * @author HAYATO IMAI
 * @date   August 2022
 *********************************************************************/
#pragma once
#include <array>
#include <tuple>
#include <cstdint>

namespace AppFrame {

  namespace Math {
    class Vector4;
    constexpr std::int8_t RowMax = 4;
    constexpr std::int8_t ColumnMax = 4;

    using MatrixArray = std::array<std::array<float, RowMax>, ColumnMax>;

    class Matrix44	{
    public:
      Matrix44();
      Matrix44(const MatrixArray value);
      Matrix44(const Matrix44&) = default;
      Matrix44(Matrix44&&) = default;

      virtual ~Matrix44() = default;

      Matrix44& operator = (const Matrix44&) = default;
      Matrix44& operator = (Matrix44&&) = default;

      const Matrix44 operator* (const Matrix44 rhs) const;
      const Matrix44 operator+ (const Vector4 rhs) const;

      inline const float GetValue(const std::int_fast8_t row, const std::int_fast8_t columun)
        const { return _rowColmun[row][columun]; }
      inline const void SetValue(const std::int_fast8_t row, const std::int_fast8_t columun, 
        const float value) { _rowColmun[row][columun] = value; }

      void Zero(MatrixArray& target);
      void Unit();

      const float Determinant() const;
      const Matrix44 GetInverse() const;

      void TransFar(const float x, const float y, const float z, bool isMake);
      void Scale(const float x, const float y, const float z, bool isMake);
      void RotateX(const float degree, bool isMake);
      void RotateY(const float degree, bool isMake);
      void RotateZ(const float degree, bool isMake);
      const Matrix44 GetRotate() const;
      inline MatrixArray& GetRowColmun() {return _rowColmun; }
    private:
      std::tuple<float, float> GetSinCos(const float degree) const;	
      MatrixArray _rowColmun;
    };
  }	// namespace Math
} // namespace AppFrame