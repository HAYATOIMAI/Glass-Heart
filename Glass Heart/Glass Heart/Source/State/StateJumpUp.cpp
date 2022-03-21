
/*********************************************************************
 * @file   StateJumpUp.cpp
 * @brief  �㏸��Ԃ̐錾
 *
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/

#include "StateJumpUp.h"
#include "../Player/Player.h"
#include "../Collision/CollisionManager.h"
#include "../Model/ModelAnimeManager.h"
#include <numbers>

namespace {
    constexpr auto StraifVector = 6.5f;                                          //!< �X�g���C�t�pX���ړ���
    constexpr auto JumpVecY = 24.5f;                                             //!< Y���ړ��ʃx�N�g��
    constexpr auto Gravity = -0.8f;                                              //!< �d�͉����x
    constexpr auto RightRotation = 90.0f * (std::numbers::pi_v<float> / 180.0f); //!< �E�����̊p�x
    constexpr auto LeftRotation = 270.0f * (std::numbers::pi_v<float> / 180.0f); //!< �������̊p�x
}

using namespace GlassHeart;

State::StateJumpUp::StateJumpUp(Player::Player& owner) : State::StateBase{ owner } {}
/** ��������� */
void State::StateJumpUp::Enter() {
    // �W�����v���x�ݒ�
    VECTOR jumpbase = VGet(0.0f, JumpVecY, 0.0f);
    _owner.SetJumpVelocity(jumpbase);
    // �W�����v���̃A�j���[�V�������Đ�
    _owner.GetModelAnime().ChangeAnime("Jump_Loop", true);
}
/** ���͏��� */
void State::StateJumpUp::Input(AppFrame::InputManager& input) {
   
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
void State::StateJumpUp::Update() {

    auto pos = _owner.GetPosition();
    // �ړ��ʃx�N�g�����擾
    auto forward = VScale(_owner.GetForward(), _owner.GetForwardSpeed());
    // �W�����v�㏸����
    auto jumpVelocity = _owner.GetJumpVelocity();
    jumpVelocity.y += Gravity;

    forward.y = jumpVelocity.y;
    // �v���C���[�̐F���擾
    int state = static_cast<int> (_owner.GetColourState());
    // �󒆂̑���̒�ʂƑ��ʔ��菈��
    pos = _owner.GetCollision().CheckHitSideAndBottom(pos, { forward.x, 0.f, 0.f }, state);
    pos = _owner.GetCollision().CheckHitSideAndBottom(pos, { 0.f, forward.y, 0.f }, state);
    //�@�������Ă����痎��
    if (_owner.GetCollision().GetSideAndBottom().HitNum > 0) {
        jumpVelocity.y = 0;

    }
    if (_owner.GetColourState() == Player::Player::ColourState::Black) {
        // �󒆂̑���ƃv���C���[�̐F���قȂ��Ă����痎��
        if (_owner.GetCollision().GetWWallThroughMesh().HitNum > 0) {
            jumpVelocity.y = 0;
        }
    }
    // �󒆂̑���ƃv���C���[�̐F���قȂ��Ă����痎��
    if (_owner.GetColourState() == Player::Player::ColourState::White) {
        if (_owner.GetCollision().GetBWallThroughMesh().HitNum > 0) {
            jumpVelocity.y = 0;
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
           // _owner.GetStateManage().PushBack("Dead");
        }
    }
    // �v���C���[�̐F���قȂ��Ă����烊�X�|�[������
    if (_owner.GetColourState() == Player::Player::ColourState::White) {
        pos = _owner.GetCollision().CheckHitBDeathMesh(pos, { 0.f, forward.y, 0.f });
    }
    // �v���C���[�̐F���قȂ��Ă����烊�X�|�[������
    if (_owner.GetCollision().GetBDeathMesh().HitNum >= 1) {
        if (_owner.GetColourState() == Player::Player::ColourState::White) {
            _owner.ResetPos();
        }
        if (_owner.GetColourState() == Player::Player::ColourState::Black) {
        }
    }
    // ���W�X�V
    _owner.SetPosition(pos);

    //�ړ��x�N�g�����}�C�i�X�ɂȂ����牺�~��ԂɈڍs
    if (jumpVelocity.y <= 0) {
        _owner.GetStateManage().PushBack("JumpFall");
    }

    _owner.SetJumpVelocity(jumpVelocity);
}
