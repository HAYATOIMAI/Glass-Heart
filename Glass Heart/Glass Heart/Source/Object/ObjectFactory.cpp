/*****************************************************************//**
 * @file   ObjectFactory.cpp
 * @brief  オブジェクトファクトリークラスの処理
 *
 * @author Hayato Imai , Yoshihiro Takahashi
 * @date   December 2021
 *********************************************************************/
#include "ObjectFactory.h"
#include "ObjectServer.h"
#include "../Application/GameMain.h"
#include "ObjectBase.h"
#include "../State/StateManager.h"
#include "../Player/Player.h"
#include "../Player/Girl.h"
#include "../Camera/CameraManager.h"
#include "../Model/ModelAnimeManager.h"
#include "../State/StateIdle.h"
#include "../State/StateRun.h"
#include "../State/StateJump.h"
#include "../State/StateBase.h"
#include "../State/StateJumpUp.h"
#include "../State/StateJumpFall.h"
#include "../State/StateFall.h"
#include "../Stage/Stage.h"
#include "../CheckPoint/CheckPoint.h"
#include "../CheckPoint/GoalPoint.h"
#include "../Camera/FollowCamera.h"
#include <AppFrame.h>

 /** コンストラクタ */
GlassHeart::Object::ObjectFactory::ObjectFactory(Application::GameMain& game) : _game{ game } {}
/** クリエイターの登録 */
bool GlassHeart::Object::ObjectFactory::Register(std::string_view type, std::unique_ptr<CreateBase> creator) {
	if (_creatorMap.contains(type.data())) {
		return false;
	}
	_creatorMap.emplace(type.data(), std::move(creator));
	return true;
}
/** オブジェクトの生成 */
std::unique_ptr<GlassHeart::Object::ObjectBase> GlassHeart::Object::ObjectFactory::Create(std::string_view type) {
	if (!_creatorMap.contains(type.data())) {
		return nullptr;
	}
	auto&& creator = _creatorMap[type.data()];
	return creator->Create(_game);
}
/** 全オブジェクト消去 */
void GlassHeart::Object::ObjectFactory::Clear() {
	_creatorMap.clear();
}
/** プレイヤーを生成 */
std::unique_ptr<GlassHeart::Object::ObjectBase> GlassHeart::Object::PlayerCreate::Create(Application::GameMain& game) {
	auto player = std::make_unique<Player::Player>(game);

	// モデルの読み込みと生成
	auto model = std::make_unique<Model::ModelAnimeManager>(*player);
	model->handle("Player");
	player->SetModelManage(std::move(model));

	// 状態を登録
	auto state = std::make_unique<GlassHeart::State::StateManager>("Idle", std::make_shared<GlassHeart::State::StateIdle>(*player));
	state->Register("Run", std::make_shared<GlassHeart::State::StateRun>(*player));
	state->Register("Fall", std::make_shared<GlassHeart::State::StateFall>(*player));
	state->Register("Jump", std::make_shared<GlassHeart::State::StateJump>(*player));
	state->Register("JumpUp", std::make_shared<GlassHeart::State::StateJumpUp>(*player));
	state->Register("JumpFall", std::make_shared<GlassHeart::State::StateJumpFall>(*player));
	player->SetStateManage(std::move(state));

	return player;
}
/** ガールを生成 */
std::unique_ptr<GlassHeart::Object::ObjectBase> GlassHeart::Object::GirlCreate::Create(Application::GameMain& game) {
	// ガールの生成
	auto girl = std::make_unique<Player::Girl>(game);
	// モデルの読み込みと生成
	auto model = std::make_unique<Model::ModelAnimeManager>(*girl);
	model->handle("Girl");
	girl->SetModelManage(std::move(model));
	// 状態を登録
	auto state = std::make_unique<State::StateManager>("wait", std::make_shared<Player::Girl::StateWait>(*girl));
	girl->SetStateManage(std::move(state));

	return girl;
}
/** ステージを生成 */
std::unique_ptr<GlassHeart::Object::ObjectBase> GlassHeart::Object::StageCreate::Create(Application::GameMain& game) {
	auto stage = std::make_unique<Stage::Stage>(game);
	return stage;
}
/** カメラを生成 */
std::unique_ptr<GlassHeart::Object::ObjectBase> GlassHeart::Object::FollowCameraCreate::Create(Application::GameMain& game) {
	// カメラの生成
	auto camera = std::make_shared<GlassHeart::Camera::CameraManager>();
	camera->Init();
	camera->SetPosition({ 0, 50, -200 });
	camera->SetTarget({ 0, 50, 0 });

	auto followCamera = std::make_unique<GlassHeart::Camera::FollowCamera>(game);
	followCamera->SetCameraManage(camera);
	followCamera->SetForwardSpeed(5.0f);

	return followCamera;
}
/** ゴールポイントを生成 */
std::unique_ptr<GlassHeart::Object::ObjectBase> GlassHeart::Object::GoalPointCreate::Create(Application::GameMain& game) {
	auto goalPoint = std::make_unique<GlassHeart::CheckPoint::GoalPoint>(game);
	return goalPoint;
}
/** チェックポイントを生成 */
std::unique_ptr<GlassHeart::Object::ObjectBase> GlassHeart::Object::CheckPointCreate::Create(Application::GameMain& game) {
	auto checkPoint = std::make_unique<CheckPoint::CheckPoint>(game);
	return checkPoint;
}