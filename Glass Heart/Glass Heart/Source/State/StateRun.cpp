/*****************************************************************//**
 * @file   StateRun.cpp
 * @brief  走り状態クラスの処理
 *
 * @author Hayato Imai,
 * @date   January 2022
 *********************************************************************/
#include "StateRun.h"
#include "../Application/GameMain.h"
#include "../Player/Player.h"
#include "../Collision/CollisionManager.h"
#include "../Model/ModelAnimeManager.h"
#include <AppFrame.h>

namespace {
  constexpr auto DefaultSpeed = 5.6f;       //!< 歩行スピード
  constexpr auto InputThresholdMax = 3000;  //!< 入力閾値
  constexpr auto Dash = "dash";             //!< 再生するアニメーションの文字列
  constexpr auto StateJump = "Jump";        //!< 遷移させるステートの文字列
  constexpr auto PlaySoundEffect = "jump";  //!< 再生するSE
}
/** 入り口処理 */
void GlassHeart::State::StateRun::Enter() {
  // 移動速度を設定
  _owner.SetForwardSpeed(DefaultSpeed);
  // 走りアニメーションを再生
  _owner.GetModelAnime().ChangeAnime(Dash, true);
}
/** 入力処理 */
void GlassHeart::State::StateRun::Input(AppFrame::Input::InputManager& input) {
  auto right = _owner.RightRotation();
  auto left = _owner.LeftRotation();
  auto& game = _owner.GetGame();
  // Aボタンが押されたらジャンプ状態へ移行
  if (input.GetJoyPad().GetXTriggerButtonA()) {
    game.GetSoundManager().Play(PlaySoundEffect);
    _owner.GetStateManage().PushBack(StateJump);
  }
  // スティック入力があれば移動
  if (input.GetJoyPad().GetAnalogStickLX() >= InputThresholdMax) {
    // 右方向に向きを変更
    _owner.SetRotation(VGet(0.0f, right, 0.0f));
  }
  else if (input.GetJoyPad().GetAnalogStickLX() <= -InputThresholdMax) {
    // 左方向に向きを変更
    _owner.SetRotation(VGet(0.0f, left, 0.0f));
  }
  else {
    // 何も入力が無ければアイドル状態へ移行
    _owner.GetStateManage().PopBack();
  }
}
/** 更新処理 */
void GlassHeart::State::StateRun::Update() {
  // 移動処理
  _owner.Move(VScale(_owner.GetForward(), _owner.GetForwardSpeed()));
}