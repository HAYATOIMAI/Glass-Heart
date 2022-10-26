#include "GoalPointCreate.h"
#include "../CheckPoint/GoalPoint.h"
#include "../Object/ObjectBase.h"
#include "../Model/ModelAnimeManager.h"
#include "../Application/GameMain.h"
/** ゴールポイントを生成 */
std::unique_ptr<GlassHeart::Object::ObjectBase> GlassHeart::Object::GoalPointCreate::Create(Application::GameMain& game) {
  auto goalPoint = std::make_unique<GlassHeart::CheckPoint::GoalPoint>(game);
  return goalPoint;
}