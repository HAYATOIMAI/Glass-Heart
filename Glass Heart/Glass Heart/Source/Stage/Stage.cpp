
/*****************************************************************//**
 * @file   Stage.cpp
 * @brief  �X�e�[�W����
 *
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/
#include "Stage.h"
#include "../Model/ModelManager.h"
#include "../Object/ObjectServer.h"
#include <numbers>

using namespace GlassHeart;

namespace {
    constexpr auto RightRotation = 0.0f * (std::numbers::pi_v<float> / 180.0f); //!< �E�����̊p�x
}

Stage::Stage::Stage(GameMain& game) : Object::ObjectBase{ game } {
    // �X�J�C�X�t�B�A�̃��f��
    _backGround = std::make_unique<Model::ModelManager>(*this);
    _backGround->handle("BackGround");
    _backGround->SetScale({ 1.f, 1.f, 1.f });
   /* _skySphere = std::make_unique<Model::ModelManager>(*this);
    _skySphere->handle("SkySphere");
    _skySphere->SetScale({ 80.f,  80.f, 80.f });*/
   
    // �X�e�[�W�̃��f��
    _testStage = std::make_unique<Model::ModelManager>(*this);
    _testStage->handle("Stage");
    _testStage->SetPosition(VGet(0.0f, 0.0f, 10.0f));
    _testStage->SetRotation(VGet(0.0f, RightRotation, 0.0f));
    _testStage->SetScale({ 1.f, 1.f, 1.f });

    // �i�r���b�V�����\��
    MV1SetFrameVisible(_testStage->GetHandle(), 2, FALSE);
    MV1SetFrameVisible(_testStage->GetHandle(), 3, FALSE);
    MV1SetFrameVisible(_testStage->GetHandle(), 4, FALSE);
    MV1SetFrameVisible(_testStage->GetHandle(), 5, FALSE);
    MV1SetFrameVisible(_testStage->GetHandle(), 6, FALSE);
    MV1SetFrameVisible(_testStage->GetHandle(), 7, FALSE);
    MV1SetFrameVisible(_testStage->GetHandle(), 8, FALSE);
    MV1SetFrameVisible(_testStage->GetHandle(), 9, FALSE);
    MV1SetFrameVisible(_testStage->GetHandle(), 10, FALSE);
    //�ȉ��̃t���[�����i�r���b�V���Ƃ��Ďg�p
    MV1SetupCollInfo(_testStage->GetHandle(), 2, 8, 8, 8);
    MV1SetupCollInfo(_testStage->GetHandle(), 3, 8, 8, 8);
    MV1SetupCollInfo(_testStage->GetHandle(), 4, 8, 8, 8);
    MV1SetupCollInfo(_testStage->GetHandle(), 5, 8, 8, 8);
    MV1SetupCollInfo(_testStage->GetHandle(), 6, 8, 8, 8);
    MV1SetupCollInfo(_testStage->GetHandle(), 7, 8, 8, 8);
    MV1SetupCollInfo(_testStage->GetHandle(), 8, 8, 8, 8);
    MV1SetupCollInfo(_testStage->GetHandle(), 9, 8, 8, 8);
    // �t�H�O�̐ݒ�
    SetFogEnable(TRUE);
    SetFogColor(247, 188, 101);
    SetFogStartEnd(50.0f, 15000.0f);
}

void Stage::Stage::Process() {
    // �X�J�C�X�t�B�A���v���C���Ɠ����ʒu�ɂ���
    _backGround->SetPosition(GetObjectServer().GetPosition("Camera"));
}

void Stage::Stage::Render() {
    _backGround->Draw();
    _testStage->Draw();
#ifdef _DEBUG
    auto linelength = 10000.f;
    VECTOR v = { 0, 0, 0 };

    DrawLine3D(VAdd(v, VGet(-linelength, 0, 0)), VAdd(v, VGet(linelength, 0, 0)), GetColor(255, 0, 0));
    DrawLine3D(VAdd(v, VGet(0, -linelength, 0)), VAdd(v, VGet(0, linelength, 0)), GetColor(0, 255, 0));
    DrawLine3D(VAdd(v, VGet(0, 0, -linelength)), VAdd(v, VGet(0, 0, linelength)), GetColor(255, 255, 255));
#endif // DEBUG
}
