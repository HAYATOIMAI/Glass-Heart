
/*****************************************************************//**
 * @file   CameraManager.cpp
 * @brief  カメラマネージャークラスの処理
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "CameraManager.h"
#include <AppFrame.h>
#include <algorithm>
#include <cmath>

using namespace GlassHeart::Camera;

namespace {

	 constexpr auto CameraDisX = 11;
	 constexpr auto CameraDisY = 2;
	 constexpr auto CameraDisZ = 10;
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
	// ターゲットの向きの真逆に長さをtargetDist
	auto fromTarget = VScale(forward, +targetDist);

	fromTarget.x = vertDist * CameraDisX;
	fromTarget.y = vertDist * CameraDisY;
	fromTarget.z = vertDist + CameraDisZ;

	// カメラの位置をプレイヤーの横位置にする
	_position = VAdd(_target, fromTarget);

	SetCameraPositionAndTarget_UpVecY(_position, _target);
}

void CameraManager::Render() {
}