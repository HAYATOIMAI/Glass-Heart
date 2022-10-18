/*********************************************************************
 * @file   CollisionManager.cpp
 * @brief  �R���W�����}�l�[�W���[�N���X�̏���
 *
 * @author Hayato Imai, Yoshihiro Takahashi
 * @date   December 2021
 *********************************************************************/
#include "CollisionManager.h"
#include "../Object/ObjectBase.h"
#include "../Application/GameMain.h"

 /** �R���X�g���N�^ */
GlassHeart::Collision::CollisionManager::CollisionManager(Object::ObjectBase& owner) : 
  _owner{ owner }, _isHitFloor{owner},_isHitJumpStand{owner}, _isHitSideBottom{owner}, 
  _isHitWDeathMesh{ owner }, _isHitBDeathMesh{ owner }, _isHitCircle{owner} {}