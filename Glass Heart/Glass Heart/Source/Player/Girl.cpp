/*********************************************************************
 * @file   Girl.cpp
 * @brief  ガールの処理
 *
 * @author Yoshihiro Takahashi
 * @date   February 2022
 *********************************************************************/
#include "Girl.h"
#include <numbers>
#include "../Object/ObjectServer.h"
#include "../Model/ModelAnimeManager.h"
#include "../Application/GameMain.h"

namespace {
  constexpr auto GirlPositionX = 25830.0f;  //!< ガールの位置X
  constexpr auto GirlPositionY = 12410.0f;  //!< ガールの位置Y
  constexpr auto GirlPositionZ = 30.0f;     //!< ガールの位置Z
}

/** コンストラクタ */
GlassHeart::Player::Girl::Girl(Application::GameMain& game) : GlassHeart::Object::ObjectBase{ game } {
  auto right = RightRotation();
  _rotation = VGet(0.0f, right, 0.0f);
  _position = VGet(GirlPositionX, GirlPositionY, GirlPositionZ);
}
/** 入力処理 */
void GlassHeart::Player::Girl::Input(AppFrame::Input::InputManager& input) {}

/** 更新処理 */
void GlassHeart::Player::Girl::Process() {
  _stateManage->Update();
  ComputeWorldTransform();
  _modelAnimeManage->Update();
  GetObjectServer().Register("Girl", _position);
}
/** 描画処理 */
void GlassHeart::Player::Girl::Render() {
  _stateManage->Draw();
}
/** ワールド座標変換 */
void GlassHeart::Player::Girl::ComputeWorldTransform() {
  auto world = MGetScale(_scale);
  world = MMult(world, MGetRotZ(_rotation.z));
  world = MMult(world, MGetRotX(_rotation.x));
  world = MMult(world, MGetRotY(_rotation.y + std::numbers::pi_v<float>));
  _worldTransform = MMult(world, MGetTranslate(_position));
}
/** 描画処理 */
void GlassHeart::Player::Girl::StateBase::Draw() {
  _owner.GetModelAnime().Draw();
}
/** 待機状態 */
void GlassHeart::Player::Girl::StateWait::Enter() {
  _owner.GetModelAnime().ChangeAnime("PC3_wait", true);
}