/*****************************************************************//**
 * @file   CollisionManager.h
 * @brief  �R���W�����}�l�[�W���[�N���X�̐錾
 *
 * @author Hayato Imai, Yoshihiro Takahashi
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <memory>
#include "IsHitFloor.h"
#include "IsHitJumpStand.h"
#include "IsHitSideAndBottom.h"
#include "IsHitWDeathMesh.h"
#include "IsHitBDeathMesh.h"
#include "IsHitCircleToCircle.h"
 /**
  * @namespace GlassHeart
  * @brief     �v���W�F�N�g��
  */
namespace GlassHeart {
  namespace Object {
    class ObjectBase;
  }
  /**
   * @namespace Collision
   * @brief     �Փ˔���֌W
   */
  namespace Collision {
    /**
     * @class CollisionManager
     * @brief �Փ˔���Ǘ��p�N���X
     */
    class CollisionManager {
    public:
      /**
       * @brief�@          �R���X�g���N�^
       *
       * @param[in] owner�@�I�u�W�F�N�g�x�[�X�N���X�ւ̎Q��
       */
      CollisionManager(GlassHeart::Object::ObjectBase& owner);
      /**
       * @brief            ���Ƃ̓����蔻����擾
       *                   
       * @return           ���Ƃ̓����蔻��̎Q��
       */
      inline IsHitFloor& GetIsHitFloor() { return _isHitFloor; }
      /**
       * @brief            �W�����v�����ۂ̏��Ƃ̓����蔻����擾
       *                   
       * @return           �W�����v�����ۂ̏��Ƃ̓����蔻��̎Q��
       */
      inline IsHitJumpStand& GetIsHitJumpStand() { return _isHitJumpStand; }
      /**
       * @brief            �󒆂ɑ��݂��Ă��鑫��̒�ʂƑ��ʂ̓����蔻����擾
       *                   
       * @return           ��ʂƑ��ʂ̓����蔻��̎Q��
       */
      inline IsHitSideAndBottom& GetIsHitSideBottom() { return _isHitSideBottom; }
      /**
       * @brief            ���S������Ƃ锒�����b�V�����擾
       *                   
       * @return           ���S������Ƃ锒�����b�V���̎Q��
       */
      inline IsHitWDeathMesh& GetIsHitWDeathMesh() { return _isHitWDeathMesh; }
      /**
       * @brief            ���S������Ƃ鍕�����b�V�����擾
       *                   
       * @return           ���S������Ƃ鍕�����b�V���̂̎Q��
       */
      inline IsHitBDeathMesh& GetIsHitBDeathMesh() { return _isHitBDeathMesh; }
      /**
       * @brief            �~�Ɖ~�̏Փ˔���N���X���擾
       *                   
       * @return           �~�Ɖ~�̏Փ˔���̎Q��
       */
      inline IsHitCircleToCircle& GetIsHitCircle() { return _isHitCircle; }
    private:
      Object::ObjectBase&  _owner;            //!< �e�N���X�ւ̎Q��
      IsHitFloor           _isHitFloor;       //!< ���Ƃ̓����蔻��N���X�̎Q��
      IsHitJumpStand       _isHitJumpStand;   //!< �W�����v�����ۂ̏��Ƃ̓����蔻��̎Q��
      IsHitSideAndBottom   _isHitSideBottom;  //!< �󒆂ɑ��݂��Ă��鑫��̒�ʂƑ��ʂ̓����蔻��̎Q��
      IsHitWDeathMesh      _isHitWDeathMesh;  //!< ���S������Ƃ锒�����b�V���̎Q��
      IsHitBDeathMesh      _isHitBDeathMesh;  //!< ���S������Ƃ鍕�����b�V���̎Q��
      IsHitCircleToCircle  _isHitCircle;      //!< �~��̓����蔻��N���X�̎Q��
    };
  } // namespce Collision
} // namespace GlassHeart