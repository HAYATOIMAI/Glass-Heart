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
  constexpr auto FogStart = 50.0f;                 //!< フォグが始まる距離
  constexpr auto FogEnd = 15000.0f;                //!< フォグが終了地点
  constexpr auto BackGround = "BackGround";        //!< 引数に持たせる文字列
  constexpr auto Target = "Camera";                //!< 引数に持たせる文字列
  constexpr auto StageHandle = "Stage";            //!< 引数に持たせる文字列
  constexpr std::int_fast16_t FogColorR = 247;     //!< フォグの色情報
  constexpr std::int_fast16_t FogColorG = 188;     //!< フォグの色情報
  constexpr std::int_fast16_t FogColorB = 101;     //!< フォグの色情報
  constexpr std::int_fast8_t DivNum = 8;           //!< コリジョン情報の空間分割数
  constexpr VECTOR Scale = { 1.0f, 1.0f, 1.0f };   //!< 拡大率
  constexpr VECTOR Pos = { 0.0f, 0.0f, 10.0f };    //!< 位置座標
  constexpr VECTOR Rotate = { 0.0f, 0.0f, 0.0f };  //!< 角度
}
/** コンストラクタ */
GlassHeart::Stage::Stage::Stage(Application::GameMain& game) : Object::ObjectBase{ game } {
  // スカイスフィアのモデル
  _backGround = std::make_unique<Model::ModelManager>(*this);
  _backGround->handle(BackGround);
  _backGround->SetScale(Scale);
  // ステージのモデル
  _stage = std::make_unique<Model::ModelManager>(*this);
  _stage->handle(StageHandle);
  _stage->SetPosition(Pos);
  _stage->SetRotation(Rotate);
  _stage->SetScale(Scale);
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
  MV1SetupCollInfo(_stage->GetHandle(), 2, DivNum, DivNum, DivNum);
  MV1SetupCollInfo(_stage->GetHandle(), 3, DivNum, DivNum, DivNum);
  MV1SetupCollInfo(_stage->GetHandle(), 4, DivNum, DivNum, DivNum);
  MV1SetupCollInfo(_stage->GetHandle(), 5, DivNum, DivNum, DivNum);
  MV1SetupCollInfo(_stage->GetHandle(), 6, DivNum, DivNum, DivNum);
  MV1SetupCollInfo(_stage->GetHandle(), 7, DivNum, DivNum, DivNum);
  MV1SetupCollInfo(_stage->GetHandle(), 8, DivNum, DivNum, DivNum);
  MV1SetupCollInfo(_stage->GetHandle(), 9, DivNum, DivNum, DivNum);
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