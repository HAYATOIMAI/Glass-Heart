#pragma once
#include <DxLib.h>
#include <memory>
#include <cstdint>

namespace GlassHeart {
	namespace Object {
		class ObjectBase;
	}

	namespace Collision {

		class IsHitSideAndBottom {
		public:
			IsHitSideAndBottom(Object::ObjectBase& owner);
			/**
			 * @brief 空中の足場の底面や側面との当たり判定
			 *
			 * @param[in] pos 位置ベクトル
			 * @param[in] forward 移動量ベクトル
			 * @return 位置ベクトル
			 */
			VECTOR CheckHitSideAndBottom(const VECTOR& pos, const VECTOR& forward, const std::uint_fast8_t state);

			inline MV1_COLL_RESULT_POLY_DIM GetSideAndBottom() { return _sideBottom; }
			inline MV1_COLL_RESULT_POLY_DIM GetBWallThroughMesh() { return _bWallThrough; }
			inline MV1_COLL_RESULT_POLY_DIM GetWWallThroughMesh() { return _wWallThrough; }
		private:
			Object::ObjectBase& _owner;              //!< 親クラスへの参照
			MV1_COLL_RESULT_POLY_DIM _sideBottom;    //!< 底面や側面との当たり判定用変数
			MV1_COLL_RESULT_POLY_DIM _bWallThrough;  //!< 白い底面や側面との当たり判定用変数
			MV1_COLL_RESULT_POLY_DIM _wWallThrough;  //!< 黒い底面や側面との当たり判定用変数
		};
	}
}