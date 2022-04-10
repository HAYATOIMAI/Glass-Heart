
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
#include "../Effect/EffectManager.h"
#include "../Application/GameMain.h"
#include <AppFrame.h>

using namespace GlassHeart;

//! �R���X�g���N�^
Object::ObjectBase::ObjectBase(GameMain& game) : _game{ game } {
    _collsionManage = std::make_unique<Collision::CollisionManager>(*this);
}
//! �f�X�g���N�^
Object::ObjectBase::~ObjectBase() {}
//! ���[���h���W�ϊ�
void Object::ObjectBase::ComputeWorldTransform() {
    auto world = MGetScale(_scale);
    world = MMult(world, MGetRotZ(_rotation.z));
    world = MMult(world, MGetRotX(_rotation.x));
    world = MMult(world, MGetRotY(_rotation.y));
    _worldTransform = MMult(world, MGetTranslate(_position));
}

void Object::ObjectBase::SetStateManage(std::unique_ptr<State::StateManager> state) {
    _stateManage = std::move(state);
}

void Object::ObjectBase::SetModelManage(std::unique_ptr<Model::ModelAnimeManager> model) {
    _modelAnimeManage = std::move(model);
}

void Object::ObjectBase::SetCameraManage(std::shared_ptr<Camera::CameraManager> camera) {
    _cameraManage = std::move(camera);
}

void Object::ObjectBase::SetEffectManage(std::unique_ptr<Effect::EffectManager> effect) {
    _effectManage = std::move(effect);
}