
/*****************************************************************//**
 * @file   ObjectServer.cpp
 * @brief  �I�u�W�F�N�g�T�[�o�[�̏���
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "ObjectServer.h"
#include "ObjectBase.h"

using namespace GlassHeart::Object;

// !�I�u�W�F�N�g�̒ǉ�
void ObjectServer::Add(std::unique_ptr<ObjectBase> obj) {
    if (_updating) {
        // �X�V����_pendingObjects�ɒǉ�����
        _pendingObjects.emplace_back(std::move(obj));
    }
    else {
        _objects.emplace_back(std::move(obj));
    }
}
//! ���͏���
void ObjectServer::Input(AppFrame::InputManager& input) {
    _updating = true;
    for (auto&& obj : _objects) {
        if (obj->IsActive()) {
            //! �I�u�W�F�N�g�ɓ��͂���
            obj->Input(input);
        }
    }
    _updating = false;
}
//! �X�V����
void ObjectServer::Process() {
    for (auto&& obj : _objects) {
        if (obj->IsActive()) {
            //! �I�u�W�F�N�g���X�V����
            obj->Process();
        }
    }
    _updating = false;

    //! �ۗ����̃I�u�W�F�N�g��_objects�Ɉړ�����
    _objects.insert(_objects.end(),
        make_move_iterator(_pendingObjects.begin()),
        make_move_iterator(_pendingObjects.end()));

    //! �ۗ����X�g���폜
    _pendingObjects.clear();

    //! ���S�����I�u�W�F�N�g���폜
    erase_if(_objects, [](auto&& obj) { return obj->IsDead(); });
}
//! �`�揈��
void ObjectServer::Render() {
    for (auto&& obj : _objects) {
        if (obj->IsActive()) {
            //! �I�u�W�F�N�g��`�悷��
            obj->Render();
        }
    }
}
//! �S�I�u�W�F�N�g���폜
void ObjectServer::AllClear() {
    _objects.clear();
    _pendingObjects.clear();
}
//! �I�u�W�F�N�g��o�^
void ObjectServer::Register(std::string_view key, VECTOR vec) {
    if (_registry.contains(key.data())) {
        _registry[key.data()] = vec;
    }
    _registry.emplace(key, vec);
}
/** �I�u�W�F�N�g�̈ʒu���擾 */
VECTOR ObjectServer::GetPosition(std::string_view key) {
    if (_registry.contains(key.data())) {
        return _registry[key.data()];
    }
    // ���o�^
    return { 0, 0, 0 };
}

VECTOR ObjectServer::GetForward(std::string_view key) {
    if (_registry.contains(key.data())) {
        return _registry[key.data()];
    }
    // ���o�^
    return { 0, 0, 0 };
}
