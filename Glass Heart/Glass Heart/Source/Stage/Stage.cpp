/*****************************************************************//**
 * @file   Stage.cpp
 * @brief  ステージクラスの処理
 *
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/
#include "Stage.h"
#include "../Model/ModelManager.h"
#include "../Object/ObjectServer.h"

namespace {
  constexpr auto FogStart = 50.0f;              //!<
  constexpr auto FogEnd = 15000.0f;             //!<
  constexpr auto Scale = 1.0f;
  constexpr auto StagePosZ = 10.0f;
  constexpr auto BackGround = "BackGround";
  constexpr auto Target = "Camera";
  constexpr std::int_fast16_t FogColorR = 247;  //!<
  constexpr std::int_fast16_t FogColorG = 188;  //!<
  constexpr std::int_fast16_t FogColorB = 101;  //!< 
  constexpr std::uint_fast8_t DivisionNum = 8;  //!< 
}
/** コンストラクタ */
GlassHeart::Stage::Stage::Stage(Application::GameMain& game) : Object::ObjectBase{ game } {
  // スカイスフィアのモデル
  _backGround = std::make_unique<Model::ModelManager>(*this);
  _backGround->handle(BackGround);
  _backGround->SetScale({ Scale, Scale, Scale });
  // ステージのモデル
  _stage = std::make_unique<Model::ModelManager>(*this);
  _stage->handle("Stage");
  _stage->SetPosition(VGet(0.0f, 0.0f, StagePosZ));
  _stage->SetRotation(VGet(0.0f, 0.0f, 0.0f));
  _stage->SetScale({ Scale, Scale, Scale });
  // ナビメッシュを非表示
  MV1SetFrameVisible(_stage->GetHandle(), 2, FALSE);
  MV1SetFrameVisible(_stage->GetHandle(), 3, FALSE);
  MV1SetFrameVisible(_stage->GetHandle(), 4, FALSE);
  MV1SetFrameVisible(_stage->GetHandle(), 5, FALSE);
  MV1SetFrameVisible(_stage->GetHandle(), 6, FALSE);
  MV1SetFrameVisible(_stage->GetHandle(), 7, FALSE);
  MV1SetFrameVisible(_stage->GetHandle(), 8, FALSE);
  MV1SetFrameVisible(_stage->GetHandle(), 9, FALSE);
  MV1SetFrameVisible(_stage->GetHandle(), 10, FALSE);
  //以下のフレームをナビメッシュとして使用
  MV1SetupCollInfo(_stage->GetHandle(), 2, DivisionNum, DivisionNum, DivisionNum);
  MV1SetupCollInfo(_stage->GetHandle(), 3, DivisionNum, DivisionNum, DivisionNum);
  MV1SetupCollInfo(_stage->GetHandle(), 4, DivisionNum, DivisionNum, DivisionNum);
  MV1SetupCollInfo(_stage->GetHandle(), 5, DivisionNum, DivisionNum, DivisionNum);
  MV1SetupCollInfo(_stage->GetHandle(), 6, DivisionNum, DivisionNum, DivisionNum);
  MV1SetupCollInfo(_stage->GetHandle(), 7, DivisionNum, DivisionNum, DivisionNum);
  MV1SetupCollInfo(_stage->GetHandle(), 8, DivisionNum, DivisionNum, DivisionNum);
  MV1SetupCollInfo(_stage->GetHandle(), 9, DivisionNum, DivisionNum, DivisionNum);
  // フォグの設定
  SetFogEnable(TRUE);
  SetFogColor(FogColorR, FogColorG, FogColorB);
  SetFogStartEnd(FogStart, FogEnd);
}
/** 更新処理 */
void GlassHeart::Stage::Stage::Process() {
  // スカイスフィアをカメラと同じ位置にする
  _backGround->SetPosition(GetObjectServer().GetPosition(Target));
}
/** 描画処理 */
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