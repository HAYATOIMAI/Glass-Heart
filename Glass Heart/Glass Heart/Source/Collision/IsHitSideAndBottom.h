/*****************************************************************//**
 * @file   IsHitSideAndBottom.h
 * @brief  �󒆂ɑ��݂��Ă��鑫��̒�ʂƑ��ʂ̓����蔻��̃N���X�̐錾
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

    class IsHitSideAndBottom {
    public:
      /**
       * @brief           �R���X�g���N�^
       *
       * @param[in] owner �e�N���X�ւ̎Q��
       */
      IsHitSideAndBottom(Object::ObjectBase& owner);
      /**
       * @brief             �󒆂̑���̒�ʂ⑤�ʂƂ̓����蔻��
       *
       * @param[in] pos     �ʒu�x�N�g��
       * @param[in] forward �ړ��ʃx�N�g��
       * @return            �ʒu�x�N�g��
       */
      VECTOR CheckHitSideAndBottom(const VECTOR& pos, const VECTOR& forward, const int_fast16_t state);

      inline MV1_COLL_RESULT_POLY_DIM GetSideAndBottom()    const { return _sideBottom; }
      inline MV1_COLL_RESULT_POLY_DIM GetBWallThroughMesh() const { return _bWallThrough; }
      inline MV1_COLL_RESULT_POLY_DIM GetWWallThroughMesh() const { return _wWallThrough; }
    private:
      Object::ObjectBase& _owner;              //!< �e�N���X�ւ̎Q��
      MV1_COLL_RESULT_POLY_DIM _sideBottom;    //!< ��ʂ⑤�ʂƂ̓����蔻��p�ϐ�
      MV1_COLL_RESULT_POLY_DIM _bWallThrough;  //!< ������ʂ⑤�ʂƂ̓����蔻��p�ϐ�
      MV1_COLL_RESULT_POLY_DIM _wWallThrough;  //!< ������ʂ⑤�ʂƂ̓����蔻��p�ϐ�
    };
  }
}