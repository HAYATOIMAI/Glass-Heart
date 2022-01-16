
/*****************************************************************//**
 * @file   Matrix.cpp
 * @brief  
 * 
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/
#include "Matrix.h"
#include "Vector4.h"
#include "Utility.h"
#include <cmath>

namespace AppFrame {
    Matrix::Matrix() {
        Unit();
    }
    Matrix::Matrix(const _matrixArray value) {
        this->_rowColumn = value;
    }
    const Matrix Matrix::operator*(const Matrix rhs) const { 
        _matrixArray result{ {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}} };

        for (auto i = 0; i < RowMax; ++i) {
            for (auto j = 0; j < ColumnMax; ++j) {
                auto m = 0.0;

                for (auto k = 0; k < 4; ++k) {
                    m += _rowColumn[i][k] * rhs.GetValue(k, j);
                }

                result[i][j] = m;
            }
        }

        return Matrix(result);
    }
    const Matrix Matrix::operator+(const Vector4 rhs) const {

        _matrixArray result = _rowColumn;

        result[3][0] += rhs.Getx();
        result[3][1] += rhs.GetY();
        result[3][2] += rhs.GetZ();


        return Matrix(result);
    }
    void Matrix::Zero(_matrixArray& target) const {
        for (auto i = 0; i < RowMax; ++i) {
            target[i].fill(0.0);
        }
    }
    void Matrix::Unit() {
        Zero(_rowColumn);

        for (auto i = 0; i < RowMax; ++i) {
            _rowColumn[i][i] = 1.0;
        }
    }
    void Matrix::LookAt(const Vector4& position, const Vector4& target, const Vector4& up) {

    }
    void Matrix::Perspective(const double fov_y, const double aspect, const double near_z, const double far_z) {

        auto cot = 1.0 / tan(fov_y * 0.5);
        auto range = far_z - near_z;
        auto temp = far_z / range;

        Zero(_rowColumn);

        _rowColumn[0][0] = cot * aspect;
        _rowColumn[1][1] = cot;
        _rowColumn[2][2] = temp;
        _rowColumn[2][3] = 1.0f;
        _rowColumn[3][2] = -near_z * temp;
    }
    void Matrix::Viewport(const double width, const double height) {
        auto w = width * 0.5;
        auto h = height * 0.5;

        Unit();

        _rowColumn[0][0] = w;
        _rowColumn[1][1] = -h;
        _rowColumn[3][0] = w;
        _rowColumn[3][1] = h;
    }
    void Matrix::Transfer(const double x, const double y, const double z, bool make) {

        if (make) {
            Unit();
        }

        _rowColumn[3][0] += x;
        _rowColumn[3][1] += y;
        _rowColumn[3][2] += z;
    }
    void Matrix::Scale(const double x, const double y, const double z, bool make) {

        if (make) {
            Unit();
        }

        _rowColumn[0][0] *= x;
        _rowColumn[1][1] *= y;
        _rowColumn[2][2] *= z;
    }
    void Matrix::RotateX(const double degree, bool make) {

        auto sin_cos = GetSinCos(degree);
        auto sin = std::get<0>(sin_cos);
        auto cos = std::get<1>(sin_cos);

        if (make) {
            Unit();

            _rowColumn[1][1] = cos;
            _rowColumn[1][2] = sin;
            _rowColumn[2][1] = -sin;
            _rowColumn[2][2] = cos;
        }
        else {
            _matrixArray array{ {{1, 0, 0, 0}, {0, cos, sin, 0}, {0, -sin, cos, 0}, {0, 0, 0, 1}} };
            Matrix rot_x(array);

            *this = *this * rot_x;
        }
    }
    void Matrix::RotateY(const double degree, bool make) {

        auto sin_cos = GetSinCos(degree);
        auto sin = std::get<0>(sin_cos);
        auto cos = std::get<1>(sin_cos);

        if (make) {
            Unit();

            _rowColumn[0][0] = cos;
            _rowColumn[0][2] = -sin;
            _rowColumn[2][0] = sin;
            _rowColumn[2][2] = cos;
        }
        else {
            _matrixArray array{ {{cos, 0, -sin, 0}, {0, 1, 0, 0}, {sin, 0, cos, 0}, {0, 0, 0, 1}} };
            Matrix  rot_y(array);

            *this = *this * rot_y;
        }
    }
    void Matrix::RotateZ(const double degree, bool make) {

        auto sin_cos = GetSinCos(degree);
        auto sin = std::get<0>(sin_cos);
        auto cos = std::get<1>(sin_cos);

        if (make) {
            Unit();

            _rowColumn[0][0] = cos;
            _rowColumn[0][1] = sin;
            _rowColumn[1][0] = -sin;
            _rowColumn[1][1] = cos;
        }
        else {
            _matrixArray array{ {{cos, sin, 0, 0}, {-sin, cos, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}} };
            Matrix rot_z(array);

            *this = *this * rot_z;
        }
    }
    const Matrix Matrix::GetRotate() const {

        _matrixArray none_transfer = _rowColumn;

        none_transfer[3][0] = 0.0;
        none_transfer[3][1] = 0.0;
        none_transfer[3][2] = 0.0;

        return Matrix(none_transfer);
    }
    std::tuple<double, double> Matrix::GetSinCos(const double degree) const {

        auto radian = Utility::DegreeToRadian(degree);

        return std::make_tuple(std::sin(radian), std::cos(radian));
    }
}