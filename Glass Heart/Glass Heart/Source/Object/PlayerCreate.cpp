#include "PlayerCreate.h"
#include "ObjectBase.h"
#include "../Application/GameMain.h"
#include "../Model/ModelAnimeManager.h"
#include "../Player/Player.h"
#include "../State/StateIdle.h"
#include "../State/StateJump.h"
#include "../State/StateJumpUp.h"
#include "../State/StateJumpFall.h"
#include "../State/StateRun.h"
#include "../State/StateFall.h"

/** プレイヤーを生成 */
std::unique_ptr<GlassHeart::Object::ObjectBase> GlassHeart::Object::PlayerCreate::Create(Application::GameMain& game) {
  auto player = std::make_unique<Player::Player>(game);

  // モデルの読み込みと生成
  auto model = std::make_unique<Model::ModelAnimeManager>(*player);
  model->handle("Player");
  player->SetModelManage(std::move(model));

  // 状態を登録
  auto state = std::make_unique<State::StateManager>("Idle", std::make_shared<State::StateIdle>(*player));
  state->Register("Run", std::make_shared<State::StateRun>(*player));
  state->Register("Fall", std::make_shared<State::StateFall>(*player));
  state->Register("Jump", std::make_shared<State::StateJump>(*player));
  state->Register("JumpUp", std::make_shared<State::StateJumpUp>(*player));
  state->Register("JumpFall", std::make_shared<State::StateJumpFall>(*player));
  player->SetStateManage(std::move(state));

  return player;
}