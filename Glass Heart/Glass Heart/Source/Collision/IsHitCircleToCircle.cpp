/*****************************************************************//**
 * @file   IsHitCircleToCircle.cpp
 * @brief  円と円の衝突判定クラスの処理
 * 
 * @author Yoshihiro Takahashi
 * @date   October 2022
 *********************************************************************/
#include "IsHitCircleToCircle.h"
#include "../Object/ObjectBase.h"
#include <cmath>
/** コンストラクタ */
GlassHeart::Collision::IsHitCircleToCircle::IsHitCircleToCircle(Object::ObjectBase& owner) : _owner{owner} {}
/** デバッグ用円表示 */
void GlassHeart::Collision::IsHitCircleToCircle::RenderCircle(const VECTOR circlePos, float range, 
  unsigned int color) {
  for (float i = 0.0f; i < 360.0f; ++i) {
    auto radian = DX_PI_F / 180 * i;
    auto x = range * std::cos(radian);
    auto z = range * std::sin(radian);

    VECTOR move = { x, 0.0f, z };

    VECTOR newPos = VAdd(circlePos, move);
    DrawPixel3D(newPos, color);
  }
}
/** 円と円の衝突判定 */
bool GlassHeart::Collision::IsHitCircleToCircle::CheckCircleToCircle(const GlassHeart::Object::ObjectBase& owner, 
  const GlassHeart::Object::ObjectBase& target) {
  _radius1 = owner.GetRadius();
  _radius2 = target.GetRadius();

  auto differVec = VSub(target.GetPosition(), owner.GetPosition());

  auto length = sqrt(differVec.x * differVec.x + differVec.z * differVec.z);

  if (length < _radius1 + _radius2) {
    return true;
  }
  return false;
}
