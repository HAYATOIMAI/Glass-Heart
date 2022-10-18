/*****************************************************************//**
 * @file   GoalPoint.cpp
 * @brief  ゴールポイントの処理
 *
 * @author Yoshihiro Takahashi
 * @date   February 2022
 *********************************************************************/
#include "GoalPoint.h"
#include "../Application/GameMain.h"
#include "../Object/ObjectServer.h"
#include "../Player/Player.h"

namespace {
  constexpr auto GoalPositionX = 25830.0f;  //!< ゴールの位置X
  constexpr auto GoalPositionY = 12420.0f;  //!< ゴールの位置Y
  constexpr auto GoalPositionZ = 30.0f;     //!< ゴールの位置Z
}
/** コンストラクタ */
GlassHeart::CheckPoint::GoalPoint::GoalPoint(Application::GameMain& game) : ObjectBase{ game } {
  _goalPoint = LoadGraph("resource/2dMaterial/light3.png");
  _position = VGet(GoalPositionX, GoalPositionY, GoalPositionZ);
  _radius = 100.0f;
  _hitFlag = false;
}
/** 更新処理 */
void GlassHeart::CheckPoint::GoalPoint::Process() {
  GetObjectServer().Register("GoalPoint", _position);

  // ゴールポイントとプレイヤーの当たり判定
  for (auto ite = GetObjectServer().GetObjectLists().begin(); ite != GetObjectServer().GetObjectLists().end(); ite++) {
    if ((*ite)->GetObjectType() == ObjectBase::ObjectType::Player) {
      if (_collsionManage->GetIsHitCircle().CheckCircleToCircle(*this, **ite) == true) {
        _hitFlag = true;
        GoToGameClear();
      }
      else {
        _hitFlag = false;
      }
    }
  }
}
/** 描画処理 */
void GlassHeart::CheckPoint::GoalPoint::Render() {
  auto cr = GetColor(0, 0, 255);

  DrawBillboard3D(_goalDrawPos, 0.5f, 0.5f, 120.0f, 0.0f, _goalPoint, TRUE);
#ifdef _DEBUG

  auto red = GetColor(255, 0, 0);
  auto green = GetColor(0, 255, 0);

  if (_hitFlag == true) {
    _collsionManage->GetIsHitCircle().RenderCircle(_position, _radius, red);
  }
  else {
    _collsionManage->GetIsHitCircle().RenderCircle(_position, _radius, green);
  }
#endif // _DEBUG
}
/** ゲームクリアへ遷移処理 */
void GlassHeart::CheckPoint::GoalPoint::GoToGameClear() {
  if (_hitFlag == true) {
    _game.GetModeServer().GoToMode("GameClear");
  }
}