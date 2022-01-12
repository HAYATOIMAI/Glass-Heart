
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


	private:
		std::tuple<double, double>GetSinCos(const double degree) const;
		_matrixArray _rowColumn;
	};
}



