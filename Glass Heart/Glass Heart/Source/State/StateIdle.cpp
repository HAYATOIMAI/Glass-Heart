
/*****************************************************************//**
 * @file   StateIdle.cpp
 * @brief  アイドル状態クラスの処理
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "StateIdle.h"
#include <AppFrame.h>
#include "../Player/Player.h"
#include "../Model/ModelAnimeManager.h"
#include "../Collision/CollisionManager.h"

using namespace GlassHeart;

void State::StateIdle::Enter() {
	_owner.SetForwardSpeed(0.0f);
	_owner.GetModelAnime().ChangeAnime("idle", true);
}

void State::StateIdle::Input(AppFrame::InputManager& input) {
	if (input.GetJoyPad().GetXinputThumbLX()) {
		_owner.GetStateManage().PushBack("Run");
	}
	if (input.GetJoyPad().GetXTriggerButtonA() && _cnt == 0) {
		//連打防止のため5フレーム間入力を制限
		_cnt = 5;
		_owner.GetStateManage().PushBack("Jump");
	}
}

void State::StateIdle::Update() {
	// 足場と接しているか
	if (_owner.GetCollision().GetHitFloor().HitFlag == 1) {
	    _owner.SetPosition(_owner.GetCollision().GetHitFloor().HitPosition);
	}

	if (_owner.GetCollision().GetHitSecondFloor().HitFlag == 1) {
		_owner.SetPosition(_owner.GetCollision().GetHitSecondFloor().HitPosition);
	}

	if (_owner.GetCollision().GetBThrough().HitFlag == 1) {
		if (_owner.GetColourState() == Player::Player::ColourState::White) {
			_owner.SetPosition(_owner.GetCollision().GetBThrough().HitPosition);
		}
	}
	if (_owner.GetCollision().GetWThrough().HitFlag == 1) {
		if (_owner.GetColourState() == Player::Player::ColourState::Black) {
			_owner.SetPosition(_owner.GetCollision().GetWThrough().HitPosition);
		}	
	}
	// 入力制限の為カウンタを減少
	if (_cnt > 0) {
		--_cnt;
	}
}
