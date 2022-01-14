
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
	_test->SetScale({ 180.f,  180.f, 180.f });

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
	_skySphere->Draw();
	_ground->Draw();
	_test->Draw();
}
