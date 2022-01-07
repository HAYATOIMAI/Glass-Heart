
/*****************************************************************//**
 * @file   CameraManager.cpp
 * @brief  �J�����}�l�[�W���[�N���X�̏���
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "CameraManager.h"
#include <AppFrame.h>
#include <algorithm>
#include <cmath>

using namespace GlassHeart::Camera;

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
	forward.y = 0.f;
	// �^�[�Q�b�g�̌����̐^�t�ɒ�����targetDist
	auto fromTarget = VScale(forward, -targetDist);
	fromTarget.y = vertDist;

	// �J�����̈ʒu���v���C���[�̌���̈ʒu�ɂ���
	_position = VAdd(_target, fromTarget);

	SetCameraPositionAndTarget_UpVecY(_position, _target);
}

void CameraManager::Render() {
}