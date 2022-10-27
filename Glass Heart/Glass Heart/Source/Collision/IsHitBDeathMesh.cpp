/*****************************************************************//**
 * @file   IsHitBDeathMesh.cpp
 * @brief  死亡判定をとる黒いメッシュとの当たり判定クラスの処理
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
/** コンストラクタ */
GlassHeart::Collision::IsHitBDeathMesh::IsHitBDeathMesh(Object::ObjectBase& owner) : _owner{owner}{
  _bDeath.HitNum = 0;
}
/** 死亡判定をとる黒いメッシュとの当たり判定 */
VECTOR GlassHeart::Collision::IsHitBDeathMesh::CheckHitBDeathMesh(const VECTOR& pos, const VECTOR& forward) {
  auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles(Stage);
  auto newPos = VAdd(pos, forward);
  auto c1 = VAdd(newPos, { 0.f,CapsuleStart,0.f });
  auto c2 = VAdd(newPos, { 0.f, CapsuleEnd, 0.f });
  _bDeath = MV1CollCheck_Capsule(handle, MV1SearchFrame(handle, DeathMeshB), c1, c2, Round);

  if (_bDeath.HitNum == 0) {
    // 衝突なし 現在位置を返す
    return pos;
  }
  else if (_bDeath.HitNum >= 1) {
    // 衝突あり 現在位置と移動量ベクトルを加算して返す
    newPos = VAdd(pos, forward);
  }
  return newPos;
}