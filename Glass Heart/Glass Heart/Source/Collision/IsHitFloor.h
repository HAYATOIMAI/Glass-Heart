#pragma once
#include <memory>
#include <cstdint>
#include <DxLib.h>

namespace GlassHeart {
	namespace Object {
		class ObjectBase;
	}

	namespace Collision {
		class IsHitFloor {
		public:
			IsHitFloor(Object::ObjectBase& owner);
			/**
			 * @brief  ���Ƃ̓����蔻��
			 *
			 * @param[in] pos �ʒu�x�N�g��
			 * @param[in] forward �ړ��ʃx�N�g��
			 * @return �ʒu�x�N�g��
			 */
			VECTOR CheckHitFloor(const VECTOR& pos, const VECTOR& forward, const std::uint_fast8_t state);

			inline MV1_COLL_RESULT_POLY GetHitFloor() { return _floor; }
			inline MV1_COLL_RESULT_POLY GetWThrough() { return _wThrough; }
			inline MV1_COLL_RESULT_POLY GetBThrough() { return _bThrough; }
		private:
			Object::ObjectBase& _owner;      //!< �e�N���X�ւ̎Q��
			MV1_COLL_RESULT_POLY _floor;     //!< ���Ƃ̓����蔻��p�ϐ�
			MV1_COLL_RESULT_POLY _wThrough;  //!< �������Ƃ̓����蔻��p�ϐ�
			MV1_COLL_RESULT_POLY _bThrough;  //!< �������Ƃ̓����蔻��p�ϐ�
		};
	}
}