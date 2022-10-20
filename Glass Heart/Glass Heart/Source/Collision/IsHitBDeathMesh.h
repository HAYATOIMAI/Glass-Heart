/*****************************************************************//**
 * @file   IsHitBDeathMesh.h
 * @brief  ���S������Ƃ鍕�����b�V���Ƃ̓����蔻��N���X�̐錾
 * 
 * @author HAYATO IMAI
 * @date   October 2022
 *********************************************************************/
#pragma once
#include <DxLib.h>

namespace GlassHeart {
  namespace Object {
    class ObjectBase;
  }

  namespace Collision {
    class IsHitBDeathMesh {
    public:
      /**
       * @ �R���X�g���N�^
       *
       * @param[in] owner �e�N���X�ւ̎Q��
       */
      IsHitBDeathMesh(Object::ObjectBase& owner);
      /**
       * @brief ���S������Ƃ鍕�����b�V���Ƃ̓����蔻��
       *
       * @param[in] pos     �ʒu�x�N�g��
       * @param[in] forward �ړ��ʃx�N�g��
       * @return �ʒu�x�N�g��
       */
      VECTOR CheckHitBDeathMesh(const VECTOR& pos, const VECTOR& forward);

      inline MV1_COLL_RESULT_POLY_DIM GetBDeathMesh() { return _bDeath; }
    private:
      Object::ObjectBase& _owner;        //!< �e�N���X�ւ̎Q��
      MV1_COLL_RESULT_POLY_DIM _bDeath;  //!< �����f�X���b�V���Ƃ̓����蔻��p�ϐ�
    };
  }
}