/*********************************************************************
 * @file   StateFall.cpp
 * @brief  プレイヤーの落下クラスの処理
 *
 * @author Hayato Imai
 * @date   February 2022
 *********************************************************************/
#include "StateFall.h"
#include "../Player/Player.h"
#include "../Model/ModelAnimeManager.h"
#include "../Collision/CollisionManager.h"
#include "../State/StateManager.h"
#include "../Application/GameMain.h"
#include "../Object/ObjectServer.h"
#include <AppFrame.h>

namespace {
  constexpr auto AirMovementSpeed = 6.5f;              //!< 空中移動用のX軸移動量
  constexpr auto Gravity = -1.0f;                      //!< 重力加速度
  constexpr auto RespawnArea = -300.0f;                //!< エリア限界
  constexpr auto InputThresholdMax = 5000;             //!< 入力閾値
  constexpr auto InputThresholdMin = 1;                //!< 入力最低値
  constexpr auto Hit  = 1;                             //!< ヒットしたかのフラグ
  constexpr auto Idle = "Idle";                        //!< 遷移させるステート
  constexpr auto Fall = "fall";                        //!< 遷移させるステート
  constexpr auto Run = "run";                          //!< 遷移させるステート
  constexpr auto CheckPoint = "CheckPoint";            //!< オブジェクトサーバーから座標を取得する為の文字列
  constexpr VECTOR Position = { -150.f, 60.f, -55.f }; //!< 位置座標
  constexpr VECTOR Velocity = { 0.0f, 5.5f, 0.0f };    //!< 
}

/** 入り口処理 */
void GlassHeart::State::StateFall::Enter() {
  // 落下モーションを再生
  _owner.GetModelAnime().ChangeAnime(Fall, true);
  // 効果音を停止
  auto& game = _owner.GetGame();
  game.GetSoundManager().StopSound(Run);
  // 落下時のはじかれる距離をセット
  _owner.SetJumpVelocity(Velocity);
}
/** 入力処理 */
void GlassHeart::State::StateFall::Input(AppFrame::Input::InputManager& input) {
  auto right = _owner.RightRotation();
  auto left = _owner.LeftRotation();
  _owner.SetForwardSpeed(0.f);
  if (input.GetJoyPad().GetAnalogStickLX() >= InputThresholdMax && input.GetJoyPad().GetAnalogStickLX() > InputThresholdMin) {
    // 右方向に向きを変更
    _owner.SetRotation(VGet(0.0f, right, 0.0f));
    _owner.SetForwardSpeed(AirMovementSpeed);
  }
  if (input.GetJoyPad().GetAnalogStickLX() <= -InputThresholdMax && input.GetJoyPad().GetAnalogStickLX() < InputThresholdMin) {
    // 左方向に向きを変更
    _owner.SetRotation(VGet(0.0f, left, 0.0f));
    _owner.SetForwardSpeed(AirMovementSpeed);
  }
}
/** 更新処理 */
void GlassHeart::State::StateFall::Update() {
  auto pos = _owner.GetPosition();
  // 移動量ベクトルを取得
  auto forward = VScale(_owner.GetForward(), _owner.GetForwardSpeed());
  // 下降処理
  auto jumpVelocity = _owner.GetJumpVelocity();
  jumpVelocity.y += Gravity;
  _owner.SetJumpVelocity(jumpVelocity);
  forward.y = jumpVelocity.y;
  // プレイヤーの色を取得
  auto state = static_cast<std::int_fast8_t> (_owner.GetColourState());
  // 空中の足場の底面と側面判定処理
  pos = _owner.GetCollision().GetIsHitSideBottom().CheckHitSideAndBottom(pos, { forward.x, 0.0f, 0.0f }, state);
  // 床との当たり判定
  pos = _owner.GetCollision().GetIsHitJumpStand().CheckJumpStand(pos, { 0.0f, forward.y, 0.0f }, state);
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
    pos = _owner.GetCollision().GetIsHitWDeathMesh().CheckHitWDeathMesh(pos, { 0.0f, forward.y, 0.0f });
  }
  // プレイヤーの色が異なっていたらリスポーン処理
  if (_owner.GetCollision().GetIsHitWDeathMesh().GetWDeathMesh().HitNum >= Hit) {
    if (_owner.GetColourState() == Player::Player::ColourState::Black) {
      _owner.ResetPos();
    }
  }
  // 死亡判定を取るメッシュと当たり判定
  if (_owner.GetColourState() == Player::Player::ColourState::Black) {
    pos = _owner.GetCollision().GetIsHitWDeathMesh().CheckHitWDeathMesh(pos, { 0.0f, forward.y, 0.0f });
  }
  // プレイヤーの色が異なっていたらリスポーン処理
  if (_owner.GetCollision().GetIsHitBDeathMesh().GetBDeathMesh().HitNum >= Hit) {
    if (_owner.GetColourState() == Player::Player::ColourState::White) {
      _owner.ResetPos();
    }
  }
  // リスポーン処理
  if (pos.y < RespawnArea) {
    if (_owner.GetCheckPointFlag() == true) {
      // オブジェクトサーバーからチェックポイントの座標を取得
      auto checkPos = _owner.GetObjectServer().GetPosition(CheckPoint);
      // プレイヤーの座標をチェックポイントにする
      pos = checkPos;
    }
    else {
      pos = Position;
    }
  }
  // 座標更新
  _owner.SetPosition(pos);
}