
/*********************************************************************
 * @file   StateJumpUp.cpp
 * @brief  
 * 
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/

#include "StateJumpUp.h"
#include "../Player/Player.h"

using namespace GlassHeart::State;

StateJumpUp::StateJumpUp(Player::Player& owner) : StateBase{owner} {}

void StateJumpUp::Enter() {
    _vX = -16.0f;
    _vY = -6.0f;
}

void StateJumpUp::Input(AppFrame::InputManager& input) {}

void StateJumpUp::Update() {

    if (_isfall != true) {
        auto j = JumpUpdate();
        _owner.SetPosition(j);
    }
    else {
        _owner.GetStateManage().PushBack("JumpFall");
    }
    if (_owner.GetPosition().y > 700.0f && _owner.GetPosition().y < 1000.0f) {
        _isfall = true;
    }
}

VECTOR StateJumpUp::JumpUpdate() {
    // ベクトルで計算
    VECTOR jumpPosition = VAdd(_owner.GetPosition(), _jumpVelocity);

    _jumpVelocity.y += _vY;

    return jumpPosition;
   // return VECTOR();
}
