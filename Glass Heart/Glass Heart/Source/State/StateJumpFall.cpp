
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
#include "../Model/ModelAnimeManager.h"
#include <numbers>

namespace {
    constexpr auto StraifVector = 3.0f; // �X�g���C�t�pX���ړ���
    constexpr auto Gravity = -0.2f;  //!< �d�͉����x
    constexpr auto RightRotation = 90.0f * (std::numbers::pi_v<float> / 180.0f); //!< �E�����̊p�x
    constexpr auto LeftRotation = 270.0f * (std::numbers::pi_v<float> / 180.0f);  //!< �������̊p�x
}

using namespace GlassHeart;

State::StateJumpFall::StateJumpFall(Player::Player& owner) : StateBase{ owner } {}

void State::StateJumpFall::Enter() {
    _owner.GetModelAnime().ChangeAnime("Jump_End", true);
}

void State::StateJumpFall::Input(AppFrame::InputManager& input) {
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
void State::StateJumpFall::Update() {
    // ���͐����̈׃J�E���^������
    if (_cnt > 0) {
        --_cnt;
    }


    auto pos = _owner.GetPosition();

    auto forward = VScale(_owner.GetForward(), _owner.GetForwardSpeed());

    auto jumpVelocity = _owner.GetJumpVelocity();
    jumpVelocity.y += Gravity;
    _owner.SetJumpVelocity(jumpVelocity);

    forward.y = jumpVelocity.y;

    int state = static_cast<int> (_owner.GetColourState());
    pos = _owner.GetCollision().CheckHitSideAndBottom(pos, { forward.x, 0, 0 }, state);

    pos = _owner.GetCollision().CheckJumpStand(pos, { 0.f, forward.y, 0.f }, state);

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

    _owner.SetPosition(pos);

     //����Ɛڂ��Ă��邩
    //Landing();

    //auto pos = _owner.GetPosition();

    //// ���X�|�[������
    //if (_owner.GetCollision().GetWDeathMesh().HitNum >= 1) {

    //    if (_owner.GetColourState() == Player::Player::ColourState::White) {
    //        _owner.SetPosition(VGet(pos.x, pos.y, pos.z));
    //        
    //        // _owner.GetStateManage().PushBack("Dead");
    //    }
    //    if (_owner.GetColourState() == Player::Player::ColourState::Black) {
    //        _owner.ResetPos();
    //    }
    //}
    //if (_owner.GetCollision().GetBDeathMesh().HitNum >= 1)  {
    //    if (_owner.GetColourState() == Player::Player::ColourState::White) {
    //        _owner.ResetPos();
    //        // _owner.GetStateManage().PushBack("Dead");
    //    }
    //    if (_owner.GetColourState() == Player::Player::ColourState::Black) {           
    //        _owner.SetPosition(VGet(pos.x, pos.y, pos.z));
    //    }
    //}
}
void State::StateJumpFall::Landing() {

    //auto pos = _owner.GetPosition();
    //auto forward = VScale(_owner.GetForward(), _owner.GetForwardSpeed());

    // _owner.GetCollision().CheckJumpStand(_owner.GetPosition(), { 0.f, 3.f, 0.f });
    // _owner.GetCollision().CheckHitWDeathMesh(_owner.GetPosition(), { 0.f, 3.f, 0.f });
    // _owner.GetCollision().CheckHitBDeathMesh(_owner.GetPosition(), { 0.f, 3.f, 0.f });
    // _owner.GetCollision().CheckThroughBMesh(_owner.GetPosition(), { 0.f, 3.f, 0.f });
    // _owner.GetCollision().CheckThroughWMesh(_owner.GetPosition(), { 0.f, 3.f, 0.f });
    // _owner.GetCollision().CheckHitSideAndBottom(_owner.GetPosition(), { 0.f, 3.f, 0.f });

    //// �󒆂̑���Ɛڂ��Ă��Ȃ������������藎��������
    //// �r���X�e�B�b�N�̓��͂��������ꍇ�A���͂ɉ������p�x�ɕ␳
    //if (_owner.GetCollision().GetStand().HitFlag == 0) {
    //    if (_subVx > 1) {
    //        _owner.SetPosition(VGet(_owner.GetPosition().x + _subVx, _owner.GetPosition().y - DownVector, _owner.GetPosition().z));
    //        _subVx = 0;
    //    }
    //    else {
    //        _owner.SetPosition(VGet(_owner.GetPosition().x + _addVx, _owner.GetPosition().y - DownVector, _owner.GetPosition().z));
    //        _addVx = 0;
    //    }

    //    if (_owner.GetCollision().GetSideAndBottom().HitNum >= 1) {
    //        if (_owner.GetRotation().y == RightRotation) {
    //            _owner.SetRotation(VGet(0.0f, LeftRotation, 0.0f));
    //            _reVx += 80.0f;
    //        }
    //        else if (_owner.GetRotation().y == LeftRotation) {
    //            _owner.SetRotation(VGet(0.0f, RightRotation, 0.0f));
    //            _reVx += 80.0f;
    //        }
    //       // _owner.SetPosition(VGet(_owner.GetPosition().x + _reVx, _owner.GetPosition().y, _owner.GetPosition().z));
    //    }
    //}
    //else {
    //    // ���n�������Ԃ��폜
    //    _owner.GetStateManage().PushBack("Idle");
    //    //_addVx = 0.f;
    //}

    //// �󒆂̑���Ɛڂ��Ă��邩
    //if (_owner.GetCollision().GetStand().HitFlag == 1) {
    //        _owner.SetPosition(_owner.GetCollision().GetStand().HitPosition);
    //        // ���n�������Ԃ��폜
    //        _owner.GetStateManage().PushBack("Idle");
    //}
    //// ���F�̂ݓ����鑫��ɐڂ��Ă��邩
    //if (_owner.GetCollision().GetBThrough().HitFlag == 1) {
    //    // �ڂ��Ă��鑫��ƈقȂ�F�̏ꍇ�݂̂Ƃǂ܂�
    //    if (_owner.GetColourState() == Player::Player::ColourState::White) {
    //        _owner.SetPosition(_owner.GetCollision().GetBThrough().HitPosition);
    //        _owner.GetStateManage().PushBack("Idle");
    //    }
    //}
    //// ���F�̂ݓ����鑫��ɐڂ��Ă��邩
    //if (_owner.GetCollision().GetWThrough().HitFlag == 1) {
    //    // �ڂ��Ă��鑫��ƈقȂ�F�̏ꍇ�݂̂Ƃǂ܂�
    //    if (_owner.GetColourState() == Player::Player::ColourState::Black) {
    //        _owner.SetPosition(_owner.GetCollision().GetWThrough().HitPosition);
    //        _owner.GetStateManage().PushBack("Idle");
    //    }
    //}

    //_owner.GetCollision().CheckHitSecondJumpStand(_owner.GetPosition(), { 0.f, 3.f, 0.f });
    //_owner.GetCollision().CheckHitSecondThroughBMesh(_owner.GetPosition(), { 0.f, 3.f, 0.f });
    //_owner.GetCollision().CheckHitSecondThroughWMesh(_owner.GetPosition(), { 0.f, 3.f, 0.f });

    //if (_owner.GetCollision().GetSecondJumpStand().HitFlag == 0) {
    //    if (_subVx > 1) {
    //        _owner.SetPosition(VGet(_owner.GetPosition().x + _subVx, _owner.GetPosition().y - DownVector, _owner.GetPosition().z));
    //        _subVx = 0;
    //    }
    //    else {
    //        _owner.SetPosition(VGet(_owner.GetPosition().x + _addVx, _owner.GetPosition().y - DownVector, _owner.GetPosition().z));
    //        _addVx = 0;
    //    }
    //}
    //else  if (_owner.GetCollision().GetSecondJumpStand().HitFlag == 1) {
    //    _owner.SetPosition(_owner.GetCollision().GetSecondJumpStand().HitPosition);
    //    // ���n�������Ԃ��폜
    //    _owner.GetStateManage().PushBack("Idle");
    //}

    //if (_owner.GetCollision().GetSecondBThroughMesh().HitFlag == 1) {
    //    if (_owner.GetColourState() == Player::Player::ColourState::White) {
    //        _owner.SetPosition(_owner.GetCollision().GetSecondBThroughMesh().HitPosition);
    //        _owner.GetStateManage().PushBack("Idle");
    //    }
    //}

    //if (_owner.GetCollision().GetSecondWThroughMesh().HitFlag == 1) {
    //    if (_owner.GetColourState() == Player::Player::ColourState::Black) {
    //        _owner.SetPosition(_owner.GetCollision().GetSecondWThroughMesh().HitPosition);
    //        _owner.GetStateManage().PushBack("Idle");
    //    }
    //}
}