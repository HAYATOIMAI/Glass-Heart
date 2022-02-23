
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
    constexpr auto StartPositionX = -150.0f;     //!< �v���C���[�̏����ʒuX
    constexpr auto StartPositionY = 35.0f;    //!< �v���C���[�̏����ʒuY
    constexpr auto StartPositionZ = -140.0f;  //!< �v���C���[�̏����ʒuZ
}

using namespace GlassHeart::Camera;

FollowCamera::FollowCamera(GameMain& game) : ObjectBase{ game } {

    _rotation = VGet(0.0f, 270.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f);
    _position = VGet(StartPositionX, StartPositionY, StartPositionZ);

    Init();

}

FollowCamera::~FollowCamera() {}

void FollowCamera::Init() {}

void FollowCamera::Process() {

    auto player = GetObjectServer().GetPosition("Player");

    // �v���C���[�Ɍ������x�N�g��
    auto forwoard = VSub(player, _position);
    // �v���C���[�Ɍ������P�ʃx�N�g��
    forwoard = VNorm(forwoard);
    // �v���C���[�Ɍ������ړ��ʃx�N�g��
    auto delta = VScale(forwoard, _forwardSpeed);

    // �v���C���[�Ɍ������Ĉړ�
    _position = VAdd(_position, delta);
    _rotation.y = std::atan2f(forwoard.x, forwoard.z);
    

    ComputeWorldTransform();
    // �J�����̍X�V
    _cameraManage->SetTarget(_position, GetForward());
    _cameraManage->Update();

    GetObjectServer().Register("Camera", _position);

}

void FollowCamera::Render() {

    //�J�����̈ʒu��\��
    _cameraManage->Render();
    //�v���C���[�̍��W��\��
    auto x = 0; auto y = 32 * 7;  auto size = 32;
    SetFontSize(size);
    DrawFormatString(x, y, GetColor(255, 255, 255), "�J�����}��X���W =  %.3f ", _position.x); y += size;
    DrawFormatString(x, y, GetColor(255, 255, 255), "�J�����}��Y���W =  %.3f ", _position.y); y += size;
    DrawFormatString(x, y, GetColor(255, 255, 255), "�J�����}��Z���W =  %.3f ", _position.z); y += size;

}
