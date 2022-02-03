
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

namespace {
    constexpr auto PlayerPositionX = 0.0f;     //!< プレイヤーの初期位置X
    constexpr auto PlayerPositionY = 70.0f;    //!< プレイヤーの初期位置Y
    constexpr auto PlayerPositionZ = -140.0f;  //!< プレイヤーの初期位置Z
}

using namespace GlassHeart::Player;

/** コンストラクタ */
Player::Player(GameMain& game) : GlassHeart::Object::ObjectBase{ game } {

    _rotation = VGet(0.0f, 270.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f);
    _position = VGet(PlayerPositionX, PlayerPositionY, PlayerPositionZ);
    
}
/** 入力処理 */
void Player::Input(AppFrame::InputManager& input) {
    _cameraManage->Input(input);
    _angularSpeed = 0;
    _stateManage->Input(input);
    //LBボタンを押すと色変更
    if (input.GetJoyPad().GetXinputLeftShoulder() && _colourCount == 0) {
        //連打防止のため1秒(60フレーム)間入力を制限
        ColorCollisionDetectionSystem();
        _colourCount = 60;
    }
}
/** 更新処理 */
void Player::Process() {
    // 入力制限の為カウンタを減少
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
}
/** 描画処理 */
void Player::Render() {
#ifdef _DEBUG
    //プレイヤーの座標を表示
    auto x = 0; auto y = 0; auto size = 32;
    auto i = 0; auto o = 32 * 6;
    SetFontSize(size);
    DrawFormatString(x, y, GetColor(255, 255, 255), "プレイヤーX座標 =  %.3f ", _position.x); y += size;
    DrawFormatString(x, y, GetColor(255, 255, 255), "プレイヤーY座標 =  %.3f ", _position.y); y += size;
    DrawFormatString(x, y, GetColor(255, 255, 255), "プレイヤーZ座標 =  %.3f ", _position.z); y += size;
    // 色状態を表示
    DrawFormatString(i, o, GetColor(255, 0, 0), _stateName.c_str(), _crState); y += size;
    //カメラの位置を表示
    _cameraManage->Render();
    DrawLine3D(VGet(_lastPosition.x, _lastPosition.y, _lastPosition.z), VGet(_position.x, _position.y / 200.0f, _position.z), GetColor(255, 0, 0));
    // コリジョン情報を表示
    _collsionManage->Render();
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
    //Y成分
    pos = _collsionManage->CheckTerrain(pos, { forward.x, forward.y, forward.z });
    // Z成分のみ移動後位置から真下に線分判定
    pos = _collsionManage->CheckTerrain(pos, { 0, forward.y, forward.z });

    pos = _collsionManage->CheckJumpStand(pos, { forward.x, forward.y, 0 });

    pos = _collsionManage->CheckJumpStand(pos, { forward.x, forward.y, forward.z });

    pos = _collsionManage->CheckJumpStand(pos, { 0, forward.y, forward.z });

    // 色状態が白のときのみ黒のメッシュと判定を行う
    if (_crState == ColourState::Black) {
        // X成分
        pos = _collsionManage->CheckHitWall(pos, { forward.x, forward.y, 0 });
        // Y成分
        pos = _collsionManage->CheckHitWall(pos, { forward.x, forward.y, forward.z });
        // Z成分
        pos = _collsionManage->CheckHitWall(pos, { 0, forward.y, forward.z });

        pos = _collsionManage->CheckJumpStand(pos, { forward.x, forward.y, 0 });

        pos = _collsionManage->CheckJumpStand(pos, { forward.x, forward.y, forward.z });

        pos = _collsionManage->CheckJumpStand(pos, { 0, forward.y, forward.z });
    }
    // 座標更新
    _position = pos;
}
/** 色判定処理 */
void Player::ColorCollisionDetectionSystem() {

    auto animHandle = _modelAnimeManage->GetHandle();

    if (_crState == ColourState::Black) {
        _stateName = "Black";
        MV1SetMaterialSpcColor(animHandle, 0, GetColorF(0.0f, 0.0f, 0.0f, 0.0f));
        _crState = ColourState::White;
    }
    else if (_crState == ColourState::White) {
        _stateName = "White";
        MV1SetMaterialSpcColor(animHandle, 0, GetColorF(1.0f, 1.0f, 1.0f, 0.0f));
        _crState = ColourState::Black;
    }
}
