#include "GirlCreate.h"
#include "../Player/Girl.h"
#include "../Object/ObjectBase.h"
#include "../Model/ModelAnimeManager.h"
#include "../Application/GameMain.h"

/** ƒK[ƒ‹‚ğ¶¬ */
std::unique_ptr<GlassHeart::Object::ObjectBase> GlassHeart::Object::GirlCreate::Create(Application::GameMain& game) {
  // ƒK[ƒ‹‚Ì¶¬
  auto girl = std::make_unique<Player::Girl>(game);
  // ƒ‚ƒfƒ‹‚Ì“Ç‚İ‚İ‚Æ¶¬
  auto model = std::make_unique<Model::ModelAnimeManager>(*girl);
  model->handle("Girl");
  girl->SetModelManage(std::move(model));
  // ó‘Ô‚ğ“o˜^
  auto state = std::make_unique<State::StateManager>("wait", std::make_shared<Player::Girl::StateWait>(*girl));
  girl->SetStateManage(std::move(state));

  return girl;
}