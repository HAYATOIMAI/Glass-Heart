/*****************************************************************//**
 * @file   StateIdle.cpp
 * @brief  アイドル状態クラスの処理
 *
 * @author Hayato Imai, Yoshihiro Takahashi
 * @date   December 2021
 *********************************************************************/
#include "StateIdle.h"
#include <AppFrame.h>
#include "../Application/GameMain.h"
#include "../Player/Player.h"
#include "../Model/ModelAnimeManager.h"
#include "../Collision/CollisionManager.h"

namespace {
  constexpr int_fast16_t RecastTime = 5;                  //!< ジャンプ連打防止用リキャストタイム
  constexpr VECTOR LineSegment = { 0.0f, -10.0f, 0.0f };  //!< 当たり判定に使用する線分の長さ
  constexpr auto Hit = 1;                                 //!< ヒットしたかのフラグ
  constexpr auto Idle = "idle";                           //!< 遷移させるステートの文字列
  constexpr auto RunSound = "run";                        //!< 再生するサウンドの文字列
  constexpr auto RunState = "Run";                        //!< 遷移させるステートの文字列
  constexpr auto JumpSound = "jump";                      //!< 再生するサウンドの文字列
  constexpr auto JumpState = "Jump";                      //!< 遷移させるステートの文字列
  constexpr auto StateFall = "Fall";                      //!< 遷移させるステートの文字列
}

 /** 入り口処理 */
void GlassHeart::State::StateIdle::Enter() {
  // ゲーム開始時プレイヤーの色を白にする
  if (_resetFlag == false) {
    _owner.SetWhite();
    _resetFlag = true;
  }
  _owner.SetForwardSpeed(0.0f);
  // 待機モーションを再生
  _owner.GetModelAnime().ChangeAnime(Idle, true);
}
/** 入力処理 */
void GlassHeart::State::StateIdle::Input(AppFrame::Input::InputManager& input) {
  auto& game = _owner.GetGame();
  // スティック入力があれば移動
  if (input.GetJoyPad().GetXinputThumbLX()) {
    // 走り状態の効果音を再生
    game.GetSoundManager().PlayLoop(RunSound);
    _owner.GetStateManage().PushBack(RunState);
  }
  else if (!input.GetJoyPad().GetXinputThumbLX()) {
    game.GetSoundManager().StopSound(RunSound);
  }
  // Aボタンが押されたらジャンプ状態へ移行
  if (input.GetJoyPad().GetXTriggerButtonA() && _recastCnt == 0) {
    // ジャンプ状態の効果音を再生
    game.GetSoundManager().Play(JumpSound);
    // 入力を制限
    _recastCnt = RecastTime;
    _owner.GetStateManage().PushBack(JumpState);
  }
}
/** 更新処理 */
void GlassHeart::State::StateIdle::Update() {
  // 入力制限の為カウンタを減少
  if (_recastCnt > 0) {
    --_recastCnt;
  }
  // プレイヤーの色と床ブロックの色が同じ場合落下させる
  auto pos = _owner.GetPosition();
  // 床メッシュと線分での当たり判定
  auto state = static_cast<int_fast16_t>(_owner.GetColourState());
  pos = _owner.GetCollision().GetIsHitFloor().CheckHitFloor(pos, LineSegment, state);
  // 色に関係なく当たるブロックと当たっていなかったら
  if (_owner.GetCollision().GetIsHitFloor().GetHitFloor().HitFlag == 0) {
    //
    if (_owner.GetColourState() == Player::Player::ColourState::Black) {
      if (_owner.GetCollision().GetIsHitFloor().GetBThrough().HitFlag == Hit) {
        _owner.GetStateManage().GoToState(StateFall);
      }
    }
    if (_owner.GetColourState() == Player::Player::ColourState::White) {
      if (_owner.GetCollision().GetIsHitFloor().GetWThrough().HitFlag == Hit) {
        _owner.GetStateManage().GoToState(StateFall);
      }
    }
  }
  _owner.SetPosition(pos);
}