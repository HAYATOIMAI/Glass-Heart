
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
}

void StateIdle::Input(AppFrame::InputManager& input) {
	if (input.GetJoyPad().GetXinputThumbLX()) {
		_owner.GetStateManage().PushBack("Run");
	}
	if (input.GetJoyPad().GetXTriggerButtonA() && _cnt == 0) {
		_cnt = 60;
		_owner.GetStateManage().PushBack("Jump");
	}
}

void StateIdle::Update() {
	// 空中の足場と接しているか
	if (_owner.GetCollision().Mcrp().HitFlag == 1) {
		// 接している足場と異なる色の場合のみとどまる
		if (_owner.GetCrName() == "White") {
<<<<<<< HEAD
			_owner.SetPosition(_owner.GetCollision().CheckTerrain(_owner.GetPosition(), { 0, 700, 0 }));
=======
			_owner.SetPosition(_owner.GetCollision().CheckJumpStand(_owner.GetPosition(), { 0, 300, 0 }));
>>>>>>> 20d15396b0340e91c89ed3ce4e63dcdfdc047354
		}
		else if (_owner.GetCrName() == "Black") {
			_owner.SetPosition(_owner.GetCollision().CheckTerrain(_owner.GetPosition(), { 0, 700, 0 }));
		}
	}
	// 空中の足場と接していなかったら地上の足場に戻す
<<<<<<< HEAD
	if (_owner.GetCollision().Mcrp().HitFlag == 0) {
		_owner.SetPosition(_owner.GetCollision().CheckTerrain(_owner.GetPosition(), { 0, 700, 0 }));
=======
	if (_owner.GetCollision().GetStand().HitFlag == 0) {
		_owner.SetPosition(_owner.GetCollision().CheckTerrain(_owner.GetPosition(), { 0, 300, 0 }));
>>>>>>> 20d15396b0340e91c89ed3ce4e63dcdfdc047354
	}

	if (_cnt > 0) {
		--_cnt;
	}
}
