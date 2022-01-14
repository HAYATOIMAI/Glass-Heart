
/*****************************************************************//**
 * @file   Matrix.h
 * @brief  
 * 
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/
#pragma once
#include <cstdint>
#include <array>
#include <tuple>

namespace AppFrame {

	class Vector4;

	constexpr uint32_t ColumnMax = 4;
	constexpr uint32_t RowMax = 4;

	using _matrixArray = std::array<std::array<double, ColumnMax>, RowMax>;

	class Matrix {
	public:
		Matrix();
		Matrix(const _matrixArray value);
		Matrix(const Matrix&) = default;
		Matrix(Matrix&&) = default;

		virtual ~Matrix() = default;

		Matrix& operator =(const Matrix&) = default; // コピー
		Matrix& operator =(Matrix&&) = default; // ムーブ

		const Matrix operator *(const Matrix rhs) const;
		const Matrix operator +(const Vector4 rhs) const;

		const double GetValue(const uint32_t row, const uint32_t column) const { return _rowColumn[row][column]; }
		const void SetValue(const uint32_t row, const uint32_t column, const double value) { _rowColumn[row][column] = value; }

		void Zero(_matrixArray & target) const;
		void Unit();

		void LookAt(const Vector4& position, const Vector4& target, const Vector4& up);
		void Perspective(const double fov_y, const double aspect, const double near_z, const double far_z);
		void Viewport(const double width, const double height);

		void Transfer(const double x, const double y, const double z, bool make);
		void Scale(const double x, const double y, const double z, bool make);
		void RotateX(const double degree, bool make);
		void RotateY(const double degree, bool make);
		void RotateZ(const double degree, bool make);

		const Matrix GetRotate() const;

	private:
		std::tuple<double, double>GetSinCos(const double degree) const;
		_matrixArray _rowColumn;
	};
}



