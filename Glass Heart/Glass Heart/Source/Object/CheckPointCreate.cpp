#include "CheckPointCreate.h"
#include "../CheckPoint/CheckPoint.h"
#include "../Object/ObjectBase.h"
#include "../Model/ModelAnimeManager.h"
#include "../Application/GameMain.h"
/** �`�F�b�N�|�C���g�𐶐� */
std::unique_ptr<GlassHeart::Object::ObjectBase> GlassHeart::Object::CheckPointCreate::Create(Application::GameMain& game) {
  auto checkPoint = std::make_unique<CheckPoint::CheckPoint>(game);
  return checkPoint;
}