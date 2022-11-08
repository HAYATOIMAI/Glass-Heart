/*****************************************************************//**
 * @file   IsHitFloor.cpp
 * @brief  床との当たり判定クラスの処理
 * 
 * @author HAYATO IMAI
 * @date   October 2022
 *********************************************************************/
#include "IsHitFloor.h"
#include "../Object/ObjectBase.h"
#include "../Application/GameMain.h"

namespace {
  constexpr auto Stage = "Stage";
  constexpr auto NavMesh_B = "BThroughFloor_NavMesh";
  constexpr auto NavMesh_W = "WThroughFloor_NavMesh";
  constexpr auto FloorMesh = "Floor_NavMesh";
  constexpr auto Hit = 1;
}
/** コンストラクタ */
GlassHeart::Collision::IsHitFloor::IsHitFloor(Object::ObjectBase& owner) :_owner{ owner } {
  _floor.HitFlag = 0;
  _bThrough.HitFlag = 0;
  _wThrough.HitFlag = 0;
}
/** 床との当たり判定 */
VECTOR GlassHeart::Collision::IsHitFloor::CheckHitFloor(const VECTOR& pos, const VECTOR& forward, 
  const int_fast16_t state) {
  auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles(Stage);
  auto newPos = VAdd(pos, forward);
  auto start = VAdd(pos, { 0.f, 1.f, 0.f });
  auto end = VAdd(pos, { 0.f, forward.y, 0.f });
  // 色によって判定するメッシュを変更
  switch (state) {
  case 0:
    _bThrough = MV1CollCheck_Line(handle, MV1SearchFrame(handle, NavMesh_B), start, end);
    if (_bThrough.HitFlag == Hit) {
      // 当たっていたら位置を返す
      return pos;
    }
    _floor = MV1CollCheck_Line(handle, MV1SearchFrame(handle, FloorMesh), start, end);
    break;
  case 1:
    _wThrough = MV1CollCheck_Line(handle, MV1SearchFrame(handle, NavMesh_W), start, end);
    if (_wThrough.HitFlag == Hit) {
      // 当たっていたら位置を返す
      return pos;
    }
    _floor = MV1CollCheck_Line(handle, MV1SearchFrame(handle, FloorMesh), start, end);
    break;
  default:
    break;
  }
  if (_floor.HitFlag == 0) {
    // 衝突なし
    return newPos;
  }
  // 当たっていたら位置を返す
  return  pos;
}