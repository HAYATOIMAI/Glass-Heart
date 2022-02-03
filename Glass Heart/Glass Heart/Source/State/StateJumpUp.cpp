
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
    if (_owner.GetPosition().y > 700.0f && _owner.GetPosition().y < 1200.0f) {
        _isfall = true;
    }
}

VECTOR StateJumpUp::JumpUpdate() {
    // �x�N�g���Ōv�Z
    VECTOR jumpPosition = VAdd(_owner.GetPosition(), _jumpVelocity);

    _jumpVelocity.y += _vY;

    return jumpPosition;
}
