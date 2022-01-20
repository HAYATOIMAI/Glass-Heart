
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
#include <sstream>

using namespace GlassHeart::Player;

namespace {
    constexpr auto DegreeToRadian = std::numbers::pi_v<float> / 180.0f;
}

/** コンストラクタ */
Player::Player(GameMain& game) : GlassHeart::Object::ObjectBase{ game } {
    _rotation = VGet(0.0f, 270.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f);
   // _state = State::White;
}
/** 入力処理 */
void Player::Input(AppFrame::InputManager& input) {
    _cameraManage->Input(input);
    _angularSpeed = 0;
    _stateManage->Input(input);

    if (input.GetJoyPad().GetXinputLeftShoulder() && _colourCount == 0) {
        ColorCollisionDetectionSystem();   
        _colourCount = 60;
    }
}
/** 更新処理 */
void Player::Process() {

    if (_colourCount > 0) {
        --_colourCount;
    }

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

   // ColorCollisionDetectionSystem();
}
/** 描画処理 */
void Player::Render() {
#ifdef _DEBUG
    //プレイヤーの座標を表示
    auto x = 0; auto y = 0; auto size = 32;
    auto i = 0; auto o = 32 * 6;
    SetFontSize(size);
    DrawFormatString(x, y, GetColor(255, 0, 0), "プレイヤーX座標 =  %.3f ", _position.x); y += size;
    DrawFormatString(x, y, GetColor(255, 0, 0), "プレイヤーY座標 =  %.3f ", _position.y); y += size;
    DrawFormatString(x, y, GetColor(255, 0, 0), "プレイヤーZ座標 =  %.3f ", _position.z); y += size;
    DrawFormatString(i, o, GetColor(255, 0, 0), _stateName.c_str(), _state); y += size;
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
/** 色判定処理 */
void Player::ColorCollisionDetectionSystem(){

    auto animHandel = _modelAnimeManage->GetHandle();


    if (_state == State::White) {
        _stateName = "Black";
        MV1SetMaterialSpcColor(animHandel, 0, GetColorF(0.0f, 0.0f, 0.0f, 0.0f));
        _state = State::Black;
    }
    else if (_state == State::Black) {
        _stateName = "White";
        MV1SetMaterialSpcColor(animHandel, 0, GetColorF(1.0f, 1.0f, 1.0f, 0.0f));
        _state = State::White;
    }
}
