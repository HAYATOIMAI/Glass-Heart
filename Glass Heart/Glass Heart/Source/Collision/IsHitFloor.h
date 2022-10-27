/*****************************************************************//**
 * @file   IsHitFloor.h
 * @brief  ���Ƃ̓����蔻��N���X�̐錾
 * 
 * @author HAYATO IMAI
 * @date   October 2022
 *********************************************************************/
#pragma once
#include <memory>
#include <cstdint>
#include <DxLib.h>

namespace GlassHeart {
  namespace Object {
    class ObjectBase;
  }

  namespace Collision {
    /**
     * @class 
     */
    class IsHitFloor {
    public:
      /**
       * @ �R���X�g���N�^
       *
       * @param[in] owner �e�N���X�ւ̎Q��
       */
      IsHitFloor(Object::ObjectBase& owner);
      /**
       * @brief             �����b�V���Ƃ̓����蔻��
       *
       * @param[in] pos     �ʒu�x�N�g��
       * @param[in] forward �ړ��ʃx�N�g��
       * @return            �ʒu�x�N�g��
       */
      VECTOR CheckHitFloor(const VECTOR& pos, const VECTOR& forward, const std::int_fast8_t state);

      inline MV1_COLL_RESULT_POLY GetHitFloor() const { return _floor; }
      inline MV1_COLL_RESULT_POLY GetWThrough() const { return _wThrough; }
      inline MV1_COLL_RESULT_POLY GetBThrough() const { return _bThrough; }
    private:
      Object::ObjectBase& _owner;      //!< �e�N���X�ւ̎Q��
      MV1_COLL_RESULT_POLY _floor;     //!< ���Ƃ̓����蔻��p�ϐ�
      MV1_COLL_RESULT_POLY _wThrough;  //!< �������Ƃ̓����蔻��p�ϐ�
      MV1_COLL_RESULT_POLY _bThrough;  //!< �������Ƃ̓����蔻��p�ϐ�
    };
  }
}