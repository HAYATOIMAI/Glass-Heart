/*********************************************************************
 * @file   StateJumpFall.cpp
 * @brief  ジャンプ下降状態の宣言
 *
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/
#include "StateJumpFall.h"
#include "../Player/Player.h"
#include "../Collision/CollisionManager.h"
#include "../Model/ModelAnimeManager.h"
#include "../Application/GameMain.h"
#include <numbers>

namespace {
  constexpr auto StraifVector = 6.5f;    //!< 空中移動用のX軸移動量
  constexpr auto Gravity = -0.6f;        //!< 重力加速度
  constexpr auto InputThreshold = 5000;  //!< 入力閾値
  constexpr auto InputThresholdMin = 1;  //!< 入力最低値
  constexpr auto Hit = 1;                //!< ヒットしたかのフラグ
  constexpr auto Idle = "Idle";          //!< 遷移させるステートの文字列
  constexpr auto JumpEnd = "Jump_End";   //!< 遷移させるステートの文字列
  constexpr auto Run = "run";            //!< 遷移させるステートの文字列
}
/** 入り口処理 */
void GlassHeart::State::StateJumpFall::Enter() {
  // 落下中のアニメーションを再生
  _owner.GetModelAnime().ChangeAnime(JumpEnd, true);
  // SEの再生を停止
  auto& game = _owner.GetGame();
  game.GetSoundManager().StopSound(Run);
}
/** 入力処理 */
void GlassHeart::State::StateJumpFall::Input(AppFrame::Input::InputManager& input) {
  auto right = _owner.RightRotation();
  auto left = _owner.LeftRotation();
  _owner.SetForwardSpeed(0.f);
  if (input.GetJoyPad().GetAnalogStickLX() >= InputThreshold && input.GetJoyPad().GetAnalogStickLX() > InputThresholdMin) {
    // 右方向に向きを変更
    _owner.SetRotation(VGet(0.0f, right, 0.0f));
    _owner.SetForwardSpeed(StraifVector);
  }
  if (input.GetJoyPad().GetAnalogStickLX() <= -InputThreshold && input.GetJoyPad().GetAnalogStickLX() < InputThresholdMin) {
    // 左方向に向きを変更
    _owner.SetRotation(VGet(0.0f, left, 0.0f));
    _owner.SetForwardSpeed(StraifVector);
  }
}
/** 更新処理 */
void GlassHeart::State::StateJumpFall::Update() {
  auto pos = _owner.GetPosition();
  // 移動量ベクトルを取得
  auto forward = VScale(_owner.GetForward(), _owner.GetForwardSpeed());
  // ジャンプ下降処理
  auto jumpVelocity = _owner.GetJumpVelocity();
  jumpVelocity.y += Gravity;
  _owner.SetJumpVelocity(jumpVelocity);

  forward.y = jumpVelocity.y;
  // プレイヤーの色を取得
  auto state = static_cast<int> (_owner.GetColourState());
  // 空中の足場の底面と側面判定処理
  pos = _owner.GetCollision().GetIsHitSideBottom().CheckHitSideAndBottom(pos, { forward.x, 0.f, 0.f }, state);
  // 床との当たり判定
  pos = _owner.GetCollision().GetIsHitJumpStand().CheckJumpStand(pos, { 0.f, forward.y, 0.f }, state);
  // 当たっていたら待機状態へ移行
  if (_owner.GetCollision().GetIsHitJumpStand().GetStand().HitFlag == Hit) {
    _owner.GetStateManage().GoToState(Idle);
  }
  if (_owner.GetColourState() == Player::Player::ColourState::Black) {
    if (_owner.GetCollision().GetIsHitJumpStand().GetWThrough().HitFlag == Hit) {
      _owner.GetStateManage().GoToState(Idle);
    }
  }
  if (_owner.GetColourState() == Player::Player::ColourState::White) {
    if (_owner.GetCollision().GetIsHitJumpStand().GetBThrough().HitFlag == Hit) {
      _owner.GetStateManage().GoToState(Idle);
    }
  }
  // 死亡判定を取るメッシュと当たり判定
  if (_owner.GetColourState() == Player::Player::ColourState::Black) {
    pos = _owner.GetCollision().GetIsHitWDeathMesh().CheckHitWDeathMesh(pos, { 0.f, forward.y, 0.f });
  }
  // プレイヤーの色が異なっていたらリスポーン処理
  if (_owner.GetCollision().GetIsHitWDeathMesh().GetWDeathMesh().HitNum >= Hit) {
    if (_owner.GetColourState() == Player::Player::ColourState::White) {
    }
    if (_owner.GetColourState() == Player::Player::ColourState::Black) {
      _owner.ResetPos();
    }
  }
  // 死亡判定を取るメッシュと当たり判定
  if (_owner.GetColourState() == Player::Player::ColourState::White) {
    pos = _owner.GetCollision().GetIsHitBDeathMesh().CheckHitBDeathMesh(pos, { 0.f, forward.y, 0.f });
  }
  // プレイヤーの色が異なっていたらリスポーン処理
  if (_owner.GetCollision().GetIsHitBDeathMesh().GetBDeathMesh().HitNum >= Hit) {
    if (_owner.GetColourState() == Player::Player::ColourState::White) {
      _owner.ResetPos();
    }
    if (_owner.GetColourState() == Player::Player::ColourState::Black) {
    }
  }
  // 座標更新
  _owner.SetPosition(pos);
}