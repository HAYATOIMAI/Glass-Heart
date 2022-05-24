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
  constexpr auto StartPosX = -150.0f;  //!< 初期位置X
  constexpr auto StartPosY = 35.0f;     //!< 初期位置Y
  constexpr auto StartPosZ = -55.0f;    //!< 初期位置Z
}
/** コンストラクタ */
GlassHeart::Camera::FollowCamera::FollowCamera(Application::GameMain& game) : ObjectBase{ game } {
  _rotation = VGet(0.0f, 270.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f);
  _position = VGet(StartPosX, StartPosY, StartPosZ);
}
/** 更新処理 */
void GlassHeart::Camera::FollowCamera::Process() {
  auto player = GetObjectServer().GetPosition("Player");

  // プレイヤーに向かうベクトル
  auto forwoard = VSub(player, _position);

  if (player.y - 2.5 < _position.y && _position.y < player.y + 2.5
    && player.x - 2.5 < _position.x && _position.x < player.x + 2.5) {
  }
  else {
    // 距離（長さ）
    auto dist = VSize(forwoard);

    VECTOR delta = { 0,0,0 };
    // プレイヤーに向かう単位ベクトル
    forwoard = VNorm(forwoard);

    if (dist > (1080 / 4)) {
      // プレイヤーに向かう移動量ベクトル
      delta = VScale(forwoard, -(1080 / 4));
      _position = VAdd(player, delta);
    }
    else {
      // プレイヤーに向かう移動量ベクトル
      delta = VScale(forwoard, _forwardSpeed);
      // プレイヤーに向かって移動
      _position = VAdd(_position, delta);
    }
    _rotation.y = std::atan2f(forwoard.x, forwoard.z);
  }

  ComputeWorldTransform();
  // カメラの更新
  _cameraManage->SetTarget(_position, GetForward());
  _cameraManage->Update();

  GetObjectServer().Register("Camera", _position);
}
/** 描画処理 */
void GlassHeart::Camera::FollowCamera::Render() {
#ifdef _DEBUG
  //カメラの位置を表示
  _cameraManage->Render();
  //カメラマンの座標を表示
  auto x = 0; auto y = 32 * 7;  auto size = 32;
  SetFontSize(size);
  DrawFormatString(x, y, GetColor(255, 255, 255), "カメラマンX座標 =  %.3f ", _position.x); y += size;
  DrawFormatString(x, y, GetColor(255, 255, 255), "カメラマンY座標 =  %.3f ", _position.y); y += size;
  DrawFormatString(x, y, GetColor(255, 255, 255), "カメラマンZ座標 =  %.3f ", _position.z); y += size;
#endif // _DEBUG
}