/*****************************************************************//**
 * @file   IsHitBDeathMesh.cpp
 * @brief  ���S������Ƃ鍕�����b�V���Ƃ̓����蔻��N���X�̏���
 * 
 * @author HAYATO IMAI
 * @date   October 2022
 *********************************************************************/
#include "IsHitBDeathMesh.h"
#include "../Object/ObjectBase.h"
#include "../Application/GameMain.h"

namespace {
  constexpr auto Stage = "Stage";
  constexpr auto DeathMeshB = "BDeath_NavMesh";
  constexpr auto Round = 20.0f;
  constexpr auto CapsuleStart = 140.0f;
  constexpr auto CapsuleEnd = 1.0f;
}
/** �R���X�g���N�^ */
GlassHeart::Collision::IsHitBDeathMesh::IsHitBDeathMesh(Object::ObjectBase& owner) : _owner{owner}{
  _bDeath.HitNum = 0;
}
/** ���S������Ƃ鍕�����b�V���Ƃ̓����蔻�� */
VECTOR GlassHeart::Collision::IsHitBDeathMesh::CheckHitBDeathMesh(const VECTOR& pos, const VECTOR& forward) {
  auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles(Stage);
  auto newPos = VAdd(pos, forward);
  auto c1 = VAdd(newPos, { 0.f,CapsuleStart,0.f });
  auto c2 = VAdd(newPos, { 0.f, CapsuleEnd, 0.f });
  _bDeath = MV1CollCheck_Capsule(handle, MV1SearchFrame(handle, DeathMeshB), c1, c2, Round);

  if (_bDeath.HitNum == 0) {
    // �Փ˂Ȃ� ���݈ʒu��Ԃ�
    return pos;
  }
  else if (_bDeath.HitNum >= 1) {
    // �Փ˂��� ���݈ʒu�ƈړ��ʃx�N�g�������Z���ĕԂ�
    newPos = VAdd(pos, forward);
  }
  return newPos;
}