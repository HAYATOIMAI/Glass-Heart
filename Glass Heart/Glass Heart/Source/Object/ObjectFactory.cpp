
/*****************************************************************//**
 * @file   ObjectFactory.cpp
 * @brief  オブジェクトファクトリークラスの処理
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "ObjectFactory.h"
#include "../Object/ObjectServer.h"
#include "ObjectServer.h"
#include "../Application/GameMain.h"
#include "ObjectBase.h"
#include "../State/StateManager.h"
#include "../Player/Player.h"
#include "../Camera/CameraManager.h"
#include "../Model/ModelAnimeManager.h"
#include "../State/StateIdle.h"
#include "../State/StateRun.h"
#include "../State/StateJump.h"
#include "../State/StateBase.h"
#include "../State/StateJumpFall.h"
#include "../Stage/Stage.h"
#include <AppFrame.h>

using namespace GlassHeart::Object;

//! コンストラクタ
ObjectFactory::ObjectFactory(GameMain& game) : _game{ game } {
}

//! クリエイターの登録
bool ObjectFactory::Register(std::string_view type, std::unique_ptr<CreateBase> creator) {
    if (_creatorMap.contains(type.data())) {
        return false;
    }
    _creatorMap.emplace(type.data(), std::move(creator));
    return true;
}

std::unique_ptr<ObjectBase> ObjectFactory::Create(std::string_view type) {

    if (!_creatorMap.contains(type.data())) {
        return nullptr;
    }
    auto&& creator = _creatorMap[type.data()];
    return creator->Create(_game);
}

void ObjectFactory::SetSpawnTable(SpawnTable spawnTable) {
    _spawnProgress = 0;
    _progress = 0;
    _spawnTable = spawnTable;
}

void ObjectFactory::UpdateSpawn() {
    while (_spawnTable.size() > _spawnProgress) {
        auto& spawnRecord = _spawnTable[_spawnProgress];
        if (spawnRecord._progress > _progress) {
            break;
        }
        else {

            auto&& actor = Create(spawnRecord._key);
            actor->SetPosition(spawnRecord._position);
            actor->SetRotation(spawnRecord._rosition);
            _game.GetObjectServer().Add(std::move(actor));
            ++_spawnProgress;
        }
    }
    ++_progress;
}

void ObjectFactory::Clear() {
    _creatorMap.clear();
}


std::unique_ptr<ObjectBase> PlayerCreate::Create(GameMain& game) {

    // カメラの生成
    auto camera = std::make_shared<GlassHeart::Camera::CameraManager>();
    camera->Init();
    camera->SetPosition({ 0, 50, -200 });
   // camera->SetPosition({ 180, 50, 200 });
    camera->SetTarget({ 0, 50, 0 });

    // プレイヤーの生成
    auto player = std::make_unique<GlassHeart::Player::Player>(game);
    player->SetCameraManage(camera);

    // モデルの読み込みと生成
    auto model = std::make_unique<GlassHeart::Model::ModelAnimeManager>(*player);
    model->handle("Player");
    player->SetModelManage(std::move(model));

    // 状態を登録
    auto state = std::make_unique<State::StateManager>("Idle", std::make_shared<State::StateIdle>(*player));
    state->Register("Run", std::make_shared<State::StateRun>(*player));
    state->Register("Jump", std::make_shared<State::StateJump>(*player));
    //state->Register("JumpFall", std::make_shared<State::JumpFall>(*player));
    player->SetStateManage(std::move(state));

    return player;
}

std::unique_ptr<ObjectBase> TestCreate::Create(GameMain& game) {

    return std::unique_ptr<ObjectBase>();
}

std::unique_ptr<ObjectBase> StageCreate::Create(GameMain& game) {
    auto stage = std::make_unique<Stage::Stage>(game);
    return stage;
}