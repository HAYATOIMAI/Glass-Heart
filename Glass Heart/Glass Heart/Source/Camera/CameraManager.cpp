/*********************************************************************
 * @file   CameraManager.cpp
 * @brief  カメラマネージャークラスの処理
 *
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/
#include "CameraManager.h"
#include <AppFrame.h>
#include <algorithm>
#include <cmath>

namespace {
  constexpr auto CameraPosX = 0;     //!< X軸の位置
  constexpr auto CameraPosY = 100;   //!< Y軸の位置
  constexpr auto CameraPosZ = -700;  //!< Z軸の位置
}
/** コンストラクタ */
GlassHeart::Camera::CameraManager::CameraManager() {
  Init();
}
/** 初期化処理 */
void GlassHeart::Camera::CameraManager::Init() {
  // カメラのニア/ファーをセット
  SetCameraNearFar(50.0f, 10000.0f);
}
/** 更新処理 */
void GlassHeart::Camera::CameraManager::Update() {
  // ターゲットの向き
  auto forward = _forwardOfTarget;
  // ターゲットの向きの真逆に長さをtargetDist
  auto fromTarget = VScale(forward, -_targetDist);
  fromTarget.x = CameraPosX;
  fromTarget.y = CameraPosY;
  fromTarget.z = CameraPosZ;
  // カメラの位置をプレイヤーの横位置にする
  _position = VAdd(_target, fromTarget);
  SetCameraPositionAndTarget_UpVecY(_position, _target);
}
/** 描画処理 */
void GlassHeart::Camera::CameraManager::Render() {
  // デバッグ用カメラ位置表示
#ifdef _DEBUG
  auto x = 0; auto y = 32 * 3; auto size = 32;
  SetFontSize(size);
  DrawFormatString(x, y, GetColor(255, 255, 255), "カメラX座標 =  %.3f ", _position.x); y += size;
  DrawFormatString(x, y, GetColor(255, 255, 255), "カメラY座標 =  %.3f ", _position.y); y += size;
  DrawFormatString(x, y, GetColor(255, 255, 255), "カメラZ座標 =  %.3f ", _position.z); y += size;
#endif // _DEBUG
}