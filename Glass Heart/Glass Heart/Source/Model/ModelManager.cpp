
/*****************************************************************//**
 * @file   ModelManager.cpp
 * @brief  ���f���}�l�[�W���[�N���X�̏���
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "ModelManager.h"
#include "AppFrame.h"
#include "../Object/ObjectBase.h"
#include "../Application/GameMain.h"

using namespace GlassHeart;
/** �R���X�g���N�^ */
Model::ModelManager::ModelManager(Object::ObjectBase& owner) : _owner{ owner } {}
/** �f�X�g���N�^ */
Model::ModelManager::~ModelManager() {}
/** ������ */
void  Model::ModelManager::Init() {}
/** �X�V���� */
void  Model::ModelManager::Update() {
    // ���[���h�s��X�V
    MV1SetMatrix(_handle, _owner.GetWorldTransform());
}
/** �`�揈�� */
void Model::ModelManager::Draw() {
    SetUseLighting(_isLighting);
    MV1DrawModel(_handle);
}
/** ���f���̎擾 */
int  Model::ModelManager::handle(std::string_view key, int no) {
    auto&& [handle, actualNo] = _owner.GetGame().GetResourceServer().GetModles(key, no);
    _handle = handle;
    _key = key;
    return 0;
}
/** ���f���̐ݒ� */
int  Model::ModelManager::SetModel(std::string_view key, int no) {
    auto [handle, actualNo] = _owner.GetGame().GetResourceServer().GetModles(key, no);
    _handle = handle;
    return actualNo;
}
/** ���W�̐ݒ� */
void  Model::ModelManager::SetPosition(VECTOR position) {
    MV1SetPosition(_handle, position);
}
/** ��]�p�x�̐ݒ� */
void  Model::ModelManager::SetRotation(VECTOR rotation) {
    MV1SetRotationXYZ(_handle, rotation);
}
/** �g�嗦�̐ݒ� */
void  Model::ModelManager::SetScale(VECTOR scale) {
    MV1SetScale(_handle, scale);
}
/** ���[���h�s��̐ݒ� */
void  Model::ModelManager::SetMatrix(MATRIX& world) {
    MV1SetMatrix(_handle, world);
}
/** �F��ݒ� */
void  Model::ModelManager::SetColor(int index, float r, float g, float b) {
    MV1SetMaterialEmiColor(_handle, index, GetColorF(r, g, b, 0.f));
}