
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

using namespace GlassHeart::Stage;

Stage::Stage(GameMain& game) : ObjectBase{ game } {
    // �X�J�C�X�t�B�A�̃��f��
    _skySphere = std::make_unique<Model::ModelManager>(*this);
    _skySphere->handle("SkySphere");
    _skySphere->SetScale({ 80.f,  80.f, 80.f });
    // �n�ʂ̃��f��
    _ground = std::make_unique<Model::ModelManager>(*this);
    _ground->handle("Terrain");
    _ground->SetScale({ 30.f, 10.f, 30.f });

    _test = std::make_unique<Model::ModelManager>(*this);
    _test->handle("Test");
    _test->SetRotation(VGet(0.0f, 180.0f * std::numbers::pi_v<float> / 180.0f, 0.0f));
    _test->SetScale({ 500.f,  80.f, 80.f });
    // ���X�e�[�W�̃��f��
    _testStage = std::make_unique<Model::ModelManager>(*this);
    _testStage->handle("TestStage");
    _testStage->SetPosition(VGet(0.0f, 0.0f, 10.0f));
    _testStage->SetRotation(VGet(0.0f, 180.0f * std::numbers::pi_v<float> / 180.0f, 0.0f));
    _testStage->SetScale({ 1.f, 1.f, 1.f });

    // �i�r���b�V�����\��
    MV1SetFrameVisible(_testStage->GetHandle(), 1, FALSE);
    MV1SetFrameVisible(_testStage->GetHandle(), 2, FALSE);
    MV1SetFrameVisible(_testStage->GetHandle(), 3, FALSE);
    MV1SetFrameVisible(_testStage->GetHandle(), 4, FALSE);
    MV1SetFrameVisible(_testStage->GetHandle(), 5, FALSE);
    MV1SetFrameVisible(_testStage->GetHandle(), 6, FALSE);
    MV1SetFrameVisible(_testStage->GetHandle(), 7, FALSE);

    // �t���[��2���i�r���b�V���Ƃ��Ďg�p
    MV1SetupCollInfo(_testStage->GetHandle(), 1, 4, 4, 4);
    MV1SetupCollInfo(_testStage->GetHandle(), 2, 4, 4, 4);
    MV1SetupCollInfo(_testStage->GetHandle(), 3, 4, 4, 4);
    MV1SetupCollInfo(_testStage->GetHandle(), 4, 4, 4, 4);
    MV1SetupCollInfo(_testStage->GetHandle(), 7, 4, 4, 4);

    // �t�H�O�̐ݒ�
    SetFogEnable(TRUE);
    SetFogColor(247, 188, 101);
    SetFogStartEnd(50.0f, 15000.0f);
}

void Stage::Process() {
    // �X�J�C�X�t�B�A���v���C���Ɠ����ʒu�ɂ���
    _skySphere->SetPosition(GetObjectServer().GetPosition("Player"));
}

void Stage::Render() {
    //_skySphere->Draw();
    //_ground->Draw();
   // _test->Draw();
   // _testWhiteAndBlack->Draw();
    _testStage->Draw();
#ifdef _DEBUG
    auto linelength = 10000.f;
    VECTOR v = { 0, 0, 0 };

    DrawLine3D(VAdd(v, VGet(-linelength, 0, 0)), VAdd(v, VGet(linelength, 0, 0)), GetColor(255, 0, 0));
    DrawLine3D(VAdd(v, VGet(0, -linelength, 0)), VAdd(v, VGet(0, linelength, 0)), GetColor(0, 255, 0));
    DrawLine3D(VAdd(v, VGet(0, 0, -linelength)), VAdd(v, VGet(0, 0, linelength)), GetColor(255, 255, 255));
#endif // DEBUG
}
