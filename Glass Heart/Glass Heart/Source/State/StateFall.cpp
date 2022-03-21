
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
    constexpr auto StraifVector = 3.0f; // �X�g���C�t�pX���ړ���
    constexpr auto JumpVecY = 0.0f;  //!< �W�����v�pY���ړ��ʃx�N�g��
    constexpr auto Gravity = -1.0f;  //!< �d�͉����x
    constexpr auto RightRotation = 90.0f * (std::numbers::pi_v<float> / 180.0f); //!< �E�����̊p�x
    constexpr auto LeftRotation = 270.0f * (std::numbers::pi_v<float> / 180.0f);  //!< �������̊p�x
}

using namespace GlassHeart;

void State::StateFall::Enter() {
    //VECTOR jumpbase = VGet(0.0f, JumpVecY, 0.0f);
    //_jumpVelocity = jumpbase;

    auto& game = _owner.GetGame();
    game.GetSoundManager().StopSound("run");

    _owner.SetJumpVelocity({ 0,3,0 });
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
        _owner.SetForwardSpeed(StraifVector);
    }
}

void State::StateFall::Update() {
    //���X�|�[������
    //if (_owner.GetCollision().GetBDeathMesh().HitNum >= 1) {
    //    if (_owner.GetColourState() == Player::Player::ColourState::White) {
    //        _owner.ResetPos();
    //        _owner.GetStateManage().PushBack("Dead");
    //    }
    //    if (_owner.GetColourState() == Player::Player::ColourState::Black) {
    //        // SetPosition(VGet(_position.x, _position.y, _position.z));

    //    }
    //}
    //if (_owner.GetCollision().GetWDeathMesh().HitNum >= 1) {
    //    if (_owner.GetColourState() == Player::Player::ColourState::White) {
    //    }
    //    if (_owner.GetColourState() == Player::Player::ColourState::Black) {
    //        _owner.ResetPos();
    //        _owner.GetStateManage().PushBack("Dead");
    //    }
    //}
    
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

    pos = _owner.GetCollision().CheckHitWDeathMesh(pos, { 0.f, forward.y, 0 });


    if (_owner.GetCollision().GetWDeathMesh().HitNum >= 1) {
        if (_owner.GetColourState() == Player::Player::ColourState::White) {
        }
        if (_owner.GetColourState() == Player::Player::ColourState::Black) {
           // _owner.ResetPos();
           _owner.GetStateManage().PushBack("Dead");
        }
    }

    pos = _owner.GetCollision().CheckHitBDeathMesh(pos, { 0.f, forward.y, 0 });

    if (_owner.GetCollision().GetBDeathMesh().HitNum >= 1) {
        if (_owner.GetColourState() == Player::Player::ColourState::White) {
            _owner.ResetPos();
            //_owner.GetStateManage().PushBack("Dead");
        }
        if (_owner.GetColourState() == Player::Player::ColourState::Black) {
            // SetPosition(VGet(_position.x, _position.y, _position.z));

        }
    }

    _owner.SetPosition(pos);
}

void State::StateFall::Landing() {

    //auto pos = _owner.GetPosition();
    //auto forward = VScale(_owner.GetForward(), _owner.GetForwardSpeed());

    //_owner.GetCollision().CheckJumpStand(_owner.GetPosition(), { 0.f, 3.f, 0.f });
    //_owner.GetCollision().CheckHitWDeathMesh(_owner.GetPosition(), { 0.f, 3.f, 0.f });
    //_owner.GetCollision().CheckHitBDeathMesh(_owner.GetPosition(), { 0.f, 3.f, 0.f });
    //_owner.GetCollision().CheckThroughBMesh(_owner.GetPosition(), { 0.f, 3.f, 0.f });
    //_owner.GetCollision().CheckThroughWMesh(_owner.GetPosition(), { 0.f, 3.f, 0.f });
    //_owner.GetCollision().CheckHitSideAndBottom(_owner.GetPosition(), { 0.f, 3.f, 0.f });

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
    //            _reVx -= 80.0f;
    //        }
    //        _owner.SetPosition(VGet(_owner.GetPosition().x + _reVx, _owner.GetPosition().y, _owner.GetPosition().z));
    //    }
    //}
    //else {
    //    // ���n�������Ԃ��폜
    //    _owner.GetStateManage().PushBack("Idle");
    //}
    //// �󒆂̑���Ɛڂ��Ă��邩
    //if (_owner.GetCollision().GetStand().HitFlag == 1) {
    //    _owner.SetPosition(_owner.GetCollision().GetStand().HitPosition);
    //    // ���n�������Ԃ��폜
    //    _owner.GetStateManage().PushBack("Idle");
    //}
    //// ���F�̂ݓ����鑫��ɐڂ��Ă��邩
    //if (_owner.GetCollision().GetBThrough().HitFlag == 1) {
    //    // �ڂ��Ă��鑫��ƈقȂ�F�̏ꍇ�݂̂Ƃǂ܂�
    //    if (_owner.GetColourState() == Player::Player::ColourState::White) {
    //        _owner.SetPosition(_owner.GetCollision().GetBThrough().HitPosition);
    //        // ���n�������Ԃ��폜
    //        _owner.GetStateManage().PushBack("Idle");
    //    }
    //}
    //// ���F�̂ݓ����鑫��ɐڂ��Ă��邩
    //if (_owner.GetCollision().GetWThrough().HitFlag == 1) {
    //    // �ڂ��Ă��鑫��ƈقȂ�F�̏ꍇ�݂̂Ƃǂ܂�
    //    if (_owner.GetColourState() == Player::Player::ColourState::Black) {
    //        _owner.SetPosition(_owner.GetCollision().GetWThrough().HitPosition);
    //        // ���n�������Ԃ��폜
    //        _owner.GetStateManage().PushBack("Idle");
    //    }
    //}
}
