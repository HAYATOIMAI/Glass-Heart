/*****************************************************************//**
 * @file   IsHitSideAndBottom.cpp
 * @brief  �󒆂ɑ��݂��Ă��鑫��̒�ʂƑ��ʂ̓����蔻��̃N���X�̏���
 * 
 * @author HAYATO IMAI
 * @date   October 2022
 *********************************************************************/
#include "IsHitSideAndBottom.h"
#include "../Object/ObjectBase.h"
#include "../Application/GameMain.h"

namespace {
  constexpr auto Stage = "Stage";
  constexpr auto NavMeshB = "BThroughFloor_NavMesh";
  constexpr auto NavMeshW = "WThroughFloor_NavMesh";
  constexpr auto WallMesh = "Floor_NavMesh";
  constexpr auto Round = 20.0f;
  constexpr auto CapsuleStart = 120.0f;
  constexpr auto CapsuleEnd = 21.0f;
}

GlassHeart::Collision::IsHitSideAndBottom::IsHitSideAndBottom(Object::ObjectBase& owner) : _owner{owner} {
  _sideBottom.HitNum = 0;
  _bWallThrough.HitNum = 0;
  _wWallThrough.HitNum = 0;
}
/** �󒆂ɑ��݂��Ă��鑫��̒�ʂƑ��ʂ̓����蔻�� */
VECTOR GlassHeart::Collision::IsHitSideAndBottom::CheckHitSideAndBottom(const VECTOR& pos, const VECTOR& forward, 
  const int_fast16_t state) {
  auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles(Stage);
  auto newPos = VAdd(pos, forward);
  auto c1 = VAdd(newPos, { 0.f, CapsuleStart, 0.f });
  auto c2 = VAdd(newPos, { 0.f, CapsuleEnd, 0.f });
  // �F�ɂ���Ĕ��肷�郁�b�V����ύX
  switch (state) {
  case 0:
    _bWallThrough = MV1CollCheck_Capsule(handle, MV1SearchFrame(handle, NavMeshB), c1, c2, Round);
    // �������Ă����猻�݂̈ʒu��Ԃ�
    if (_bWallThrough.HitNum > 0) {
      return pos;
    }
    _sideBottom = MV1CollCheck_Capsule(handle, MV1SearchFrame(handle, WallMesh), c1, c2, Round);
    break;
  case 1:
    _wWallThrough = MV1CollCheck_Capsule(handle, MV1SearchFrame(handle, NavMeshW), c1, c2, Round);
    // �������Ă����猻�݂̈ʒu��Ԃ�
    if (_wWallThrough.HitNum > 0) {
      return pos;
    }
    _sideBottom = MV1CollCheck_Capsule(handle, MV1SearchFrame(handle, WallMesh), c1, c2, Round);
    break;
  default:
    break;
  }
  // �Փ˖���
  if (_sideBottom.HitNum == 0) {
    return newPos;
  }
  return pos;
}