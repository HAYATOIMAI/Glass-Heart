
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

using namespace GlassHeart::State;

StateJumpUp::StateJumpUp(Player::Player& owner) : StateBase{ owner } {}
/** ��������� */
void StateJumpUp::Enter() {

    if (_owner.GetRotation().y == 270.0f * (std::numbers::pi_v<float> / 180.0f)) {
        VECTOR jumpbase = VGet(0.0f, 100.0f, 0.0f);
        _jumpVelocity = jumpbase;
    }
    else if (_owner.GetRotation().y == 90.0f * (std::numbers::pi_v<float> / 180.0f)) {
        VECTOR jumpbase = VGet(0.0f, 100.f, 0.0f);
        _jumpVelocity = jumpbase;
    }
    _owner.GetModelAnime().ChangeAnime("Jump_Loop", true);
}
/** �X�V���� */
void StateJumpUp::Update() {

    auto jump = JumpUpdate();

    _owner.GetCollision().CheckHitSideAndBottom(_owner.GetPosition(), { 0, 3, 0 });
    // ��������������Y��0�ȉ��Ŗ�����Ώ㏸
    if (_isfall != true || jump.y > 0.f) {
        if (_owner.GetCollision().GetSideAndBottom().HitNum == 0) {
            _vX = _owner.GetPosition().x;
            _owner.SetPosition(VGet(_vX, jump.y + _vY, _vZ));
           
        }
        else if (_owner.GetCollision().GetSideAndBottom().HitNum >= 1) {
           
            _owner.SetPosition(jump);
            _owner.GetStateManage().PushBack("Idle");
        }
       // _owner.SetPosition(jump);
        //_owner.GetCollision().CheckJumpStand(_owner.GetPosition(), { 0, 3, 0 });
        //_owner.GetCollision().CheckThroughBWallMesh(_owner.GetPosition(), { 0, 3, 0 });
        //_owner.GetCollision().CheckThroughWWallMesh(_owner.GetPosition(), { 0, 3, 0 });

        if (_owner.GetCollision().GetBWallThroughMesh().HitNum >= 1) {
            _owner.SetPosition(_owner.GetCollision().GetBWallThroughMesh().Dim->HitPosition);
        }
        if (_owner.GetCollision().GetWWallThroughMesh().HitNum >= 1) {
            _owner.SetPosition(_owner.GetCollision().GetWWallThroughMesh().Dim->HitPosition);
        }
    }
    // �ړ��x�N�g�����}�C�i�X�ɂȂ����牺�~��ԂɈڍs
    if (_jumpVelocity.y < 0) {
        _owner.GetStateManage().PushBack("JumpFall");
        _isfall = true;

    }
}
/** �W�����v������ */
VECTOR StateJumpUp::JumpUpdate() {
    // �x�N�g���Ōv�Z
    VECTOR jumpPosition = VAdd(_owner.GetPosition(), _jumpVelocity);

    _jumpVelocity.y += _jY;

    return jumpPosition;
}
