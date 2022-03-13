
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
    constexpr auto DownVector = 13.5f; // Y���̈ړ��ʃx�N�g�����~��
    constexpr auto JumpVecY = 20.0f;  //!< �W�����v�pY���ړ��ʃx�N�g��
    constexpr auto StraifVector = 10.0f; // �X�g���C�t�pX���ړ���
    constexpr auto Gravity = -1.0f;
    constexpr auto RightRotation = 90.0f * (std::numbers::pi_v<float> / 180.0f); //!< �E�����̊p�x
    constexpr auto LeftRotation = 270.0f * (std::numbers::pi_v<float> / 180.0f);  //!< �������̊p�x
}

using namespace GlassHeart;

State::StateJumpFall::StateJumpFall(Player::Player& owner) : StateBase{ owner } {}

void State::StateJumpFall::Enter() {

    // �W�����v���x�ݒ�
    //VECTOR jumpbase = VGet(0.0f, JumpVecY, 0.0f);
    //_jumpVelocity = jumpbase;

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
        _owner.SetForwardSpeed(-StraifVector);
    }
}
/** �X�V���� */
void State::StateJumpFall::Update() {
    // ���͐����̈׃J�E���^������
    if (_cnt > 0) {
        --_cnt;
    }

   // auto pos = _owner.GetPosition();

   // auto forward = VScale(_owner.GetForward(), _owner.GetForwardSpeed());

   // _jumpVelocity.y += Gravity;

   // forward.y = _jumpVelocity.y;

   //// (pos.x+forward.x, pos.y)��Wall_NavMesh�Ɣ���
   //// ������Fpos.x���̂܂܂ɂ��Ĉړ��L�����Z��
   //// �͂���Fpos.x+=forward.x�ړ�������

   //// (pos.x, pos.y+forward.y)��Wall_NavMesh�Ɣ���
   //// ������Fpos.y���̂܂܂ɂ��Ĉړ��L�����Z��
   //// �͂���Fpos.y+=forward.y�ړ�������

   //// �Ō�ɍX�V����
   //// _owner.SetPosition(pos);

   // pos = _owner.GetCollision().CheckJumpStand(VGet(pos.x + forward.x, pos.y, pos.z), _owner.GetForward());

   // if (_owner.GetCollision().GetStand().HitFlag == 0) {
   //     pos.x += forward.x;
   // }
   // else if (_owner.GetCollision().GetStand().HitFlag == 1) {
   //     //pos.x;
   //    // _owner.GetStateManage().GoToState("Idle");
   // }

   // pos = _owner.GetCollision().CheckJumpStand(VGet(pos.x, pos.y + forward.y, pos.z), _owner.GetForward());

   // if (_owner.GetCollision().GetStand().HitFlag == 0) {
   //     pos.y += forward.y;
   // }
   // else if (_owner.GetCollision().GetStand().HitFlag == 1) {
   //     //pos.y;
   //     _owner.GetStateManage().GoToState("Idle");
   // }

   // pos = _owner.GetCollision().CheckHitSecondJumpStand(VGet(pos.x + forward.x, pos.y, pos.z), _owner.GetForward());

   // if (_owner.GetCollision().GetSecondStand().HitFlag == 0) {
   //     pos.x += forward.x;
   // }
   // else if (_owner.GetCollision().GetSecondStand().HitFlag == 1) {
   //    // _owner.GetStateManage().GoToState("Idle");
   // }

   // pos = _owner.GetCollision().CheckHitSecondJumpStand(VGet(pos.x, pos.y + forward.y, pos.z), _owner.GetForward());

   // if (_owner.GetCollision().GetSecondStand().HitFlag == 0) {
   //     pos.y += forward.y;
   // }
   // else if (_owner.GetCollision().GetSecondStand().HitFlag == 1) {
   //     _owner.GetStateManage().GoToState("Idle");
   // }

   // pos = _owner.GetCollision().CheckThroughBMesh(VGet(pos.x + forward.x, pos.y, pos.z), _owner.GetForward());

   // if (_owner.GetCollision().GetBThrough().HitFlag == 0) {
   //     pos.x += forward.x;
   // }
   // else if (_owner.GetCollision().GetBThrough().HitFlag == 1) {
   //     pos.x;
   // }

   // pos = _owner.GetCollision().CheckThroughBMesh(VGet(pos.x, pos.y + forward.y, pos.z), _owner.GetForward());

   // if (_owner.GetCollision().GetBThrough().HitFlag == 0) {
   //     pos.y += forward.y;
   // }
   // else if (_owner.GetCollision().GetBThrough().HitFlag == 1) {
   //     _owner.GetStateManage().GoToState("Idle");
   // }

   // pos = _owner.GetCollision().CheckThroughWMesh(VGet(pos.x + forward.x, pos.y, pos.z), _owner.GetForward());

   // if (_owner.GetCollision().GetWThrough().HitFlag == 0) {
   //     pos.x += forward.x;
   // }
   // else if (_owner.GetCollision().GetWThrough().HitFlag == 1) {
   // }

   // pos = _owner.GetCollision().CheckThroughWMesh(VGet(pos.x, pos.y + forward.y, pos.z), _owner.GetForward());

   // if (_owner.GetCollision().GetWThrough().HitFlag == 0) {
   //     pos.y += forward.y;
   // }
   // else if (_owner.GetCollision().GetWThrough().HitFlag == 1) {
   //     _owner.GetStateManage().GoToState("Idle");
   // }

    //_owner.SetPosition(pos);
     //����Ɛڂ��Ă��邩
    Landing();

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
    if (_owner.GetCollision().GetBDeathMesh().HitNum >= 1)  {
        if (_owner.GetColourState() == Player::Player::ColourState::White) {
            _owner.ResetPos();
            // _owner.GetStateManage().PushBack("Dead");
        }
        if (_owner.GetColourState() == Player::Player::ColourState::Black) {           
            _owner.SetPosition(VGet(pos.x, pos.y, pos.z));
        }
    }
}
void State::StateJumpFall::Landing() {

    auto pos = _owner.GetPosition();
    auto forward = VScale(_owner.GetForward(), _owner.GetForwardSpeed());

     _owner.GetCollision().CheckJumpStand(pos, forward);
     _owner.GetCollision().CheckHitWDeathMesh(pos, forward );
     _owner.GetCollision().CheckHitBDeathMesh(pos, forward );
     _owner.GetCollision().CheckThroughBMesh(pos, forward );
     _owner.GetCollision().CheckThroughWMesh(pos, forward );
     _owner.GetCollision().CheckHitSideAndBottom(pos, forward);

     _owner.GetCollision().CheckHitSecondJumpStand(pos, forward);
     _owner.GetCollision().CheckHitSecondThroughBMesh(pos, forward);
     _owner.GetCollision().CheckHitSecondThroughWMesh(pos, forward);

    // �󒆂̑���Ɛڂ��Ă��Ȃ������������藎��������
    // �r���X�e�B�b�N�̓��͂��������ꍇ�A���͂ɉ������p�x�ɕ␳
    if (_owner.GetCollision().GetStand().HitFlag == 0) {
            _owner.SetPosition(VGet(pos.x +_owner.GetForwardSpeed(), pos.y - DownVector, pos.z));

        if (_owner.GetCollision().GetSideAndBottom().HitNum >= 1) {
            if (_owner.GetRotation().y == RightRotation) {
                _owner.SetRotation(VGet(0.0f, LeftRotation, 0.0f));
                _reVx += 80.0f;
            }
            else if (_owner.GetRotation().y == LeftRotation) {
                _owner.SetRotation(VGet(0.0f, RightRotation, 0.0f));
                _reVx += 80.0f;
            }
            _owner.SetPosition(VGet(pos.x + _reVx, pos.y, pos.z));
        }
    }
    else {
        // ���n�������Ԃ��폜
        _owner.GetStateManage().PushBack("Idle");
        //_addVx = 0.f;
    }

    // �󒆂̑���Ɛڂ��Ă��邩
    if (_owner.GetCollision().GetStand().HitFlag == 1) {
            _owner.SetPosition(_owner.GetCollision().GetStand().HitPosition);
            // ���n�������Ԃ��폜
            _owner.GetStateManage().PushBack("Idle");
    }
    // ���F�̂ݓ����鑫��ɐڂ��Ă��邩
    if (_owner.GetCollision().GetBThrough().HitFlag == 1) {
        // �ڂ��Ă��鑫��ƈقȂ�F�̏ꍇ�݂̂Ƃǂ܂�
        if (_owner.GetColourState() == Player::Player::ColourState::White) {
            _owner.SetPosition(_owner.GetCollision().GetBThrough().HitPosition);
            _owner.GetStateManage().PushBack("Idle");
        }
    }
    // ���F�̂ݓ����鑫��ɐڂ��Ă��邩
    if (_owner.GetCollision().GetWThrough().HitFlag == 1) {
        // �ڂ��Ă��鑫��ƈقȂ�F�̏ꍇ�݂̂Ƃǂ܂�
        if (_owner.GetColourState() == Player::Player::ColourState::Black) {
            _owner.SetPosition(_owner.GetCollision().GetWThrough().HitPosition);
            _owner.GetStateManage().PushBack("Idle");
        }
    }

    if (_owner.GetCollision().GetSecondJumpStand().HitFlag == 0) {
        _owner.SetPosition(VGet(pos.x + _owner.GetForwardSpeed(), pos.y - DownVector, pos.z));
    }
    else  if (_owner.GetCollision().GetSecondJumpStand().HitFlag == 1) {
        _owner.SetPosition(_owner.GetCollision().GetSecondJumpStand().HitPosition);
        // ���n�������Ԃ��폜
        _owner.GetStateManage().GoToState("Idle");
    }

    if (_owner.GetCollision().GetSecondBThroughMesh().HitFlag == 1) {
        if (_owner.GetColourState() == Player::Player::ColourState::White) {
            _owner.SetPosition(_owner.GetCollision().GetSecondBThroughMesh().HitPosition);
            _owner.GetStateManage().PushBack("Idle");
        }
    }

    if (_owner.GetCollision().GetSecondWThroughMesh().HitFlag == 1) {
        if (_owner.GetColourState() == Player::Player::ColourState::Black) {
            _owner.SetPosition(_owner.GetCollision().GetSecondWThroughMesh().HitPosition);
            _owner.GetStateManage().PushBack("Idle");
        }
    }
}