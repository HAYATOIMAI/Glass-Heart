/*****************************************************************//**
 * @file   CollisionManager.h
 * @brief  �R���W�����}�l�[�W���[�N���X�̐錾
 *
 * @author Hayato Imai, Yoshihiro Takahashi
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <memory>
#include <DxLib.h>
#include "IsHitFloor.h"
#include "IsHitJumpStand.h"
#include "IsHitSideAndBottom.h"
#include "IsHitWDeathMesh.h"
#include "IsHitBDeathMesh.h"
#include "IsHitCircleToCircle.h"
 /**
  * @namespace GlassHeart
  * @brief �v���W�F�N�g��
  */
namespace GlassHeart {
  namespace Object {
    class ObjectBase;
  }
  /**
   * @namespace Collision
   * @brief �Փ˔���
   */
  namespace Collision {
    /**
     * @class CollisionManager
     * @brief �Փ˔���Ǘ��p�N���X
     */
    class CollisionManager {
    public:
      /**
       * @brief�@�R���X�g���N�^
       *
       * @param[in] owner�@�I�u�W�F�N�g�x�[�X�N���X�ւ̎Q��
       */
      CollisionManager(GlassHeart::Object::ObjectBase& owner);
      /**
       * @ ���Ƃ̓����蔻��̃Q�b�^�[
       * 
       * @return 
       */
      inline IsHitFloor& GetIsHitFloor() { return _isHitFloor; }
      /**
       * @ �W�����v�����ۂ̏��Ƃ̓����蔻��̃Q�b�^�[
       * 
       * @return 
       */
      inline IsHitJumpStand& GetIsHitJumpStand()      { return _isHitJumpStand; }
      /**
       * @ �󒆂ɑ��݂��Ă��鑫��̒�ʂƑ��ʂ̓����蔻��̃Q�b�^�[
       * 
       * @return 
       */
      inline IsHitSideAndBottom& GetIsHitSideBottom() { return _isHitSideBottom; }
      /**
       * @ ���S������Ƃ锒�����b�V���̃Q�b�^�[
       * 
       * @return 
       */
      inline IsHitWDeathMesh& GetIsHitWDeathMesh()    { return _isHitWDeathMesh; }
      /**
       * @ ���S������Ƃ鍕�����b�V���̃Q�b�^�[
       * 
       * @return 
       */
      inline IsHitBDeathMesh& GetIsHitBDeathMesh()    { return _isHitBDeathMesh; }
      /**
       * @ �~��̓����蔻��N���X�̎Q��
       * 
       * @return 
       */
      inline IsHitCircleToCircle& GetIsHitCircle()    { return _isHitCircle; }
    private:
      Object::ObjectBase&  _owner;            //!< �e�N���X�ւ̎Q��
      IsHitFloor           _isHitFloor;       //!< ���Ƃ̓����蔻��N���X�̎Q��
      IsHitJumpStand       _isHitJumpStand;   //!< 
      IsHitSideAndBottom   _isHitSideBottom;  //!<
      IsHitWDeathMesh      _isHitWDeathMesh;  //!<
      IsHitBDeathMesh      _isHitBDeathMesh;  //!<
      IsHitCircleToCircle  _isHitCircle;      //!< �~��̓����蔻��N���X�̎Q��
    };
  } // namespce Collision
} // namespace GlassHeart