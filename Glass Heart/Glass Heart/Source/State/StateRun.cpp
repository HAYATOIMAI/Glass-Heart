
/*****************************************************************//**
 * @file   StateRun.cpp
 * @brief  �����ԃN���X�̏���
 *
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/
#include "StateRun.h"
#include "../Player/Player.h"
#include "../Collision/CollisionManager.h"
#include "../Model/ModelAnimeManager.h"
#include <AppFrame.h>
#include <numbers>

using namespace GlassHeart;

namespace {
    constexpr auto DefaultSpeed = 3.5f; //!< ���s�X�s�[�h
    constexpr auto RightRotation = 270.0f * (std::numbers::pi_v<float> / 180.0f); //!< �E�����̊p�x
    constexpr auto LeftRotation = 90.0f * (std::numbers::pi_v<float> / 180.0f);  //!< �������̊p�x
}

void State::StateRun::Enter() {
    _owner.SetForwardSpeed(DefaultSpeed);
    _owner.GetModelAnime().ChangeAnime("dash", true);
}

void State::StateRun::Input(AppFrame::InputManager& input) {
    // A�{�^���������ꂽ��W�����v��Ԃֈڍs
    if (input.GetJoyPad().GetXTriggerButtonA()) {
        _owner.GetStateManage().PushBack("Jump");
    }
    if (input.GetJoyPad().GetAnalogStickLX() >= 3000) {
        // �E�����Ɍ�����ύX
        _owner.SetRotation(VGet(0.0f, RightRotation, 0.0f));
        if (input.GetJoyPad().GetAnalogStickLX() >= 30000) {
            _owner.SetForwardSpeed(DefaultSpeed * 1.0f);
        }
    }
    else if (input.GetJoyPad().GetAnalogStickLX() <= -3000) {
        // �������Ɍ�����ύX
        _owner.SetRotation(VGet(0.0f, LeftRotation, 0.0f));
        if (input.GetJoyPad().GetAnalogStickLX() <= -30000) {
            _owner.SetForwardSpeed(DefaultSpeed * 1.0f);
        }
    }
    else {
        _owner.GetStateManage().PopBack();
    }
}

void State::StateRun::Update() {

    auto pos = _owner.GetPosition();

    _owner.Move(VScale(_owner.GetForward(), _owner.GetForwardSpeed()));


    _owner.GetCollision().CheckHitBDeathMesh(pos, { 0.f, 3.f, 0.f });
    _owner.GetCollision().CheckHitWDeathMesh(pos, { 0.f, 3.f, 0.f });

    // ���X�|�[������
    if (_owner.GetCollision().GetWDeathMesh().HitNum >= 1) {

        if (_owner.GetColourState() == Player::Player::ColourState::White) {
            //_owner.SetPosition();
        }
        if (_owner.GetColourState() == Player::Player::ColourState::Black) {
            _owner.ResetPos();
            // _owner.GetStateManage().PushBack("Dead");
        }
    } 
    if (_owner.GetCollision().GetBDeathMesh().HitNum >= 1) {
        if (_owner.GetColourState() == Player::Player::ColourState::White) {
            _owner.ResetPos();
            // _owner.GetStateManage().PushBack("Dead");
        }
        if (_owner.GetColourState() == Player::Player::ColourState::Black) {
           // _owner.SetPosition();
        }
    }
}
