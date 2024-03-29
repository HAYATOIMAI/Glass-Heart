#include "GirlCreate.h"
#include "../Player/Girl.h"
#include "../Object/ObjectBase.h"
#include "../Model/ModelAnimeManager.h"
#include "../Application/GameMain.h"

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