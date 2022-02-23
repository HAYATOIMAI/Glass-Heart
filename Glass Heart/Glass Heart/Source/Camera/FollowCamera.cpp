
/*****************************************************************//**
 * @file   FollowCamera.cpp
 * @brief  フォローカメラの処理
 *
 * @author Yoshihiro Takahashi
 * @date   December 2021
 *********************************************************************/
#include "FollowCamera.h"
#include "../Camera/CameraManager.h"
#include "../Object/ObjectServer.h"
#include "../Player/Player.h"
#include <numbers>

namespace {
    constexpr auto StartPositionX = -150.0f;     //!< プレイヤーの初期位置X
    constexpr auto StartPositionY = 35.0f;    //!< プレイヤーの初期位置Y
    constexpr auto StartPositionZ = -140.0f;  //!< プレイヤーの初期位置Z
}

using namespace GlassHeart::Camera;

FollowCamera::FollowCamera(GameMain& game) : ObjectBase{ game } {

    _rotation = VGet(0.0f, 270.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f);
    _position = VGet(StartPositionX, StartPositionY, StartPositionZ);

    Init();

}

FollowCamera::~FollowCamera() {}

void FollowCamera::Init() {}

void FollowCamera::Process() {

    auto player = GetObjectServer().GetPosition("Player");

    // プレイヤーに向かうベクトル
    auto forwoard = VSub(player, _position);
    // プレイヤーに向かう単位ベクトル
    forwoard = VNorm(forwoard);
    // プレイヤーに向かう移動量ベクトル
    auto delta = VScale(forwoard, _forwardSpeed);

    // プレイヤーに向かって移動
    _position = VAdd(_position, delta);
    _rotation.y = std::atan2f(forwoard.x, forwoard.z);
    

    ComputeWorldTransform();
    // カメラの更新
    _cameraManage->SetTarget(_position, GetForward());
    _cameraManage->Update();

    GetObjectServer().Register("Camera", _position);

}

void FollowCamera::Render() {

    //カメラの位置を表示
    _cameraManage->Render();
    //プレイヤーの座標を表示
    auto x = 0; auto y = 32 * 7;  auto size = 32;
    SetFontSize(size);
    DrawFormatString(x, y, GetColor(255, 255, 255), "カメラマンX座標 =  %.3f ", _position.x); y += size;
    DrawFormatString(x, y, GetColor(255, 255, 255), "カメラマンY座標 =  %.3f ", _position.y); y += size;
    DrawFormatString(x, y, GetColor(255, 255, 255), "カメラマンZ座標 =  %.3f ", _position.z); y += size;

}
