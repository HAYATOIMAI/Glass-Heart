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

namespace {
  constexpr auto FogStart = 50.0f;                 //!< �t�H�O���n�܂鋗��
  constexpr auto FogEnd = 15000.0f;                //!< �t�H�O���I���n�_
  constexpr auto BackGround = "BackGround";        //!< �����Ɏ������镶����
  constexpr auto Target = "Camera";                //!< �����Ɏ������镶����
  constexpr auto StageHandle = "Stage";            //!< �����Ɏ������镶����
  constexpr std::int_fast16_t FogColorR = 247;     //!< �t�H�O�̐F���
  constexpr std::int_fast16_t FogColorG = 188;     //!< �t�H�O�̐F���
  constexpr std::int_fast16_t FogColorB = 101;     //!< �t�H�O�̐F���
  constexpr std::int_fast8_t DivNum = 8;           //!< �R���W�������̋�ԕ�����
  constexpr VECTOR Scale = { 1.0f, 1.0f, 1.0f };   //!< �g�嗦
  constexpr VECTOR Pos = { 0.0f, 0.0f, 10.0f };    //!< �ʒu���W
  constexpr VECTOR Rotate = { 0.0f, 0.0f, 0.0f };  //!< �p�x
}
/** �R���X�g���N�^ */
GlassHeart::Stage::Stage::Stage(Application::GameMain& game) : Object::ObjectBase{ game } {
  // �X�J�C�X�t�B�A�̃��f��
  _backGround = std::make_unique<Model::ModelManager>(*this);
  _backGround->handle(BackGround);
  _backGround->SetScale(Scale);
  // �X�e�[�W�̃��f��
  _stage = std::make_unique<Model::ModelManager>(*this);
  _stage->handle(StageHandle);
  _stage->SetPosition(Pos);
  _stage->SetRotation(Rotate);
  _stage->SetScale(Scale);
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
  MV1SetupCollInfo(_stage->GetHandle(), 2, DivNum, DivNum, DivNum);
  MV1SetupCollInfo(_stage->GetHandle(), 3, DivNum, DivNum, DivNum);
  MV1SetupCollInfo(_stage->GetHandle(), 4, DivNum, DivNum, DivNum);
  MV1SetupCollInfo(_stage->GetHandle(), 5, DivNum, DivNum, DivNum);
  MV1SetupCollInfo(_stage->GetHandle(), 6, DivNum, DivNum, DivNum);
  MV1SetupCollInfo(_stage->GetHandle(), 7, DivNum, DivNum, DivNum);
  MV1SetupCollInfo(_stage->GetHandle(), 8, DivNum, DivNum, DivNum);
  MV1SetupCollInfo(_stage->GetHandle(), 9, DivNum, DivNum, DivNum);
  // �t�H�O�̐ݒ�
  SetFogEnable(TRUE);
  SetFogColor(FogColorR, FogColorG, FogColorB);
  SetFogStartEnd(FogStart, FogEnd);
}
/** �X�V���� */
void GlassHeart::Stage::Stage::Process() {
  // �X�J�C�X�t�B�A���J�����Ɠ����ʒu�ɂ���
  _backGround->SetPosition(GetObjectServer().GetPosition(Target));
}
/** �`�揈�� */
void GlassHeart::Stage::Stage::Render() {
  _backGround->Draw();
  _stage->Draw();
#ifdef _DEBUG
  auto linelength = 10000.f;
  VECTOR v = { 0.0f, 0.0f, 0.0f };

  DrawLine3D(VAdd(v, VGet(-linelength, 0, 0)), VAdd(v, VGet(linelength, 0, 0)), GetColor(255, 0, 0));
  DrawLine3D(VAdd(v, VGet(0, -linelength, 0)), VAdd(v, VGet(0, linelength, 0)), GetColor(0, 255, 0));
  DrawLine3D(VAdd(v, VGet(0, 0, -linelength)), VAdd(v, VGet(0, 0, linelength)), GetColor(255, 255, 255));
#endif // DEBUG
}