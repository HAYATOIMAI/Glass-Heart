
/*********************************************************************
 * @file   StateJumpFall.cpp
 * @brief  
 * 
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/
#include "StateJumpFall.h"
#include "../Player/Player.h"
#include "../Collision/CollisionManager.h"

using namespace GlassHeart::State;

StateJumpFall::StateJumpFall(Player::Player& owner) : StateBase{owner} {
}

void StateJumpFall::Enter() {
}

void StateJumpFall::Input(AppFrame::InputManager& input) {
}

void StateJumpFall::Update() {
	_owner.SetPosition(_owner.GetCollision().CheckTerrain(_owner.GetPosition(), { 0, 300, 0 }));

	_owner.GetStateManage().GoToState("Idle");
}