
/*****************************************************************//**
 * @file   StateRun.cpp
 * @brief  �����ԃN���X�̏���
 *
 * @author Hayato Imai, 
 * @date   January 2022
 *********************************************************************/
#include "StateRun.h"
#include "../Application/GameMain.h"
#include "../Player/Player.h"
#include "../Collision/CollisionManager.h"
#include "../Model/ModelAnimeManager.h"
#include <AppFrame.h>
#include <numbers>

using namespace GlassHeart;

namespace {
    constexpr auto DefaultSpeed = 8.5f / 1.5f; //!< ���s�X�s�[�h
    constexpr auto RightRotation = 90.0f * (std::numbers::pi_v<float> / 180.0f);  //!< �E�����̊p�x
    constexpr auto LeftRotation = 270.0f * (std::numbers::pi_v<float> / 180.0f);  //!< �������̊p�x
}

void State::StateRun::Enter() {
    _owner.SetForwardSpeed(DefaultSpeed);
    // ����A�j���[�V�������Đ�
    _owner.GetModelAnime().ChangeAnime("dash", true);
}

void State::StateRun::Input(AppFrame::InputManager& input) {
    auto& game = _owner.GetGame();
    // A�{�^���������ꂽ��W�����v��Ԃֈڍs
    if (input.GetJoyPad().GetXTriggerButtonA()) {
        game.GetSoundManager().Play("jump");
        _owner.GetStateManage().PushBack("Jump");
    }
    // �X�e�B�b�N���͂�����Έړ�
    if (input.GetJoyPad().GetAnalogStickLX() >= 3000) {
        // �E�����Ɍ�����ύX
        _owner.SetRotation(VGet(0.0f, RightRotation, 0.0f));
    }
    else if (input.GetJoyPad().GetAnalogStickLX() <= -3000) {
        // �������Ɍ�����ύX
        _owner.SetRotation(VGet(0.0f, LeftRotation, 0.0f));
    }
    else {
        // �������͂�������΃A�C�h����Ԃֈڍs
        _owner.GetStateManage().PopBack();
    }
}
/** �X�V���� */
void State::StateRun::Update() {
    // �ړ�����
    _owner.Move(VScale(_owner.GetForward(), _owner.GetForwardSpeed()));
}
