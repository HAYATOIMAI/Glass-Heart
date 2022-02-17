
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
    constexpr auto DownVector = 20; // ���~��
    constexpr auto StraifVector = 18.0f; // �X�g���C�t�pX���ړ���
}

using namespace GlassHeart::State;

StateJumpFall::StateJumpFall(Player::Player& owner) : StateBase{ owner } {}

void StateJumpFall::Enter() {
    _owner.GetModelAnime().ChangeAnime("Jump_End", true);
}

void StateJumpFall::Input(AppFrame::InputManager& input) {
    if (input.GetJoyPad().GetAnalogStickLX() >= 5000) {
        // �E�����Ɍ�����ύX
        _owner.SetRotation(VGet(0.0f, 270.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f));
        _addVx = -StraifVector;
    }
    if (input.GetJoyPad().GetAnalogStickLX() <= -5000) {
        // �������Ɍ�����ύX
        _owner.SetRotation(VGet(0.0f, 90.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f));
        _addVx = StraifVector;
    }
}
/** �X�V���� */
void StateJumpFall::Update() {
   
    // ����Ɛڂ��Ă��邩
    Landing();

    // ���X�|�[������
    if (_owner.GetCollision().GetDeathMesh().HitFlag == 1) {

        if (_owner.GetCrName() == "White") {
            _owner.ResetPos();
            // _owner.GetStateManage().PushBack("Dead");
        }
        if (_owner.GetCrName() == "Black") {
            _owner.SetPosition(_owner.GetCollision().GetDeathMesh().HitPosition);
        }
    }
    IsDeath();
}
void StateJumpFall::Landing() {

    _owner.GetCollision().CheckJumpStand(_owner.GetPosition(), { 0, 3, 0 });
    _owner.GetCollision().CheckHitDeathFloor(_owner.GetPosition(), { 0, 3, 0 });
    _owner.GetCollision().CheckThroughBMesh(_owner.GetPosition(), { 0, 3, 0 });
    _owner.GetCollision().CheckThroughWMesh(_owner.GetPosition(), { 0, 3, 0 });
   

    // �󒆂̑���Ɛڂ��Ă��Ȃ������������藎��������
    // �r���X�e�B�b�N�̓��͂��������ꍇ�A���͂ɉ������p�x�ɕ␳
    if (_owner.GetCollision().GetStand().HitFlag == 0) {
        _owner.SetPosition(VGet(_owner.GetPosition().x + _addVx, _owner.GetPosition().y - DownVector, _owner.GetPosition().z));
    }
    else {
        // ���n�������Ԃ��폜
        _owner.GetStateManage().PushBack("Idle");
        _addVx = 0.f;
    }

    // �󒆂̑���Ɛڂ��Ă��邩
    if (_owner.GetCollision().GetStand().HitFlag == 1) {
        // �ڂ��Ă��鑫��ƈقȂ�F�̏ꍇ�݂̂Ƃǂ܂�
        if (_owner.GetCrName() == "White" || _owner.GetCrName() == "Black") {
            _owner.SetPosition(_owner.GetCollision().GetStand().HitPosition);
            // ���n�������Ԃ��폜
            _owner.GetStateManage().PushBack("Idle");
        }
    }
    // ���F�̂ݓ����鑫��ɐڂ��Ă��邩
    if (_owner.GetCollision().GetBThrough().HitFlag == 1) {
        // �ڂ��Ă��鑫��ƈقȂ�F�̏ꍇ�݂̂Ƃǂ܂�
        if (_owner.GetCrName() == "White") {
            _owner.SetPosition(_owner.GetCollision().GetBThrough().HitPosition);
            _owner.GetStateManage().PushBack("Idle");
        }
    }
    // ���F�̂ݓ����鑫��ɐڂ��Ă��邩
    if (_owner.GetCollision().GetWThrough().HitFlag == 1) {
        // �ڂ��Ă��鑫��ƈقȂ�F�̏ꍇ�݂̂Ƃǂ܂�
        if (_owner.GetCrName() == "Black") {
            _owner.SetPosition(_owner.GetCollision().GetWThrough().HitPosition);
            _owner.GetStateManage().PushBack("Idle");
        }
    }

   
}

void StateJumpFall::IsDeath() {
    // ����������
    // �����K�u���b�N�ɒ��n������
    if (_owner.GetCollision().GetStand().HitFlag == 1) {
        // ���n����
        _owner.SetPosition(_owner.GetCollision().GetStand().HitPosition);
        auto landing = _owner.GetCollision().GetStand().HitPosition.y;
        // �ō��n�_�ƒ��n�n�_�Ƃ̍������擾
        auto difference = _owner.GetHighestPosition().y - landing;
        // �������傫�������玀�S
        if (difference > 50.0f) {
            _owner.ResetPos();
        }
    }
}