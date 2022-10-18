/*********************************************************************
 * @file   StateJump.cpp
 * @brief  ジャンプ状態クラスの処理
 *
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/
#include "StateJump.h"
#include "../Player/Player.h"
#include "../Model/ModelAnimeManager.h"

namespace {
  constexpr auto JumpStart = "Jump_start";  //!< 遷移させるステートの文字列
  constexpr auto JumpUp = "JumpUp";         //!< 遷移させるステートの文字列
}

 /** コンストラクタ */
GlassHeart::State::StateJump::StateJump(Player::Player& owner) : StateBase{ owner } {}
/** 入り口処理 */
void GlassHeart::State::StateJump::Enter() {
  // ジャンプ開始モーション再生
  _owner.GetModelAnime().ChangeAnime(JumpStart, true);
}
/** 入力処理 */
void GlassHeart::State::StateJump::Input(AppFrame::Input::InputManager& input) {}
/** 更新処理 */
void GlassHeart::State::StateJump::Update() {
  _owner.GetStateManage().GoToState(JumpUp);
}