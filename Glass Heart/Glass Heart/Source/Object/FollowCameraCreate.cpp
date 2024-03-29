#include "FollowCameraCreate.h"
#include "../Camera/FollowCamera.h"
#include "../Camera/CameraManager.h"
#include "../Object/ObjectBase.h"
#include "../Model/ModelAnimeManager.h"
#include "../Application/GameMain.h"
#include <DxLib.h>

namespace {
  constexpr VECTOR CameraPosition = { 0.0f, 50.0f, -200.0f };
  constexpr VECTOR Target = { 0.0f, 50.0f, 0.0f };
  constexpr auto ForwardSpeed = 5.0f;
}
/** カメラを生成 */
std::unique_ptr<GlassHeart::Object::ObjectBase> GlassHeart::Object::FollowCameraCreate::Create(Application::GameMain& game) {
  // カメラの生成
  auto camera = std::make_shared<GlassHeart::Camera::CameraManager>();
  camera->Init();
  camera->SetPosition(CameraPosition);
  camera->SetTarget(Target);

  auto followCamera = std::make_unique<GlassHeart::Camera::FollowCamera>(game);
  followCamera->SetCameraManage(camera);
  followCamera->SetForwardSpeed(ForwardSpeed);

  return followCamera;
}