
/*****************************************************************//**
 * @file   Stage.cpp
 * @brief  ステージ処理
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
    constexpr auto RightRotation = 0.0f * (std::numbers::pi_v<float> / 180.0f); //!< 右方向の角度
}

Stage::Stage::Stage(GameMain& game) : Object::ObjectBase{ game } {
    // スカイスフィアのモデル
    _backGround = std::make_unique<Model::ModelManager>(*this);
    _backGround->handle("BackGround");
    _backGround->SetScale({ 1.f, 1.f, 1.f });
   /* _skySphere = std::make_unique<Model::ModelManager>(*this);
    _skySphere->handle("SkySphere");
    _skySphere->SetScale({ 80.f,  80.f, 80.f });*/
   
    // ステージのモデル
    _testStage = std::make_unique<Model::ModelManager>(*this);
    _testStage->handle("Stage");
    _testStage->SetPosition(VGet(0.0f, 0.0f, 10.0f));
    _testStage->SetRotation(VGet(0.0f, RightRotation, 0.0f));
    _testStage->SetScale({ 1.f, 1.f, 1.f });

    // ナビメッシュを非表示
    MV1SetFrameVisible(_testStage->GetHandle(), 2, FALSE);
    MV1SetFrameVisible(_testStage->GetHandle(), 3, FALSE);
    MV1SetFrameVisible(_testStage->GetHandle(), 4, FALSE);
    MV1SetFrameVisible(_testStage->GetHandle(), 5, FALSE);
    MV1SetFrameVisible(_testStage->GetHandle(), 6, FALSE);
    MV1SetFrameVisible(_testStage->GetHandle(), 7, FALSE);
    MV1SetFrameVisible(_testStage->GetHandle(), 8, FALSE);
    MV1SetFrameVisible(_testStage->GetHandle(), 9, FALSE);
    MV1SetFrameVisible(_testStage->GetHandle(), 10, FALSE);
    //以下のフレームをナビメッシュとして使用
    MV1SetupCollInfo(_testStage->GetHandle(), 2, 8, 8, 8);
    MV1SetupCollInfo(_testStage->GetHandle(), 3, 8, 8, 8);
    MV1SetupCollInfo(_testStage->GetHandle(), 4, 8, 8, 8);
    MV1SetupCollInfo(_testStage->GetHandle(), 5, 8, 8, 8);
    MV1SetupCollInfo(_testStage->GetHandle(), 6, 8, 8, 8);
    MV1SetupCollInfo(_testStage->GetHandle(), 7, 8, 8, 8);
    MV1SetupCollInfo(_testStage->GetHandle(), 8, 8, 8, 8);
    MV1SetupCollInfo(_testStage->GetHandle(), 9, 8, 8, 8);
    // フォグの設定
    SetFogEnable(TRUE);
    SetFogColor(247, 188, 101);
    SetFogStartEnd(50.0f, 15000.0f);
}

void Stage::Stage::Process() {
    // スカイスフィアをプレイヤと同じ位置にする
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
