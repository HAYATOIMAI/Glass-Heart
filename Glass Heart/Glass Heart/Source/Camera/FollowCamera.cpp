/*****************************************************************//**
 * @file   FollowCamera.cpp
 * @brief  �t�H���[�J�����̏���
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
  constexpr auto StartPosX = -150.0f;  //!< �����ʒuX
  constexpr auto StartPosY = 35.0f;     //!< �����ʒuY
  constexpr auto StartPosZ = -55.0f;    //!< �����ʒuZ
}
/** �R���X�g���N�^ */
GlassHeart::Camera::FollowCamera::FollowCamera(Application::GameMain& game) : ObjectBase{ game } {
  _rotation = VGet(0.0f, 270.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f);
  _position = VGet(StartPosX, StartPosY, StartPosZ);
}
/** �X�V���� */
void GlassHeart::Camera::FollowCamera::Process() {
  auto player = GetObjectServer().GetPosition("Player");

  // �v���C���[�Ɍ������x�N�g��
  auto forwoard = VSub(player, _position);

  if (player.y - 2.5 < _position.y && _position.y < player.y + 2.5
    && player.x - 2.5 < _position.x && _position.x < player.x + 2.5) {
  }
  else {
    // �����i�����j
    auto dist = VSize(forwoard);

    VECTOR delta = { 0,0,0 };
    // �v���C���[�Ɍ������P�ʃx�N�g��
    forwoard = VNorm(forwoard);

    if (dist > (1080 / 4)) {
      // �v���C���[�Ɍ������ړ��ʃx�N�g��
      delta = VScale(forwoard, -(1080 / 4));
      _position = VAdd(player, delta);
    }
    else {
      // �v���C���[�Ɍ������ړ��ʃx�N�g��
      delta = VScale(forwoard, _forwardSpeed);
      // �v���C���[�Ɍ������Ĉړ�
      _position = VAdd(_position, delta);
    }
    _rotation.y = std::atan2f(forwoard.x, forwoard.z);
  }

  ComputeWorldTransform();
  // �J�����̍X�V
  _cameraManage->SetTarget(_position, GetForward());
  _cameraManage->Update();

  GetObjectServer().Register("Camera", _position);
}
/** �`�揈�� */
void GlassHeart::Camera::FollowCamera::Render() {
#ifdef _DEBUG
  //�J�����̈ʒu��\��
  _cameraManage->Render();
  //�J�����}���̍��W��\��
  auto x = 0; auto y = 32 * 7;  auto size = 32;
  SetFontSize(size);
  DrawFormatString(x, y, GetColor(255, 255, 255), "�J�����}��X���W =  %.3f ", _position.x); y += size;
  DrawFormatString(x, y, GetColor(255, 255, 255), "�J�����}��Y���W =  %.3f ", _position.y); y += size;
  DrawFormatString(x, y, GetColor(255, 255, 255), "�J�����}��Z���W =  %.3f ", _position.z); y += size;
#endif // _DEBUG
}