/*********************************************************************
 * @file   StateJumpUp.cpp
 * @brief  上昇状態の宣言
 *
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/

#include "StateJumpUp.h"
#include "../Player/Player.h"
#include "../Collision/CollisionManager.h"
#include "../Model/ModelAnimeManager.h"

namespace {
  constexpr auto StraifVector = 6.5f;                      //!< 空中移動用のX軸移動量 
  constexpr auto Gravity = -0.8f;                          //!< 重力加速度
  constexpr auto InputThreshold = 5000;                    //!< 入力閾値
  constexpr auto InputThresholdMin = 1;                    //!< 入力最低値
  constexpr auto Hit = 1;                                  //!< ヒットしたかのフラグ
  constexpr auto JumpLoop = "Jump_Loop";                   //!< 遷移させるステートの文字列
  constexpr auto JumpFall = "JumpFall";                    //!< 遷移させるステートの文字列
  constexpr VECTOR JumpVeclosity = { 0.0f, 24.5f, 0.0f };  //!< 上昇量
}

GlassHeart::State::StateJumpUp::StateJumpUp(Player::Player& owner) : State::StateBase{ owner } {}
/** 入り口処理 */
void GlassHeart::State::StateJumpUp::Enter() {
  // ジャンプ速度設定
  VECTOR jumpbase = JumpVeclosity;
  _owner.SetJumpVelocity(jumpbase);
  // ジャンプ中のアニメーションを再生
  _owner.GetModelAnime().ChangeAnime(JumpLoop, true);
}
/** 入力処理 */
void GlassHeart::State::StateJumpUp::Input(AppFrame::Input::InputManager& input) {
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
void GlassHeart::State::StateJumpUp::Update() {
  auto pos = _owner.GetPosition();
  // 移動量ベクトルを取得
  auto forward = VScale(_owner.GetForward(), _owner.GetForwardSpeed());
  // ジャンプ上昇処理
  auto jumpVelocity = _owner.GetJumpVelocity();
  jumpVelocity.y += Gravity;
  forward.y = jumpVelocity.y;
  // プレイヤーの色を取得
  int state = static_cast<int> (_owner.GetColourState());
  // 空中の足場の底面と側面判定処理
  pos = _owner.GetCollision().GetIsHitSideBottom().CheckHitSideAndBottom(pos, { forward.x, 0.f, 0.f }, state);
  pos = _owner.GetCollision().GetIsHitSideBottom().CheckHitSideAndBottom(pos, { 0.f, forward.y, 0.f }, state);
  //　当たっていたら落下
  if (_owner.GetCollision().GetIsHitSideBottom().GetSideAndBottom().HitNum > 0) {
    jumpVelocity.y = 0.0f;
  }
  if (_owner.GetColourState() == Player::Player::ColourState::Black) {
    // 空中の足場とプレイヤーの色が異なっていたら落下
    if (_owner.GetCollision().GetIsHitSideBottom().GetWWallThroughMesh().HitNum > 0) {
      jumpVelocity.y = 0.0f;
    }
  }
  // 空中の足場とプレイヤーの色が異なっていたら落下
  if (_owner.GetColourState() == Player::Player::ColourState::White) {
    if (_owner.GetCollision().GetIsHitSideBottom().GetBWallThroughMesh().HitNum > 0) {
      jumpVelocity.y = 0.0f;
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
  // プレイヤーの色が異なっていたらリスポーン処理
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

  //移動ベクトルがマイナスになったら下降状態に移行
  if (jumpVelocity.y <= 0.0f) {
    _owner.GetStateManage().GoToState(JumpFall);
  }
  _owner.SetJumpVelocity(jumpVelocity);
}