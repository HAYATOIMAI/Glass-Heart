
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
    constexpr auto JumpVecY = 80.0f;  //!< �W�����v�pY���ړ��ʃx�N�g��
    constexpr auto RerocateY = 35.0f; //!< ����̒�ʂ⑤�ʏՓˎ��̈ʒu�C����
}

using namespace GlassHeart;

State::StateJumpUp::StateJumpUp(Player::Player& owner) : State::StateBase{ owner } {}
/** ��������� */
void State::StateJumpUp::Enter() {
    if (_owner.GetRotation().y == 270.0f * (std::numbers::pi_v<float> / 180.0f)) {
        VECTOR jumpbase = VGet(0.0f, JumpVecY, 0.0f);
        _jumpVelocity = jumpbase;
    }
    else if (_owner.GetRotation().y == 90.0f * (std::numbers::pi_v<float> / 180.0f)) {
        VECTOR jumpbase = VGet(0.0f, JumpVecY, 0.0f);
        _jumpVelocity = jumpbase;
    }
    _owner.GetModelAnime().ChangeAnime("Jump_Loop", true);
}
void State::StateJumpUp::Input(AppFrame::InputManager& input) {
   
    if (input.GetJoyPad().GetAnalogStickLX() >= 5000 && input.GetJoyPad().GetAnalogStickLX() > 1) {
        // �E�����Ɍ�����ύX
        _owner.SetRotation(VGet(0.0f, 270.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f));
        _subVx -= StraifVector;
    }
    if (input.GetJoyPad().GetAnalogStickLX() <= -5000 && input.GetJoyPad().GetAnalogStickLX() < 1) {
        // �������Ɍ�����ύX
        _owner.SetRotation(VGet(0.0f, 90.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f));
        _addVx = StraifVector;
    }
    input.GetJoyPad().InputReject();
}
/** �X�V���� */
void State::StateJumpUp::Update() {

    auto jump = JumpUpdate();

    _owner.GetCollision().CheckHitSideAndBottom(_owner.GetPosition(), { 0.f, 3.f, 0.f });
    _owner.GetCollision().CheckHitWall(_owner.GetPosition(), { 0.f, 3.f, 0.f });
    _owner.GetCollision().CheckThroughBWallMesh(_owner.GetPosition(), { 0.f, 3.f, 0.f });
    _owner.GetCollision().CheckThroughWWallMesh(_owner.GetPosition(), { 0.f, 3.f, 0.f });

    // �������������͈ړ��x�N�g����0�ȉ��Ŗ�����Ώ㏸
    if (_isfall != true || jump.y > 0.f) {

        _position = _owner.GetPosition();

        // ��ʂɏՓ˂�����
        if (_owner.GetCollision().GetSideAndBottom().HitNum == 0) {
            // �Փ˂��Ă��Ȃ��̂ł��̂܂܃W�����v
            if (_addVx > 1) {
                _owner.SetPosition(VGet(_position.x  + _addVx, jump.y, jump.z));
                _addVx = 0;
            }
            else  {
                _owner.SetPosition(VGet(_position.x  + _subVx, jump.y, jump.z));
                _subVx = 0;
            }
        }
        else if (_owner.GetCollision().GetSideAndBottom().HitNum >= 1) {
            // �Փ˂����̂ŉ����߂�
            _owner.SetPosition(VGet(_position.x, _position.y - RerocateY, _position.z));
            _vX = 0.f;
            
        }
        // �ǖʂɏՓ˂�����
        if (_owner.GetCollision().CollPol().HitNum >= 1) {
            if (_owner.GetRotation().y == 270.0f * (std::numbers::pi_v<float> / 180.0f)) {
                _owner.SetRotation(VGet(0.0f, 90.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f));
                _vX -= 80.0f;
            } else  {
                _owner.SetRotation(VGet(0.0f, 270.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f));
                _vX += 80.0f;
            }
            _owner.SetPosition(VGet(_position.x + _vX, _position.y, _position.z));
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
    // �ړ��x�N�g�����}�C�i�X�ɂȂ����牺�~��ԂɈڍs
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
