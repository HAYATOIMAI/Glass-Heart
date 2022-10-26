/*****************************************************************//**
 * @file   IsHitCircleToCircle.h
 * @brief  �~�Ɖ~�̏Փ˔���N���X�̐錾
 *
 * @author Yoshihiro Takahashi
 * @date   October 2022
 *********************************************************************/
#pragma once
#include <DxLib.h>

namespace GlassHeart {
  namespace Object {
    class ObjectBase;
  }

  namespace Collision {
    class IsHitCircleToCircle {
    public:
      /**
       * @ �R���X�g���N�^
       *
       * @param[in] owner �e�N���X�ւ̎Q��
       */
      IsHitCircleToCircle(Object::ObjectBase& owner);
      /**
       * @brief �f�o�b�O�p�����蔻��`�揈��
       *
       * @param[in] circlePos �~�̈ʒu�x�N�g��
       * @param[in] range �͈�
       * @param[in] color �F���
       */
      void RenderCircle(const VECTOR circlePos, float range, unsigned int color);
      /**
       * @brief �~�̓����蔻��
       *
       * @param[in] owner  �`�F�b�N�|�C���g
       * @param[in] target �v���C���[
       * @return �ڐG���Ă��邩
       */
      bool CheckCircleToCircle(const GlassHeart::Object::ObjectBase& owner, const GlassHeart::Object::ObjectBase& target);
    private:
      Object::ObjectBase& _owner;  //!< �e�N���X�ւ̎Q��
      float _radius1{ 0.0f };      //!< �`�F�b�N�|�C���g�Ƃ̓����蔻��p���a
      float _radius2{ 0.0f };      //!< �`�F�b�N�|�C���g�Ƃ̓����蔻��p���a
    };
  }
}