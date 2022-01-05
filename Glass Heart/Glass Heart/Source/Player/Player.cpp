
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
	// 角度の更新
	auto angle = GetRotation();
	angle.y += _angularSpeed;
	SetRotation(angle);
	// 状態の更新
	_stateManage->Update();
	// ワールド行列の更新
	ComputeWorldTransform();
	// モデルの更新
	_modelAnimeManage->Update();
	// カメラの更新
	_cameraManage->SetTarget(_position, GetForward());
	_cameraManage->Update();
	// オブジェクトサーバーに位置を送信
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
	// X成分のみ移動後位置から真下に線分判定
	pos = _collsionManage->CheckTerrain(pos, { forward.x, forward.y, 0 });
	// Z成分のみ移動後位置から真下に線分判定
	pos = _collsionManage->CheckTerrain(pos, { 0, forward.y, forward.z });
	// 座標更新
	_position = pos;
}
void Player::HitCheckEnemy() {
}