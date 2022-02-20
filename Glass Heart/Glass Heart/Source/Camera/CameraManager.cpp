
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

using namespace GlassHeart::Camera;

namespace {

     constexpr auto CameraDisX = 0;  //!< X軸の倍率
     constexpr auto CameraDisY = 1;   //!< Y軸の倍率
     constexpr auto CameraDisZ = 7;  //!< Z軸の倍率
}

CameraManager::CameraManager() {
    Init();
}

void CameraManager::Init() {
    SetCameraNearFar(50.0f, 10000.0f);
}

void CameraManager::Input(AppFrame::InputManager& input) {
}

void CameraManager::Update() {

    // ターゲットの向き※Yは無視
    auto forward = _forwardOfTarget;
    forward.x = 0.0f;
    forward.y = 0.0f;
    forward.z = 0.0f;
    // ターゲットの向きの真逆に長さをtargetDist
    auto fromTarget = VScale(forward, -targetDist);
    fromTarget.x = vertDist * CameraDisX;
    fromTarget.y = vertDist * CameraDisY;
    fromTarget.z = vertDist * CameraDisZ;
    /*fromTarget.x = -120.5f;
    fromTarget.y = 70.0f;
    fromTarget.z = 3.0f;*/

    // カメラの位置をプレイヤーの横位置にする
    _position = VAdd(_target, fromTarget);
    // カメラを正射影に変更
    //SetupCamera_Ortho(900.0f);
    SetCameraPositionAndTarget_UpVecY(_position, _target);
}

void CameraManager::Render() {
#ifdef _DEBUG
    auto x = 0; auto y = 32 * 3; auto size = 32;
    SetFontSize(size);
    DrawFormatString(x, y, GetColor(255, 255, 255), "カメラX座標 =  %.3f ", _position.x); y += size;
    DrawFormatString(x, y, GetColor(255, 255, 255), "カメラY座標 =  %.3f ", _position.y); y += size;
    DrawFormatString(x, y, GetColor(255, 255, 255), "カメラZ座標 =  %.3f ", _position.z); y += size;
#endif // _DEBUG
}