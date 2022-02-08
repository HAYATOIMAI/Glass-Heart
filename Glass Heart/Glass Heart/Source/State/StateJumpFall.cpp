
/*********************************************************************
 * @file   StateJumpFall.cpp
 * @brief  �v���C���[�̗������
 * 
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/
#include "StateJumpFall.h"
#include "../Player/Player.h"
#include "../Collision/CollisionManager.h"
#include <numbers>

using namespace GlassHeart::State;

StateJumpFall::StateJumpFall(Player::Player& owner) : StateBase{owner} {}

void StateJumpFall::Enter() {}

void StateJumpFall::Input(AppFrame::InputManager& input) {
    if (input.GetJoyPad().GetAnalogStickLX() >= 5000) {
        // �E�����Ɍ�����ύX
        _owner.SetRotation(VGet(0.0f, 270.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f));
        if (input.GetJoyPad().GetAnalogStickLX() >= 10000) {
            _owner.SetForwardSpeed(10.0f * 2.0f);
        }
    }
    if (input.GetJoyPad().GetAnalogStickLX() <= 5000) {
        // �������Ɍ�����ύX
        _owner.SetRotation(VGet(0.0f, 90.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f));
        if (input.GetJoyPad().GetAnalogStickLX() <= 10000) {
            _owner.SetForwardSpeed(1.0f * 2.0f);
        }
    }
}

void StateJumpFall::Update() {
    // ���̍����ȏゾ������@�n�ʂƐڂ��Ă��邩�m�F
    if (_owner.GetPosition().y >= 300) {
        //_owner.GetCollision().CheckJumpStand(_owner.GetPosition(), { 0, 3, 0 });
        _owner.GetCollision().CheckTerrain(_owner.GetPosition(), { 0, 300, 0 });
        // �󒆂̑���Ɛڂ��Ă��邩
        if (_owner.GetCollision().Mcrp().HitFlag == 1) {
            // �ڂ��Ă��鑫��ƈقȂ�F�̏ꍇ�݂̂Ƃǂ܂�
            if (_owner.GetCrName() == "White") {
                _owner.SetPosition(_owner.GetCollision().Mcrp().HitPosition);
            }
            _owner.GetStateManage().PushBack("Idle");
        }
        // �󒆂̑���Ɛڂ��Ă��Ȃ�������n��̑���ɖ߂�
        if (_owner.GetCollision().Mcrp().HitFlag == 0) {
            _owner.GetStateManage().PushBack("Idle");
        }
    }
}