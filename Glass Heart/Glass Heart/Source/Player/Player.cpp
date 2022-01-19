
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
#include <numbers>

using namespace GlassHeart::Player;

namespace {
    constexpr auto DegreeToRadian = std::numbers::pi_v<float> / 180.0f;
}

/** コンストラクタ */
Player::Player(GameMain& game) : GlassHeart::Object::ObjectBase{ game } {
    _rotation = VGet(0.0f, 270.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f);
}
/** 入力処理 */
void Player::Input(AppFrame::InputManager& input) {
    _cameraManage->Input(input);
    _angularSpeed = 0;
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
    auto x = 0; auto y = 0; auto size = 32;
    SetFontSize(size);
    DrawFormatString(x, y, GetColor(255, 0, 0), "プレイヤーX座標 =  %.3f ", _position.x); y += size;
    DrawFormatString(x, y, GetColor(255, 0, 0), "プレイヤーY座標 =  %.3f ", _position.y); y += size;
    DrawFormatString(x, y, GetColor(255, 0, 0), "プレイヤーZ座標 =  %.3f ", _position.z); y += size;
    _cameraManage->Render();
    DrawLine3D(VGet(_lastPosition.x, _lastPosition.y, _lastPosition.z), VGet(_position.x, _position.y / 200.0f, _position.z), GetColor(255, 0, 0));
#endif // _DEBUG

    _stateManage->Draw();
}
/** ワールド座標変換 */
void Player::ComputeWorldTransform() {
    auto world = MGetScale(_scale);
    world = MMult(world, MGetRotZ(_rotation.z));
    world = MMult(world, MGetRotX(_rotation.x));
    world = MMult(world, MGetRotY(_rotation.y + std::numbers::pi_v<float>));
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

void Player::HitCheckEnemy() {
}
