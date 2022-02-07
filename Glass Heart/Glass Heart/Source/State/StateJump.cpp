
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
    _jumpStartPosition = _owner.GetPosition();

    if (_owner.GetRotation().y == 270.0f * (std::numbers::pi_v<float> / 180.0f)) {
        VECTOR jumpbase = VGet(-12.0f, _jumpPower, 0.0f);
        _jumpVelocity = jumpbase;
    }
    else if(_owner.GetRotation().y ==  90.0f * (std::numbers::pi_v<float> / 180.0f)) {
        VECTOR jumpbase = VGet(12.0f, _jumpPower, 0.0f);
        _jumpVelocity = jumpbase;
    }

    _owner.GetModelAnime().ChangeAnime("Jump_start", true);
}
/** ���͏��� */
void StateJump::Input(AppFrame::InputManager& input) {
    if (input.GetJoyPad().GetXinputThumbLX()) {
        _owner.GetStateManage().PushBack("Run");
    }
    if (input.GetJoyPad().GetXTriggerButtonA()) {
        _gravity = -8.0f; // Y���̃W�����v��
        _isJump = true;
    }
}
/** �X�V���� */
void StateJump::Update() {
    // �Ή�����{�^���������ꂽ��W�����v�������s
    if (_isJump == true){
         JumpFunction(_isJump);
    }   

    

    // �󒆃u���b�N�̓V��Ƃ̓����蔻��(����@�\����)
    //_owner.GetCollision().CheckHitCeiling(_owner.GetPosition(), { 0, -100, 0 });

}
/** �W�����v�������� */
void StateJump::JumpFunction(const bool isJumpStart) {

    auto jump = JumpProcess();
    // ���̍����ȏォ�t���O��true�Ȃ�W�����v�J�n
    if (isJumpStart ||  jump.y > 70.0f) {
        _owner.SetPosition(jump);
        // ���̍����ȏ�ɂȂ�����㏸��ԂɈڍs
        if (_owner.GetPosition().y > 700.f) {

            _owner.GetStateManage().PushBack("JumpUp");
        }
    }
    else {
        _isJump = false;
    }

}
/** �W�����v������ */
VECTOR StateJump::JumpProcess() {
    
    // �x�N�g���Ōv�Z
    VECTOR jumpPosition = VAdd(_owner.GetPosition(), _jumpVelocity);

    _jumpVelocity.y += _gravity;

    return jumpPosition;
}