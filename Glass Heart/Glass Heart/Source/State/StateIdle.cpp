
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

using namespace GlassHeart::State;

void StateIdle::Enter() {
	_owner.SetForwardSpeed(0.0f);
	_owner.GetModelAnime().ChangeAnime("idle", true);

	//MV1SetupCollInfo(_owner.GetModelAnime().GetHandle(), MV1SearchFrame(_owner.GetModelAnime().GetHandle(), "CollisionNavMesh"), 4, 4, 4);
}

void StateIdle::Input(AppFrame::InputManager& input) {
	if (input.GetJoyPad().GetXinputThumbLX()) {
		_owner.GetStateManage().PushBack("Run");
	}
	if (input.GetJoyPad().GetXTriggerButtonA() && _cnt == 0) {
		//連打防止のため5フレーム間入力を制限
		_cnt = 5;
		_owner.GetStateManage().PushBack("Jump");
	}
}

void StateIdle::Update() {
	// 空中の足場と接しているか
	if (_owner.GetCollision().Mcrp().HitFlag == 1) {
	    _owner.SetPosition(_owner.GetCollision().CheckHitFloor(_owner.GetPosition(), { 0, 3, 0 }));
	}

	if (_owner.GetCollision().GetBThrough().HitFlag == 1) {
		if (_owner.GetColourState() == Player::Player::ColourState::White) {
			_owner.SetPosition(_owner.GetCollision().CheckThroughBMesh(_owner.GetPosition(), { 0, 3, 0 }));
		}
	}
	if (_owner.GetCollision().GetWThrough().HitFlag == 1) {
		if (_owner.GetColourState() == Player::Player::ColourState::Black) {
			_owner.SetPosition(_owner.GetCollision().CheckThroughWMesh(_owner.GetPosition(), { 0, 3, 0 }));
		}	
	}
	// 入力制限の為カウンタを減少
	if (_cnt > 0) {
		--_cnt;
	}
}
