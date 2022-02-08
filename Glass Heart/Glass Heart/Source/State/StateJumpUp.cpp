
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
    // �������Ŗ�����Ώ㏸
    if (_isfall != true) {
        auto j = JumpUpdate();
        _owner.SetPosition(j);
    }
    else {
        _owner.GetStateManage().PushBack("JumpFall");
    }
    // ���̍����ɒB�����痎���J�n
<<<<<<< HEAD
    if (_owner.GetPosition().y > 900.0f && _owner.GetPosition().y < 1500.0f) {
=======
    if (_owner.GetPosition().y > 1000.0f) {
>>>>>>> 20d15396b0340e91c89ed3ce4e63dcdfdc047354
        _isfall = true;
    }
}

VECTOR StateJumpUp::JumpUpdate() {
    // �x�N�g���Ōv�Z
    VECTOR jumpPosition = VAdd(_owner.GetPosition(), _jumpVelocity);

    _jumpVelocity.y += _vY;

    return jumpPosition;
}
