
/*********************************************************************
 * @file   CameraManager.cpp
 * @brief  �J�����}�l�[�W���[�N���X�̏���
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

     constexpr auto CameraDisX = 8;  //!< X���̔{��
     constexpr auto CameraDisY = 3;   //!< Y���̔{��
     constexpr auto CameraDisZ = 10;  //!< Z���̔{��
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

    // �^�[�Q�b�g�̌�����Y�͖���
    auto forward = _forwardOfTarget;
    forward.x = 0.0f;
    forward.y = 0.0f;
    // �^�[�Q�b�g�̌����̐^�t�ɒ�����targetDist
    auto fromTarget = VScale(forward, -targetDist);
    fromTarget.x = vertDist * CameraDisX;
    fromTarget.y = vertDist * CameraDisY;
    fromTarget.z = vertDist + CameraDisZ;

    // �J�����̈ʒu���v���C���[�̉��ʒu�ɂ���
    _position = VAdd(_target, fromTarget);

    SetCameraPositionAndTarget_UpVecY(_position, _target);
}

void CameraManager::Render() {
}