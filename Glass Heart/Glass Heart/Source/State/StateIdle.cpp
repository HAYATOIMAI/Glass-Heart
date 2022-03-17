
/*****************************************************************//**
 * @file   StateIdle.cpp
 * @brief  アイドル状態クラスの処理
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "StateIdle.h"
#include <AppFrame.h>
#include "../Application/GameMain.h"
#include "../Player/Player.h"
#include "../Model/ModelAnimeManager.h"
#include "../Collision/CollisionManager.h"

using namespace GlassHeart;

void State::StateIdle::Enter() {
	_owner.SetForwardSpeed(0.0f);
	_owner.GetModelAnime().ChangeAnime("idle", true);
}

void State::StateIdle::Input(AppFrame::InputManager& input) {
	auto& game = _owner.GetGame();

	if (input.GetJoyPad().GetXinputThumbLX()) {
		game.GetSoundManager().PlayLoop("run");
		_owner.GetStateManage().PushBack("Run");
	}
	else if (!input.GetJoyPad().GetXinputThumbLX()) {
		game.GetSoundManager().StopSound("run");
	}
	if (input.GetJoyPad().GetXTriggerButtonA() && _cnt == 0) {
		game.GetSoundManager().Play("jump");
		_cnt = 5;
		_owner.GetStateManage().PushBack("Jump");
	}
}

void State::StateIdle::Update() {
	//// 足場と接しているか
	//if (_owner.GetCollision().GetHitFloor().HitFlag == 1) {
	//    _owner.SetPosition(_owner.GetCollision().GetHitFloor().HitPosition);
	//}

	//if (_owner.GetCollision().GetHitSecondFloor().HitFlag == 1) {
	//	_owner.SetPosition(_owner.GetCollision().GetHitSecondFloor().HitPosition);
	//}

	//if (_owner.GetCollision().GetBThrough().HitFlag == 1) {
	//	if (_owner.GetColourState() == Player::Player::ColourState::White) {
	//		_owner.SetPosition(_owner.GetCollision().GetBThrough().HitPosition);
	//	}
	//}
	//if (_owner.GetCollision().GetWThrough().HitFlag == 1) {
	//	if (_owner.GetColourState() == Player::Player::ColourState::Black) {
	//		_owner.SetPosition(_owner.GetCollision().GetWThrough().HitPosition);
	//	}	
	//}

	// 入力制限の為カウンタを減少
	if (_cnt > 0) {
		--_cnt;
	}
}
