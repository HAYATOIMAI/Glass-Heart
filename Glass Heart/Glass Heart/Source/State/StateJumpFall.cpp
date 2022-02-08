
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
#include <numbers>
<<<<<<< HEAD
=======


namespace {
	constexpr auto DownVector = 20; // 1�b���Ƃ̉��~��
	constexpr auto StraifVector = 18.0f; // �X�g���C�t�pX���ړ���
}
>>>>>>> 20d15396b0340e91c89ed3ce4e63dcdfdc047354

using namespace GlassHeart::State;

StateJumpFall::StateJumpFall(Player::Player& owner) : StateBase{ owner } {}

void StateJumpFall::Enter() {}

void StateJumpFall::Input(AppFrame::InputManager& input) {
<<<<<<< HEAD
    if (input.GetJoyPad().GetAnalogStickLX() >= 5000) {
        // �E�����Ɍ�����ύX
        _owner.SetRotation(VGet(0.0f, 270.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f));
        if (input.GetJoyPad().GetAnalogStickLX() >= 10000) {
            _owner.SetForwardSpeed(10.0f * 2.0f);
        }
    }
    if (input.GetJoyPad().GetAnalogStickLX() <= 5000) {
        // �������Ɍ�����ύX
        _owner.SetRotation(VGet(0.0f, 90.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f));
        if (input.GetJoyPad().GetAnalogStickLX() <= 10000) {
            _owner.SetForwardSpeed(1.0f * 2.0f);
        }
    }
}

void StateJumpFall::Update() {
    // ���̍����ȏゾ������@�n�ʂƐڂ��Ă��邩�m�F
    if (_owner.GetPosition().y >= 300) {
<<<<<<< HEAD
        //_owner.GetCollision().CheckJumpStand(_owner.GetPosition(), { 0, 3, 0 });
=======
        _owner.GetCollision().CheckJumpStand(_owner.GetPosition(), { 0, 300, 0 });
>>>>>>> 989e81406f870dcb22c2ed52ae5680147a58cf2f
        _owner.GetCollision().CheckTerrain(_owner.GetPosition(), { 0, 300, 0 });
        // �󒆂̑���Ɛڂ��Ă��邩
        if (_owner.GetCollision().Mcrp().HitFlag == 1) {
            // �ڂ��Ă��鑫��ƈقȂ�F�̏ꍇ�݂̂Ƃǂ܂�
            if (_owner.GetCrName() == "White") {
                _owner.SetPosition(_owner.GetCollision().Mcrp().HitPosition);
            }
            _owner.GetStateManage().PushBack("Idle");
        }
        // �󒆂̑���Ɛڂ��Ă��Ȃ�������n��̑���ɖ߂�
        if (_owner.GetCollision().Mcrp().HitFlag == 0) {
            _owner.GetStateManage().PushBack("Idle");
        }
    }
=======

	if (input.GetJoyPad().GetAnalogStickLX() >= 6000) {
		// �E�����Ɍ�����ύX
		_owner.SetRotation(VGet(0.0f, 270.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f));
		_addVx = -StraifVector;
	}
	if (input.GetJoyPad().GetAnalogStickLX() <= 6000) {
		// �������Ɍ�����ύX
		_owner.SetRotation(VGet(0.0f, 90.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f));
		_addVx = StraifVector;
	}
}

void StateJumpFall::Update() {
	// ����Ɛڂ��Ă��邩
	_owner.GetCollision().CheckJumpStand(_owner.GetPosition(), { 0, 3, 0 });

	// �󒆂̑���Ɛڂ��Ă��Ȃ������������藎��������
	// �r���X�e�B�b�N�̓��͂��������ꍇ�A���͂ɉ������p�x�ɕ␳
	if (_owner.GetCollision().GetStand().HitFlag == 0) {
		_owner.SetPosition(VGet(_owner.GetPosition().x /*+ _addVx*/, _owner.GetPosition().y - DownVector, _owner.GetPosition().z));
	}
	else {
		// ���n�������Ԃ��폜
		_owner.GetStateManage().PopBack();
	}

	// �󒆂̑���Ɛڂ��Ă��邩
	if (_owner.GetCollision().GetStand().HitFlag == 1) {
		// �ڂ��Ă��鑫��ƈقȂ�F�̏ꍇ�݂̂Ƃǂ܂�
		if (_owner.GetCrName() == "White") {
			_owner.SetPosition(_owner.GetCollision().GetStand().HitPosition);
			// ���n�������Ԃ��폜
			_owner.GetStateManage().PopBack();
		}
	}
>>>>>>> 20d15396b0340e91c89ed3ce4e63dcdfdc047354
}