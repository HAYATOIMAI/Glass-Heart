#include "StageCreate.h"
#include "../Stage/Stage.h"
#include "../Object/ObjectBase.h"
#include "../Model/ModelAnimeManager.h"
#include "../Application/GameMain.h"

/** ステージを生成 */
std::unique_ptr<GlassHeart::Object::ObjectBase> GlassHeart::Object::StageCreate::Create(Application::GameMain& game) {
  auto stage = std::make_unique<Stage::Stage>(game);
  return stage;
}