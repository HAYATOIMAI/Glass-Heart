
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
#include <AppFrame.h>
#include <sstream>

using namespace GlassHeart::Player;
namespace {
    constexpr auto DegreeToRadian = DX_PI_F / 180.0f;
}


Player::Player(GameMain& game) : GlassHeart::Object::ObjectBase{ game } {
    _jumpStartPosition = VGet(0.0f, 0.0f, 0.0f);
    _jumpVelocity = VGet(0.0f, 0.0f, 0.0f);
    _lastPosition = _position;
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
    if (input.GetJoyPad().GetXinputButtonA()) {
        _isJump = true;
        if (_isJump) {
            JumpFunction(_isJump);
        }
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

    _lastPosition = _position;
}
void Player::Render() {
#ifdef _DEBUG
    std::stringstream ss;
    ss << "プレイヤー座標" << _position.x << _position.y << _position.z << "\n";
    DrawString(370 - 36, -25 + 115, ss.str().c_str(), GetColor(255, 255, 255));
#endif // _DEBUG

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
void GlassHeart::Player::Player::JumpFunction(const bool isJumpStart)
{
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
void GlassHeart::Player::Player::JumpStart()
{
    _jumpTimer = 0.0;
    _jumpStartPosition = _position;

    VECTOR jumpbase = VGet(0.0f, 0.0f, static_cast<float>(-_jumpPower));
    MATRIX jump_rotate = MMult(MGetRotX(static_cast<float>(_jumpAngle) * DegreeToRadian), MGetRotY(_rotation.y * DegreeToRadian));


    _jumpVelocity = VTransform(jumpbase, jump_rotate);
}
VECTOR GlassHeart::Player::Player::JumpProcess()
{
    // ベクトル
    VECTOR jumpposition = VAdd(_position, _jumpVelocity);

    _jumpVelocity.y -= static_cast<float>(_gravity);

    ////放物線
    //VECTOR jumppos = VAdd(_jumpStartPosition, VScale(_jumpVelocity, _jumpTimer));
    //auto jumpY = (0.5 * _gravity * _jumpTimer * _jumpTimer);

    //jumppos.y -= jumpY;
    //_jumpTimer += 1.0;

    return jumpposition;
}
bool Player::JumpEnd(const VECTOR& jumppos){
    if (_lastPosition.y < jumppos.y) {
        return false;
    }

    return false;
}
void Player::HitCheckEnemy() {
}
