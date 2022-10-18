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

namespace {
  constexpr auto CameraPosX = 0;     //!< X���̈ʒu
  constexpr auto CameraPosY = 100;   //!< Y���̈ʒu
  constexpr auto CameraPosZ = -700;  //!< Z���̈ʒu
}
/** �R���X�g���N�^ */
GlassHeart::Camera::CameraManager::CameraManager() {
  Init();
}
/** ���������� */
void GlassHeart::Camera::CameraManager::Init() {
  // �J�����̃j�A/�t�@�[���Z�b�g
  SetCameraNearFar(50.0f, 10000.0f);
}
/** �X�V���� */
void GlassHeart::Camera::CameraManager::Update() {
  // �^�[�Q�b�g�̌���
  auto forward = _forwardOfTarget;
  // �^�[�Q�b�g�̌����̐^�t�ɒ�����targetDist
  auto fromTarget = VScale(forward, -_targetDist);
  fromTarget.x = CameraPosX;
  fromTarget.y = CameraPosY;
  fromTarget.z = CameraPosZ;
  // �J�����̈ʒu���v���C���[�̉��ʒu�ɂ���
  _position = VAdd(_target, fromTarget);
  SetCameraPositionAndTarget_UpVecY(_position, _target);
}
/** �`�揈�� */
void GlassHeart::Camera::CameraManager::Render() {
  // �f�o�b�O�p�J�����ʒu�\��
#ifdef _DEBUG
  auto x = 0; auto y = 32 * 3; auto size = 32;
  SetFontSize(size);
  DrawFormatString(x, y, GetColor(255, 255, 255), "�J����X���W =  %.3f ", _position.x); y += size;
  DrawFormatString(x, y, GetColor(255, 255, 255), "�J����Y���W =  %.3f ", _position.y); y += size;
  DrawFormatString(x, y, GetColor(255, 255, 255), "�J����Z���W =  %.3f ", _position.z); y += size;
#endif // _DEBUG
}