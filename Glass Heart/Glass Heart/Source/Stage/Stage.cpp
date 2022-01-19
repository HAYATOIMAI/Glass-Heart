
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

using namespace GlassHeart::Stage;

Stage::Stage(GameMain& game) : ObjectBase{game} {
	// スカイスフィアのモデル
	_skySphere = std::make_unique<Model::ModelManager>(*this);
	_skySphere->handle("SkySphere");
	_skySphere->SetScale({ 80.f,  80.f, 80.f });
	// 地面のモデル
	_ground = std::make_unique<Model::ModelManager>(*this);
	_ground->handle("Terrain");
	_ground->SetScale({ 30.f, 10.f, 30.f });

	_test = std::make_unique<Model::ModelManager>(*this);
	_test->handle("Test");
	_test->SetRotation(VGet(0.0f,180.0f * std::numbers::pi_v<float> / 180.0f, 0.0f));
	_test->SetScale({ 500.f,  80.f, 80.f });

	// ナビメッシュを非表示
	MV1SetFrameVisible(_ground->GetHandle(), 3, FALSE);
	// フレーム1をナビメッシュとして使用
	MV1SetupCollInfo(_ground->GetHandle(), 1, 10, 10, 10);

	// フォグの設定
	SetFogEnable(TRUE);
	SetFogColor(247, 188, 101);
	SetFogStartEnd(50.0f, 15000.0f);
}

void Stage::Process() {
	// スカイスフィアをプレイヤと同じ位置にする
	_skySphere->SetPosition(GetObjectServer().GetPosition("Player"));
}

void Stage::Render() {
	//_skySphere->Draw();
	//_ground->Draw();
	_test->Draw();
#ifdef _DEBUG
	float linelength = 10000.f;
	VECTOR v = { 0, 0, 0 };
	DrawLine3D(VAdd(v, VGet(-linelength, 0, 0)), VAdd(v, VGet(linelength, 0, 0)), GetColor(255, 0, 0));
	DrawLine3D(VAdd(v, VGet(0, -linelength, 0)), VAdd(v, VGet(0, linelength, 0)), GetColor(0, 255, 0));
	DrawLine3D(VAdd(v, VGet(0, 0, -linelength)), VAdd(v, VGet(0, 0, linelength)), GetColor(255, 255, 255));
#endif // DEBUG
}
