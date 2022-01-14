
/*****************************************************************//**
 * @file   StateRun.cpp
 * @brief  ‘–‚èó‘ÔƒNƒ‰ƒX‚Ìˆ—
 * 
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/
#include "StateRun.h"
#include "../Player/Player.h"
#include "../Collision/CollisionManager.h"
#include "../Model/ModelAnimeManager.h"
#include <AppFrame.h>

using namespace GlassHeart::State;

void StateRun::Enter() {
	_owner.SetForwardSpeed(10.0f);
	_owner.GetModelAnime().ChangeAnime("MO_SDChar_run", true);
}

void StateRun::Input(AppFrame::InputManager& input) {

	if (input.GetJoyPad().GetXinputButtonB()) {
		_owner.GetStateManage().PushBack("Action");
	}
	if (input.GetJoyPad().GetXinputRight()) {
		return;
	}
	if (input.GetJoyPad().GetXinputButtonA()) {
		_owner.GetStateManage().PushBack("Jump");
	}
	_owner.GetStateManage().PopBack();
}

void StateRun::Update() {
	_owner.Move(VScale(_owner.GetForward(), _owner.GetForwardSpeed()));
}
