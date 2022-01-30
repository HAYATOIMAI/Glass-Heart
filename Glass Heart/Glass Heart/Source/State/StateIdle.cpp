
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
	_owner.GetModelAnime().ChangeAnime("MO_SDChar_idle", true);
}

void StateIdle::Input(AppFrame::InputManager& input) {
	if (input.GetJoyPad().GetXinputButtonB()) {
		_owner.GetStateManage().PushBack("Action");
	}
	if (input.GetJoyPad().GetXinputThumbLX()) {
		_owner.GetStateManage().PushBack("Run");
	}
	//if (input.GetJoyPad().GetTrg().Buttons[XINPUT_BUTTON_A]) {
	//	_cnt = 60;
	//	_owner.GetStateManage().PushBack("Jump");
	//}
	if (input.GetJoyPad().GetXTriggerButtonA() && _cnt == 0) {
		_cnt = 60;
		_owner.GetStateManage().PushBack("Jump");
	}
}

void StateIdle::Update() {
	_owner.SetPosition(_owner.GetCollision().CheckTerrain(_owner.GetPosition(), { 0, 300, 0 }));
	
	if (_cnt > 0) {
		--_cnt;
	}
}
