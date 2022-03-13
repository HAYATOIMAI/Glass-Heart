
/*********************************************************************
 * @file   StateJumpUp.cpp
 * @brief
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
    constexpr auto StraifVector = 10.0f; // �X�g���C�t�pX���ړ���
    constexpr auto JumpVecY = 40.0f;  //!< �W�����v�pY���ړ��ʃx�N�g��
    constexpr auto RerocateY = 35.0f; //!< ����̒�ʂ⑤�ʏՓˎ��̈ʒu�C����
    constexpr auto RightRotation = 90.0f * (std::numbers::pi_v<float> / 180.0f); //!< �E�����̊p�x
    constexpr auto LeftRotation = 270.0f * (std::numbers::pi_v<float> / 180.0f);  //!< �������̊p�x
}

using namespace GlassHeart;

State::StateJumpUp::StateJumpUp(Player::Player& owner) : State::StateBase{ owner } {}
/** ��������� */
void State::StateJumpUp::Enter() {
    // �W�����v���x�ݒ�
    VECTOR jumpbase = VGet(0.0f, JumpVecY, 0.0f);
    _jumpVelocity = jumpbase;

    _owner.GetModelAnime().ChangeAnime("Jump_Loop", true);
}
void State::StateJumpUp::Input(AppFrame::InputManager& input) {
   
    //if (input.GetJoyPad().GetAnalogStickLX() >= 5000 && input.GetJoyPad().GetAnalogStickLX() > 1) {
    //    // �E�����Ɍ�����ύX
    //    _owner.SetRotation(VGet(0.0f, RightRotation, 0.0f));
    //    _subVx += StraifVector;
    //}
    //if (input.GetJoyPad().GetAnalogStickLX() <= -5000 && input.GetJoyPad().GetAnalogStickLX() < 1) {
    //    // �������Ɍ�����ύX
    //    _owner.SetRotation(VGet(0.0f, LeftRotation, 0.0f));
    //    _addVx -= StraifVector;
    //}
    
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
    //input.GetJoyPad().InputReject();
}
/** �X�V���� */
void State::StateJumpUp::Update() {

    //auto pos = _owner.GetPosition();

    //auto forward = VScale(_owner.GetForward(), _owner.GetForwardSpeed());

    //_jumpVelocity.y += -2.0f;

    //forward.y = _jumpVelocity.y;
    //// forward������̈ړ���x��y

    //// (pos.x+forward.x, pos.y)��Wall_NavMesh�Ɣ���
    //// ������Fpos.x���̂܂܂ɂ��Ĉړ��L�����Z��
    //// �͂���Fpos.x+=forward.x�ړ�������

    //// (pos.x, pos.y+forward.y)��Wall_NavMesh�Ɣ���
    //// ������Fpos.y���̂܂܂ɂ��Ĉړ��L�����Z��
    //// �͂���Fpos.y+=forward.y�ړ�������

    //// �Ō�ɍX�V����
    //// _owner.SetPosition(pos);

    //pos =  _owner.GetCollision().CheckHitSideAndBottom(VGet(pos.x + forward.x, pos.y, pos.z), _owner.GetForward());

    //if (_owner.GetCollision().GetSideAndBottom().HitNum == 0) {
    //    pos.x += forward.x;
    //}
    //else if (_owner.GetCollision().GetSideAndBottom().HitNum >= 1) {
    //    pos.x;
    //    //_owner.GetStateManage().GoToState("Fall");
    //}

    //pos = _owner.GetCollision().CheckHitSideAndBottom(VGet(pos.x, pos.y + forward.y, pos.z), _owner.GetForward());

    //if (_owner.GetCollision().GetSideAndBottom().HitNum == 0) {
    //    pos.y += forward.y;
    //}
    //else if (_owner.GetCollision().GetSideAndBottom().HitNum >= 1) {
    //    pos.y;
    //    _owner.GetStateManage().GoToState("Fall");
    //}

    // _owner.SetPosition(pos);

    // if (_jumpVelocity.y < 0) {
    //     _owner.GetStateManage().PushBack("JumpFall");
    //     _isfall = true;
    // }

    auto jump = JumpUpdate();

    auto pos = _owner.GetPosition();

    auto forward = VScale(_owner.GetForward(), _owner.GetForwardSpeed());

    _owner.GetCollision().CheckHitSideAndBottom(pos, forward);
    _owner.GetCollision().CheckThroughBWallMesh(pos, forward);
    _owner.GetCollision().CheckThroughWWallMesh(pos, forward);

    // �������������͈ړ��x�N�g����0�ȉ��Ŗ�����Ώ㏸
    if (_isfall != true  || jump.y > 0.f) {

        _position = _owner.GetPosition();

        // ��ʂɏՓ˂�����
        if (_owner.GetCollision().GetSideAndBottom().HitNum == 0) {
            // �Փ˂��Ă��Ȃ��̂ł��̂܂܃W�����v
            _owner.SetPosition(VGet(pos.x + _owner.GetForwardSpeed(), jump.y, jump.z));
        }
        else if (_owner.GetCollision().GetSideAndBottom().HitNum >= 1) {
            // �Փ˂����̂ŉ����߂�
            //_owner.SetPosition(VGet(_position.x, _position.y - RerocateY, _position.z));
            _owner.GetStateManage().PushBack("Fall");
            _vX = 0.f;
            
        }
        // �ǖʂɏՓ˂�����
        if (_owner.GetCollision().GetSideAndBottom().HitNum >= 1) {
            if (_owner.GetRotation().y == RightRotation) {
                _owner.SetRotation(VGet(0.0f, LeftRotation, 0.0f));
                //_vX -= 80.0f;
                _owner.SetForwardSpeed(-80.0f);
            } else  {
                _owner.SetRotation(VGet(0.0f, RightRotation, 0.0f));
                //_vX += 80.0f;
                _owner.SetForwardSpeed(80.0f);
            }
            _owner.SetPosition(VGet(_position.x + _owner.GetForwardSpeed(), _position.y, _position.z));
            _vX = 0.f;
        }
        //if (_owner.GetCollision().GetBWallThroughMesh().HitNum == 0) {
        //    // �Փ˂��Ă��Ȃ��̂ł��̂܂܃W�����v
        //    _owner.SetPosition(VGet(_position.x, jump.y, jump.z));
        //}
        //else if (_owner.GetCollision().GetBWallThroughMesh().HitNum >= 1) {
        //    // �Փ˂����̂ŉ����߂�
        //    _owner.SetPosition(VGet(_position.x, _position.y - 35.f, _position.z));
        //}

        //if (_owner.GetCollision().GetWWallThroughMesh().HitNum == 0) {
        //    // �Փ˂��Ă��Ȃ��̂ł��̂܂܃W�����v
        //    _owner.SetPosition(VGet(_position.x, jump.y, jump.z));
        //}
        //else if (_owner.GetCollision().GetWWallThroughMesh().HitNum >= 1) {
        //    // �Փ˂����̂ŉ����߂�
        //    _owner.SetPosition(VGet(_position.x, _position.y - 35.f, _position.z));

        //}
    }
     //�ړ��x�N�g�����}�C�i�X�ɂȂ����牺�~��ԂɈڍs
    if (_jumpVelocity.y < 0) {
        _owner.GetStateManage().PushBack("JumpFall");
        _isfall = true;
    }
}
/** �W�����v������ */
VECTOR State::StateJumpUp::JumpUpdate() {
    // �x�N�g���Ōv�Z
    // �ړ��x�N�g���ɏd�͉����x�𑫂�������
    // 0��菬�����Ȃ����痎��
    VECTOR jumpPosition = VAdd(_owner.GetPosition(), _jumpVelocity);

    _jumpVelocity.y += _jY;

    return jumpPosition;
}
