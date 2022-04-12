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

using namespace GlassHeart;

namespace {
     constexpr auto CameraDisX = 0;   //!< X軸の倍率
     constexpr auto CameraDisY = 1;   //!< Y軸の倍率
     constexpr auto CameraDisZ = -7;  //!< Z軸の倍率
}
/** コンストラクタ */
Camera::CameraManager::CameraManager() {
    Init();
}
/** 初期化処理 */
void Camera::CameraManager::Init() {
    // カメラのニア/ファーをセット 
    SetCameraNearFar(50.0f, 10000.0f);
}
/** 更新処理 */
void Camera::CameraManager::Update() {
    // ターゲットの向き
    auto forward = _forwardOfTarget;
    forward.x = 0.0f;
    forward.y = 0.0f;
    forward.z = 0.0f;
    // ターゲットの向きの真逆に長さをtargetDist
    auto fromTarget = VScale(forward, -_targetDist);
    fromTarget.x = _vertDist * CameraDisX;
    fromTarget.y = _vertDist * CameraDisY;
    fromTarget.z = _vertDist * CameraDisZ;
    // カメラの位置をプレイヤーの横位置にする
    _position = VAdd(_target, fromTarget);
    SetCameraPositionAndTarget_UpVecY(_position, _target);
}
/** 描画処理 */
void Camera::CameraManager::Render() {
    // デバッグ用カメラ位置表示
#ifdef _DEBUG
    auto x = 0; auto y = 32 * 3; auto size = 32;
    SetFontSize(size);
    DrawFormatString(x, y, GetColor(255, 255, 255), "カメラX座標 =  %.3f ", _position.x); y += size;
    DrawFormatString(x, y, GetColor(255, 255, 255), "カメラY座標 =  %.3f ", _position.y); y += size;
    DrawFormatString(x, y, GetColor(255, 255, 255), "カメラZ座標 =  %.3f ", _position.z); y += size;
#endif // _DEBUG
}