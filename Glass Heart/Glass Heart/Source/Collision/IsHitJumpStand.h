/*****************************************************************//**
 * @file   IsHitJumpStand.h
 * @brief  �W�����v�����ۂ̏��Ƃ̓����蔻��̐錾
 * 
 * @author HAYATO IMAI
 * @date   October 2022
 *********************************************************************/
#pragma once
#include <DxLib.h>
#include <memory>
#include <cstdint>

namespace GlassHeart {
  namespace Object {
    class ObjectBase;
  }

  namespace Collision {
    class IsHitJumpStand {
    public:
      /**
       * @ �R���X�g���N�^
       *
       * @param[in] owner �e�N���X�ւ̎Q��
       */
      IsHitJumpStand(Object::ObjectBase& owner);
      /**
       * @brief �󒆂̑���Ƃ̓����蔻��
       *
       * @param[in] pos �ʒu�x�N�g��
       * @param[in] forward  �ړ��ʃx�N�g��
       * @return  �ʒu�x�N�g��
       */
      VECTOR CheckJumpStand(const VECTOR& pos, const VECTOR& forward, const std::uint_fast8_t state);

      inline MV1_COLL_RESULT_POLY GetStand()    { return _stand; }
      inline MV1_COLL_RESULT_POLY GetWThrough() { return _wThrough; }
      inline MV1_COLL_RESULT_POLY GetBThrough() { return _bThrough; }
    private:
      Object::ObjectBase& _owner;      //!< �e�N���X�ւ̎Q��
      MV1_COLL_RESULT_POLY _stand;     //!< �W�����v�p���Ƃ̓����蔻��ϐ�
      MV1_COLL_RESULT_POLY _wThrough;  //!< �������Ƃ̓����蔻��p�ϐ�
      MV1_COLL_RESULT_POLY _bThrough;  //!< �������Ƃ̓����蔻��p�ϐ�
    };
  }
}