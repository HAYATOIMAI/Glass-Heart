
/*****************************************************************//**
 * @file   Player.cpp
 * @brief  プレイヤーの処理
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
#include <sstream>
#include <cmath>

using namespace GlassHeart::Player;

namespace {
	constexpr auto DegreeToRadian = DX_PI_F / 180.0f;
}

/** コンストラクタ */
Player::Player(GameMain& game) : GlassHeart::Object::ObjectBase{ game } {
	_jumpStartPosition = VGet(0.0f, 0.0f, 0.0f);
	_jumpVelocity = VGet(0.0f, 0.0f, 0.0f);
	_lastPosition = _position;
}
/** 入力処理 */
void Player::Input(AppFrame::InputManager& input) {
	_cameraManage->Input(input);

	_angularSpeed = 0;
	if (input.GetJoyPad().GetXinputThumbLX()) {

		auto fx = 0.0f; auto fy = 0.0f;
		auto isLeft = false;

		fx = static_cast<float>(input.GetJoyPad().GetAnalogStickLX() / 10000.f);
		fy = static_cast<float>(input.GetJoyPad().GetAnalogStickLY() / 10000.f);

		auto length = sqrt(fx * fx + fy * fy);
		auto analogMin = 0.2f;
		if (length < analogMin) {
			length = 0.0f;
		}
		else {
			length = 5.0f;
			isLeft = true;
		}
		if (fx > 0 ) {
			//_angularSpeed += 180.0f * (DX_PI_F / 180.0f);
		}
		else {
			_angularSpeed -= 180.0f * (DX_PI_F / 180.0f);
		}	
	}
	if (input.GetJoyPad().GetXinputButtonA()) {
		_isJump = true;
		if (_isJump) {
			JumpFunction(_isJump);
		}
	}

	_stateManage->Input(input);
}
/** 更新処理 */
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

	_lastPosition = _position;
}
/** 描画処理 */
void Player::Render() {
#ifdef _DEBUG
	
#endif // _DEBUG

	_stateManage->Draw();
}
/** ワールド座標変換 */
void Player::ComputeWorldTransform() {
	auto world = MGetScale(_scale);
	world = MMult(world, MGetRotZ(_rotation.z));
	world = MMult(world, MGetRotX(_rotation.x));
	world = MMult(world, MGetRotY(_rotation.y + DX_PI_F));
	_worldTransform = MMult(world, MGetTranslate(_position));
}
/** 移動処理 */
void Player::Move(const VECTOR& forward) {
	auto pos = _position;
	// X成分のみ移動後位置から真下に線分判定
	pos = _collsionManage->CheckTerrain(pos, { forward.x, forward.y, 0 });
	// Z成分のみ移動後位置から真下に線分判定
	pos = _collsionManage->CheckTerrain(pos, { 0, forward.y, forward.z });
	// 座標更新
	_position = pos;
}
void Player::JumpFunction(const bool isJumpStart) {
	if (isJumpStart) {
		JumpStart();
	}

	auto jumpposition = JumpProcess();

	if (isJumpStart || jumpposition.y > _groundY) {
		_position = jumpposition;
	}
	else {
		JumpEnd(jumpposition);
		_isJump = false;
	}
}
void Player::JumpStart()
{
	_jumpTimer = 0.0;
	_jumpStartPosition = _position;

	VECTOR jumpbase = VGet(0.0f, 0.0f, static_cast<float>(-_jumpPower));
	MATRIX jump_rotate = MMult(MGetRotX(static_cast<float>(_jumpAngle) * DegreeToRadian), MGetRotY(_rotation.y * DegreeToRadian));


	_jumpVelocity = VTransform(jumpbase, jump_rotate);
}
VECTOR Player::JumpProcess()
{
	// ベクトル
	VECTOR jumpposition = VAdd(_position, _jumpVelocity);

	_jumpVelocity.y -= static_cast<float> (_gravity);

	////放物線
	//VECTOR jumppos = VAdd(_jumpStartPosition, VScale(_jumpVelocity, _jumpTimer));
	//auto jumpY = (0.5 * _gravity * _jumpTimer * _jumpTimer);

	//jumppos.y -= jumpY;
	//_jumpTimer += 1.0;

	return jumpposition;
}
bool Player::JumpEnd(const VECTOR& jumppos) {
	if (_lastPosition.y < jumppos.y) {
		return false;
	}

	return false;
}
void Player::HitCheckEnemy() {
}
