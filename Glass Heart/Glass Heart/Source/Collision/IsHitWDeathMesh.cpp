/*****************************************************************//**
 * @file   IsHitWDeathMesh.cpp
 * @brief  ���S������Ƃ锒�����b�V���Ƃ̓����蔻��N���X�̏���
 * 
 * @author HAYATO IMAI
 * @date   October 2022
 *********************************************************************/
#include "IsHitWDeathMesh.h"
#include "../Object/ObjectBase.h"
#include "../Application/GameMain.h"

namespace {
  constexpr auto Stage = "Stage";
  constexpr auto DeathMeshW = "WDeath_NavMesh";
  constexpr auto Round = 20.0f;
  constexpr auto CapsuleStart = 140.0f;
  constexpr auto CapsuleEnd = 1.0f;
}
/** �R���X�g���N�^ */
GlassHeart::Collision::IsHitWDeathMesh::IsHitWDeathMesh(Object::ObjectBase& owner) : _owner{owner} {
  _wDeath.HitNum = 0;
}
/** ���S������Ƃ锒�����b�V���Ƃ̓����蔻�� */
VECTOR GlassHeart::Collision::IsHitWDeathMesh::CheckHitWDeathMesh(const VECTOR& pos, const VECTOR& forward) {
  auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles(Stage);
  auto newPos = VAdd(pos, forward);
  auto c1 = VAdd(newPos, { 0.f, CapsuleStart,0.f });
  auto c2 = VAdd(newPos, { 0.f, CapsuleEnd, 0.f });
  _wDeath = MV1CollCheck_Capsule(handle, MV1SearchFrame(handle, DeathMeshW), c1, c2, Round);

  if (_wDeath.HitNum == 0) {
    // �Փ˂Ȃ� ���݈ʒu��Ԃ�
    return pos;
  }
  else if (_wDeath.HitNum >= 1) {
    // �Փ˂��� ���݈ʒu�ƈړ��ʃx�N�g�������Z���ĕԂ�
    newPos = VAdd(pos, forward);
  }
  return  newPos;
}