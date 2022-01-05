
/*****************************************************************//**
 * @file   StateIdle.cpp
 * @brief  
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
	if (input.GetJoyPad().GetXinputRight()) {
		_owner.GetStateManage().PushBack("Run");
	}
}

void StateIdle::Update() {
	_owner.GetPosition() = _owner.GetCollision().CheckTerrain(_owner.GetPosition(), { 0, 300, 0 });

}
