
/*********************************************************************
 * @file   StateJump.cpp
 * @brief  �W�����v��ԃN���X�̏���
 * 
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/

#include "StateJump.h"
#include "../Player/Player.h"
#include "../Model/ModelAnimeManager.h"
#include "../Collision/CollisionManager.h"
#include <numbers>
#include <AppFrame.h>

namespace {
    constexpr auto DegreeToRadian = std::numbers::pi_v<float> / 180.0f;
}

using namespace GlassHeart::State;

/** �R���X�g���N�^ */
StateJump::StateJump(Player::Player& owner) : StateBase{ owner } {
    _jumpStartPosition = VGet(0.0f, 0.0f, 0.0f);
    _jumpVelocity = VGet(0.0f, 0.0f, 0.0f);
    _lastPosition = _owner.GetPosition();
}
/** ��������� */
void StateJump::Enter() {

    _jumpTimer = 0.0f;
    _jumpStartPosition = _owner.GetPosition();

    VECTOR jumpbase = VGet(0.0f, _jumpPower, 0.0f);

    _jumpVelocity = jumpbase;

    _owner.GetModelAnime().ChangeAnime("MO_SDChar_jumpStart", true);
}
/** ���͏��� */
void StateJump::Input(AppFrame::InputManager& input) {
    if (input.GetJoyPad().GetXinputThumbLX()) {
        _owner.GetStateManage().PushBack("Run");
    }
    if (input.GetJoyPad().GetXTriggerButtonA()) {
        _gravity = -7.0f; // Y���̃W�����v��
       
        _isJump = true;
    }

}
/** �X�V���� */
void StateJump::Update() {

    /*_vY -= 1.0f;
    _jumpVelocity.y -= _vY;*/

    if (_isJump == true){
        
         JumpFunction(_isJump);
    }   
}

void StateJump::JumpFunction(const bool isJumpStart) {

   auto jump = JumpProcess();

    if (isJumpStart ||  jump.y > 70.0f) {
        _owner.SetPosition(jump);
        if (_owner.GetPosition().y > 700.f) {
            _owner.GetStateManage().PushBack("JumpUp");
        }
    }
    else {
       
        //JumpLand(jump);
        _isJump = false;
    }
}
/** �W�����v������ */
VECTOR StateJump::JumpProcess() {
    //�������̎��Ōv�Z
    //VECTOR jumpPosition = VAdd(_jumpStartPosition, VScale(_jumpVelocity, _jumpTimer));
    //auto jumpY = (0.5 * _gravity * _jumpTimer * _jumpTimer);

    //jumpPosition.y -= jumpY;
    //_jumpTimer += 1.0f;
    
    // �x�N�g���Ōv�Z
    VECTOR jumpPosition = VAdd(_owner.GetPosition(), _jumpVelocity);

    _jumpVelocity.y += _gravity;

    return jumpPosition;
}

bool StateJump::JumpLand(const VECTOR& pos) {
    if (_lastPosition.y < pos.y)
    {
        return false;
    }

   

    if (_owner.GetCollision().Mcrp().HitFlag == 1 && _jumpVelocity.y < 0) {
        _owner.SetPosition(VGet(0.0f, _owner.GetCollision().Mcrp().HitPosition.y, 0.0f));
        _jumpVelocity = VGet(0.0f, 0.0f, 0.0f);
        return true;
    }
    return false;
}