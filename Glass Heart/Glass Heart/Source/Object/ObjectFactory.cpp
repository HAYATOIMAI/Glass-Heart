/*****************************************************************//**
 * @file   ObjectFactory.cpp
 * @brief  �I�u�W�F�N�g�t�@�N�g���[�N���X�̏���
 *
 * @author Hayato Imai , Yoshihiro Takahashi
 * @date   December 2021
 *********************************************************************/
#include "ObjectFactory.h"
#include "ObjectServer.h"
#include "../Application/GameMain.h"
#include "ObjectBase.h"
#include <AppFrame.h>

 /** �R���X�g���N�^ */
GlassHeart::Object::ObjectFactory::ObjectFactory(Application::GameMain& game) : _game{ game } {}
/** �N���G�C�^�[�̓o�^ */
bool GlassHeart::Object::ObjectFactory::Register(std::string_view type, std::unique_ptr<CreateBase> creator) {
  if (_creatorMap.contains(type.data())) {
    return false;
  }
  _creatorMap.emplace(type.data(), std::move(creator));
  return true;
}
/** �I�u�W�F�N�g�̐��� */
std::unique_ptr<GlassHeart::Object::ObjectBase> GlassHeart::Object::ObjectFactory::Create(std::string_view type) {
  if (!_creatorMap.contains(type.data())) {
    return nullptr;
  }
  auto&& creator = _creatorMap[type.data()];
  return creator->Create(_game);
}
/** �S�I�u�W�F�N�g���� */
void GlassHeart::Object::ObjectFactory::Clear() {
  _creatorMap.clear();
}