
/*********************************************************************
 * @file   StateJumpUp.cpp
 * @brief  
 * 
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/

#include "StateJumpUp.h"
#include "../Player/Player.h"
#include <numbers>


using namespace GlassHeart::State;

StateJumpUp::StateJumpUp(Player::Player& owner) : StateBase{owner} {}

void StateJumpUp::Enter() {
    _vX = -7.0f;
    _vY = -16.0f;
}

void StateJumpUp::Input(AppFrame::InputManager& input) {}

void StateJumpUp::Update() {
    // 落下中で無ければ上昇
    if (_isfall != true) {
        auto j = JumpUpdate();
        _owner.SetPosition(j);
    }
    else {
        _owner.GetStateManage().PushBack("JumpFall");
    }
    // 一定の高さに達したら落下開始
<<<<<<< HEAD
    if (_owner.GetPosition().y > 900.0f && _owner.GetPosition().y < 1500.0f) {
=======
    if (_owner.GetPosition().y > 1000.0f) {
>>>>>>> 20d15396b0340e91c89ed3ce4e63dcdfdc047354
        _isfall = true;
    }
}

VECTOR StateJumpUp::JumpUpdate() {
    // ベクトルで計算
    VECTOR jumpPosition = VAdd(_owner.GetPosition(), _jumpVelocity);

    _jumpVelocity.y += _vY;

    return jumpPosition;
}
