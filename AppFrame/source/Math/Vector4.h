/*****************************************************************//**
 * @file   Vector4.h
 * @brief  四元数クラスの宣言
 * 
 * @author HAYATO IMAI
 * @date   August 2022
 *********************************************************************/
#pragma once
namespace AppFrame {

	namespace Math {

		class Matrix44;

		class Vector4	{
		public:
			/**
			 * @ コンストラクタ
			 * 
			 */
			Vector4();
			Vector4(const float x, const float y, const float z) : _x(x), _y(y), _z(z), _w(1.0f) {}
			Vector4(const float x, const float y, const float z, float w) : _x(x), _y(y), _z(z), _w(w) {}
			/**
			 * @ コピーコンストラクタ
			 * 
			 * @param 
			 */
			Vector4(const Vector4&) = default;
			/**
			 * @ ムーブコンストラクタ
			 * 
			 * @param 
			 */
			Vector4(Vector4&&) = default;
			/**
			 * @ デストラクタ
			 */
		  virtual~Vector4() = default;

			Vector4& operator =(const Vector4&) = default;
			Vector4& operator	=(Vector4&&) = default;

			const Vector4 operator +(const Vector4& rhs) const;
			const Vector4 operator -(const Vector4& rhs) const;
			const Vector4 operator *(const float rhs) const;
			const Vector4 operator /(const float rhs) const;
			const Vector4 operator *(const Matrix44& rhs) const;

			void Set(const Vector4& vec);
			void Set(const float x, const float y, const float z);
			void Add(const Vector4& vec);
			void Add(const float x, const float y, const float z);

			const float Length() const;

			void Normalized();
			const Vector4 Normalize() const;

			const float Dot(const Vector4& rhs) const;
			const Vector4 Cross(const Vector4& rhs)	const;

			Vector4 Transform(const Vector4& vec, Matrix44& mat);

			const float GetX() const { return _x; }
			const float GetY() const { return _y; }
			const float GetZ() const { return _z; }
			const float GetW() const { return _w; }
		private:
			float _x{ 0.0f };	 //!< X成分
			float _y{ 0.0f };	 //!< Y成分
			float _z{ 0.0f };	 //!< Z成分
			float _w{ 1.0f };	 //!< W成分
		};
	} // namespace Math
}	// namespace AppFrame