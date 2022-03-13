
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
#include <numbers>
#include <AppFrame.h>

namespace {
    constexpr auto DownVector = 13.5f; // ���~��
    constexpr auto StraifVector = 10.0f; // �X�g���C�t�pX���ړ���
    constexpr auto JumpVecY = 0.0f;  //!< �W�����v�pY���ړ��ʃx�N�g��
    constexpr auto Gravity = -2.0f;
    constexpr auto RightRotation = 90.0f * (std::numbers::pi_v<float> / 180.0f); //!< �E�����̊p�x
    constexpr auto LeftRotation = 270.0f * (std::numbers::pi_v<float> / 180.0f);  //!< �������̊p�x
}

using namespace GlassHeart;

void State::StateFall::Enter() {
    VECTOR jumpbase = VGet(0.0f, JumpVecY, 0.0f);
    _jumpVelocity = jumpbase;
}

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
        _owner.SetForwardSpeed(-StraifVector);
    }
}

void State::StateFall::Update() {
    Landing();
    
    //auto pos = _owner.GetPosition();

    //auto forward = VScale(_owner.GetForward(), _owner.GetForwardSpeed());

    //_jumpVelocity.y += Gravity;

    //forward.y = _jumpVelocity.y;

    //pos = _owner.GetCollision().CheckJumpStand(VGet(pos.x + forward.x, pos.y, pos.z), _owner.GetForward());

    //if (_owner.GetCollision().GetStand().HitFlag == 0) {
    //    pos.x += forward.x;
    //}
    //else if (_owner.GetCollision().GetStand().HitFlag == 1) {
    //   // _owner.GetStateManage().GoToState("Idle");
    //}

    //pos = _owner.GetCollision().CheckJumpStand(VGet(pos.x, pos.y + forward.y, pos.z), _owner.GetForward());

    //if (_owner.GetCollision().GetStand().HitFlag == 0) {
    //    pos.y += forward.y;
    //}
    //else if (_owner.GetCollision().GetStand().HitFlag == 1) {
    //    _owner.GetStateManage().GoToState("Idle");
    //}

    //pos = _owner.GetCollision().CheckHitSecondFloor(VGet(pos.x + forward.x, pos.y, pos.z), _owner.GetForward());

    //if (_owner.GetCollision().GetHitSecondFloor().HitFlag == 0) {
    //    pos.x += forward.x;
    //}
    //else if (_owner.GetCollision().GetHitSecondFloor().HitFlag == 1) {
    //    //_owner.GetStateManage().GoToState("Idle");
    //}

    //pos = _owner.GetCollision().CheckHitSecondFloor(VGet(pos.x, pos.y + forward.y, pos.z), _owner.GetForward());

    //if (_owner.GetCollision().GetHitFloor().HitFlag == 0) {
    //    pos.y += forward.y;
    //}
    //else if (_owner.GetCollision().GetHitFloor().HitFlag == 1) {
    //    _owner.GetStateManage().GoToState("Idle");
    //}

    //_owner.SetPosition(pos);
    auto pos = _owner.GetPosition();

    // ���X�|�[������
    if (_owner.GetCollision().GetWDeathMesh().HitNum >= 1) {

        if (_owner.GetColourState() == Player::Player::ColourState::White) {
            _owner.SetPosition(VGet(pos.x, pos.y, pos.z));

            // _owner.GetStateManage().PushBack("Dead");
        }
        if (_owner.GetColourState() == Player::Player::ColourState::Black) {
            _owner.ResetPos();
        }
    }
    if (_owner.GetCollision().GetBDeathMesh().HitNum >= 1) {
        if (_owner.GetColourState() == Player::Player::ColourState::White) {
            _owner.ResetPos();
            // _owner.GetStateManage().PushBack("Dead");
        }
        if (_owner.GetColourState() == Player::Player::ColourState::Black) {
            _owner.SetPosition(VGet(pos.x, pos.y, pos.z));
        }
    }
}

void State::StateFall::Landing() {

    auto pos = _owner.GetPosition();
    auto forward = VScale(_owner.GetForward(), _owner.GetForwardSpeed());

    _owner.GetCollision().CheckJumpStand(pos, forward);
    _owner.GetCollision().CheckHitWDeathMesh(pos, forward);
    _owner.GetCollision().CheckHitBDeathMesh(pos, forward);
    _owner.GetCollision().CheckThroughBMesh(pos, forward);
    _owner.GetCollision().CheckThroughWMesh(pos, forward);
    _owner.GetCollision().CheckHitSideAndBottom(pos, forward);

    _owner.GetCollision().CheckHitSecondJumpStand(pos, forward);
    _owner.GetCollision().CheckHitSecondThroughBMesh(pos, forward);
    _owner.GetCollision().CheckHitSecondThroughWMesh(pos, forward);

    // �󒆂̑���Ɛڂ��Ă��Ȃ������������藎��������
    // �r���X�e�B�b�N�̓��͂��������ꍇ�A���͂ɉ������p�x�ɕ␳
    if (_owner.GetCollision().GetStand().HitFlag == 0) {
        _owner.SetPosition(VGet(_owner.GetPosition().x + _owner.GetForwardSpeed(), _owner.GetPosition().y - DownVector, _owner.GetPosition().z));

        if (_owner.GetCollision().GetSideAndBottom().HitNum >= 1) {
            if (_owner.GetRotation().y == RightRotation) {
                _owner.SetRotation(VGet(0.0f, LeftRotation, 0.0f));
                _reVx += 80.0f;
            }
            else if (_owner.GetRotation().y == LeftRotation) {
                _owner.SetRotation(VGet(0.0f, RightRotation, 0.0f));
                _reVx -= 80.0f;
            }
            _owner.SetPosition(VGet(_owner.GetPosition().x + _reVx, _owner.GetPosition().y, _owner.GetPosition().z));
        }
    }
    else {
        // ���n�������Ԃ��폜
        _owner.GetStateManage().PopBack();
    }
    // �󒆂̑���Ɛڂ��Ă��邩
    if (_owner.GetCollision().GetStand().HitFlag == 1) {
        _owner.SetPosition(_owner.GetCollision().GetStand().HitPosition);
        // ���n�������Ԃ��폜
        _owner.GetStateManage().PopBack();
    }
    // ���F�̂ݓ����鑫��ɐڂ��Ă��邩
    if (_owner.GetCollision().GetBThrough().HitFlag == 1) {
        // �ڂ��Ă��鑫��ƈقȂ�F�̏ꍇ�݂̂Ƃǂ܂�
        if (_owner.GetColourState() == Player::Player::ColourState::White) {
            _owner.SetPosition(_owner.GetCollision().GetBThrough().HitPosition);
            // ���n�������Ԃ��폜
            _owner.GetStateManage().PopBack();
        }
    }
    // ���F�̂ݓ����鑫��ɐڂ��Ă��邩
    if (_owner.GetCollision().GetWThrough().HitFlag == 1) {
        // �ڂ��Ă��鑫��ƈقȂ�F�̏ꍇ�݂̂Ƃǂ܂�
        if (_owner.GetColourState() == Player::Player::ColourState::Black) {
            _owner.SetPosition(_owner.GetCollision().GetWThrough().HitPosition);
            // ���n�������Ԃ��폜
            _owner.GetStateManage().PopBack();
        }
    }

    if (_owner.GetCollision().GetSecondBThroughMesh().HitFlag == 1) {
        if (_owner.GetColourState() == Player::Player::ColourState::White) {
            _owner.SetPosition(_owner.GetCollision().GetSecondBThroughMesh().HitPosition);
            // ���n�������Ԃ��폜
            _owner.GetStateManage().PopBack();
        }
    }

    if (_owner.GetCollision().GetSecondWThroughMesh().HitFlag == 1) {
        if (_owner.GetColourState() == Player::Player::ColourState::Black) {
            _owner.SetPosition(_owner.GetCollision().GetSecondWThroughMesh().HitPosition);
            // ���n�������Ԃ��폜
            _owner.GetStateManage().PopBack();
        }
    }
}
