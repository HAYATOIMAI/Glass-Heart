/*****************************************************************//**
 * @file   Stage.cpp
 * @brief  �X�e�[�W�N���X�̏���
 *
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/
#include "Stage.h"
#include "../Model/ModelManager.h"
#include "../Object/ObjectServer.h"
#include <numbers>

namespace {
  constexpr auto RightRotation = 0.0f * (std::numbers::pi_v<float> / 180.0f); //!< �E�����̊p�x
  constexpr auto FogStart = 50.0f;
  constexpr auto FogEnd = 15000.0f;
  constexpr std::int_fast16_t FogColorR = 247;
  constexpr std::int_fast16_t FogColorG = 188;
  constexpr std::int_fast16_t FogColorB = 101;
}
/** �R���X�g���N�^ */
GlassHeart::Stage::Stage::Stage(Application::GameMain& game) : Object::ObjectBase{ game } {
  // �X�J�C�X�t�B�A�̃��f��
  _backGround = std::make_unique<Model::ModelManager>(*this);
  _backGround->handle("BackGround");
  _backGround->SetScale({ 1.f, 1.f, 1.f });
  // �X�e�[�W�̃��f��
  _stage = std::make_unique<Model::ModelManager>(*this);
  _stage->handle("Stage");
  _stage->SetPosition(VGet(0.0f, 0.0f, 10.0f));
  _stage->SetRotation(VGet(0.0f, RightRotation, 0.0f));
  _stage->SetScale({ 1.f, 1.f, 1.f });
  // �i�r���b�V�����\��
  MV1SetFrameVisible(_stage->GetHandle(), 2, FALSE);
  MV1SetFrameVisible(_stage->GetHandle(), 3, FALSE);
  MV1SetFrameVisible(_stage->GetHandle(), 4, FALSE);
  MV1SetFrameVisible(_stage->GetHandle(), 5, FALSE);
  MV1SetFrameVisible(_stage->GetHandle(), 6, FALSE);
  MV1SetFrameVisible(_stage->GetHandle(), 7, FALSE);
  MV1SetFrameVisible(_stage->GetHandle(), 8, FALSE);
  MV1SetFrameVisible(_stage->GetHandle(), 9, FALSE);
  MV1SetFrameVisible(_stage->GetHandle(), 10, FALSE);
  //�ȉ��̃t���[�����i�r���b�V���Ƃ��Ďg�p
  MV1SetupCollInfo(_stage->GetHandle(), 2, 8, 8, 8);
  MV1SetupCollInfo(_stage->GetHandle(), 3, 8, 8, 8);
  MV1SetupCollInfo(_stage->GetHandle(), 4, 8, 8, 8);
  MV1SetupCollInfo(_stage->GetHandle(), 5, 8, 8, 8);
  MV1SetupCollInfo(_stage->GetHandle(), 6, 8, 8, 8);
  MV1SetupCollInfo(_stage->GetHandle(), 7, 8, 8, 8);
  MV1SetupCollInfo(_stage->GetHandle(), 8, 8, 8, 8);
  MV1SetupCollInfo(_stage->GetHandle(), 9, 8, 8, 8);
  // �t�H�O�̐ݒ�
  SetFogEnable(TRUE);
  SetFogColor(FogColorR, FogColorG, FogColorB);
  SetFogStartEnd(FogStart, FogEnd);
}
/** �X�V���� */
void GlassHeart::Stage::Stage::Process() {
  // �X�J�C�X�t�B�A���J�����Ɠ����ʒu�ɂ���
  _backGround->SetPosition(GetObjectServer().GetPosition("Camera"));
}
/** �`�揈�� */
void GlassHeart::Stage::Stage::Render() {
  _backGround->Draw();
  _stage->Draw();
#ifdef _DEBUG
  auto linelength = 10000.f;
  VECTOR v = { 0, 0, 0 };

  DrawLine3D(VAdd(v, VGet(-linelength, 0, 0)), VAdd(v, VGet(linelength, 0, 0)), GetColor(255, 0, 0));
  DrawLine3D(VAdd(v, VGet(0, -linelength, 0)), VAdd(v, VGet(0, linelength, 0)), GetColor(0, 255, 0));
  DrawLine3D(VAdd(v, VGet(0, 0, -linelength)), VAdd(v, VGet(0, 0, linelength)), GetColor(255, 255, 255));
#endif // DEBUG
}