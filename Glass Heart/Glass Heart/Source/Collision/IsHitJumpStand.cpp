/*****************************************************************//**
 * @file   IsHitJumpStand.cpp
 * @brief  �W�����v�����ۂ̏��Ƃ̓����蔻��̏���
 * 
 * @author HAYATO IMAI
 * @date   October 2022
 *********************************************************************/
#include "IsHitJumpStand.h"
#include "../Object/ObjectBase.h"
#include "../Application/GameMain.h"
#include <AppFrame.h>

namespace {
  constexpr auto Stage = "Stage";
  constexpr auto NavMesh_B = "BThroughFloor_NavMesh";
  constexpr auto NavMesh_W = "WThroughFloor_NavMesh";
  constexpr auto StandMesh = "Floor_NavMesh";
}
/** �R���X�g���N�^ */
GlassHeart::Collision::IsHitJumpStand::IsHitJumpStand(Object::ObjectBase& owner) :_owner{ owner } {
  _stand.HitFlag = 0;
  _bThrough.HitFlag = 0;
  _wThrough.HitFlag = 0;
}
/** �W�����v�����ۂ̏��Ƃ̓����蔻�� */
VECTOR GlassHeart::Collision::IsHitJumpStand::CheckJumpStand(const VECTOR& pos, const VECTOR& forward, 
  const std::int_fast8_t state) {
  auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles(Stage);
  auto newPos = VAdd(pos, forward);
  auto start = VAdd(pos, { 0.f, 0.f, 0.f });
  auto end = VAdd(pos, { 0.f, forward.y, 0.f });
  // �F�ɂ���Ĕ��肷�郁�b�V����ύX
  switch (state) {
  case 0:
    _bThrough = MV1CollCheck_Line(handle, MV1SearchFrame(handle, NavMesh_B), start, end);
    if (_bThrough.HitFlag == 0) {
      // �Փ˂Ȃ�
    }
    else if (_bThrough.HitFlag == 1) {
      // �Փ˂���Γ��������ʒu�Ɉړ�
      newPos = _bThrough.HitPosition;
    }
    _stand = MV1CollCheck_Line(handle, MV1SearchFrame(handle, StandMesh), start, end);
    break;
  case 1:
    _wThrough = MV1CollCheck_Line(handle, MV1SearchFrame(handle, NavMesh_W), start, end);
    if (_wThrough.HitFlag == 0) {
      // �Փ˂Ȃ�
    }
    else if (_wThrough.HitFlag == 1) {
      // �Փ˂���Γ��������ʒu�Ɉړ�
      newPos = _wThrough.HitPosition;
    }
    _stand = MV1CollCheck_Line(handle, MV1SearchFrame(handle, StandMesh), start, end);
    break;
  default:
    break;
  }
  if (_stand.HitFlag == 0) {
    // �Փ˂Ȃ�
    return newPos;
  }
  else if (_stand.HitFlag == 1) {
    // �Փ˂���Γ��������ʒu�Ɉړ�
    newPos = _stand.HitPosition;
  }

  return  newPos;
}
