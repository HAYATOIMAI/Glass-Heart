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

using namespace GlassHeart;

namespace {
     constexpr auto CameraDisX = 0;   //!< X���̔{��
     constexpr auto CameraDisY = 1;   //!< Y���̔{��
     constexpr auto CameraDisZ = -7;  //!< Z���̔{��
}
/** �R���X�g���N�^ */
Camera::CameraManager::CameraManager() {
    Init();
}
/** ���������� */
void Camera::CameraManager::Init() {
    // �J�����̃j�A/�t�@�[���Z�b�g 
    SetCameraNearFar(50.0f, 10000.0f);
}
/** �X�V���� */
void Camera::CameraManager::Update() {
    // �^�[�Q�b�g�̌���
    auto forward = _forwardOfTarget;
    forward.x = 0.0f;
    forward.y = 0.0f;
    forward.z = 0.0f;
    // �^�[�Q�b�g�̌����̐^�t�ɒ�����targetDist
    auto fromTarget = VScale(forward, -_targetDist);
    fromTarget.x = _vertDist * CameraDisX;
    fromTarget.y = _vertDist * CameraDisY;
    fromTarget.z = _vertDist * CameraDisZ;
    // �J�����̈ʒu���v���C���[�̉��ʒu�ɂ���
    _position = VAdd(_target, fromTarget);
    SetCameraPositionAndTarget_UpVecY(_position, _target);
}
/** �`�揈�� */
void Camera::CameraManager::Render() {
    // �f�o�b�O�p�J�����ʒu�\��
#ifdef _DEBUG
    auto x = 0; auto y = 32 * 3; auto size = 32;
    SetFontSize(size);
    DrawFormatString(x, y, GetColor(255, 255, 255), "�J����X���W =  %.3f ", _position.x); y += size;
    DrawFormatString(x, y, GetColor(255, 255, 255), "�J����Y���W =  %.3f ", _position.y); y += size;
    DrawFormatString(x, y, GetColor(255, 255, 255), "�J����Z���W =  %.3f ", _position.z); y += size;
#endif // _DEBUG
}