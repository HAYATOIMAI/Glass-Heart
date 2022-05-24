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

 /** 入り口処理 */
void GlassHeart::State::StateIdle::Enter() {
	// ゲーム開始時プレイヤーの色を白にする
	if (_resetFlag == false) {
		_owner.SetWhite();
		_resetFlag = true;
	}

	_owner.SetForwardSpeed(0.0f);
	// 待機モーションを再生
	_owner.GetModelAnime().ChangeAnime("idle", true);
}
/** 入力処理 */
void GlassHeart::State::StateIdle::Input(AppFrame::Input::InputManager& input) {
	auto& game = _owner.GetGame();
	// スティック入力があれば移動
	if (input.GetJoyPad().GetXinputThumbLX()) {
		// 走り状態の効果音を再生
		game.GetSoundManager().PlayLoop("run");
		_owner.GetStateManage().PushBack("Run");
	}
	else if (!input.GetJoyPad().GetXinputThumbLX()) {
		game.GetSoundManager().StopSound("run");
	}
	// Aボタンが押されたらジャンプ状態へ移行
	if (input.GetJoyPad().GetXTriggerButtonA() && _recastCnt == 0) {
		// ジャンプ状態の効果音を再生
		game.GetSoundManager().Play("jump");
		// 入力を制限
		_recastCnt = 5;
		_owner.GetStateManage().PushBack("Jump");
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
	int state = static_cast<int>(_owner.GetColourState());
	pos = _owner.GetCollision().CheckHitFloor(pos, { 0.f, -10.f, 0.f }, state);
	// 色に関係なく当たるブロックと当たっていなかったら
	if (_owner.GetCollision().GetHitFloor().HitFlag == 0) {
		//
		if (_owner.GetColourState() == Player::Player::ColourState::Black) {
			if (_owner.GetCollision().GetBThrough().HitFlag == 1) {
				_owner.GetStateManage().GoToState("Fall");
			}
		}
		if (_owner.GetColourState() == Player::Player::ColourState::White) {
			if (_owner.GetCollision().GetWThrough().HitFlag == 1) {
				_owner.GetStateManage().GoToState("Fall");
			}
		}
	}
	_owner.SetPosition(pos);
}