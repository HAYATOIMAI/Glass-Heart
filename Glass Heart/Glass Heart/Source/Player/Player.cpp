
/*****************************************************************//**
 * @file   Player.cpp
 * @brief
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "Player.h"
#include "../Object/ObjectServer.h"
#include "../Camera/CameraManager.h"
#include "../Collision/CollisionManager.h"
#include "../Model/ModelAnimeManager.h"
#include "../State/StateManager.h"
#include "../Application/GameMain.h"
#include <AppFrame.h>

using namespace GlassHeart::Player;

Player::Player(GameMain& game) : GlassHeart::Object::ObjectBase{ game } {
}
void Player::Input(AppFrame::InputManager& input) {
	_cameraManage->Input(input);

	_angularSpeed = 0;
	if (input.GetJoyPad().GetXinputLeft()) {
		_angularSpeed -= (DX_PI_F / 180.0f) * 3.0f;
	}
	else if (input.GetJoyPad().GetXinputRight()) {
		_angularSpeed += (DX_PI_F / 180.0f) * 3.0f;
	}
	_stateManage->Input(input);
}
void Player::Process() {
	// �p�x�̍X�V
	auto angle = GetRotation();
	angle.y += _angularSpeed;
	SetRotation(angle);
	// ��Ԃ̍X�V
	_stateManage->Update();
	// ���[���h�s��̍X�V
	ComputeWorldTransform();
	// ���f���̍X�V
	_modelAnimeManage->Update();
	// �J�����̍X�V
	_cameraManage->SetTarget(_position, GetForward());
	_cameraManage->Update();
	// �I�u�W�F�N�g�T�[�o�[�Ɉʒu�𑗐M
	GetObjectServer().Register("Player", _position);

}
void Player::Render() {
	_stateManage->Draw();
}
void Player::ComputeWorldTransform() {
	auto world = MGetScale(_scale);
	world = MMult(world, MGetRotZ(_rotation.z));
	world = MMult(world, MGetRotX(_rotation.x));
	world = MMult(world, MGetRotY(_rotation.y + DX_PI_F));
	_worldTransform = MMult(world, MGetTranslate(_position));
}
void Player::Move(const VECTOR& forward) {
	auto pos = _position;
	// X�����݈̂ړ���ʒu����^���ɐ�������
	pos = _collsionManage->CheckTerrain(pos, { forward.x, forward.y, 0 });
	// Z�����݈̂ړ���ʒu����^���ɐ�������
	pos = _collsionManage->CheckTerrain(pos, { 0, forward.y, forward.z });
	// ���W�X�V
	_position = pos;
}
void Player::HitCheckEnemy() {
}