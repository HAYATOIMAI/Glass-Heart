
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


namespace {
	constexpr auto DownVector = 20; // 1�b���Ƃ̉��~��
	constexpr auto StraifVector = 18.0f; // �X�g���C�t�pX���ړ���
}

using namespace GlassHeart::State;

StateJumpFall::StateJumpFall(Player::Player& owner) : StateBase{ owner } {}

void StateJumpFall::Enter() {}

void StateJumpFall::Input(AppFrame::InputManager& input) {

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
}