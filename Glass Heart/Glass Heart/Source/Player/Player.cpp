
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
    //constexpr auto StartPositionX = 25600.0f;  //!< テスト用プレイヤーの初期位置X
    //constexpr auto StartPositionY = 12420.0f;  //!< テスト用プレイヤーの初期位置Y
    //constexpr auto StartPositionZ = -55.0f;  //!< テスト用プレイヤーの初期位置Z
    constexpr auto StartPositionX = -150.0f;  //!< プレイヤーの初期位置X
    constexpr auto StartPositionY = 35.0f;    //!< プレイヤーの初期位置Y
    constexpr auto StartPositionZ = -55.0f;  //!< プレイヤーの初期位置Z
    constexpr auto Recast = 20;  //!<　色変更リキャストタイム 
    constexpr auto RightRotation = 90.0f * (std::numbers::pi_v<float> / 180.0f); //!< 右方向の角度
    constexpr auto LeftRotation = 270.0f * (std::numbers::pi_v<float> / 180.0f);  //!< 左方向の角度
}

using namespace GlassHeart;

/** コンストラクタ */
Player::Player::Player(GameMain& game) : GlassHeart::Object::ObjectBase{ game } {
    _rotation = VGet(0.0f, RightRotation, 0.0f);
    _position = VGet(StartPositionX, StartPositionY, StartPositionZ);
    _radius = 25.0f;
}
/** 入力処理 */
void Player::Player::Input(AppFrame::InputManager& input) {
    if (_deadFlag == false) {
        _cameraManage->Input(input);
        _stateManage->Input(input);
    }
    //LBボタンを押すと色変更
    if (input.GetJoyPad().GetXinputLeftShoulder() && _recastCount == 0) {
        //連打防止のため20フレーム間入力を制限
        ColorCollisionDetectionSystem();
        _recastCount = Recast;
    }
    // Bボタンを押すとチェックポイントに保存
    if (_hitFlag == true) {

        if (input.GetJoyPad().GetXTriggerButtonB()) {
            _checkPointFlag = true;
        }
    }
#ifdef _DEBUG
    if (input.GetJoyPad().GetXinputRightShoulder()) {
        _rotation = VGet(0.0f, RightRotation, 0.0f);
        _position = VGet(StartPositionX, StartPositionY + 20, StartPositionZ);
    }
#endif // _DEBUG
}
/** 更新処理 */
void Player::Player::Process() {
    // 入力制限の為カウンタを減少
    if (_recastCount > 0) {
        --_recastCount;
    }
    if (_deathCoolCount > 0) {
        --_deathCoolCount;
    }

    if (_deadFlag == false) {
        // 状態の更新
        _stateManage->Update();
        // ワールド行列の更新
        ComputeWorldTransform();
        // モデルの更新
        _modelAnimeManage->Update();
    }
    if (GetCollision().GetWDeathMesh().HitNum >= 1) {
        if (GetColourState() == Player::Player::ColourState::White) {
            SetPosition(_position);
            // _owner.GetStateManage().PushBack("Dead");
        }
        if (GetColourState() == Player::Player::ColourState::Black) {
            ResetPos();
        }
    }
    if (GetCollision().GetBDeathMesh().HitNum >= 1) {
        if (GetColourState() == Player::Player::ColourState::White) {
            ResetPos();
            // _owner.GetStateManage().PushBack("Dead");
        }
        if (GetColourState() == Player::Player::ColourState::Black) {
            SetPosition(_position);
        }
    }
    // オブジェクトサーバーに位置を送信
    GetObjectServer().Register("Player", _position);
    // チェックポイントとの当たり判定
    for (auto ite = GetObjectServer().GetObjectLists().begin(); ite != GetObjectServer().GetObjectLists().end(); ite++) {
        // オブジェクトタイプがチェックポイントだったら
        if ((*ite)->GetObjectType() == ObjectBase::ObjectType::CheckPoint) {
            // 円形と円形の当たり判定(当たったらtrueを返す)
            if (_collsionManage->CheckCircleToCircle(*this, **ite) == true) {
                // 当たった
                _hitFlag = true;
            }
            else {
                // 当たらなかった
                _hitFlag = false;
            }
        }
    }
#ifdef _DEBUG
    if (_position.y < -100.0f) {
        if (_checkPointFlag == true) {
            // オブジェクトサーバーからチェックポイントの座標を取得
            auto checkPos = GetObjectServer().GetPosition("CheckPoint");
            // プレイヤーの座標をチェックポイントにする
            _position = checkPos;
        }
        else {
            _position = VGet(StartPositionX, StartPositionY, StartPositionZ);
        }
    }
#endif // DEBUG
}
/** 描画処理 */
void Player::Player::Render() {
#ifdef _DEBUG
    //プレイヤーの座標を表示
    auto x = 0; auto y = 0; auto size = 32;
    auto i = 0; auto o = 32 * 6; auto timeY = 32 * 10;
    auto white = GetColor(255, 255, 255);

    SetFontSize(size);
    DrawFormatString(x, y, GetColor(255, 255, 255), "プレイヤーX座標 =  %.3f ", _position.x); y += size;
    DrawFormatString(x, y, GetColor(255, 255, 255), "プレイヤーY座標 =  %.3f ", _position.y); y += size;
    DrawFormatString(x, y, GetColor(255, 255, 255), "プレイヤーZ座標 =  %.3f ", _position.z); y += size;
    // 色状態を表示
    DrawFormatString(i, o, GetColor(255, 255, 255), _stateName.c_str(), _crState); y += size;
    //カメラの位置を表示
    //_cameraManage->Render();
#endif // _DEBUG
    _stateManage->Draw();
}
/** ワールド座標変換 */
void Player::Player::ComputeWorldTransform() {
    auto world = MGetScale(_scale);
    world = MMult(world, MGetRotZ(_rotation.z));
    world = MMult(world, MGetRotX(_rotation.x));
    world = MMult(world, MGetRotY(_rotation.y + std::numbers::pi_v<float>)); // モデルの向きはここで調整
    _worldTransform = MMult(world, MGetTranslate(_position));
}
/** 移動処理 */
void Player::Player::Move(const VECTOR& forward) {
    auto pos = _position;

    int state = static_cast<int> (_crState);
    pos = _collsionManage->CheckHitSideAndBottom(pos, { forward.x, 0.f, 0.f }, state);
    pos = _collsionManage->CheckHitFloor(pos, { 0.f, -10.f, 0.f }, state);

    pos = _collsionManage->CheckHitBDeathMesh(pos, { 0.f, forward.y, 0.f });

    pos = _collsionManage->CheckHitWDeathMesh(pos, { 0.f, forward.y, 0.f });

    if (_collsionManage->GetHitFloor().HitFlag == 0) {
        GetStateManage().PushBack("Fall");
    }
    if (_crState == Player::ColourState::Black) {
        if (_collsionManage->GetWThrough().HitFlag == 0) {
            //GetStateManage().PushBack("Fall");
        }
    }
    if (_crState == Player::Player::ColourState::White) {
        if (_collsionManage->GetBThrough().HitFlag == 0) {
            //GetStateManage().GoToState("Fall");
        }
    }
    //if (_collsionManage->GetBDeathMesh().HitNum >= 1) {
    //    if (GetColourState() == Player::Player::ColourState::White) {
    //        //SetPosition(VGet(_position.x, _position.y, _position.z));
    //       GetStateManage().PushBack("Dead");
    //    }
    //    if (GetColourState() == Player::Player::ColourState::Black) {
    //        ResetPos();
    //    }
    //}
    //if (_collsionManage->GetWDeathMesh().HitNum >= 1) {
    //    if (GetColourState() == Player::Player::ColourState::White) {
    //        //SetPosition(VGet(_position.x, _position.y, _position.z));
    //         GetStateManage().PushBack("Dead");
    //    }
    //    if (GetColourState() == Player::Player::ColourState::Black) {
    //        ResetPos();
    //    }
    //}
    // 座標更新
    _position = pos;
}
/** 色判定処理 */
void Player::Player::ColorCollisionDetectionSystem() {
    if (_crState == ColourState::Black) {
        SetWhite();
    }
    else if (_crState == ColourState::White) {
        SetBlack();
    }
}

void GlassHeart::Player::Player::SetWhite() {
    auto animHandle = _modelAnimeManage->GetHandle();
    _stateName = "White";
    MV1SetFrameVisible(animHandle, 0, FALSE);
    MV1SetFrameVisible(animHandle, 1, TRUE);
    MV1SetFrameVisible(animHandle, 2, FALSE);
    MV1SetFrameVisible(animHandle, 3, TRUE);
    _crState = ColourState::White;
}

void GlassHeart::Player::Player::SetBlack() {
    auto animHandle = _modelAnimeManage->GetHandle();
    _stateName = "Black";
    MV1SetFrameVisible(animHandle, 1, FALSE);
    MV1SetFrameVisible(animHandle, 0, TRUE);
    MV1SetFrameVisible(animHandle, 3, FALSE);
    MV1SetFrameVisible(animHandle, 2, TRUE);
    _crState = ColourState::Black;
}

void Player::Player::ResetPos() {
    // デスメッシュと当たっていたら
    if (_collsionManage->GetWDeathMesh().HitNum >= 1) {
        if (_deadFlag == false) {
            _deadFlag = true;
            _deathCoolCount = 120;
        }
        if (_checkPointFlag == true) {
            if (_deadFlag == true && _deathCoolCount == 0) {
                // オブジェクトサーバーからチェックポイントの座標を取得
                auto checkPos = GetObjectServer().GetPosition("CheckPoint");
                // プレイヤーの座標をチェックポイントにする
                _position = checkPos;
                _deadFlag = false;
            }
        }
        else {
            if (_deadFlag == true && _deathCoolCount == 0) {
                _position = VGet(StartPositionX, StartPositionY, StartPositionZ);
                _deadFlag = false;
            }
        }
    }
    if (_collsionManage->GetBDeathMesh().HitNum >= 1) {
        if (_deadFlag == false) {
            _deadFlag = true;
            _deathCoolCount = 120;
        }
        if (_checkPointFlag == true) {
            if (_deadFlag == true && _deathCoolCount == 0) {
                // オブジェクトサーバーからチェックポイントの座標を取得
                auto checkPos = GetObjectServer().GetPosition("CheckPoint");
                // プレイヤーの座標をチェックポイントにする
                _position = checkPos;
                _deadFlag = false;
            }
        }
        else {
            if (_deadFlag == true && _deathCoolCount == 0) {
                _position = VGet(StartPositionX, StartPositionY, StartPositionZ);
                _deadFlag = false;
            }
        }
    }
}