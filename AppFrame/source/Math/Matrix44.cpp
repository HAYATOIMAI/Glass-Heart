#include "Matrix44.h"
#include "Vector4.h"
#include <cmath>
#include <numbers>

namespace AppFrame {

	namespace Math {
		Matrix44::Matrix44() {
			Unit();
		}
		Matrix44::Matrix44(const MatrixArray value) {
			this->_rowColmun = value;
		}
		const Matrix44 Matrix44::operator*(const Matrix44 rhs) const {
			MatrixArray result{ {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}} };

			for (auto i = 0; i < ColumnMax; ++i) {
				for (auto j = 0; j < RowMax; ++j) {
					auto m = 0.0f;

					for (auto k = 0; k < 4; ++k) {
						m += _rowColmun[i][k] * rhs.GetValue(k, j);
					}
					result[i][j] = m;
				}
			}
			return Matrix44(result);
		}
		const Matrix44 Matrix44::operator+(const Vector4 rhs) const {
			MatrixArray result = _rowColmun;
			result[3][0] = rhs.GetX();
			result[3][1] = rhs.GetY();
			result[3][2] = rhs.GetZ();

			return Matrix44(result);
		}
		void Matrix44::Zero(MatrixArray& target) {
			for (auto i = 0; i < ColumnMax; ++i) {
				target[i].fill(0.0f);
			}
		}
		void Matrix44::Unit() {
			Zero(_rowColmun);

			for (auto i = 0; i < ColumnMax; ++i) {
				_rowColmun[i][i] = 1.0f;
			}
		}
		const float Matrix44::Determinant() const {
			MatrixArray upperTrianguler = _rowColmun;

			for (auto i = 0; i < ColumnMax; ++i) {
				for (auto j = 0; j < RowMax; ++j) {
					if (i >= j) {
						continue;
					}

					auto coefficient = upperTrianguler[j][i] / upperTrianguler[i][i];

					for (auto k = 0; k < RowMax; ++k) {
						upperTrianguler[j][k] -= upperTrianguler[i][k] * coefficient;
					}
				}
			}
			auto determinant = 1.0f;

			for (auto i = 0; i < ColumnMax; ++i) {
				determinant *= upperTrianguler[i][i];
			}
			return determinant;
		}
		const Matrix44 Matrix44::GetInverse() const {
			MatrixArray inverse{ {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}} };
			MatrixArray temporaly = _rowColmun;

			for (auto i = 0; i < ColumnMax; ++i) {
				auto coefficient = 1.0f / temporaly[i][i];
        
				for (auto j = 0; j < RowMax; ++j) {
					temporaly[i][j] *= coefficient;
					inverse[i][j] *= coefficient;
				}
				for (auto j = 0; j < RowMax; ++j) {
					if (i == j) {
						continue;
					}
					coefficient = temporaly[j][i];

					for (auto k = 0; k < RowMax; ++k) {
						temporaly[j][k] -= temporaly[i][k] * coefficient;
						inverse[j][k] -= inverse[i][k] * coefficient;
					}
				}
			}
			return Matrix44(inverse);
		}
		void Matrix44::TransFar(const float x, const float y, const float z, bool isMake) {
			if (isMake)	{
				Unit();
			}
			_rowColmun[3][0] += x;
			_rowColmun[3][1] += y;
			_rowColmun[3][2] += z;
		}
		void Matrix44::Scale(const float x, const float y, const float z, bool isMake) {
			if (isMake) {
				Unit();
			}
			_rowColmun[0][0] *= x;
			_rowColmun[1][1] *= y;
			_rowColmun[2][2] *= z;
		}
		void Matrix44::RotateX(const float degree, bool isMake) {
			auto sinCos = GetSinCos(degree);
			auto sin = std::get<0>(sinCos);
			auto cos = std::get<1>(sinCos);

			if (isMake) {
				Unit();

				_rowColmun[1][1] =  cos;
				_rowColmun[1][2] =  sin;
				_rowColmun[2][1] = -sin;
				_rowColmun[2][2] =  cos;
			}
			else {
				MatrixArray array{ {{1, 0, 0, 0}, {0, cos, sin, 0}, {0, -sin, cos, 0}, {0, 0, 0, 1}} };
				Matrix44 rotateX(array);

				*this = *this * rotateX;
			}
		}
		void Matrix44::RotateY(const float degree, bool isMake) {
			auto sinCos = GetSinCos(degree);
			auto sin = std::get<0>(sinCos);
			auto cos = std::get<1>(sinCos);

			if (isMake) {
				Unit();

				_rowColmun[0][0] =  cos;
				_rowColmun[0][2] = -sin;
				_rowColmun[2][0] =  sin;
				_rowColmun[2][2] =  cos;
			}
			else {
				MatrixArray array{ {{cos, 0, -sin, 0}, {0, 1, 0, 0}, {sin, 0, cos, 0}, {0, 0, 0, 1}} };
				Matrix44 rotateY(array);

				*this = *this * rotateY;
			}
		}
		void Matrix44::RotateZ(const float degree, bool isMake) {
			auto sinCos = GetSinCos(degree);
			auto sin = std::get<0>(sinCos);
			auto cos = std::get<1>(sinCos);

			if (isMake) {
				Unit();

				_rowColmun[0][0] =  cos;
				_rowColmun[0][1] =  sin;
				_rowColmun[1][0] = -sin;
				_rowColmun[1][1] =  cos;
			}
			else {
				MatrixArray array{ {{cos, sin, 0, 0}, {-sin, cos, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}} };
				Matrix44 rotateZ(array);

				*this = *this * rotateZ;
			}
		}
		const Matrix44 Matrix44::GetRotate() const {
			MatrixArray noneTranfer = _rowColmun;

			noneTranfer[3][0] = 0.0f;
			noneTranfer[3][1] = 0.0f;
			noneTranfer[3][2] = 0.0f;

			return Matrix44(noneTranfer);
		}
		std::tuple<float, float> Matrix44::GetSinCos(const float degree) const {
			auto radian = degree * std::numbers::pi_v<float> / 180.0f;
			return std::make_tuple(std::sin(radian), std::cos(radian));
		}
	} // namespace Math
} // namespace AppFrame