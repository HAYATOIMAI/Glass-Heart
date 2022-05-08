/*****************************************************************//**
 * @file   ObjectBase.cpp
 * @brief  �I�u�W�F�N�g�̊��N���X�̏���
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "ObjectBase.h"
#include "ObjectServer.h"
#include "ObjectFactory.h"
#include "../Model/ModelAnimeManager.h"
#include "../Collision/CollisionManager.h"
#include "../Camera/CameraManager.h"
#include "../State/StateManager.h"
#include "../Application/GameMain.h"
#include <AppFrame.h>

/** �R���X�g���N�^ */
GlassHeart::Object::ObjectBase::ObjectBase(Application::GameMain& game) : _game{ game } {
    _collsionManage = std::make_unique<Collision::CollisionManager>(*this);
}
/** �f�X�g���N�^ */
GlassHeart::Object::ObjectBase::~ObjectBase() {}
/** ���[���h���W�ϊ� */
void GlassHeart::Object::ObjectBase::ComputeWorldTransform() {
    auto world = MGetScale(_scale);
    world = MMult(world, MGetRotZ(_rotation.z));
    world = MMult(world, MGetRotX(_rotation.x));
    world = MMult(world, MGetRotY(_rotation.y));
    _worldTransform = MMult(world, MGetTranslate(_position));
}

void GlassHeart::Object::ObjectBase::SetStateManage(std::unique_ptr<GlassHeart::State::StateManager> state) {
    _stateManage = std::move(state);
}

void GlassHeart::Object::ObjectBase::SetModelManage(std::unique_ptr<GlassHeart::Model::ModelAnimeManager> model) {
    _modelAnimeManage = std::move(model);
}

void GlassHeart::Object::ObjectBase::SetCameraManage(std::shared_ptr<GlassHeart::Camera::CameraManager> camera) {
    _cameraManage = std::move(camera);
}

GlassHeart::Object::ObjectServer& GlassHeart::Object::ObjectBase::GetObjectServer() {
    return _game.GetObjectServer();
}