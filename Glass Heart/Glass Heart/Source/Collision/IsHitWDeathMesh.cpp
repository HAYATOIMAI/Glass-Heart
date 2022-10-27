/*****************************************************************//**
 * @file   IsHitWDeathMesh.cpp
 * @brief  死亡判定をとる白いメッシュとの当たり判定クラスの処理
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
/** コンストラクタ */
GlassHeart::Collision::IsHitWDeathMesh::IsHitWDeathMesh(Object::ObjectBase& owner) : _owner{owner} {
  _wDeath.HitNum = 0;
}
/** 死亡判定をとる白いメッシュとの当たり判定 */
VECTOR GlassHeart::Collision::IsHitWDeathMesh::CheckHitWDeathMesh(const VECTOR& pos, const VECTOR& forward) {
  auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles(Stage);
  auto newPos = VAdd(pos, forward);
  auto c1 = VAdd(newPos, { 0.f, CapsuleStart,0.f });
  auto c2 = VAdd(newPos, { 0.f, CapsuleEnd, 0.f });
  _wDeath = MV1CollCheck_Capsule(handle, MV1SearchFrame(handle, DeathMeshW), c1, c2, Round);

  if (_wDeath.HitNum == 0) {
    // 衝突なし 現在位置を返す
    return pos;
  }
  else if (_wDeath.HitNum >= 1) {
    // 衝突あり 現在位置と移動量ベクトルを加算して返す
    newPos = VAdd(pos, forward);
  }
  return  newPos;
}