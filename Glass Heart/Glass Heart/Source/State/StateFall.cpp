
/*********************************************************************
 * @file   StateFall.cpp
 * @brief  �v���C���[�̗����N���X�̏���
 * 
 * @author Hayato Imai
 * @date   February 2022
 *********************************************************************/
#include "StateFall.h"
#include "../Player/Player.h"
#include "../Model/ModelAnimeManager.h"
#include "../Collision/CollisionManager.h"
#include "../State/StateManager.h"
#include "../Application/GameMain.h"
#include "../Object/ObjectServer.h"
#include <numbers>
#include <AppFrame.h>

namespace {
    constexpr auto StraifVector = 6.5f; // �X�g���C�t�pX���ړ���
    constexpr auto JumpVecY = 0.0f;  //!< �W�����v�pY���ړ��ʃx�N�g��
    constexpr auto Gravity = -1.0f;  //!< �d�͉����x
    constexpr auto RightRotation = 90.0f * (std::numbers::pi_v<float> / 180.0f); //!< �E�����̊p�x
    constexpr auto LeftRotation = 270.0f * (std::numbers::pi_v<float> / 180.0f);  //!< �������̊p�x
}

using namespace GlassHeart;
/** ��������� */
void State::StateFall::Enter() {

    auto& game = _owner.GetGame();
    game.GetSoundManager().StopSound("run");

    _owner.SetJumpVelocity({ 0.f,5.5f,0.f });
}
/** ���͏��� */
void State::StateFall::Input(AppFrame::InputManager& input) {
    _owner.SetForwardSpeed(0.f);
    if (input.GetJoyPad().GetAnalogStickLX() >= 5000 && input.GetJoyPad().GetAnalogStickLX() > 1) {
        // �E�����Ɍ�����ύX
        _owner.SetRotation(VGet(0.0f, RightRotation, 0.0f));
        _owner.SetForwardSpeed(StraifVector);
    }
    if (input.GetJoyPad().GetAnalogStickLX() <= -5000 && input.GetJoyPad().GetAnalogStickLX() < 1) {
        // �������Ɍ�����ύX
        _owner.SetRotation(VGet(0.0f, LeftRotation, 0.0f));
        _owner.SetForwardSpeed(StraifVector);
    }
}
/** �X�V���� */
void State::StateFall::Update() {
    
    auto pos = _owner.GetPosition();
    // �ړ��ʃx�N�g�����擾
    auto forward = VScale(_owner.GetForward(), _owner.GetForwardSpeed());
    // ���~����
    auto jumpVelocity = _owner.GetJumpVelocity();
    jumpVelocity.y += Gravity;
    _owner.SetJumpVelocity(jumpVelocity);

    forward.y = jumpVelocity.y;
    // �v���C���[�̐F���擾
    int state = static_cast<int> (_owner.GetColourState());
    // �󒆂̑���̒�ʂƑ��ʔ��菈��
    pos = _owner.GetCollision().CheckHitSideAndBottom(pos, { forward.x, 0.f, 0.f }, state);
    // ���Ƃ̓����蔻��
    pos = _owner.GetCollision().CheckJumpStand(pos, { 0.f, forward.y, 0.f }, state);
    // �������Ă�����ҋ@��Ԃֈڍs
    if (_owner.GetCollision().GetStand().HitFlag == 1) {
        _owner.GetStateManage().GoToState("Idle");
    }
    if (_owner.GetColourState() == Player::Player::ColourState::Black) {
        if (_owner.GetCollision().GetWThrough().HitFlag == 1) {
            _owner.GetStateManage().GoToState("Idle");
        }
    }
    if (_owner.GetColourState() == Player::Player::ColourState::White) {
        if (_owner.GetCollision().GetBThrough().HitFlag == 1) {
            _owner.GetStateManage().GoToState("Idle");
        }
    }
    // ���S�������郁�b�V���Ɠ����蔻��
    if (_owner.GetColourState() == Player::Player::ColourState::Black) {
        pos = _owner.GetCollision().CheckHitWDeathMesh(pos, { 0.f, forward.y, 0.f });
    }
    // �v���C���[�̐F���قȂ��Ă����烊�X�|�[������
    if (_owner.GetCollision().GetWDeathMesh().HitNum >= 1) {
        if (_owner.GetColourState() == Player::Player::ColourState::White) {
        }
        if (_owner.GetColourState() == Player::Player::ColourState::Black) {
            _owner.ResetPos();
        }
    }
    // ���S�������郁�b�V���Ɠ����蔻��
    if (_owner.GetColourState() == Player::Player::ColourState::Black) {
        pos = _owner.GetCollision().CheckHitWDeathMesh(pos, { 0.f, forward.y, 0.f });
    }
    // �v���C���[�̐F���قȂ��Ă����烊�X�|�[������
    if (_owner.GetCollision().GetBDeathMesh().HitNum >= 1) {
        if (_owner.GetColourState() == Player::Player::ColourState::White) {
            _owner.ResetPos();
        }
        if (_owner.GetColourState() == Player::Player::ColourState::Black) {
        }
    }
    // ���X�|�[������
    if (pos.y < -300.0f) {
        if (_owner.GetCheckPointFlag() == true) {
            // �I�u�W�F�N�g�T�[�o�[����`�F�b�N�|�C���g�̍��W���擾
            auto checkPos = _owner.GetObjectServer().GetPosition("CheckPoint");
            // �v���C���[�̍��W���`�F�b�N�|�C���g�ɂ���
            pos = checkPos;
        }
        else {
            pos = VGet(-150.f, 40.f, -55.f);
        }
    }
    // ���W�X�V
    _owner.SetPosition(pos);
}
